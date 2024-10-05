#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <stdio.h>
#include "game.h"  // Certifique-se de incluir o game.h, que contém as definições de GameState e AllegroGame

// Declaração da função iniciar_fase_1 (a implementação está em Fase_1.c)
void iniciar_fase_1(ALLEGRO_DISPLAY* display);

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
                    game_state = FASE_1;  // Muda o estado do jogo para FASE_1
                }

                // Verifica se o botão "Sair" foi clicado
                if (mouse_x >= 879 && mouse_x <= 1184 && mouse_y >= 599 && mouse_y <= 654) {
                    printf("Sair foi clicado!\n");
                    running = false;  // Sai do loop principal
                }

                // Verifica se o botão "Resumo" foi clicado
                if (mouse_x >= 120 && mouse_x <= 380 && mouse_y >= 561 && mouse_y <= 695) {
                    printf("Resumo foi clicado!\n");
                    game_state = RESUMO;  // Muda o estado do jogo para RESUMO (não implementado)
                }
            }

            // Desenha a imagem de fundo do menu e atualiza a tela
            al_draw_scaled_bitmap(background, 0, 0, al_get_bitmap_width(background), al_get_bitmap_height(background),
                                  0, 0, al_get_display_width(display), al_get_display_height(display), 0);
            al_flip_display();  // Atualiza a tela com o novo frame
        }
        // Se o estado do jogo for FASE_1
        else if (game_state == FASE_1) {
            iniciar_fase_1(display);  // Chama a função que inicia a Fase 1
            game_state = MENU;  // Após a Fase 1, volta para o MENU
        }
    }

    // Libera os recursos alocados após o término do loop
    al_destroy_timer(timer);
    al_destroy_event_queue(event_queue);
}

/*
Resumo:
Este código define a função `iniciar_tela_menu`, que exibe a tela de menu do jogo. Ele detecta cliques
no mouse para iniciar o jogo, mostrar o resumo ou sair. O estado do jogo muda para `FASE_1` quando o
jogador clica em "Iniciar Jogo". O loop principal do jogo escuta eventos e atualiza a tela conforme o estado atual.
*/
