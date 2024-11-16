#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <stdio.h>
#include "game.h"
#include "mapa.h"  // Adicionado para incluir as funções do mapa

void iniciar_fase_1(ALLEGRO_DISPLAY* display);
void iniciar_fase_2(ALLEGRO_DISPLAY* display);
void iniciar_fase_3(ALLEGRO_DISPLAY* display);

// Função que inicializa a tela de resumo sobre a Revolução Francesa
void iniciar_resumo(ALLEGRO_DISPLAY* display) {
    bool running = true;
    ALLEGRO_EVENT_QUEUE* event_queue = al_create_event_queue();
    ALLEGRO_TIMER* timer = al_create_timer(1.0 / 60.0);  // Temporizador para 60 FPS

    // Registrar as fontes de eventos
    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_timer_event_source(timer));
    al_register_event_source(event_queue, al_get_mouse_event_source());  // Para detectar cliques de mouse
    al_start_timer(timer);

    // Configurações de texto
    ALLEGRO_FONT* font = al_create_builtin_font();  // Usa a fonte padrão do Allegro
    ALLEGRO_COLOR white = al_map_rgb(255, 255, 255);  // Cor branca para o texto

    while (running) {
        ALLEGRO_EVENT event;
        al_wait_for_event(event_queue, &event);

        // Fecha a janela se o usuário clicar no botão de fechar
        if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
            running = false;
        }

        // Verifique se o usuário clicou no botão "Voltar"
        if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
            int mouse_x = event.mouse.x;
            int mouse_y = event.mouse.y;

            // Verifica se o botão "Voltar" foi clicado
            if (mouse_x >= 300 && mouse_x <= 500 && mouse_y >= 400 && mouse_y <= 450) {
                running = false;  // Sai da tela de resumo e retorna ao menu
            }
        }

        // Limpa a tela e desenha o texto de resumo linha por linha
        al_clear_to_color(al_map_rgb(0, 0, 0));  // Preenche o fundo com cor preta

        // Desenhar o resumo linha por linha
        int x = al_get_display_width(display) / 2;
        int y = al_get_display_height(display) / 4;

        al_draw_text(font, white, x, y, ALLEGRO_ALIGN_CENTER, "A Revolução Francesa foi um movimento social");
        al_draw_text(font, white, x, y + 20, ALLEGRO_ALIGN_CENTER, "e político que ocorreu na França entre 1789 e 1799.");
        al_draw_text(font, white, x, y + 40, ALLEGRO_ALIGN_CENTER, "Ela foi marcada pela derrubada da monarquia");
        al_draw_text(font, white, x, y + 60, ALLEGRO_ALIGN_CENTER, "e a instauração de uma república.");
        al_draw_text(font, white, x, y + 80, ALLEGRO_ALIGN_CENTER, "Foi um evento de grande impacto histórico,");
        al_draw_text(font, white, x, y + 100, ALLEGRO_ALIGN_CENTER, "inspirando mudanças em todo o mundo.");

        // Desenhar o botão "Voltar"
        al_draw_filled_rectangle(300, 400, 500, 450, al_map_rgb(100, 100, 100));  // Botão cinza
        al_draw_text(font, white, 400, 415, ALLEGRO_ALIGN_CENTER, "Voltar");  // Texto do botão

        al_flip_display();  // Atualiza a tela com o conteúdo do resumo
    }

    // Libera recursos
    al_destroy_font(font);
    al_destroy_timer(timer);
    al_destroy_event_queue(event_queue);
}

// Função que inicializa a tela de menu do jogo
void iniciar_tela_menu(ALLEGRO_DISPLAY* display, ALLEGRO_BITMAP* background) {
    GameState game_state = MENU;  // Define o estado inicial do jogo como MENU

    // Cria a fila de eventos e o temporizador para controlar o loop do jogo
    ALLEGRO_EVENT_QUEUE* event_queue = al_create_event_queue();
    ALLEGRO_TIMER* timer = al_create_timer(1.0 / 60.0);  // Temporizador para 60 FPS

    // Registra as fontes de eventos (display, temporizador, mouse)
    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_timer_event_source(timer));
    al_register_event_source(event_queue, al_get_mouse_event_source());

    // Inicia o temporizador
    al_start_timer(timer);

    bool running = true;  // Controla o loop principal do jogo

    // Loop principal do jogo
    while (running) {
        ALLEGRO_EVENT event;
        al_wait_for_event(event_queue, &event);  // Espera por eventos (fechar janela, mouse, etc.)

        // Fecha o jogo se a janela for fechada
        if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
            running = false;
        }

        // Verifica se o estado atual é o MENU
        if (game_state == MENU) {
            // Verifica se houve clique do mouse
            if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
                int mouse_x = event.mouse.x;
                int mouse_y = event.mouse.y;

                // Verifica se o botão "Iniciar Jogo" foi clicado
                if (mouse_x >= 456 && mouse_x <= 813 && mouse_y >= 604 && mouse_y <= 647) {
                    printf("Iniciar Jogo foi clicado!\n");
                    game_state = MAPA;  // Agora vai para o mapa
                }

                // Verifica se o botão "Sair" foi clicado
                if (mouse_x >= 879 && mouse_x <= 1184 && mouse_y >= 599 && mouse_y <= 654) {
                    printf("Sair foi clicado!\n");
                    running = false;  // Sai do loop principal
                }

                // Verifica se o botão "Resumo" foi clicado
                if (mouse_x >= 120 && mouse_x <= 380 && mouse_y >= 561 && mouse_y <= 695) {
                    printf("Resumo foi clicado!\n");
                    game_state = RESUMO;  // Muda o estado do jogo para RESUMO
                }
            }

            // Desenha a imagem de fundo do menu e atualiza a tela
            al_draw_scaled_bitmap(background, 0, 0, al_get_bitmap_width(background), al_get_bitmap_height(background),
                0, 0, al_get_display_width(display), al_get_display_height(display), 0);
            al_flip_display();  // Atualiza a tela com o novo frame
        }
        // Se o estado do jogo for MAPA
        else if (game_state == MAPA) {
            init_mapa();  // Inicializa a tela do mapa
            while (game_state == MAPA) {
                ALLEGRO_EVENT event;
                al_wait_for_event(event_queue, &event);
                al_clear_to_color(al_map_rgb(0, 0, 0));  // Limpa a tela
                draw_mapa();  // Desenha o mapa
                handle_mapa_event(event, &game_state);  // Lida com o evento de clique
                al_flip_display();
            }
            destroy_mapa();
        }
        // Se o estado do jogo for RESUMO
        else if (game_state == RESUMO) {
            iniciar_resumo(display);  // Chama a função que exibe o resumo
            game_state = MENU;  // Volta para o MENU após o resumo
        }
        // Se o estado do jogo for FASE_1
        else if (game_state == FASE_1) {
            iniciar_fase_1(display);  // Chama a função da Fase 1
            game_state = MENU;  // Volta para o MENU após a fase
        }
        // Se o estado do jogo for FASE_2
        else if (game_state == FASE_2) {
            iniciar_fase_2(display);  // Chama a função da Fase 2
            game_state = MENU;  // Volta para o MENU após a fase
        }
        // Se o estado do jogo for FASE_3
        else if (game_state == FASE_3) {
            iniciar_fase_3(display);  // Chama a função da Fase 3 (de teste)
            game_state = MENU;  // Volta para o MENU após a fase
        }
    }

    // Libera os recursos alocados após o término do loop
    al_destroy_timer(timer);
    al_destroy_event_queue(event_queue);
}