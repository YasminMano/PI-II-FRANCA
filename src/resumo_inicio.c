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

    ALLEGRO_BITMAP* bg = al_load_bitmap("assets/images/fundo_inicio.png");
    if (!bg) {
        al_destroy_display(display);
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

            if (mouse_x >= 550 && mouse_x <= 750 && mouse_y >= 550 && mouse_y <= 620) {
                running = false;
                *game_state = TELA_INICIO; // Retorna para a tela inicial
            }
        }

        al_clear_to_color(al_map_rgb(0, 0, 0));

        ALLEGRO_COLOR white = al_map_rgb(0, 0, 0);
        int x = al_get_display_width(display) / 2;
        int y = al_get_display_height(display) / 8;

        al_clear_to_color(al_map_rgb(255, 255, 255));
        al_draw_scaled_bitmap(bg, 0, 0, al_get_bitmap_width(bg), al_get_bitmap_height(bg), 0, 0, al_get_display_width(display), al_get_display_height(display), 0);
        al_draw_filled_rectangle(550, 550, 750, 620, al_map_rgb(100, 100, 100));
        al_draw_text(font, white, 650, 580, ALLEGRO_ALIGN_CENTER, "Voltar");
        al_draw_text(font, white, x, y, ALLEGRO_ALIGN_CENTER, "Resumo Geral:");
        al_draw_text(font, white, x, y + 40, ALLEGRO_ALIGN_CENTER, "A Revolução Francesa (1789-1799) foi um movimento que derrubou");
        al_draw_text(font, white, x, y + 80, ALLEGRO_ALIGN_CENTER, "a monarquia absoluta, motivado por desigualdades sociais, crises");
        al_draw_text(font, white, x, y + 120, ALLEGRO_ALIGN_CENTER, "econômicas e ideais iluministas. Começou com a formação da");
        al_draw_text(font, white, x, y + 160, ALLEGRO_ALIGN_CENTER, "Assembleia Nacional e proclamou a Declaração dos Direitos do");
        al_draw_text(font, white, x, y + 200, ALLEGRO_ALIGN_CENTER, "Homem e do Cidadão, promovendo liberdade, igualdade e");
        al_draw_text(font, white, x, y + 240, ALLEGRO_ALIGN_CENTER, "fraternidade. A monarquia de Luís XVI foi abolida, dando lugar à Primeira");
        al_draw_text(font, white, x, y + 280, ALLEGRO_ALIGN_CENTER, "República. Contudo, o período foi marcado por instabilidade e o");
        al_draw_text(font, white, x, y + 320, ALLEGRO_ALIGN_CENTER, "Reino do Terror, com execuções em massa. A revolução encerrou-se");
        al_draw_text(font, white, x, y + 360, ALLEGRO_ALIGN_CENTER, "com o golpe de Napoleão Bonaparte, transformando a França e");
        al_draw_text(font, white, x, y + 400, ALLEGRO_ALIGN_CENTER, "influenciando o mundo com ideais democráticos e de cidadania.");
        al_flip_display();
    }

    // Libera os recursos de forma adequada
    al_destroy_font(font);
    al_destroy_event_queue(queue);
    al_destroy_bitmap(bg);
}
