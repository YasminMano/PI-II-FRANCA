#include "jogo.h"
#include "jogador.h"
#include "guarda.h"

// Função para inicializar o jogo
void init_jogo(Jogo* jogo) {
    al_init(); // Inicializa a biblioteca Allegro
    al_install_keyboard(); // Instala o sistema de teclado
    jogo->timer = al_create_timer(1.0 / 30.0); // Cria o timer com 30 quadros por segundo
    jogo->background = al_load_bitmap("assets/images/cenario1.png"); // Carrega a imagem de fundo
    jogo->event_queue = al_create_event_queue(); // Cria a fila de eventos
    al_register_event_source(jogo->event_queue, al_get_display_event_source(jogo->display)); // Registra a fonte de eventos da janela
    al_register_event_source(jogo->event_queue, al_get_timer_event_source(jogo->timer)); // Registra a fonte de eventos do timer
    al_register_event_source(jogo->event_queue, al_get_keyboard_event_source()); // Registra a fonte de eventos do teclado
    al_start_timer(jogo->timer); // Inicia o timer
}

// Função para detectar colisão entre jogador e guarda
bool detectar_colisao(Jogador* jogador, Guarda* guarda) {
    // Obtém as coordenadas do jogador (com base na posição e nas dimensões da sprite)
    int jogador_left = jogador->pos_x;
    int jogador_right = jogador->pos_x + jogador->frame_width * jogador->scale_factor;
    int jogador_top = jogador->pos_y;
    int jogador_bottom = jogador->pos_y + jogador->frame_height * jogador->scale_factor;

    // Obtém as coordenadas do guarda
    int guarda_left = guarda->pos_x;
    int guarda_right = guarda->pos_x + guarda->frame_width * guarda->scale_factor;
    int guarda_top = guarda->pos_y;
    int guarda_bottom = guarda->pos_y + guarda->frame_height * guarda->scale_factor;

    // Verifica se há colisão horizontal e vertical
    bool colisao = jogador_right > guarda_left && jogador_left < guarda_right &&
        jogador_bottom > guarda_top && jogador_top < guarda_bottom;

    // Verifica se o jogador colidiu com a parte superior do guarda (cair sobre ele)
    if (colisao && jogador_bottom > guarda_top && jogador_top < guarda_top + 50) { // Ajuste o valor 50 conforme necessário
        return true; // Colisão na parte superior do guarda
    }

    return colisao; // Caso contrário, retorna a colisão padrão
}