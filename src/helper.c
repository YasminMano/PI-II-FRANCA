#ifndef HELPER_H
#define HELPER_H

#include <allegro5/allegro.h>
#include "headers/game.h"  // Incluindo game.h para usar AllegroGame

// Função auxiliar que verifica o clique do mouse. 
// Essa função monitora o estado atual e o estado anterior do mouse,
// para saber se o botão do mouse foi pressionado ou liberado.
void checkMouseClick(struct AllegroGame *game, bool *last_mouse_pressed, bool *last_was_mouse_pressed) {
    al_get_mouse_state(game->mouse_state);  // Obtém o estado atual do mouse

    // Verifica se o botão esquerdo do mouse foi pressionado
    game->is_mouse_pressed = game->mouse_state->buttons & 1;

    // Verifica se o botão do mouse foi liberado (clicado e solto)
    game->was_mouse_pressed = *last_mouse_pressed && !game->is_mouse_pressed;

    // Atualiza os estados anteriores
    *last_mouse_pressed = game->is_mouse_pressed;
    *last_was_mouse_pressed = game->was_mouse_pressed;
}

#endif

/*
Resumo:
O arquivo `helper.c` contém uma função auxiliar para monitorar cliques do mouse no jogo. 
A função `checkMouseClick` verifica se o botão do mouse foi pressionado ou solto e atualiza
os estados correspondentes dentro da estrutura `AllegroGame`, o que facilita a detecção de cliques
para interações dentro do jogo.
*/
