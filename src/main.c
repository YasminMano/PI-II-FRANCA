#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <stdio.h>
#include "headers/game.h"
#include "headers/Tela_inicio.h"
#include "headers/resumo_fase.h"
#include "headers/fases.h"

// Variável global que define o estado do jogo
GameState game_state = TELA_INICIO;

int main() {
    if (!al_init()) {
        printf("Erro ao inicializar Allegro!\n");
        return -1;
    }
    // Inicializa os addons necessários
    al_init_image_addon();
    al_install_mouse();
    al_install_keyboard();
    al_init_primitives_addon();

    // Criação do display
    ALLEGRO_DISPLAY* display = al_create_display(1280, 720);
    if (!display) {
        printf("Erro ao criar o display!\n");
        return -1;
    }

    al_set_window_title(display, "A Revolução Francesa");

    // Criação da fila de eventos
    ALLEGRO_EVENT_QUEUE* event_queue = al_create_event_queue();
    if (!event_queue) {
        printf("Erro ao criar a fila de eventos!\n");
        al_destroy_display(display);
        return -1;
    }

    // Registra as fontes de eventos
    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_mouse_event_source());

    // Carrega a imagem de fundo do menu inicial
    ALLEGRO_BITMAP* background = al_load_bitmap("assets/images/telainicio.png");
    if (!background) {
        printf("Erro ao carregar a imagem de fundo!\n");
        al_destroy_event_queue(event_queue);
        al_destroy_display(display);
        return -1;
    }

    bool running = true;

    // Loop principal do jogo
    while (running) {
        switch (game_state) {
            case TELA_INICIO:
                iniciar_tela_menu(display, background, &game_state, event_queue);
                break;

            case MAPA:
                init_mapa(event_queue);  // Certifique-se de passar a fila de eventos
                while (game_state == MAPA) {
                    ALLEGRO_EVENT event;
                    al_wait_for_event(event_queue, &event);
                    draw_mapa();
                    handle_mapa_event(event, &game_state);
                    al_flip_display();
                }
                destroy_mapa();
                break;

            case RESUMO:
                iniciar_resumo(display, &game_state);
                game_state = TELA_INICIO;
                break;

            case FASE_1:
                iniciar_fase_1(display, &game_state);
                break;

            case FASE_2:
                iniciar_fase_2(display, &game_state);
                break;

            case FASE_2_3:
                iniciar_fase_2_3(display, &game_state);
                break;

            case CORREDOR:
                corredor(display, &game_state);
                break;

            case QUARTO:
                quarto(display, &game_state);
                break;

            case QUARTO2:
                quarto2(display, &game_state);
                break;

            case BAU:
                bau(display, &game_state);
                break;

            case BANHEIRO:
                banheiro(display, &game_state);
                break;

            case FASE_3:
                iniciar_fase_3(display, &game_state);
                break;

            case PAUSE_MENU:
                exibir_menu_pausa(display, &game_state);
                break;

            case SAIR:
                running = false;
                break;

            default:
                printf("Estado desconhecido!\n");
                running = false;
                break;
        }
    }

    // Libera recursos
    al_destroy_bitmap(background);
    al_destroy_event_queue(event_queue);
    al_destroy_display(display);

    return 0;
}
