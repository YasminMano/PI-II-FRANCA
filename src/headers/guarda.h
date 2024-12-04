#ifndef GUARDA_H
#define GUARDA_H

#include <allegro5/allegro.h>
#include "game.h"
#include "jogador.h"

// Estrutura para o guarda (inimigo)
typedef struct {
    ALLEGRO_BITMAP* sprite_sheet;  // Imagem que contém a animação do guarda
    int pos_x, pos_y;              // Posições horizontais e verticais do guarda na tela
    int frame_width, frame_height; // Largura e altura de cada quadro da animação do guarda
    float scale_factor;            // Fator de escala para redimensionamento da animação do guarda
    float movement_speed;          // Velocidade de movimento do guarda
    bool move_right;               // Flag que indica a direção do movimento do guarda
    int min_x, max_x;              // Limites de movimento horizontal do guarda
    int current_frame;             // Quadro atual da animação do guarda
    float frame_time, frame_timer; // Controle do tempo de animação do guarda
    int total_frames;              // Número total de quadros da animação
    int frames_per_row;            // Número de quadros por linha na sprite do guarda
    bool morto;                    // Flag para indicar se o guarda está morto
} Guarda;

void init_guarda(Guarda* guarda, int display_width, int display_height);
void desenha_guarda(Guarda* guarda);

#endif
