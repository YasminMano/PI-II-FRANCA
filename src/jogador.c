#include "jogador.h"

// Função para inicializar o jogador
void init_jogador(Jogador* jogador, int display_height) {
    jogador->sprite_sheet = al_load_bitmap("assets/images/teste_personagem.png"); // Carrega a imagem do personagem
    jogador->frame_width = 265;    // Define a largura de cada quadro da animação
    jogador->frame_height = 376;   // Define a altura de cada quadro da animação
    jogador->pos_x = 50;           // Define a posição inicial do jogador no eixo X
    jogador->scale_factor = 0.6;   // Define o fator de escala da animação
    jogador->pos_y = display_height - jogador->frame_height * jogador->scale_factor; // Define a posição inicial do jogador no eixo Y
    jogador->initial_pos_y = jogador->pos_y;  // Guarda a posição inicial no eixo Y para controle do pulo
    jogador->jump_velocity = -12.0f;  // Define a velocidade inicial do pulo
    jogador->gravity = 0.4f;         // Define a intensidade da gravidade
    jogador->movement_speed = 2.0;   // Define a velocidade de movimento do jogador
    jogador->frame_time = 0.2;       // Define o tempo de cada quadro na animação
    jogador->frame_timer = 0;        // Inicializa o contador do tempo de animação
    jogador->total_moving_frames = 3; // Define o número total de quadros para a animação de movimento
    jogador->current_frame = 0;      // Inicializa o quadro da animação como 0
    jogador->facing_right = true;    // Inicializa a direção do jogador (para a direita)
    jogador->jumping = false;        // Inicializa a flag de pulo (não pulando)
    jogador->move_left = false;      // I
    jogador->move_right = false;
    jogador->moving = false;
    jogador->knocked_back = false;
    jogador->knockback_velocity = 0;
    jogador->vidas = 3;
}

// Função que desenha o jogador na tela
void desenha_jogador(Jogador* jogador) {
    int frame_x[] = { 0, 265, 530 }; // Array que contém as coordenadas X dos quadros da animação
    int frame_cx = frame_x[jogador->current_frame]; // Pega o quadro atual da animação
    int frame_cy = 0; // Define a linha da sprite (sempre 0, pois há apenas uma linha de quadros)

    al_draw_scaled_bitmap(
        jogador->sprite_sheet,      // Imagem que contém os quadros
        frame_cx, frame_cy,         // Posições X e Y do quadro atual
        jogador->frame_width,       // Largura do quadro
        jogador->frame_height,      // Altura do quadro
        jogador->pos_x, jogador->pos_y, // Posições do jogador na tela
        jogador->frame_width * jogador->scale_factor, // Largura escalada
        jogador->frame_height * jogador->scale_factor, // Altura escalada
        jogador->facing_right ? 0 : ALLEGRO_FLIP_HORIZONTAL // Flip horizontal dependendo da direção do jogador
    );
}