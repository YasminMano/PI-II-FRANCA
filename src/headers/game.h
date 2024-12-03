#ifndef GAME_H
#define GAME_H

#include <allegro5/allegro.h>        // Inclui as funções principais da biblioteca Allegro
#include <allegro5/allegro_font.h>   // Inclui as funções de manipulação de fontes no Allegro

// Enum que define os possíveis estados do jogo
typedef enum {
    TELA_INICIO,  // Tela inicial do jogo (menu principal)
    RESUMO,       // Tela de resumo inicial
    RESUMO_1,     // Resumo da Fase 1
    RESUMO_2,     // Resumo da Fase 2
    RESUMO_3,     // Resumo da Fase 3
    MAPA,         // Tela do mapa
    FASE_1,       // Primeira fase do jogo
    FASE_2,       // Segunda fase do jogo
    FASE_3,       // Terceira fase do jogo
    PAUSE_MENU,   // Tela de pausa
    SAIR          // Estado para encerrar o jogo
} GameState;

// Estrutura que contém todas as informações necessárias para gerenciar o jogo
typedef struct AllegroGame {
    ALLEGRO_DISPLAY* display;          // Janela do jogo
    ALLEGRO_EVENT_QUEUE* queue;        // Fila de eventos (teclado, mouse, etc.)
    ALLEGRO_TIMER* timer;              // Controlador de tempo do jogo
    ALLEGRO_FONT* font;                // Fonte principal
    ALLEGRO_FONT* font_small;          // Fonte menor
    ALLEGRO_FONT* font_big;            // Fonte maior
    ALLEGRO_EVENT event;               // Estrutura para armazenar eventos
    ALLEGRO_MOUSE_STATE* mouse_state;  // Estado atual do mouse
    bool is_mouse_pressed;             // Indica se o mouse está pressionado
    bool was_mouse_pressed;            // Indica se o mouse estava pressionado anteriormente
    bool is_sound;                     // Indica se o som está ativado
} AllegroGame;

// Declara a variável global que armazena o estado atual do jogo
extern GameState game_state;

#endif // GAME_H
