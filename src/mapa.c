#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <stdio.h>
#include "headers/game.h"
#include "headers/mapa.h"
#include "headers/resumo_fase.h"
#include "game.h"
#include "headers/game.h"
#include "headers/resumo_fase.h"

ALLEGRO_BITMAP* background_mapa = NULL;
ALLEGRO_BITMAP* red_circle = NULL;
ALLEGRO_BITMAP* message_box = NULL; // Adicionada a caixa de mensagem
ALLEGRO_BITMAP* texto_mapa = NULL; // A imagem de texto do mapa

// Coordenadas e tamanhos das áreas clicáveis (bolinhas e caixa)
int bolinha1_x = 570, bolinha1_y = 250, bolinha_size = 50;
int bolinha2_x = 450, bolinha2_y = 450;
int bolinha3_x = 690, bolinha3_y = 570;
int caixa1_x = 620, caixa1_y = 250, caixa_size = 50;
int caixa2_x = 500, caixa2_y = 450;
int caixa3_x = 740, caixa3_y = 570;

void init_mapa(event_queue) {
    background_mapa = al_load_bitmap("assets/images/mapa_2.png");
    red_circle = al_load_bitmap("assets/images/vermelho.png");
    message_box = al_load_bitmap("assets/images/caixa_mensagem.png");
    texto_mapa = al_load_bitmap("assets/images/texto_mapa.png"); // Carregar a nova imagem

    if (!background_mapa || !red_circle || !message_box || !texto_mapa) {
        printf("Erro ao carregar a imagem do mapa, círculo vermelho, caixa de mensagem ou texto do mapa.\n");
    }
}

void draw_mapa() {
    if (background_mapa) {
        // Desenha o mapa redimensionado para a tela inteira
        al_draw_scaled_bitmap(background_mapa, 0, 0, al_get_bitmap_width(background_mapa), al_get_bitmap_height(background_mapa),
            0, 0, al_get_display_width(al_get_current_display()), al_get_display_height(al_get_current_display()), 0);
    }

    // Desenha as bolinhas vermelhas
    al_draw_scaled_bitmap(red_circle, 0, 0, al_get_bitmap_width(red_circle), al_get_bitmap_height(red_circle),
        bolinha1_x, bolinha1_y, bolinha_size, bolinha_size, 0);
    al_draw_scaled_bitmap(red_circle, 0, 0, al_get_bitmap_width(red_circle), al_get_bitmap_height(red_circle),
        bolinha2_x, bolinha2_y, bolinha_size, bolinha_size, 0);
    al_draw_scaled_bitmap(red_circle, 0, 0, al_get_bitmap_width(red_circle), al_get_bitmap_height(red_circle),
        bolinha3_x, bolinha3_y, bolinha_size, bolinha_size, 0);

    // Desenha a caixa de mensagem
    al_draw_scaled_bitmap(message_box, 0, 0, al_get_bitmap_width(message_box), al_get_bitmap_height(message_box),
        caixa1_x, caixa1_y, caixa_size, caixa_size, 0);
    al_draw_scaled_bitmap(message_box, 0, 0, al_get_bitmap_width(message_box), al_get_bitmap_height(message_box),
        caixa2_x, caixa2_y, caixa_size, caixa_size, 0);
    al_draw_scaled_bitmap(message_box, 0, 0, al_get_bitmap_width(message_box), al_get_bitmap_height(message_box),
        caixa3_x, caixa3_y, caixa_size, caixa_size, 0);

    // Desenha o texto do mapa no canto superior esquerdo (ajustando a posição conforme necessário)
    // Desenha o texto do mapa no canto superior esquerdo (ajustando a posição e o tamanho)
if (texto_mapa) {
    int texto_width = al_get_bitmap_width(texto_mapa);
    int texto_height = al_get_bitmap_height(texto_mapa);

    // Defina o fator de escala para reduzir o tamanho (0.5 significa metade do tamanho original)
    float scale_factor = 0.38;

    // Calcula o novo tamanho baseado no fator de escala
    int scaled_width = texto_width * scale_factor;
    int scaled_height = texto_height * scale_factor;

    int texto_x = 0; // 10px de margem da borda esquerda
    int texto_y = 90; // 10px de margem superior

    // Desenha a imagem escalada
    al_draw_scaled_bitmap(texto_mapa, 0, 0, texto_width, texto_height, texto_x, texto_y, scaled_width, scaled_height, 0);
}

}

bool is_mouse_over_area(int mouse_x, int mouse_y, int area_x, int area_y, int area_size) {
    return (mouse_x >= area_x && mouse_x <= (area_x + area_size) &&
        mouse_y >= area_y && mouse_y <= (area_y + area_size));
}

void handle_mapa_event(ALLEGRO_EVENT event, GameState* game_state) {
    if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
        int mouse_x = event.mouse.x;
        int mouse_y = event.mouse.y;

        if (is_mouse_over_area(mouse_x, mouse_y, caixa1_x, caixa1_y, caixa_size)) {
            init_resumo_fase_1(al_get_current_display(), game_state);
        }
        else if (is_mouse_over_area(mouse_x, mouse_y, caixa2_x, caixa2_y, caixa_size)) {
            init_resumo_fase_2(al_get_current_display(), game_state);
        }
        else if (is_mouse_over_area(mouse_x, mouse_y, caixa3_x, caixa3_y, caixa_size)) {
            init_resumo_fase_3(al_get_current_display(), game_state);
        }
        else if (is_mouse_over_area(mouse_x, mouse_y, bolinha1_x, bolinha1_y, bolinha_size)) {
            *game_state = FASE_1;
        }
        else if (is_mouse_over_area(mouse_x, mouse_y, bolinha2_x, bolinha2_y, bolinha_size)) {
            *game_state = FASE_2;
        }
        else if (is_mouse_over_area(mouse_x, mouse_y, bolinha3_x, bolinha3_y, bolinha_size)) {
            *game_state = FASE_3;
        }
    }
}

void destroy_mapa() {
    if (background_mapa) {
        al_destroy_bitmap(background_mapa);
    }
    if (red_circle) {
        al_destroy_bitmap(red_circle);
    }
    if (message_box) {
        al_destroy_bitmap(message_box);
    }
    if (texto_mapa) { // Não esquecer de liberar a imagem do texto
        al_destroy_bitmap(texto_mapa);
    }
}
