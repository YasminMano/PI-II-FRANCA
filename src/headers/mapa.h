#ifndef MAPA_H
#define MAPA_H

#include <allegro5/allegro.h>
#include "game.h"  // Certifique-se de que game.h contém as definições necessárias para GameState

void init_mapa();  // Função para inicializar a tela do mapa
void draw_mapa();  // Função para desenhar o mapa
void handle_mapa_event(ALLEGRO_EVENT event, GameState* game_state);  // Função para lidar com os eventos no mapa
void destroy_mapa();  // Função para destruir os recursos do mapa

#endif  // MAPA_H