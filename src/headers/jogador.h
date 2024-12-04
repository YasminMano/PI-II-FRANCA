#ifndef JOGADOR_H
#define JOGADOR_H

#include <allegro5/allegro.h>
#include "game.h"

// Estrutura para o jogador
typedef struct {
    ALLEGRO_BITMAP* sprite_sheet;  // Imagem que contém a animação do jogador
    int pos_x, pos_y;              // Posições horizontais e verticais do jogador na tela
    int initial_pos_y;             // Posição inicial no eixo Y (usado para controlar a gravidade)
    int frame_width, frame_height; // Largura e altura de cada quadro da animação
    int current_frame;             // Quadro atual da animação (controle de animação)
    float scale_factor;            // Fator de escala para redimensionamento da animação
    bool facing_right;             // Flag que indica para que direção o jogador está virado
    bool jumping;                  // Flag que indica se o jogador está pulando
    bool knocked_back;             // Flag que indica se o jogador foi empurrado
    float knockback_velocity;      // Velocidade do empurrão do jogador
    float jump_velocity;           // Velocidade do pulo
    float gravity;                 // Força da gravidade no jogo
    bool move_left, move_right, moving; // Flags para controlar o movimento do jogador
    float movement_speed;          // Velocidade de movimento do jogador
    float frame_time, frame_timer; // Controle do tempo de animação do jogador
    int total_moving_frames;       // Número de quadros de movimento do jogador
    int vidas;                     // Número de vidas do jogador
} Jogador;

void init_jogador(Jogador* jogador, int display_height);
void desenha_jogador(Jogador* jogador);

#endif
