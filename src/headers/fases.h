#ifndef FASES_H
#define FASES_H

#include <allegro5/allegro.h>
#include "game.h"

// Declaração das funções para iniciar cada fase
void iniciar_fase_1(ALLEGRO_DISPLAY* display, GameState* game_state);
void iniciar_fase1_2(ALLEGRO_DISPLAY* display, GameState* game_state);
void iniciar_fase1_3(ALLEGRO_DISPLAY* display, GameState* game_state);
void iniciar_fase_2(ALLEGRO_DISPLAY* display, GameState* game_state);
void iniciar_fase_2_3(ALLEGRO_DISPLAY* display, GameState* game_state);
void corredor(ALLEGRO_DISPLAY* display, GameState* game_state);
void quarto(ALLEGRO_DISPLAY* display, GameState* game_state);
void quarto2(ALLEGRO_DISPLAY* display, GameState* game_state);
void bau(ALLEGRO_DISPLAY* display, GameState* game_state);
void banheiro(ALLEGRO_DISPLAY* display, GameState* game_state);
void iniciar_fase_3(ALLEGRO_DISPLAY* display, GameState* game_state);

#endif
