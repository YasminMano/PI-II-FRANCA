#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <stdio.h>
#include "headers/resumo_inicio.h"
#include "headers/game.h"

void iniciar_resumo(ALLEGRO_DISPLAY* display, GameState* game_state) {
    // Verifique se os ponteiros são nulos antes de usar
    if (!display) {
        printf("Erro: display é NULL dentro de iniciar_resumo.\n");
        return;
    }

    if (!game_state) {
        printf("Erro: game_state é NULL dentro de iniciar_resumo.\n");
        return;
    }

    bool running = true;
    ALLEGRO_FONT* font = al_create_builtin_font();
    if (!font) {
        printf("Erro ao criar a fonte embutida do Allegro!\n");
        return;
    }

    ALLEGRO_EVENT_QUEUE* queue = al_create_event_queue();
    if (!queue) {
        printf("Erro ao criar a fila de eventos!\n");
        al_destroy_font(font);
        return;
    }

    al_register_event_source(queue, al_get_display_event_source(display));
    al_register_event_source(queue, al_get_mouse_event_source());

    while (running) {
        ALLEGRO_EVENT event;
        al_wait_for_event(queue, &event);

        if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
            running = false;
        }

        if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
            int mouse_x = event.mouse.x;
            int mouse_y = event.mouse.y;

            if (mouse_x >= 300 && mouse_x <= 500 && mouse_y >= 400 && mouse_y <= 450) {
                running = false;
                *game_state = TELA_INICIO; // Retorna para a tela inicial
            }
        }

        al_clear_to_color(al_map_rgb(0, 0, 0));

        ALLEGRO_COLOR white = al_map_rgb(255, 255, 255);
        int x = al_get_display_width(display) / 2;
        int y = al_get_display_height(display) / 4;

        al_draw_text(font, white, x, y, ALLEGRO_ALIGN_CENTER, "Resumo Geral:");
        al_draw_text(font, white, x, y + 40, ALLEGRO_ALIGN_CENTER, "A Revolução Francesa foi um movimento político e social.");
        al_draw_text(font, white, x, y + 80, ALLEGRO_ALIGN_CENTER, "Ela ocorreu entre 1789 e 1799, marcando o início da democracia.");
        al_draw_text(font, white, x, y + 120, ALLEGRO_ALIGN_CENTER, "Inspirou mudanças ao redor do mundo.");

        // Botão "Voltar"
        al_draw_filled_rectangle(300, 400, 500, 450, al_map_rgb(100, 100, 100));
        al_draw_text(font, white, 400, 415, ALLEGRO_ALIGN_CENTER, "Voltar");

        al_flip_display();
    }

    // Libera os recursos de forma adequada
    al_destroy_font(font);
    al_destroy_event_queue(queue);
}
