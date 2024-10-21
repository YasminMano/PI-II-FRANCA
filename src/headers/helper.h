#ifndef HELPER_H
#define HELPER_H

#include <allegro5/allegro.h>
#include "screens.h"

// Função que verifica se o mouse está sobre um texto específico.
// Ela usa a posição do mouse, as coordenadas do texto e a fonte para determinar isso.
bool isMouseOverText(ALLEGRO_MOUSE_STATE *mouse_state, int text_x, int text_y, const char *text, ALLEGRO_FONT *font);

// Função que verifica se o mouse está sobre uma área retangular (box) específica.
// Ela usa a posição do mouse e as coordenadas/dimensões da caixa.
bool isMouseOverBox(ALLEGRO_MOUSE_STATE *mouse_state, int box_x, int box_y, int box_width, int box_height);

// Função que verifica o estado do clique do mouse.
// Ela registra se o botão do mouse foi pressionado e se foi liberado.
void checkMouseClick(struct AllegroGame *game, bool *last_mouse_pressed, bool *last_was_mouse_pressed);

#endif

/*
Resumo:
O arquivo `helper.h` declara funções auxiliares usadas para verificar a interação do mouse no jogo. 
Essas funções ajudam a determinar se o mouse está sobre um texto ou uma área (caixa) e controlam o estado do clique do mouse. 
Elas são utilizadas para facilitar a implementação de elementos interativos, como botões e áreas clicáveis.
*/
