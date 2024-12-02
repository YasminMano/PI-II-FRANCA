#ifndef TELA_INICIO_H
#define TELA_INICIO_H

#include <allegro5/allegro.h>
#include "game.h"

// Função que inicia a tela de menu do jogo, recebendo o display, o background e o estado do jogo
void iniciar_tela_menu(ALLEGRO_DISPLAY* display, ALLEGRO_BITMAP* background, GameState* game_state, ALLEGRO_EVENT_QUEUE* event_queue);

#endif
