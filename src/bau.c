#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/keyboard.h>
#include <allegro5/keycodes.h>
#include "headers/game.h"

// Estrutura para o contexto do jogo
typedef struct {
    ALLEGRO_DISPLAY* display;
    ALLEGRO_TIMER* timer;
    ALLEGRO_EVENT_QUEUE* event_queue;
    ALLEGRO_BITMAP* background;
} Jogo_bau;

// Função para inicializar o jogo
void init_jogo_bau(Jogo_bau* jogo2) {
    al_init();
    al_install_keyboard();
    jogo2->timer = al_create_timer(1.0 / 30.0);// Cria um timer para controlar a taxa de atualização do jogo
    jogo2->background = al_load_bitmap("assets/images/final2.png");
    jogo2->event_queue = al_create_event_queue();
    al_register_event_source(jogo2->event_queue, al_get_display_event_source(jogo2->display));
    al_register_event_source(jogo2->event_queue, al_get_timer_event_source(jogo2->timer));
    al_register_event_source(jogo2->event_queue, al_get_keyboard_event_source());
    al_start_timer(jogo2->timer);
}

void bau(ALLEGRO_DISPLAY* display, GameState* game_state, int quartos, int numero_aleatorio) {
    Jogo_bau jogo2;
    jogo2.display = display;
    init_jogo_bau(&jogo2);

    bool running = true;// Indica se o loop do jogo está rodando

    if (numero_aleatorio % 2 == 0 && quartos==2) {
        jogo2.background = al_load_bitmap("assets/images/final1.png");
    }
    if (numero_aleatorio % 2 == 0 && quartos == 3) {
        jogo2.background = al_load_bitmap("assets/images/final3.png");
    }
    if (numero_aleatorio % 2 == 1 && quartos == 3) {
        jogo2.background = al_load_bitmap("assets/images/final4.png");
    }

    while (running) {
        ALLEGRO_EVENT event;
        al_wait_for_event(jogo2.event_queue, &event);// Espera por um evento (teclado, timer, etc.)

        if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {// Se o usuário fechar a janela, encerra o jogo
            running = false;
        }

        if (event.type == ALLEGRO_EVENT_KEY_DOWN) {  // Detecta quando uma tecla é pressionada
            if (event.keyboard.keycode == ALLEGRO_KEY_SPACE && numero_aleatorio % 2 == 0) {
                iniciar_fase_2(display, &game_state);
                running = false;
            }
            if (event.keyboard.keycode == ALLEGRO_KEY_SPACE && quartos==1) {
                quarto(display, &game_state);
                running = false;
            }
            if (event.keyboard.keycode == ALLEGRO_KEY_SPACE && quartos == 2) {
                quarto2(display, &game_state);
                running = false;
            }
            if (event.keyboard.keycode == ALLEGRO_KEY_SPACE && quartos == 3) {
                banheiro(display, &game_state, numero_aleatorio);
                running = false;
            }
        }
        // Limpa a tela e desenha o cenário e o personagem
        al_clear_to_color(al_map_rgb(255, 255, 255));
        al_draw_scaled_bitmap(jogo2.background, 0, 0, al_get_bitmap_width(jogo2.background),
            al_get_bitmap_height(jogo2.background), 0, 0,
            al_get_display_width(display), al_get_display_height(display), 0);
        al_flip_display();// Atualiza a tela
        printf("%d\n", numero_aleatorio);
    }

    // Destrói os recursos após o fim do jogo
    al_destroy_bitmap(jogo2.background);
    al_destroy_timer(jogo2.timer);
    al_destroy_event_queue(jogo2.event_queue);
}