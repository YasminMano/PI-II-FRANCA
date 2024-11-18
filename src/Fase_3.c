#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h> // Para geração de números aleatórios

// Estrutura para armazenar informações sobre cada pergunta
typedef struct {
    ALLEGRO_BITMAP* imagem_pergunta; // Imagem da pergunta
    char alternativas[3][128];      // Alternativas de resposta
    int resposta_certa;             // Índice da resposta correta
} Pergunta;

// Função para embaralhar as alternativas de uma pergunta
void embaralhar_alternativas(Pergunta* pergunta) {
    int indices[] = {0, 1, 2};
    char alternativas_temp[3][128];
    int resposta_certa_original = pergunta->resposta_certa;

    // Copiar as alternativas para um array temporário
    for (int i = 0; i < 3; i++) {
        strcpy(alternativas_temp[i], pergunta->alternativas[i]);
    }

    // Embaralhar os índices
    for (int i = 2; i > 0; i--) {
        int j = rand() % (i + 1);
        int temp = indices[i];
        indices[i] = indices[j];
        indices[j] = temp;
    }

    // Reorganizar as alternativas com base nos índices embaralhados
    for (int i = 0; i < 3; i++) {
        strcpy(pergunta->alternativas[i], alternativas_temp[indices[i]]);
        if (indices[i] == resposta_certa_original) {
            pergunta->resposta_certa = i;
        }
    }
}

// Função para exibir a tela de fim (vitória ou derrota) com ajuste automático de proporções
void exibir_tela_fim(ALLEGRO_DISPLAY* display, const char* caminho_imagem) {
    ALLEGRO_BITMAP* imagem_fim = al_load_bitmap(caminho_imagem);
    if (!imagem_fim) {
        printf("Erro ao carregar a imagem de fim de jogo: %s\n", caminho_imagem);
        return;
    }

    int tela_largura = al_get_display_width(display);
    int tela_altura = al_get_display_height(display);

    al_clear_to_color(al_map_rgb(0, 0, 0)); // Limpa a tela antes de desenhar
    al_draw_scaled_bitmap(imagem_fim, 0, 0, 1024, 1024, // Dimensões originais da imagem
                          0, 0, tela_largura, tela_altura, // Ajuste para preencher a tela
                          0); // Sem flips
    al_flip_display();
    al_rest(3.0); // Aguarda 3 segundos para exibir a tela
    al_destroy_bitmap(imagem_fim);
}

// Função para iniciar a fase 3
void iniciar_fase_3(ALLEGRO_DISPLAY* display) {
    if (!al_init_image_addon()) { // Inicializa o addon de imagens
        printf("Falha ao inicializar o addon de imagens.\n");
        return;
    }

    srand(time(NULL)); // Inicializa o gerador de números aleatórios

    bool running = true;
    ALLEGRO_EVENT_QUEUE* event_queue = al_create_event_queue();
    ALLEGRO_TIMER* timer = al_create_timer(1.0 / 60.0); // Temporizador para 60 FPS

    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_timer_event_source(timer));
    al_register_event_source(event_queue, al_get_mouse_event_source());
    al_start_timer(timer);

    // Configuração de botões e fontes
    ALLEGRO_FONT* font = al_create_builtin_font();
    ALLEGRO_COLOR white = al_map_rgb(255, 255, 255);
    ALLEGRO_COLOR button_color = al_map_rgb(100, 100, 100);

    // Carregar o cenário e os personagens
    ALLEGRO_BITMAP* cenario = al_load_bitmap("assets/images/cenario3.png");
    ALLEGRO_BITMAP* personagens = al_load_bitmap("assets/images/personagens_3tela.png");
    ALLEGRO_BITMAP* rei = al_load_bitmap("assets/images/Luis_XIV.png");

    // Verifica se os recursos foram carregados corretamente
    if (!cenario || !personagens || !rei) {
        printf("Erro ao carregar o cenário ou personagens. Verifique os arquivos.\n");
        return;
    }

    // Carregar as imagens das perguntas e definir alternativas
    Pergunta perguntas[5] = {
        {al_load_bitmap("assets/images/question1.png"), {"Foi a Guerra dos Cem Anos, que ainda nos afeta!", "Foi a sua corte luxuosa e os impostos esmagadores!", "Foi a Revolução Industrial que desestabilizou tudo!"}, 1},
        {al_load_bitmap("assets/images/question2.png"), {"Liberdade, Igualdade e Fraternidade!", "Paz, Pão e Terra!", "Ordem e Progresso!"}, 0},
        {al_load_bitmap("assets/images/question3.png"), {"Os comerciantes que enriqueceram às nossas custas!", "Os filósofos que só sabem falar e nunca agir!", "Foi a monarquia que nos explorou!"}, 2},
        {al_load_bitmap("assets/images/question4.png"), {"Jean-Jacques Rousseau, o filósofo rebelde!", "Foi Maximilien Robespierre, o verdadeiro líder!", "Foi Napoleão, claro!"}, 1},
        {al_load_bitmap("assets/images/question5.png"), {"A Constituição de 1791!", "A Declaração Universal dos Direitos Humanos!", "A Declaração dos Direitos do Homem e do Cidadão!"}, 2}
    };

    // Verifica se as imagens das perguntas foram carregadas
    for (int i = 0; i < 5; i++) {
        if (!perguntas[i].imagem_pergunta) {
            printf("Erro ao carregar a imagem da pergunta %d. Verifique o arquivo.\n", i + 1);
            running = false;
        }
        embaralhar_alternativas(&perguntas[i]); // Embaralha as alternativas de cada pergunta
    }

    if (!running) {
        printf("Abortando a fase devido a erros no carregamento dos recursos.\n");
        return;
    }

    // Coordenadas dos botões
    int botao_x = 350;                // NOVA POSIÇÃO X DOS BOTÕES (alterada para mais à direita)
    int botao_y[3] = {440, 510, 580}; // NOVAS POSIÇÕES Y DOS BOTÕES (alteradas para mais abaixo)
    int largura = 420;               // Largura dos botões
    int altura = 50;                 // Altura dos botões

    int indice_pergunta = 0; // Controle da pergunta atual
    int erros = 0;           // Contador de erros

    while (running) {
        ALLEGRO_EVENT event;
        al_wait_for_event(event_queue, &event);

        // Fecha a janela se o usuário clicar no botão de fechar
        if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
            running = false;
        }

        // Verifica se o usuário clicou em um botão
        if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
            int mouse_x = event.mouse.x;
            int mouse_y = event.mouse.y;

            for (int i = 0; i < 3; i++) {
                if (mouse_x >= botao_x && mouse_x <= botao_x + largura &&
                    mouse_y >= botao_y[i] && mouse_y <= botao_y[i] + altura) {
                    if (i == perguntas[indice_pergunta].resposta_certa) {
                        indice_pergunta++;
                        if (indice_pergunta >= 5) {
                            exibir_tela_fim(display, "assets/images/end_game.png"); // Tela de vitória
                            running = false;
                        }
                    } else {
                        erros++;
                        printf("Erros: %d\n", erros); // Mostra no console o contador de erros
                        if (erros > 2) {
                            exibir_tela_fim(display, "assets/images/death.png"); // Tela de derrota
                            running = false;
                        }
                    }
                }
            }
        }

        // Limpa a tela e desenha os elementos
        al_clear_to_color(al_map_rgb(0, 0, 0));

        // Ajusta cenário para preencher a tela
        al_draw_scaled_bitmap(cenario, 0, 0, al_get_bitmap_width(cenario), al_get_bitmap_height(cenario), 
                              0, 0, al_get_display_width(display), al_get_display_height(display), 0);

        // Desenha os personagens
        al_draw_bitmap(personagens, 50, 350, 0); // Invasores à esquerda
        al_draw_bitmap(rei, 700, 350, 0);        // Rei à direita

        // Desenha a imagem da pergunta atual (sem redimensionamento)
        al_draw_bitmap(perguntas[indice_pergunta].imagem_pergunta, 450, -110, 0); // Posição original

        // Exibe as alternativas como botões
        for (int i = 0; i < 3; i++) {
            al_draw_filled_rectangle(botao_x, botao_y[i], botao_x + largura, botao_y[i] + altura, button_color);
            al_draw_text(font, white, botao_x + largura / 2, botao_y[i] + 15, ALLEGRO_ALIGN_CENTER,
                         perguntas[indice_pergunta].alternativas[i]);
        }

        al_flip_display(); // Atualiza a tela
    }

    // Libera recursos
    al_destroy_bitmap(cenario);
    al_destroy_bitmap(personagens);
    al_destroy_bitmap(rei);
    for (int i = 0; i < 5; i++) {
        al_destroy_bitmap(perguntas[i].imagem_pergunta);
    }
    al_destroy_font(font);
    al_destroy_timer(timer);
    al_destroy_event_queue(event_queue);
}
