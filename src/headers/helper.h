#ifndef HELPER_H
#define HELPER_H

#include <stdbool.h>       // Para suporte ao tipo booleano (true/false)
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>  // Para manipulação de fontes no Allegro
#include "headers/game.h"          // Inclui AllegroGame para gerenciamento do jogo

// Verifica se o mouse está sobre um texto específico.
// Usa as coordenadas do texto, a fonte, e a posição do mouse para determinar.
bool isMouseOverText(ALLEGRO_MOUSE_STATE* mouse_state, int text_x, int text_y, const char* text, ALLEGRO_FONT* font);

// Verifica se o mouse está sobre uma área retangular (box) específica.
// Usa a posição do mouse e as coordenadas/dimensões da caixa.
bool isMouseOverBox(ALLEGRO_MOUSE_STATE* mouse_state, int box_x, int box_y, int box_width, int box_height);

// Verifica o estado do clique do mouse.
// Registra se o botão do mouse foi pressionado e se foi liberado.
void checkMouseClick(struct AllegroGame* game, bool* last_mouse_pressed, bool* last_was_mouse_pressed);

#endif // HELPER_H

/*
Resumo:
O arquivo helper.h declara funções auxiliares relacionadas à interação do mouse no jogo:
1. isMouseOverText: Verifica se o mouse está sobre um texto.
2. isMouseOverBox: Verifica se o mouse está sobre uma área retangular.
3. checkMouseClick: Controla o estado de cliques do mouse.
Essas funções facilitam a criação de interfaces interativas, como botões ou áreas clicáveis, no jogo.
*/
