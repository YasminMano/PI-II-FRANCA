#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/keyboard.h>
#include <allegro5/keycodes.h>
#include <stdio.h> // Para exibir mensagens

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
} Jogador;

// Estrutura para o guarda (inimigo)
typedef struct {
    ALLEGRO_BITMAP* sprite_sheet;
    int pos_x, pos_y;
    int frame_width, frame_height;
    float scale_factor;
    float movement_speed;
    bool move_right;
    int min_x, max_x;
    int current_frame;
    float frame_time, frame_timer;
    int total_frames;
    int frames_per_row;
} Guarda;

// Estrutura para o contexto do jogo
typedef struct {
    ALLEGRO_DISPLAY* display;
    ALLEGRO_TIMER* timer;
    ALLEGRO_EVENT_QUEUE* event_queue;
    ALLEGRO_BITMAP* background;
} Jogo;

// Função para inicializar o jogador
void init_jogador(Jogador* jogador, int display_height) {
    jogador->sprite_sheet = al_load_bitmap("assets/images/teste_personagem.png");
    jogador->frame_width = 265;
    jogador->frame_height = 376;
    jogador->pos_x = 50;
    jogador->scale_factor = 0.6;
    jogador->pos_y = display_height - jogador->frame_height * jogador->scale_factor;
    jogador->initial_pos_y = jogador->pos_y;
    jogador->jump_velocity = -10.0f;
<<<<<<< HEAD
<<<<<<< HEAD
    jogador->gravity = 0.4f;
=======
    jogador->gravity = 0.5f;
>>>>>>> 8bb8570 (corrigindo divergencias)
=======
    jogador->gravity = 0.5f;
>>>>>>> d19ad89 (Ajustado o tamanho da tela do jogo para full scream, ajustado também o pulo do persongame, o botão esc ainda não funciona)
    jogador->movement_speed = 2.0;
    jogador->frame_time = 0.2;
    jogador->frame_timer = 0;
    jogador->total_moving_frames = 3;
    jogador->current_frame = 0;
    jogador->facing_right = true;
    jogador->jumping = false;
    jogador->move_left = false;
    jogador->move_right = false;
    jogador->moving = false;
    jogador->knocked_back = false;
    jogador->knockback_velocity = 0;
    jogador->vidas = 3;
}

// Função para inicializar o guarda (inimigo)
void init_guarda(Guarda* guarda, int display_width, int display_height) {
    guarda->sprite_sheet = al_load_bitmap("assets/images/guarda.png");
<<<<<<< HEAD
<<<<<<< HEAD
    guarda->frame_width = 120;  // Largura de cada quadro do guarda
    guarda->frame_height = 170; // Altura de cada quadro do guarda
    guarda->scale_factor = 1.2; // Ajuste de escala para manter o tamanho proporcional
=======
    guarda->frame_width = 200;  // Largura de cada quadro do guarda
    guarda->frame_height = 200; // Altura de cada quadro do guarda
    guarda->scale_factor = 0.6; // Ajuste de escala para manter o tamanho proporcional
>>>>>>> 8bb8570 (corrigindo divergencias)
=======
    guarda->frame_width = 200;  // Largura de cada quadro do guarda
    guarda->frame_height = 200; // Altura de cada quadro do guarda
    guarda->scale_factor = 0.6; // Ajuste de escala para manter o tamanho proporcional
>>>>>>> d19ad89 (Ajustado o tamanho da tela do jogo para full scream, ajustado também o pulo do persongame, o botão esc ainda não funciona)
    guarda->pos_x = display_width - guarda->frame_width * guarda->scale_factor - 50;
    guarda->pos_y = display_height - guarda->frame_height * guarda->scale_factor;
    guarda->movement_speed =1.5;
    guarda->move_right = false;
    guarda->min_x = display_width - guarda->frame_width * guarda->scale_factor - 200;
    guarda->max_x = display_width - guarda->frame_width * guarda->scale_factor - 50;
    guarda->current_frame = 0;
<<<<<<< HEAD
<<<<<<< HEAD
    guarda->frame_time = 0.3;
=======
    guarda->frame_time = 0.2;
>>>>>>> 8bb8570 (corrigindo divergencias)
=======
    guarda->frame_time = 0.2;
>>>>>>> d19ad89 (Ajustado o tamanho da tela do jogo para full scream, ajustado também o pulo do persongame, o botão esc ainda não funciona)
    guarda->frame_timer = 0;
    guarda->total_frames = 6;    // Total de quadros (2 colunas x 3 linhas)
    guarda->frames_per_row = 2;  // Quantidade de quadros por linha
}

// Função para inicializar o jogo
void init_jogo(Jogo* jogo) {
    al_init();
    al_install_keyboard();
    jogo->timer = al_create_timer(1.0 / 30.0);
    jogo->background = al_load_bitmap("assets/images/cenario1.png");
    jogo->event_queue = al_create_event_queue();
    al_register_event_source(jogo->event_queue, al_get_display_event_source(jogo->display));
    al_register_event_source(jogo->event_queue, al_get_timer_event_source(jogo->timer));
    al_register_event_source(jogo->event_queue, al_get_keyboard_event_source());
    al_start_timer(jogo->timer);
}

// Função que desenha o jogador
void desenha_jogador(Jogador* jogador) {
    int frame_x[] = { 0, 265, 530 };
    int frame_y[] = { 0, 376 };
    int frame_cx = frame_x[jogador->current_frame];
    int frame_cy = frame_y[0];

    if (jogador->facing_right) {
        al_draw_scaled_bitmap(jogador->sprite_sheet, frame_cx, frame_cy, jogador->frame_width, jogador->frame_height, jogador->pos_x, jogador->pos_y, jogador->frame_width * jogador->scale_factor, jogador->frame_height * jogador->scale_factor, 0);
    }
    else {
        al_draw_scaled_bitmap(jogador->sprite_sheet, frame_cx, frame_cy, jogador->frame_width, jogador->frame_height, jogador->pos_x, jogador->pos_y, jogador->frame_width * jogador->scale_factor, jogador->frame_height * jogador->scale_factor, ALLEGRO_FLIP_HORIZONTAL);
    }
}

// Função que desenha o guarda (inimigo)
void desenha_guarda(Guarda* guarda) {
    // Calcula a posição do quadro atual no sprite sheet
    int frame_coluna = guarda->current_frame % guarda->frames_per_row;
<<<<<<< HEAD
<<<<<<< HEAD
    int frame_linha = guarda->current_frame / 3;
    int frame_x = frame_coluna * guarda->frame_width;
    int frame_y = frame_linha * guarda->frame_height;

    al_draw_scaled_bitmap(guarda->sprite_sheet, frame_x, frame_y, guarda->frame_width, guarda->frame_height, guarda->pos_x, guarda->pos_y, guarda->frame_width * guarda->scale_factor, guarda->frame_height * guarda->scale_factor, ALLEGRO_FLIP_HORIZONTAL);
=======
=======
>>>>>>> d19ad89 (Ajustado o tamanho da tela do jogo para full scream, ajustado também o pulo do persongame, o botão esc ainda não funciona)
    int frame_linha = guarda->current_frame / guarda->frames_per_row;
    int frame_x = frame_coluna * guarda->frame_width;
    int frame_y = frame_linha * guarda->frame_height;

    al_draw_scaled_bitmap(
        guarda->sprite_sheet,
        frame_x, frame_y, guarda->frame_width, guarda->frame_height,
        guarda->pos_x, guarda->pos_y,
        guarda->frame_width * guarda->scale_factor, guarda->frame_height * guarda->scale_factor,
        0
    );
<<<<<<< HEAD
>>>>>>> 8bb8570 (corrigindo divergencias)
=======
>>>>>>> d19ad89 (Ajustado o tamanho da tela do jogo para full scream, ajustado também o pulo do persongame, o botão esc ainda não funciona)
}

// Função para detectar colisão entre jogador e guarda
bool detectar_colisao(Jogador* jogador, Guarda* guarda) {
    int jogador_left = jogador->pos_x;
    int jogador_right = jogador->pos_x + jogador->frame_width * jogador->scale_factor;
    int jogador_top = jogador->pos_y;
    int jogador_bottom = jogador->pos_y + jogador->frame_height * jogador->scale_factor;

    int guarda_left = guarda->pos_x;
    int guarda_right = guarda->pos_x + guarda->frame_width * guarda->scale_factor;
    int guarda_top = guarda->pos_y;
    int guarda_bottom = guarda->pos_y + guarda->frame_height * guarda->scale_factor;

    if (jogador_right > guarda_left && jogador_left < guarda_right &&
        jogador_bottom > guarda_top && jogador_top < guarda_bottom) {
        return true;
    }
    return false;
}

// Função que inicia a fase 1 do jogo
void iniciar_fase_1(ALLEGRO_DISPLAY* display) {
    Jogo jogo;
    jogo.display = display;
    init_jogo(&jogo);

    Jogador jogador;
    init_jogador(&jogador, al_get_display_height(display));

    Guarda guarda;
    init_guarda(&guarda, al_get_display_width(display), al_get_display_height(display));

    bool running = true;

    while (running) {
        ALLEGRO_EVENT event;
        al_wait_for_event(jogo.event_queue, &event);

        if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
            running = false;
        }

        if (event.type == ALLEGRO_EVENT_KEY_DOWN) {
            if (!jogador.knocked_back) {
                if (event.keyboard.keycode == ALLEGRO_KEY_D) {
                    jogador.move_right = true;
                    jogador.facing_right = true;
                    jogador.moving = true;
                }
                else if (event.keyboard.keycode == ALLEGRO_KEY_A) {
                    jogador.move_left = true;
                    jogador.facing_right = false;
                    jogador.moving = true;
                }
                else if (event.keyboard.keycode == ALLEGRO_KEY_SPACE && !jogador.jumping) {
                    jogador.jumping = true;
                }
            }
        }
        else if (event.type == ALLEGRO_EVENT_KEY_UP) {
            if (event.keyboard.keycode == ALLEGRO_KEY_D) {
                jogador.move_right = false;
                if (!jogador.move_left) jogador.moving = false;
            }
            else if (event.keyboard.keycode == ALLEGRO_KEY_A) {
                jogador.move_left = false;
                if (!jogador.move_right) jogador.moving = false;
            }
        }

        if (!jogador.knocked_back) {
            if (jogador.move_right) jogador.pos_x += jogador.movement_speed;
            if (jogador.move_left) jogador.pos_x -= jogador.movement_speed;
        }

        if (jogador.jumping) {
            jogador.pos_y += jogador.jump_velocity;
            jogador.jump_velocity += jogador.gravity;
            if (jogador.pos_y >= jogador.initial_pos_y) {
                jogador.pos_y = jogador.initial_pos_y;
                jogador.jumping = false;
                jogador.jump_velocity = -10.0f;
            }
        }

        if (jogador.moving) {
            jogador.frame_timer += 1.0 / 30.0;
            if (jogador.frame_timer >= jogador.frame_time) {
                jogador.current_frame = (jogador.current_frame + 1) % jogador.total_moving_frames;
                jogador.frame_timer = 0;
            }
        }
        else {
            jogador.current_frame = 0;
        }

        if (guarda.move_right) {
            guarda.pos_x += guarda.movement_speed;
            if (guarda.pos_x >= guarda.max_x) {
                guarda.move_right = false;
            }
        }
        else {
            guarda.pos_x -= guarda.movement_speed;
            if (guarda.pos_x <= guarda.min_x) {
                guarda.move_right = true;
            }
        }

        if (detectar_colisao(&jogador, &guarda)) {
            printf("Colisão detectada!\n");
            jogador.knocked_back = true;
            jogador.knockback_velocity = 6.0f;
            jogador.jump_velocity = -6.0f;

            jogador.vidas--;
            printf("Vidas restantes: %d\n", jogador.vidas);

            if (jogador.vidas <= 0) {
                printf("Game Over!\n");
                running = false;
            }
        }

        if (jogador.knocked_back) {
            if (jogador.facing_right) {
                jogador.pos_x -= jogador.knockback_velocity;
            }
            else {
                jogador.pos_x += jogador.knockback_velocity;
            }
            jogador.pos_y += jogador.jump_velocity;
            jogador.knockback_velocity -= 0.2f;
            jogador.jump_velocity += jogador.gravity;

            if (jogador.pos_y >= jogador.initial_pos_y) {
                jogador.pos_y = jogador.initial_pos_y;
                jogador.knocked_back = false;
                jogador.jump_velocity = -10.0f;
            }
        }

        guarda.frame_timer += 1.0 / 30.0;
        if (guarda.frame_timer >= guarda.frame_time) {
            guarda.current_frame = (guarda.current_frame + 1) % guarda.total_frames;
            guarda.frame_timer = 0;
        }

        al_clear_to_color(al_map_rgb(255, 255, 255));
        al_draw_scaled_bitmap(jogo.background, 0, 0, al_get_bitmap_width(jogo.background), al_get_bitmap_height(jogo.background), 0, 0, al_get_display_width(display), al_get_display_height(display), 0);

        desenha_jogador(&jogador);
        desenha_guarda(&guarda);

        al_flip_display();
    }
  

    al_destroy_bitmap(jogo.background);
    al_destroy_bitmap(jogador.sprite_sheet);
    al_destroy_bitmap(guarda.sprite_sheet);
    al_destroy_timer(jogo.timer);
    al_destroy_event_queue(jogo.event_queue);
}
