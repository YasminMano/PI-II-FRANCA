#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <stdio.h>
#include "headers/pause_menu.h"
#include "headers/game.h"

// Função para exibir o menu de pausa
void exibir_menu_pausa(ALLEGRO_DISPLAY* display, GameState* game_state) {
    // Carregar o fundo da tela de pausa
    ALLEGRO_BITMAP* fundo_pause = al_load_bitmap("assets/images/pause_menu.png");
    ALLEGRO_BITMAP* botao_mapa_img = al_load_bitmap("assets/images/botao_mapa_pause.png");
    ALLEGRO_BITMAP* botao_menu_img = al_load_bitmap("assets/images/botao_menu_pause.png");

    if (!fundo_pause || !botao_mapa_img || !botao_menu_img) {
        printf("Erro ao carregar as imagens de pausa.\n");
        if (fundo_pause) al_destroy_bitmap(fundo_pause);
        if (botao_mapa_img) al_destroy_bitmap(botao_mapa_img);
        if (botao_menu_img) al_destroy_bitmap(botao_menu_img);
        return;
    }

    // Dimensões da tela
    int screen_width = al_get_display_width(display);
    int screen_height = al_get_display_height(display);

    // Dimensões dos botões
    int botao_mapa_width = al_get_bitmap_width(botao_mapa_img);
    int botao_mapa_height = al_get_bitmap_height(botao_mapa_img);

    int botao_menu_width = al_get_bitmap_width(botao_menu_img);
    int botao_menu_height = al_get_bitmap_height(botao_menu_img);

    // Ajustar a posição dos botões para ficarem mais centralizados
    int botao_spacing = 40; // Espaçamento entre os botões
    int botao_mapa_x = screen_width / 1.5 - botao_mapa_width - botao_spacing / 1.5;
    int botao_mapa_y = screen_height / 2 - botao_mapa_height / 2;

    int botao_menu_x = screen_width / 3 + botao_spacing / 3;
    int botao_menu_y = screen_height / 2 - botao_menu_height / 2;

    bool running = true;
    ALLEGRO_EVENT_QUEUE* event_queue = al_create_event_queue();
    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_mouse_event_source());

    while (running) {
        ALLEGRO_EVENT event;
        al_wait_for_event(event_queue, &event);

        if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
            running = false;
            *game_state = SAIR;
        } else if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
            int mouse_x = event.mouse.x;
            int mouse_y = event.mouse.y;

            // Verificar se o botão "Mapa" foi clicado
            if (mouse_x >= botao_mapa_x && mouse_x <= botao_mapa_x + botao_mapa_width &&
                mouse_y >= botao_mapa_y && mouse_y <= botao_mapa_y + botao_mapa_height) {
                *game_state = MAPA;
                running = false;
            }

            // Verificar se o botão "Menu" foi clicado
            if (mouse_x >= botao_menu_x && mouse_x <= botao_menu_x + botao_menu_width &&
                mouse_y >= botao_menu_y && mouse_y <= botao_menu_y + botao_menu_height) {
                *game_state = TELA_INICIO;
                running = false;
            }
        }

        // Desenhar o fundo
        al_clear_to_color(al_map_rgb(0, 0, 0));
        al_draw_scaled_bitmap(fundo_pause, 0, 0, al_get_bitmap_width(fundo_pause),
                              al_get_bitmap_height(fundo_pause), 0, 0, screen_width, screen_height, 0);

        // Desenhar o botão "Mapa"
        al_draw_bitmap(botao_mapa_img, botao_mapa_x, botao_mapa_y, 0);

        // Desenhar o botão "Menu"
        al_draw_bitmap(botao_menu_img, botao_menu_x, botao_menu_y, 0);

        al_flip_display();
    }

    al_destroy_bitmap(fundo_pause);
    al_destroy_bitmap(botao_mapa_img);
    al_destroy_bitmap(botao_menu_img);
    al_destroy_event_queue(event_queue);
}
