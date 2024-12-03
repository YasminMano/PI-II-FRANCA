#ifndef SCREENS_H
#define SCREENS_H

#include "game.h"  // Incluindo game.h para usar GameState e AllegroGame

// Função que desenha a tela de início (menu principal) do jogo.
// Utiliza a estrutura AllegroGame para acessar as informações do display e eventos.
bool drawTelaInicio(struct AllegroGame* game);

// Função que desenha a primeira fase do jogo.
// Utiliza a estrutura AllegroGame para renderizar a fase no display.
bool drawFase1(struct AllegroGame* game);

// Função que desenha a segunda fase do jogo.
// Similar à função anterior, ela usa a estrutura AllegroGame para manipular o display e outros componentes.
bool drawFase2(struct AllegroGame* game);

#endif

/*
Resumo:
O arquivo `screens.h` declara as funções responsáveis por desenhar diferentes telas no jogo, como a tela de início (menu),
a primeira e a segunda fase. Essas funções agora utilizam diretamente a variável global `game_state` em vez de receber
um ponteiro para GameState.
*/
