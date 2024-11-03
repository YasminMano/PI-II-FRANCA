#include "pause_menu.h"
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_color.h>
#include <stdio.h> // Para depuração

void handle_pause_menu(AllegroGame* game, GameState* state) {
    bool in_pause_menu = true;
    ALLEGRO_EVENT event;

    // Exibe o menu de pausa na tela
    al_clear_to_color(al_map_rgb(0, 0, 0));
    al_draw_text(game->font_big, al_map_rgb(255, 255, 255), 640, 200, ALLEGRO_ALIGN_CENTER, "PAUSA");
    al_draw_text(game->font, al_map_rgb(255, 255, 255), 640, 350, ALLEGRO_ALIGN_CENTER, "1 - Voltar ao Menu Principal");
    al_draw_text(game->font, al_map_rgb(255, 255, 255), 640, 400, ALLEGRO_ALIGN_CENTER, "2 - Voltar ao Mapa");
    al_draw_text(game->font, al_map_rgb(255, 255, 255), 640, 450, ALLEGRO_ALIGN_CENTER, "ESC - Retornar ao Jogo");
    al_flip_display();

    while (in_pause_menu) {
        al_wait_for_event(game->queue, &event);

        if (event.type == ALLEGRO_EVENT_KEY_DOWN) {
            printf("Tecla pressionada no menu de pausa: %d\n", event.keyboard.keycode); // Depuração
            switch (event.keyboard.keycode) {
            case ALLEGRO_KEY_1:
                *state = MENU;
                in_pause_menu = false;
                printf("Opção 1 selecionada: Voltar ao Menu Principal\n");
                break;
            case ALLEGRO_KEY_2:
                *state = MAPA;
                in_pause_menu = false;
                printf("Opção 2 selecionada: Voltar ao Mapa\n");
                break;
            case ALLEGRO_KEY_ESCAPE:
                in_pause_menu = false;
                printf("ESC pressionado: Retornar ao Jogo\n");
                break;
            }
        }
    }

    // Redesenha o display após sair do menu de pausa
    al_clear_to_color(al_map_rgb(0, 0, 0));
    al_flip_display();
}
