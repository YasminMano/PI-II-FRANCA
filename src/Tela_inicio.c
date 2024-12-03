#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <stdio.h>
#include "game.h"

// Função que inicializa a tela de menu do jogo
void iniciar_tela_menu(ALLEGRO_DISPLAY* display, ALLEGRO_BITMAP* background, GameState* game_state, ALLEGRO_EVENT_QUEUE* event_queue) {
    ALLEGRO_TIMER* timer = al_create_timer(1.0 / 60.0);  // Temporizador para 60 FPS

    // Registra o temporizador na fila de eventos
    al_register_event_source(event_queue, al_get_timer_event_source(timer));
    al_start_timer(timer);

    bool running = true;  // Controla o loop principal do menu

    // Loop principal do menu
    while (running) {
        ALLEGRO_EVENT event;
        al_wait_for_event(event_queue, &event);  // Espera por eventos

        // Fecha o jogo se a janela for fechada
        if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
            running = false;
            *game_state = SAIR;  // Atualiza o estado para sair
        }

        // Verifica cliques no mouse
        if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
            int mouse_x = event.mouse.x;
            int mouse_y = event.mouse.y;

            // Verifica se o botão "Iniciar Jogo" foi clicado
            if (mouse_x >= 456 && mouse_x <= 813 && mouse_y >= 604 && mouse_y <= 647) {
                printf("Iniciar Jogo foi clicado!\n");
                *game_state = MAPA;  // Vai para o mapa
                running = false;  // Sai do menu
            }

            // Verifica se o botão "Resumo" foi clicado
            if (mouse_x >= 120 && mouse_x <= 380 && mouse_y >= 561 && mouse_y <= 695) {
                printf("Resumo foi clicado!\n");
                *game_state = RESUMO;  // Vai para o resumo inicial
                running = false;  // Sai do menu
            }

            // Verifica se o botão "Sair" foi clicado
            if (mouse_x >= 879 && mouse_x <= 1184 && mouse_y >= 599 && mouse_y <= 654) {
                printf("Sair foi clicado!\n");
                *game_state = SAIR;  // Atualiza o estado para sair
                running = false;  // Sai do menu
            }
        }

        // Desenha o fundo do menu
        al_clear_to_color(al_map_rgb(0, 0, 0));
        al_draw_scaled_bitmap(background, 0, 0, al_get_bitmap_width(background), al_get_bitmap_height(background),
                              0, 0, al_get_display_width(display), al_get_display_height(display), 0);

        // Atualiza o display
        al_flip_display();
    }

    // Libera os recursos alocados
    al_destroy_timer(timer);
}
