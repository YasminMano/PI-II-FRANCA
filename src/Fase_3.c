#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h> // Para geração de números aleatórios
#include "headers/game.h"

// Estrutura para armazenar informações sobre cada pergunta
typedef struct {
    ALLEGRO_BITMAP* imagem_pergunta;
    char alternativas[3][128];
    int resposta_certa;
} Pergunta;

// Função para embaralhar as alternativas de uma pergunta
void embaralhar_alternativas(Pergunta* pergunta) {
    int indices[] = {0, 1, 2};
    char alternativas_temp[3][128];
    int resposta_certa_original = pergunta->resposta_certa;

    for (int i = 0; i < 3; i++) {
        strcpy_s(alternativas_temp[i], sizeof(alternativas_temp[i]), pergunta->alternativas[i]);
        alternativas_temp[i][sizeof(alternativas_temp[i]) - 1] = '\0'; // Garantir que termina em '\0'
    }


    for (int i = 2; i > 0; i--) {
        int j = rand() % (i + 1);
        int temp = indices[i];
        indices[i] = indices[j];
        indices[j] = temp;
    }

    for (int i = 0; i < 3; i++) {
        strcpy_s(pergunta->alternativas[i], sizeof(pergunta->alternativas[i]), alternativas_temp[indices[i]]);
        pergunta->alternativas[i][sizeof(pergunta->alternativas[i]) - 1] = '\0'; // Garantir que termina em '\0'

        if (indices[i] == resposta_certa_original) {
            pergunta->resposta_certa = i;
        }
    }
}

// Função para exibir a tela de fim
void exibir_tela_fim(ALLEGRO_DISPLAY* display, const char* caminho_imagem) {
    ALLEGRO_BITMAP* imagem_fim = al_load_bitmap(caminho_imagem);
    if (!imagem_fim) {
        printf("Erro ao carregar a imagem de fim de jogo: %s\n", caminho_imagem);
        return;
    }

    int tela_largura = al_get_display_width(display);
    int tela_altura = al_get_display_height(display);

    al_clear_to_color(al_map_rgb(0, 0, 0));
    al_draw_scaled_bitmap(imagem_fim, 0, 0, 1024, 1024,
                          0, 0, tela_largura, tela_altura, 0);
    al_flip_display();
    al_rest(3.0);
    al_destroy_bitmap(imagem_fim);
}

// Função para iniciar a fase 3 com vida e erro
void iniciar_fase_3(ALLEGRO_DISPLAY* display, GameState* game_state) {
    // Inicializações
    if (!al_init_image_addon()) {
        printf("Falha ao inicializar o addon de imagens.\n");
        return;
    }

    srand(time(NULL));

    bool running = true;
    ALLEGRO_EVENT_QUEUE* event_queue = al_create_event_queue();
    ALLEGRO_TIMER* timer = al_create_timer(1.0 / 60.0);

    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_timer_event_source(timer));
    al_register_event_source(event_queue, al_get_mouse_event_source());
    al_start_timer(timer);

    ALLEGRO_FONT* font = al_create_builtin_font();
    ALLEGRO_COLOR white = al_map_rgb(255, 255, 255);
    ALLEGRO_COLOR button_color = al_map_rgb(100, 100, 100);

    ALLEGRO_BITMAP* cenario = al_load_bitmap("assets/images/cenario3.png");
    ALLEGRO_BITMAP* personagens = al_load_bitmap("assets/images/personagens_3tela.png");
    ALLEGRO_BITMAP* rei = al_load_bitmap("assets/images/Luis_XIV.png");
    ALLEGRO_BITMAP* botao_pause = al_load_bitmap("assets/images/botao_pause.png");

    // Carregar as imagens de vida
    ALLEGRO_BITMAP* vida_3 = al_load_bitmap("assets/images/vida_3.png");
    ALLEGRO_BITMAP* vida_2 = al_load_bitmap("assets/images/vida_2.png");
    ALLEGRO_BITMAP* vida_1 = al_load_bitmap("assets/images/vida_1.png");

    if (!cenario || !personagens || !rei || !botao_pause || !vida_3 || !vida_2 || !vida_1) {
        printf("Erro ao carregar recursos.\n");
        return;
    }

    // Reduzir o tamanho do botão de pausa
    float botao_pause_scale = 0.15;
    int pause_width = al_get_bitmap_width(botao_pause) * botao_pause_scale;
    int pause_height = al_get_bitmap_height(botao_pause) * botao_pause_scale;

    // Posicionar no canto superior direito
    int pause_x = al_get_display_width(display) - pause_width - 10; // 10px de margem
    int pause_y = 10; // 10px de margem superior

    Pergunta perguntas[5] = {
        {al_load_bitmap("assets/images/question1.png"), {"Foi a Guerra dos Cem Anos, que ainda nos afeta!", "Foi a sua corte luxuosa e os impostos esmagadores!", "Foi a Revolução Industrial que desestabilizou tudo!"}, 1},
        {al_load_bitmap("assets/images/question2.png"), {"Liberdade, Igualdade e Fraternidade!", "Paz, Pão e Terra!", "Ordem e Progresso!"}, 0},
        {al_load_bitmap("assets/images/question3.png"), {"Os comerciantes que enriqueceram às nossas custas!", "Os filósofos que só sabem falar e nunca agir!", "Foi a monarquia que nos explorou!"}, 2},
        {al_load_bitmap("assets/images/question4.png"), {"Jean-Jacques Rousseau, o filósofo rebelde!", "Foi Maximilien Robespierre, o verdadeiro líder!", "Foi Napoleão, claro!"}, 1},
        {al_load_bitmap("assets/images/question5.png"), {"Constituição de 1791!", "Declaração Universal!", "A Declaração dos Direitos do Homem e do Cidadão!"}, 2}
    };

    for (int i = 0; i < 5; i++) {
        if (!perguntas[i].imagem_pergunta) {
            printf("Erro ao carregar a imagem da pergunta %d.\n", i + 1);
            running = false;
        }
        embaralhar_alternativas(&perguntas[i]);
    }

    if (!running) {
        printf("Abortando a fase devido a erros no carregamento dos recursos.\n");
        return;
    }

    int botao_x = 350;
    int botao_y[3] = {440, 510, 580};
    int largura = 420;
    int altura = 50;

    int indice_pergunta = 0;
    int erros = 0;

    while (running) {
        ALLEGRO_EVENT event;
        al_wait_for_event(event_queue, &event);

        if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
            running = false;
        }

        if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
            int mouse_x = event.mouse.x;
            int mouse_y = event.mouse.y;

            if (mouse_x >= pause_x && mouse_x <= pause_x + pause_width &&
                mouse_y >= pause_y && mouse_y <= pause_y + pause_height) {
                printf("Botão de pausa clicado. Voltando ao mapa.\n");
                running = false;
                *game_state = PAUSE_MENU; // Corrigido para atualizar o estado corretamente
            }

            for (int i = 0; i < 3; i++) {
                if (mouse_x >= botao_x && mouse_x <= botao_x + largura &&
                    mouse_y >= botao_y[i] && mouse_y <= botao_y[i] + altura) {
                    if (i == perguntas[indice_pergunta].resposta_certa) {
                        indice_pergunta++;
                        if (indice_pergunta >= 5) {
                            exibir_tela_fim(display, "assets/images/end_game.png");
                            running = false;
                            *game_state = MAPA; // Corrigido para retornar ao mapa após a vitória
                        }
                    } else {
                        erros++;
                        if (erros > 2) {
                            exibir_tela_fim(display, "assets/images/death.png");
                            running = false;
                            *game_state = MAPA; // Corrigido para retornar ao mapa após a derrota
                        }
                    }
                }
            }
        }

        // Seleciona a imagem de vida com base no número de erros
        ALLEGRO_BITMAP* imagem_vida = vida_3;
        if (erros == 1) {
            imagem_vida = vida_2;
        } else if (erros == 2) {
            imagem_vida = vida_1;
        }

        al_clear_to_color(al_map_rgb(0, 0, 0));

        // Desenhar o cenário e outros elementos
        al_draw_scaled_bitmap(cenario, 0, 0, al_get_bitmap_width(cenario), al_get_bitmap_height(cenario),
                              0, 0, al_get_display_width(display), al_get_display_height(display), 0);

        al_draw_bitmap(personagens, 50, 350, 0);
        al_draw_bitmap(rei, 700, 350, 0);

        al_draw_bitmap(perguntas[indice_pergunta].imagem_pergunta, 450, -110, 0);

        // Reduzir o tamanho das imagens de vida
        float vida_scale = 0.35; // Escala reduzida das imagens de vida
        int vida_width = al_get_bitmap_width(imagem_vida) * vida_scale;
        int vida_height = al_get_bitmap_height(imagem_vida) * vida_scale;

        int vida_x = 10; // Posição à esquerda
        int vida_y = pause_y; // Alinhado com o botão de pausa
  

        al_draw_scaled_bitmap(imagem_vida, 0, 0, al_get_bitmap_width(imagem_vida), al_get_bitmap_height(imagem_vida),
                              vida_x, vida_y, vida_width, vida_height, 0);

        // Desenhar o botão de pausa
        al_draw_scaled_bitmap(botao_pause, 0, 0, al_get_bitmap_width(botao_pause), al_get_bitmap_height(botao_pause),
                              pause_x, pause_y, pause_width, pause_height, 0);

        for (int i = 0; i < 3; i++) {
            al_draw_filled_rectangle(botao_x, botao_y[i], botao_x + largura, botao_y[i] + altura, button_color);
            al_draw_text(font, white, botao_x + largura / 2, botao_y[i] + 15, ALLEGRO_ALIGN_CENTER,
                         perguntas[indice_pergunta].alternativas[i]);
        }

        al_flip_display();
    }

    al_destroy_bitmap(cenario);
    al_destroy_bitmap(personagens);
    al_destroy_bitmap(rei);
    al_destroy_bitmap(botao_pause);
    al_destroy_bitmap(vida_3);
    al_destroy_bitmap(vida_2);
    al_destroy_bitmap(vida_1);
    for (int i = 0; i < 5; i++) {
        al_destroy_bitmap(perguntas[i].imagem_pergunta);
    }
    al_destroy_font(font);
    al_destroy_timer(timer);
    al_destroy_event_queue(event_queue);
}


