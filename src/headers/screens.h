#ifndef SCREENS_H
#define SCREENS_H

#include "game.h"  // Incluindo game.h para usar GameState e AllegroGame

// Função que desenha a tela de início (menu principal) do jogo.
// Ela utiliza a estrutura AllegroGame para acessar as informações do display e eventos,
// além de usar o GameState para gerenciar as transições de estado.
bool drawTelaInicio(struct AllegroGame *game, GameState *gameState);

// Função que desenha a primeira fase do jogo.
// Ela recebe a estrutura AllegroGame, que contém as informações necessárias
// para renderizar a fase no display.
bool drawFase1(struct AllegroGame *game);

// Função que desenha a segunda fase do jogo.
// Similar à função anterior, ela usa a estrutura AllegroGame para manipular o display e outros componentes.
bool drawFase2(struct AllegroGame *game);

#endif

/*
Resumo:
O arquivo `screens.h` declara as funções responsáveis por desenhar diferentes telas no jogo, como a tela de início (menu), 
a primeira e a segunda fase. Cada função usa a estrutura AllegroGame para acessar componentes importantes do Allegro, 
como o display e os eventos, e o GameState para controlar o fluxo entre as diferentes telas do jogo.
*/
