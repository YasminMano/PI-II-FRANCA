#ifndef GAME_H  // Previne que o arquivo seja incluído mais de uma vez

#define GAME_H

#include <allegro5/allegro.h>        // Inclui as funções principais da biblioteca Allegro
#include <allegro5/allegro_font.h>   // Inclui as funções de manipulação de fontes no Allegro

// Enum que define os possíveis estados do jogo
typedef enum {
    MENU,         // Menu principal do jogo
    RESUMO,       // Tela de resumo
    MAPA,        // Tela do mapa
    FASE_1,       // Primeira fase do jogo
    FASE_2,       // Segunda fase do jogo
    FASE_3,       // Terceira fase do jogo
    CONFIG,       // Tela de configurações
    GAME,         // Estado de jogo ativo
    TELA_INICIO   // Tela de início do jogo
} GameState;     // Nome do tipo que representa os estados do jogo

// Estrutura que contém todas as informações necessárias para gerenciar o jogo
typedef struct AllegroGame {
    ALLEGRO_DISPLAY *display;          // Janela do jogo
    ALLEGRO_EVENT_QUEUE *queue;        // Fila de eventos (teclado, mouse, etc.)
    ALLEGRO_TIMER *timer;              // Controlador de tempo do jogo
    ALLEGRO_FONT *font;                // Fonte principal
    ALLEGRO_FONT *font_small;          // Fonte menor
    ALLEGRO_FONT *font_big;            // Fonte maior
    ALLEGRO_EVENT event;               // Estrutura para armazenar eventos
    ALLEGRO_MOUSE_STATE *mouse_state;  // Estado atual do mouse
    bool is_mouse_pressed;             // Indica se o mouse está pressionado
    bool was_mouse_pressed;            // Indica se o mouse estava pressionado anteriormente
    bool is_sound;                     // Indica se o som está ativado
} AllegroGame;  // Nome da estrutura que armazena todos os elementos essenciais do jogo

#endif  // Fim da verificação de inclusão múltipla

// Resumo:
// O arquivo `game.h` define dois elementos importantes: 
// 1. O enum `GameState`, que lista todos os estados possíveis do jogo (menu, fases, etc.).
// 2. A estrutura `AllegroGame`, que agrupa todos os elementos do Allegro (display, eventos, fontes, etc.) necessários para o funcionamento do jogo.
