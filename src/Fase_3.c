#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h> // Para geração de números aleatórios
#include "headers/game.h"
#include "headers/mapa.h"

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
    }

    for (int i = 2; i > 0; i--) {
        int j = rand() % (i + 1);
        int temp = indices[i];
        indices[i] = indices[j];
        indices[j] = temp;
    }

    for (int i = 0; i < 3; i++) {
        strcpy_s(pergunta->alternativas[i], sizeof(pergunta->alternativas[i]), alternativas_temp[indices[i]]);
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

// Função para iniciar a fase 3
void iniciar_fase_3(ALLEGRO_DISPLAY* display, GameState* game_state) {
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

    if (!cenario || !personagens || !rei || !botao_pause) {
        printf("Erro ao carregar o cenário, personagens ou botão de pausa.\n");
        return;
    }

    int pause_x = al_get_display_width(display) / 2 - al_get_bitmap_width(botao_pause) / 2;
    int pause_y = al_get_display_height(display) / 2 - al_get_bitmap_height(botao_pause) / 2;

    Pergunta perguntas[5] = {
        {al_load_bitmap("assets/images/question1.png"), {"Foi a Guerra dos Cem Anos!", "Foi a corte luxuosa!", "Foi a Revolução Industrial!"}, 1},
        {al_load_bitmap("assets/images/question2.png"), {"Liberdade, Igualdade e Fraternidade!", "Paz, Pão e Terra!", "Ordem e Progresso!"}, 0},
        {al_load_bitmap("assets/images/question3.png"), {"Comerciantes ricos!", "Filósofos inativos!", "A monarquia!"}, 2},
        {al_load_bitmap("assets/images/question4.png"), {"Rousseau!", "Robespierre!", "Napoleão!"}, 1},
        {al_load_bitmap("assets/images/question5.png"), {"Constituição de 1791!", "Declaração Universal!", "Declaração dos Direitos do Homem!"}, 2}
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

            if (mouse_x >= pause_x && mouse_x <= pause_x + al_get_bitmap_width(botao_pause) &&
                mouse_y >= pause_y && mouse_y <= pause_y + al_get_bitmap_height(botao_pause)) {
                printf("Botão de pausa clicado. Voltando ao mapa.\n");
                running = false;
                *game_state = MAPA; // Corrigido para atualizar o estado corretamente
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

        al_clear_to_color(al_map_rgb(0, 0, 0));

        al_draw_scaled_bitmap(cenario, 0, 0, al_get_bitmap_width(cenario), al_get_bitmap_height(cenario),
                              0, 0, al_get_display_width(display), al_get_display_height(display), 0);

        al_draw_bitmap(personagens, 50, 350, 0);
        al_draw_bitmap(rei, 700, 350, 0);

        al_draw_bitmap(perguntas[indice_pergunta].imagem_pergunta, 450, -110, 0);

        al_draw_bitmap(botao_pause, pause_x, pause_y, 0);

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
    for (int i = 0; i < 5; i++) {
        al_destroy_bitmap(perguntas[i].imagem_pergunta);
    }
    al_destroy_font(font);
    al_destroy_timer(timer);
    al_destroy_event_queue(event_queue);
}
