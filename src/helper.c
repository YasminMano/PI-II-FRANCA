#include "headers/helper.h"
#include <allegro5/allegro.h>

// Função auxiliar que verifica o clique do mouse
void checkMouseClick(struct AllegroGame* game, bool* last_mouse_pressed, bool* last_was_mouse_pressed) {
    ALLEGRO_MOUSE_STATE mouse_state;
    al_get_mouse_state(&mouse_state);  // Obtém o estado atual do mouse

    // Verifica se o botão esquerdo do mouse foi pressionado
    game->is_mouse_pressed = mouse_state.buttons & 1;

    // Verifica se o botão do mouse foi liberado (clicado e solto)
    game->was_mouse_pressed = *last_mouse_pressed && !game->is_mouse_pressed;

    // Atualiza os estados anteriores
    *last_mouse_pressed = game->is_mouse_pressed;
    *last_was_mouse_pressed = game->was_mouse_pressed;
}
