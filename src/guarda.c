#include "guarda.h"

// Função para inicializar o guarda (inimigo)
void init_guarda(Guarda* guarda, int display_width, int display_height) {
    guarda->sprite_sheet = al_load_bitmap("assets/images/guarda.png"); // Carrega a imagem do guarda
    guarda->frame_width = 120;  // Largura de cada quadro do guarda
    guarda->frame_height = 170; // Altura de cada quadro do guarda
    guarda->scale_factor = 1.2; // Fator de escala do guarda
    guarda->pos_x = display_width - guarda->frame_width * guarda->scale_factor - 50; // Define a posição inicial do guarda no eixo X
    guarda->pos_y = display_height - guarda->frame_height * guarda->scale_factor; // Define a posição inicial do guarda no eixo Y
    guarda->movement_speed = 1.5; // Define a velocidade de movimento do guarda
    guarda->move_right = false;   // Inicializa a direção de movimento do guarda (não se move para a direita)
    guarda->min_x = display_width - guarda->frame_width * guarda->scale_factor - 200; // Define o limite mínimo do movimento
    guarda->max_x = display_width - guarda->frame_width * guarda->scale_factor - 50;  // Define o limite máximo do movimento
    guarda->current_frame = 0;     // Inicializa o quadro da animação do guarda
    guarda->frame_time = 0.3;      // Define o tempo entre os quadros na animação do guarda
    guarda->frame_timer = 0;       // Inicializa o contador de animação do guarda
    guarda->total_frames = 6;      // Número total de quadros da animação
    guarda->frames_per_row = 2;    // Número de quadros por linha na animação do guarda
    guarda->morto = false;         // Inicializa a flag de morte
}

// Função que desenha o guarda na tela
void desenha_guarda(Guarda* guarda) {
    if (guarda->morto) return; // Não desenha o guarda se ele estiver morto

    int frame_coluna = guarda->current_frame % guarda->frames_per_row;  // Coluna do quadro na sprite
    int frame_linha = guarda->current_frame / 3;                         // Linha do quadro na sprite
    int frame_x = frame_coluna * guarda->frame_width;                    // Posição X do quadro
    int frame_y = frame_linha * guarda->frame_height;                    // Posição Y do quadro

    al_draw_scaled_bitmap(guarda->sprite_sheet, frame_x, frame_y, guarda->frame_width, guarda->frame_height,
        guarda->pos_x, guarda->pos_y, guarda->frame_width * guarda->scale_factor, guarda->frame_height * guarda->scale_factor,
        ALLEGRO_FLIP_HORIZONTAL); // Desenha a sprite do guarda
}
