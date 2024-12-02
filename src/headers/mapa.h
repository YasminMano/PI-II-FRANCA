#ifndef MAPA_H
#define MAPA_H

#include <allegro5/allegro.h>
#include "headers/game.h"

// Declaração da função init_mapa para receber a fila de eventos
void init_mapa(ALLEGRO_EVENT_QUEUE* event_queue);

// Outras funções relacionadas ao mapa
void draw_mapa();
void handle_mapa_event(ALLEGRO_EVENT event, GameState* game_state);
void destroy_mapa();

#endif
