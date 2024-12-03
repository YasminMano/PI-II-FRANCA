#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/keyboard.h>
#include <allegro5/keycodes.h>
#include "headers/game.h"

// Estrutura para o jogador
typedef struct {
    ALLEGRO_BITMAP* sprite_sheet;
    int pos_x, pos_y;
    int initial_pos_y;
    int frame_width, frame_height;
    int current_frame;
    float scale_factor;
    bool facing_right;
    bool jumping;
    bool knocked_back;
    float knockback_velocity;
    float jump_velocity;
    float gravity;
    bool move_left, move_right, moving;
    float movement_speed;
    float frame_time, frame_timer;
    int total_moving_frames;
    int vidas;
} Jogador_corredor;

// Função para inicializar o jogador
void init_jogador_corredor(Jogador_corredor* jogador2, int display_height) {
    jogador2->sprite_sheet = al_load_bitmap("assets/images/mulher.png");
    jogador2->frame_width = 136;// Largura de cada frame do personagem
    jogador2->frame_height = 250;// Altura de cada frame do personagem
    jogador2->pos_x = 50;// Posição X inicial
    jogador2->scale_factor = 0.9;// Escala do personagem ajustada
    jogador2->pos_y = display_height - jogador2->frame_height * jogador2->scale_factor - 40;// Ajuste para que o personagem toque o chão
    jogador2->initial_pos_y = jogador2->pos_y;// Armazena a posição inicial do personagem para controlar o pulo
    jogador2->jump_velocity = -15.0f;// Velocidade inicial do pulo
    jogador2->gravity = 0.7f;// Gravidade para desacelerar o pulo
    jogador2->movement_speed = 5.0;// Velocidade de movimento
    jogador2->frame_time = 0.2;// Tempo de cada frame
    jogador2->frame_timer = 0;
    jogador2->total_moving_frames = 3;// Total de frames da animação (3 por linha)
    jogador2->current_frame = 0;// Frame atual
    jogador2->facing_right = true;// Indica a direção que o personagem está virado
    jogador2->jumping = false;// Indica se o personagem está pulando
    jogador2->move_left = false;// Indica se o personagem está se movendo para a esquerda
    jogador2->move_right = false;// Indica se o personagem está se movendo para a direita
    jogador2->moving = false;// Indica se o personagem está se movendo
    jogador2->knocked_back = false;
    jogador2->knockback_velocity = 0;
    jogador2->vidas = 3;
}

// Estrutura para o contexto do jogo
typedef struct {
    ALLEGRO_DISPLAY* display;
    ALLEGRO_TIMER* timer;
    ALLEGRO_EVENT_QUEUE* event_queue;
    ALLEGRO_BITMAP* background;
} Jogo_corredor;

// Função para inicializar o jogo
void init_jogo_corredor(Jogo_corredor* jogo2) {
    al_init();
    al_install_keyboard();
    jogo2->timer = al_create_timer(1.0 / 30.0);// Cria um timer para controlar a taxa de atualização do jogo
    jogo2->background = al_load_bitmap("assets/images/caminho.png");
    jogo2->event_queue = al_create_event_queue();
    al_register_event_source(jogo2->event_queue, al_get_display_event_source(jogo2->display));
    al_register_event_source(jogo2->event_queue, al_get_timer_event_source(jogo2->timer));
    al_register_event_source(jogo2->event_queue, al_get_keyboard_event_source());
    al_start_timer(jogo2->timer);
}

// Função que desenha o jogador
static void desenha_jogador_corredor(Jogador_corredor* jogador2) {
    int frame_x[] = { 0, 213, 346 };
    int frame_cx = frame_x[jogador2->current_frame];
    int frame_cy = 0;

    al_draw_scaled_bitmap(
        jogador2->sprite_sheet,
        frame_cx, frame_cy,
        jogador2->frame_width, jogador2->frame_height,
        jogador2->pos_x, jogador2->pos_y,
        jogador2->frame_width * jogador2->scale_factor,
        jogador2->frame_height * jogador2->scale_factor,
        jogador2->facing_right ? 0 : ALLEGRO_FLIP_HORIZONTAL
    );
}
int z = 0;
void corredor(ALLEGRO_DISPLAY* display, GameState* game_state) {
    Jogo_corredor jogo2;
    jogo2.display = display;
    init_jogo_corredor(&jogo2);

    Jogador_corredor jogador2;
    init_jogador_corredor(&jogador2, al_get_display_height(display));

    jogo2.background = al_load_bitmap("assets/images/corredor.png");

    if (z == 1) {
        jogador2.pos_x = 135;
    }
    else if (z == 2) {
        jogador2.pos_x = 610;
    }
    else if (z == 3) {
        jogador2.pos_x = 1090;
    }

    bool running = true;  // Indica se o loop do jogo está rodando

    // Loop principal do jogo
    while (running) {
        ALLEGRO_EVENT event;
        al_wait_for_event(jogo2.event_queue, &event);// Espera por um evento (teclado, timer, etc.)

        if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {// Se o usuário fechar a janela, encerra o jogo
            running = false;
        }

        if (event.type == ALLEGRO_EVENT_KEY_DOWN) {// Detecta quando uma tecla é pressionada
            if (!jogador2.knocked_back) {
                if (event.keyboard.keycode == ALLEGRO_KEY_D) {// Move para a direita
                    jogador2.move_right = true;
                    jogador2.facing_right = true;
                    jogador2.moving = true;
                }
                else if (event.keyboard.keycode == ALLEGRO_KEY_A) {// Move para a esquerda
                    jogador2.move_left = true;
                    jogador2.facing_right = false;
                    jogador2.moving = true;
                }
                else if (event.keyboard.keycode == ALLEGRO_KEY_SPACE && !jogador2.jumping) {// Pulo
                    jogador2.jumping = true;
                }
                // F muda a tela
                else if (event.keyboard.keycode == ALLEGRO_KEY_F && jogador2.pos_x >= 60 && jogador2.pos_x <= 215) {
                    z = 1; 
                    quarto(display, &game_state);
                    running = false;
                }
                else if (event.keyboard.keycode == ALLEGRO_KEY_F && jogador2.pos_x >= 555 && jogador2.pos_x <= 670) {
                    z = 2;
                    quarto(display, &game_state);
                    running = false;
                }
                else if (event.keyboard.keycode == ALLEGRO_KEY_F && jogador2.pos_x >= 1015 && jogador2.pos_x <= 1160) {
                    z = 3;
                    quarto(display, &game_state);
                    running = false;
                }
            }
        }
        else if (event.type == ALLEGRO_EVENT_KEY_UP) {// Detecta quando uma tecla é solta
            if (event.keyboard.keycode == ALLEGRO_KEY_D) {// Para de se mover para a direita
                jogador2.move_right = false;
                if (!jogador2.move_left) jogador2.moving = false;
            }
            else if (event.keyboard.keycode == ALLEGRO_KEY_A) {// Para de se mover para a esquerda
                jogador2.move_left = false;
                if (!jogador2.move_right) jogador2.moving = false;
            }
        }

        // Movimento horizontal
        if (!jogador2.knocked_back) {
            if (jogador2.move_right) jogador2.pos_x += jogador2.movement_speed;
            if (jogador2.move_left) jogador2.pos_x -= jogador2.movement_speed;
        }

        // Lógica de pulo
        if (jogador2.jumping) {
            jogador2.pos_y += jogador2.jump_velocity;
            jogador2.jump_velocity += jogador2.gravity;
            if (jogador2.pos_y >= jogador2.initial_pos_y) {
                jogador2.pos_y = jogador2.initial_pos_y;
                jogador2.jumping = false;
                jogador2.jump_velocity = -10.0f;
            }
        }

        // Controle da animação do movimento
        if (jogador2.moving) {
            jogador2.frame_timer += 1.0 / 30.0;
            if (jogador2.frame_timer >= jogador2.frame_time) {
                jogador2.current_frame = (jogador2.current_frame + 1) % jogador2.total_moving_frames;
                jogador2.frame_timer = 0;
            }
        }
        else {
            jogador2.current_frame = 0;// Se não estiver se movendo, exibe o primeiro frame
        }

        if (jogador2.knocked_back) {
            if (jogador2.facing_right) {
                jogador2.pos_x -= jogador2.knockback_velocity;
            }
            else {
                jogador2.pos_x += jogador2.knockback_velocity;
            }
            jogador2.pos_y += jogador2.jump_velocity;
            jogador2.knockback_velocity -= 0.2f;
            jogador2.jump_velocity += jogador2.gravity;

            if (jogador2.pos_y >= jogador2.initial_pos_y) {
                jogador2.pos_y = jogador2.initial_pos_y;
                jogador2.knocked_back = false;
                jogador2.jump_velocity = -10.0f;
            }
        }

        if (jogador2.pos_x > 1180) {
            jogador2.move_right = false;
        }
        if (jogador2.pos_x < 0) {
            jogador2.move_left = false;
        }

        // Limpa a tela e desenha o cenário e o personagem
        al_clear_to_color(al_map_rgb(255, 255, 255));
        al_draw_scaled_bitmap(jogo2.background, 0, 0, al_get_bitmap_width(jogo2.background),
            al_get_bitmap_height(jogo2.background), 0, 0,
            al_get_display_width(display), al_get_display_height(display), 0);

        // Desenha o personagem na direção correta com ajuste de escala
        desenha_jogador_corredor(&jogador2);
        al_flip_display();// Atualiza a tela
        printf("%d\n", z);
    }
    // Destrói os recursos após o fim do jogo
    al_destroy_bitmap(jogo2.background);
    al_destroy_bitmap(jogador2.sprite_sheet);
    al_destroy_timer(jogo2.timer);
    al_destroy_event_queue(jogo2.event_queue);
}
