#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <stdio.h>
#include "game.h"

ALLEGRO_BITMAP *background_mapa = NULL;
ALLEGRO_BITMAP *red_circle = NULL;

// Coordenadas e tamanhos das áreas clicáveis (bolinhas)
int bolinha1_x = 570, bolinha1_y = 250, bolinha_size = 50;
int bolinha2_x = 450, bolinha2_y = 450;
int bolinha3_x = 690, bolinha3_y = 570;

// Função que inicializa o mapa
void init_mapa() {
    // Carregar a imagem do mapa e a bolinha vermelha
    background_mapa = al_load_bitmap("assets/images/mapa_2.png");
    red_circle = al_load_bitmap("assets/images/vermelho.png");

    if (!background_mapa || !red_circle) {
        printf("Erro ao carregar a imagem do mapa ou círculo vermelho.\n");
    }
}

// Função que desenha o mapa e as bolinhas clicáveis
void draw_mapa() {
    if (background_mapa) {
        // Desenha o mapa redimensionado para a tela inteira
        al_draw_scaled_bitmap(background_mapa, 0, 0, al_get_bitmap_width(background_mapa), al_get_bitmap_height(background_mapa), 
                              0, 0, al_get_display_width(al_get_current_display()), al_get_display_height(al_get_current_display()), 0);
    }

    // Desenha as bolinhas vermelhas nas suas posições
    al_draw_scaled_bitmap(red_circle, 0, 0, al_get_bitmap_width(red_circle), al_get_bitmap_height(red_circle),
                          bolinha1_x, bolinha1_y, bolinha_size, bolinha_size, 0); // Bolinha 1
    al_draw_scaled_bitmap(red_circle, 0, 0, al_get_bitmap_width(red_circle), al_get_bitmap_height(red_circle),
                          bolinha2_x, bolinha2_y, bolinha_size, bolinha_size, 0); // Bolinha 2
    al_draw_scaled_bitmap(red_circle, 0, 0, al_get_bitmap_width(red_circle), al_get_bitmap_height(red_circle),
                          bolinha3_x, bolinha3_y, bolinha_size, bolinha_size, 0); // Bolinha 3
}

// Função que verifica se o mouse clicou dentro de uma bolinha
bool is_mouse_over_bolinha(int mouse_x, int mouse_y, int bolinha_x, int bolinha_y, int bolinha_size) {
    return (mouse_x >= bolinha_x && mouse_x <= (bolinha_x + bolinha_size) &&
            mouse_y >= bolinha_y && mouse_y <= (bolinha_y + bolinha_size));
}

// Função que lida com os eventos e cliques nas bolinhas
void handle_mapa_event(ALLEGRO_EVENT event, GameState *game_state) {
    if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
        int mouse_x = event.mouse.x;
        int mouse_y = event.mouse.y;

        // Verifica se o clique foi na bolinha 1
        if (is_mouse_over_bolinha(mouse_x, mouse_y, bolinha1_x, bolinha1_y, bolinha_size)) {
            *game_state = FASE_1;  // Vai para a Fase 1
        }
        // Verifica se o clique foi na bolinha 2
        else if (is_mouse_over_bolinha(mouse_x, mouse_y, bolinha2_x, bolinha2_y, bolinha_size)) {
            *game_state = FASE_2;  // Vai para a Fase 2
        }
        // Verifica se o clique foi na bolinha 3
        else if (is_mouse_over_bolinha(mouse_x, mouse_y, bolinha3_x, bolinha3_y, bolinha_size)) {
            *game_state = FASE_3;  // Vai para a Fase 3
        }
    }
}

// Função que destrói os recursos do mapa
void destroy_mapa() {
    if (background_mapa) {
        al_destroy_bitmap(background_mapa);
    }
    if (red_circle) {
        al_destroy_bitmap(red_circle);
    }
}
