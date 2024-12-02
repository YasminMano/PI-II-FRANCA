#include <stdio.h>
#include "screens.h"  // Inclui as definições de funções e estruturas relacionadas às telas
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include "handle.h"  // Para o controle de eventos e transição de telas

// Função para desenhar a tela inicial do menu
bool drawTelaInicio(struct AllegroGame* game) {
    // Carrega a imagem de fundo da tela de início
    ALLEGRO_BITMAP* bitmap = al_load_bitmap("assets/images/telainicio.png");
    if (!bitmap) {
        // Se houver erro ao carregar a imagem, exibe uma mensagem de erro e retorna false
        fprintf(stderr, "Falha ao carregar telainicio.png\n");
        return false;
    }

    // Desenha a imagem de fundo na tela
    al_draw_bitmap(bitmap, 0, 0, 0);

    // Lida com transição de estado: verifica se a tecla ENTER foi pressionada
    if (game->event.type == ALLEGRO_EVENT_KEY_DOWN && game->event.keyboard.keycode == ALLEGRO_KEY_ENTER) {
        game_state = MAPA;  // Transição para o estado MAPA
    }

    // Libera a memória ocupada pela imagem
    al_destroy_bitmap(bitmap);
    return true;  // Indica que a tela foi desenhada corretamente
}

// Função para desenhar a tela da Fase 1 do jogo
bool drawFase1(struct AllegroGame* game) {
    // Carrega a imagem de fundo da Fase 1
    ALLEGRO_BITMAP* bitmap = al_load_bitmap("assets/images/cenario1.png");
    if (!bitmap) {
        // Se houver erro ao carregar a imagem, exibe uma mensagem de erro e retorna false
        fprintf(stderr, "Falha ao carregar cenario1.png\n");
        return false;
    }

    // Desenha a imagem de fundo na tela
    al_draw_bitmap(bitmap, 0, 0, 0);

    // Lida com transição de estado: verifica se a tecla ENTER foi pressionada
    if (game->event.type == ALLEGRO_EVENT_KEY_DOWN && game->event.keyboard.keycode == ALLEGRO_KEY_ENTER) {
        game_state = FASE_2;  // Transição para o estado FASE_2
    }

    // Libera a memória ocupada pela imagem
    al_destroy_bitmap(bitmap);
    return true;  // Indica que a tela foi desenhada corretamente
}

// Função para desenhar a tela da Fase 2 do jogo
bool drawFase2(struct AllegroGame* game) {
    // Carrega a imagem de fundo da Fase 2
    ALLEGRO_BITMAP* bitmap = al_load_bitmap("assets/images/cenario2.png");  // Certifique-se de que esse arquivo exista no caminho correto
    if (!bitmap) {
        // Se houver erro ao carregar a imagem, exibe uma mensagem de erro e retorna false
        fprintf(stderr, "Falha ao carregar cenario2.png\n");
        return false;
    }

    // Desenha a imagem de fundo na tela
    al_draw_bitmap(bitmap, 0, 0, 0);

    // Libera a memória ocupada pela imagem
    al_destroy_bitmap(bitmap);
    return true;  // Indica que a tela foi desenhada corretamente
}

/*
Resumo:
O arquivo screens.c foi ajustado para usar a variável global game_state em vez de um ponteiro para GameState.
As transições de estado agora utilizam game_state diretamente, mantendo consistência com o restante do projeto.
*/
