#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <stdio.h>
#include "game.h"
#include "pause_menu.h"
#include "headers/Tela_inicio.h" // Inclui a função para inicializar a tela de menu

// Declaração da função de iniciar a fase 1
void iniciar_fase_1(ALLEGRO_DISPLAY* display);

int main() {
    if (!al_init()) {
        printf("Erro ao inicializar Allegro!\n");
        return -1;
    }

    al_init_image_addon();
    al_install_mouse();
    al_install_keyboard();
    al_init_primitives_addon();

    al_set_new_display_flags(ALLEGRO_FULLSCREEN);
    ALLEGRO_DISPLAY* display = al_create_display(1280, 720);
    if (!display) {
        printf("Erro ao criar o display!\n");
        return -1;
    }

    al_set_window_title(display, "A Revolucao Francesa");

    ALLEGRO_EVENT_QUEUE* event_queue = al_create_event_queue();
    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_keyboard_event_source());

    ALLEGRO_BITMAP* background = al_load_bitmap("assets/images/telainicio.png");
    if (!background) {
        printf("Erro ao carregar a imagem de fundo!\n");
        al_destroy_display(display);
        return -1;
    }

    // Configuração inicial do estado do jogo e estrutura AllegroGame
    GameState state = MENU;
    AllegroGame game = { display, event_queue, NULL, NULL, NULL, NULL, {0}, NULL, false, false, true };

    bool running = true;
    while (running) {
        ALLEGRO_EVENT event;
        al_wait_for_event(event_queue, &event);

        // Fecha o jogo ao fechar a janela
        if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
            running = false;
            break;
        }

        // Processa eventos de teclado
        if (event.type == ALLEGRO_EVENT_KEY_DOWN) {
            if (event.keyboard.keycode == ALLEGRO_KEY_ESCAPE) {
                printf("ESC foi pressionado no jogo - entrando no menu de pausa\n"); // Depuração

                // Entra no menu de pausa se estiver em uma fase ativa
                if (state == FASE_1 || state == FASE_2 || state == FASE_3) {
                    handle_pause_menu(&game, &state);
                    printf("Estado atual após pausa: %d\n", state); // Depuração
                }
            }
        };

        // Controle de estados do jogo
        switch (state) {
        case MENU:
            iniciar_tela_menu(display, background);
            state = MAPA;
            break;

        case MAPA:
            iniciar_fase_1(display);
            state = FASE_1;
            break;

        case FASE_1:
            // Aqui estaria o código específico da fase 1
            break;

        case FASE_2:
            // Aqui estaria o código específico da fase 2
            break;

        case FASE_3:
            // Aqui estaria o código específico da fase 3
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
    al_destroy_event_queue(event_queue);

    return 0;
}
