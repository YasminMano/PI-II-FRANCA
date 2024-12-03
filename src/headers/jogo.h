#ifndef JOGO_H
#define JOGO_H

#include <allegro5/allegro.h>
#include "game.h"
#include "jogador.h"
#include "guarda.h"

// Estrutura para o contexto do jogo
typedef struct {
    ALLEGRO_DISPLAY* display;           // Janela de exibição do jogo
    ALLEGRO_TIMER* timer;               // Timer para controlar o tempo e o FPS do jogo
    ALLEGRO_EVENT_QUEUE* event_queue;   // Fila de eventos que armazena as interações do usuário
    ALLEGRO_BITMAP* background;         // Imagem de fundo do jogo
} Jogo;

void init_jogo(Jogo* jogo);
bool detectar_colisao(Jogador* jogador, Guarda* guarda);

#endif
