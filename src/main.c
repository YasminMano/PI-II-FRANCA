#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <stdio.h>
#include "game.h"
#include "Tela_inicio.h"
#include "resumo_fase.h"

// Declaração da função de iniciar as fases
void iniciar_fase_1(ALLEGRO_DISPLAY* display);
void iniciar_fase_2(ALLEGRO_DISPLAY* display);
void iniciar_fase_3(ALLEGRO_DISPLAY* display);

int main() {
    if (!al_init()) {
        printf("Erro ao inicializar Allegro!\n");
        return -1;
    }

    al_init_image_addon();
    al_install_mouse();
    al_install_keyboard();
    al_init_primitives_addon();

    // al_set_new_display_flags(ALLEGRO_FULLSCREEN);
    ALLEGRO_DISPLAY* display = al_create_display(1280, 720);
    if (!display) {
        printf("Erro ao criar o display!\n");
        return -1;
    }

    al_set_window_title(display, "A Revolução Francesa");

    AllegroGame game;
    game.display = display;
    game.queue = al_create_event_queue();
    al_register_event_source(game.queue, al_get_display_event_source(display));
    al_register_event_source(game.queue, al_get_keyboard_event_source());

    ALLEGRO_BITMAP* background = al_load_bitmap("assets/images/telainicio.png");
    if (!background) {
        printf("Erro ao carregar a imagem de fundo!\n");
        al_destroy_display(display);
        return -1;
    }

    // Configuração inicial do estado do jogo
    GameState state = MENU;

    bool running = true;
    while (running) {
        ALLEGRO_EVENT event;
        al_wait_for_event(game.queue, &event);

        // Fecha o jogo ao fechar a janela
        if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
            running = false;
            break;
        }

        // Processa eventos de teclado
        if (event.type == ALLEGRO_EVENT_KEY_DOWN) {
            if (event.keyboard.keycode == ALLEGRO_KEY_ESCAPE) {
                printf("ESC foi pressionado - mas o menu de pausa não está implementado.\n");
                // Menu de pausa desativado temporariamente
            }
        }

        // Controle de estados do jogo
        switch (state) {
        case MENU:
            iniciar_tela_menu(display, background);
            state = MAPA;
            break;

        case MAPA:
            // Inicializa o mapa e aguarda a seleção de uma fase
            init_mapa();
            while (state == MAPA) {
                al_wait_for_event(game.queue, &event);
                draw_mapa();
                handle_mapa_event(event, &state); // Pode mudar para RESUMO ou outras fases
                al_flip_display();
            }
            destroy_mapa();
            break;

        case RESUMO:
            // Exibe a tela de resumo da Fase 1
            init_resumo_fase_1(display, &state);
            state = FASE_1; // Após o resumo, inicia a Fase 1
            break;
        case RESUMO_2:
            // Exibe a tela de resumo da Fase 2
            init_resumo_fase_2(display, &state);
            state = FASE_1; // Após o resumo, inicia a Fase 1
            break;

        case RESUMO_3:
            // Exibe a tela de resumo da Fase 3
            init_resumo_fase_3(display, &state);
            state = FASE_1; // Após o resumo, inicia a Fase 1
            break;

        case FASE_1:
            iniciar_fase_1(display);
            state = MAPA; // Volta para o mapa após a Fase 1
            break;

        case FASE_2:
            iniciar_fase_2(display);
            state = MAPA; // Volta para o mapa após a Fase 2
            break;

        case FASE_3:
            iniciar_fase_3(display);
            state = MAPA; // Volta para o mapa após a Fase 3
            break;

        default:
            break;
        }

        // Atualiza o display após cada loop para refletir alterações na tela
        al_flip_display();
    }

    // Liberação dos recursos
    al_destroy_bitmap(background);
    al_destroy_display(display);
    al_destroy_event_queue(game.queue);

    return 0;
}
