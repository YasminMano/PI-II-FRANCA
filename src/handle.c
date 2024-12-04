#include "headers/handle.h"
#include "headers/screens.h"
#include "headers/helper.h"
#include "headers/mapa.h"  // Adicionado para incluir as funções do mapa

// Função que gerencia as transições de telas e estados do jogo
bool handleScrens(struct AllegroGame* game) {
    bool redraw = true;  // Variável para controlar se a tela precisa ser redesenhada

    // Se o evento for do tipo TIMER, a tela precisa ser redesenhada
    if (game->event.type == ALLEGRO_EVENT_TIMER)
        redraw = true;
    // Se o evento for de fechamento da janela, retorna false e encerra o jogo
    else if (game->event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
        return false;

    // Lida com eventos de pressionamento de teclas
    if (game->event.type == ALLEGRO_EVENT_KEY_DOWN) {
        // Se a tecla ESC for pressionada, volta ao MENU se não estiver nele
        if (game->event.keyboard.keycode == ALLEGRO_KEY_ESCAPE) {
            if (game_state != TELA_INICIO) {
                game_state = TELA_INICIO;
            }
        }
    }

    // Se a tela precisa ser redesenhada e não há outros eventos na fila
    if (redraw && al_is_event_queue_empty(game->queue)) {
        // Limpa a tela para preto
        al_clear_to_color(al_map_rgb(0, 0, 0));

        // Verifica o estado atual do jogo e desenha a tela correspondente
        switch (game_state) {
        case TELA_INICIO:
             // Desenha a tela inicial e, se a tecla ENTER for pressionada, vai para a FASE_1
            if (!drawTelaInicio(game)) return false;
            if (game->event.type == ALLEGRO_EVENT_KEY_DOWN && game->event.keyboard.keycode == ALLEGRO_KEY_ENTER) {
                game_state = FASE_1;
            }
            break;
        case MAPA:
            // Desenha a tela do mapa e verifica cliques nos botões
            draw_mapa();
            handle_mapa_event(game->event, &game_state);
            break;
        case FASE_1:
            // Desenha a fase 1 e, se ENTER for pressionado, vai para a FASE_2
            if (!drawFase1(game)) return false;
            if (game->event.type == ALLEGRO_EVENT_KEY_DOWN && game->event.keyboard.keycode == ALLEGRO_KEY_ENTER) {
                game_state = FASE_2;
            }
            break;
        case FASE_2:
            // Desenha a fase 2
            if (!drawFase2(game)) return false;
            break;
        default:
            break;
        }

        // Atualiza o display com o conteúdo desenhado
        al_flip_display();
    }

    return true;  // Continua executando o jogo
}
