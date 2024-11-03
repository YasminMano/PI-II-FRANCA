// pause_menu.h
#ifndef PAUSE_MENU_H
#define PAUSE_MENU_H

#include "game.h"

void handle_pause_menu(AllegroGame* game, GameState* state);

#endif // PAUSE_MENU_H



/**
 * handle_pause_menu - Exibe o menu de pausa e lida com a escolha do jogador.
 *
 * Essa função pausa o jogo e exibe um menu que permite ao jogador escolher
 * entre voltar ao menu principal ou retornar à tela de mapa. Ela atualiza
 * o estado do jogo com base na escolha do jogador.
 *
 * Parâmetros:
 * - AllegroGame *game: ponteiro para a estrutura principal do jogo, contendo
 *   o display, fila de eventos, fontes, etc.
 * - GameState *state: ponteiro para o estado atual do jogo, que será modificado
 *   conforme a escolha do jogador no menu de pausa.
 */