#ifndef HANDLE_H  // Previne que o arquivo seja incluído mais de uma vez
#define HANDLE_H

#include <stdbool.h>     // Inclui suporte para o tipo booleano (true/false)
#include "headers/game.h"        // Inclui game.h para acessar GameState e AllegroGame

// Função que lida com a lógica de transição entre as telas do jogo
bool handleScrens(struct AllegroGame* game);

#endif  // Fim da verificação de inclusão múltipla

// Resumo:
// O arquivo handle.h define a função handleScrens, que é responsável por gerenciar as transições entre os diferentes estados do jogo (como menu, fases, etc.). 
// Ele usa a estrutura AllegroGame e o enum GameState definidos em game.h para realizar essa tarefa.
