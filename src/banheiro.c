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
} Jogador_banheiro;

// Fun��o para inicializar o jogador
void init_jogador_banheiro(Jogador_banheiro* jogador2, int display_height) {
    jogador2->sprite_sheet = al_load_bitmap("assets/images/mulher.png");
    jogador2->frame_width = 136;// Largura de cada frame do personagem
    jogador2->frame_height = 250;// Altura de cada frame do personagem
    jogador2->pos_x = 50;// Posi��o X inicial
    jogador2->scale_factor = 1.4;// Escala do personagem ajustada
    jogador2->pos_y = display_height - jogador2->frame_height * jogador2->scale_factor - 60;// Ajuste para que o personagem toque o ch�o
    jogador2->initial_pos_y = jogador2->pos_y;// Armazena a posi��o inicial do personagem para controlar o pulo
    jogador2->jump_velocity = -15.0f;// Velocidade inicial do pulo
    jogador2->gravity = 0.7f;// Gravidade para desacelerar o pulo
    jogador2->movement_speed = 5.0;// Velocidade de movimento
    jogador2->frame_time = 0.2;// Tempo de cada frame
    jogador2->frame_timer = 0;
    jogador2->total_moving_frames = 3;// Total de frames da anima��o (3 por linha)
    jogador2->current_frame = 0;// Frame atual
    jogador2->facing_right = true;// Indica a dire��o que o personagem est� virado
    jogador2->jumping = false;// Indica se o personagem est� pulando
    jogador2->move_left = false;// Indica se o personagem est� se movendo para a esquerda
    jogador2->move_right = false;// Indica se o personagem est� se movendo para a direita
    jogador2->moving = false;// Indica se o personagem est� se movendo
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
} Jogo_banheiro;

// Fun��o para inicializar o jogo
void init_jogo_banheiro(Jogo_banheiro* jogo2) {
    al_init();
    al_install_keyboard();
    jogo2->timer = al_create_timer(1.0 / 30.0);// Cria um timer para controlar a taxa de atualiza��o do jogo
    jogo2->background = al_load_bitmap("assets/images/banheiro.png");
    jogo2->event_queue = al_create_event_queue();
    al_register_event_source(jogo2->event_queue, al_get_display_event_source(jogo2->display));
    al_register_event_source(jogo2->event_queue, al_get_timer_event_source(jogo2->timer));
    al_register_event_source(jogo2->event_queue, al_get_keyboard_event_source());
    al_start_timer(jogo2->timer);
}

// Fun��o que desenha o jogador
static void desenha_jogador_banheiro(Jogador_banheiro* jogador2) {
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

int p = 0;

void banheiro(ALLEGRO_DISPLAY* display, GameState* game_state, int k) {
    Jogo_banheiro jogo2;
    jogo2.display = display;
    init_jogo_banheiro(&jogo2);

    Jogador_banheiro jogador2;
    init_jogador_banheiro(&jogador2, al_get_display_height(display));

    // Carregar a imagem da tecla de pausa
    ALLEGRO_BITMAP* tecla_pause = al_load_bitmap("assets/images/botao_pause.png");
    if (!tecla_pause) {
        printf("Falha ao carregar a imagem tecla_pause.png!\n");
        return;
    }

    // Desenha a imagem da tecla de pausa no centro da tela (ajustada)
                 // Fator de escala para diminuir a imagem
    float escala = 0.15f;  // Reduz a imagem para 50% do tamanho original
    int offset_x = 25; // Move para a direita
    int offset_y = 25; // Move para cima

    int largura_imagem = al_get_bitmap_width(tecla_pause);
    int altura_imagem = al_get_bitmap_height(tecla_pause);

    bool running = true;  // Indica se o loop do jogo est� rodando
    if (p == 1) {
        jogador2.pos_x = 215;
        p = 0;
    }
    else {
        jogador2.pos_x = 50;
        p = 0;
    }
    // Loop principal do jogo
    while (running) {
        ALLEGRO_EVENT event;
        al_wait_for_event(jogo2.event_queue, &event);// Espera por um evento (teclado, timer, etc.)

        if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {// Se o usu�rio fechar a janela, encerra o jogo
            running = false;
        }

        if (event.type == ALLEGRO_EVENT_KEY_DOWN) {
            if (!jogador2.knocked_back) {
                switch (event.keyboard.keycode) {
                    case ALLEGRO_KEY_D:  // Move para a direita
                        jogador2.move_right = true;
                        jogador2.facing_right = true;
                        jogador2.moving = true;
                        break;
                    case ALLEGRO_KEY_A:  // Move para a esquerda
                        jogador2.move_left = true;
                        jogador2.facing_right = false;
                        jogador2.moving = true;
                        break;
                    case ALLEGRO_KEY_SPACE:  // Pulo
                        if (!jogador2.jumping) {
                            jogador2.jumping = true;
                        }
                        break;
                    case ALLEGRO_KEY_F:  // Abre portas com condições específicas
                        if (jogador2.pos_x <= 150) {
                            if (k == 1) {
                                quarto(display, &game_state);
                                *game_state = QUARTO;
                                running = false;
                            } else if (k == 2) {
                                quarto2(display, &game_state);
                                *game_state = QUARTO2;
                                running = false;
                            }
                        }
                        break;
                    case ALLEGRO_KEY_E:  // Abre o baú
                        if (jogador2.pos_x >= 140 && jogador2.pos_x <= 340) {
                            p = 1;
                            bau(display, &game_state, 3, k);
                            running = false;
                        }
                        break;
                    case ALLEGRO_KEY_P:  // Pausa
                        printf("Botão de pausa clicado. Voltando ao mapa.\n");
                        *game_state = PAUSE_MENU;
                        running = false;
                        break;
                }
            }
        } else if (event.type == ALLEGRO_EVENT_KEY_UP) {
            switch (event.keyboard.keycode) {
                case ALLEGRO_KEY_D:  // Para de se mover para a direita
                    jogador2.move_right = false;
                    if (!jogador2.move_left) {
                        jogador2.moving = false;
                    }
                    break;
                case ALLEGRO_KEY_A:  // Para de se mover para a esquerda
                    jogador2.move_left = false;
                    if (!jogador2.move_right) {
                        jogador2.moving = false;
                    }
                    break;
            }
        }


        // Movimento horizontal
        if (!jogador2.knocked_back) {
            if (jogador2.move_right) jogador2.pos_x += jogador2.movement_speed;
            if (jogador2.move_left) jogador2.pos_x -= jogador2.movement_speed;
        }

        // L�gica de pulo
        if (jogador2.jumping) {
            jogador2.pos_y += jogador2.jump_velocity;
            jogador2.jump_velocity += jogador2.gravity;
            if (jogador2.pos_y >= jogador2.initial_pos_y) {
                jogador2.pos_y = jogador2.initial_pos_y;
                jogador2.jumping = false;
                jogador2.jump_velocity = -10.0f;
            }
        }

        // Controle da anima��o do movimento
        if (jogador2.moving) {
            jogador2.frame_timer += 1.0 / 30.0;
            if (jogador2.frame_timer >= jogador2.frame_time) {
                jogador2.current_frame = (jogador2.current_frame + 1) % jogador2.total_moving_frames;
                jogador2.frame_timer = 0;
            }
        }
        else {
            jogador2.current_frame = 0;// Se n�o estiver se movendo, exibe o primeiro frame
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

        if (jogador2.pos_x > 1030) {
            jogador2.move_right = false;
        }
        if (jogador2.pos_x < 55) {
            jogador2.move_left = false;
        }

        if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
            running = false;
        }

        // Limpa a tela e desenha o cen�rio e o personagem
        al_clear_to_color(al_map_rgb(255, 255, 255));
        al_draw_scaled_bitmap(jogo2.background, 0, 0, al_get_bitmap_width(jogo2.background),
            al_get_bitmap_height(jogo2.background), 0, 0,
            al_get_display_width(display), al_get_display_height(display), 0);
        // Desenha o personagem na dire��o correta com ajuste de escala
        desenha_jogador_banheiro(&jogador2);
        //desenha o pause
        al_draw_scaled_bitmap(tecla_pause,
            0, 0, largura_imagem, altura_imagem,// Fonte da imagem
            (al_get_display_width(display) - largura_imagem * escala) / 1.05 + offset_x,// Nova posi��o X
            (al_get_display_height(display) - altura_imagem * escala) / 8.5 - offset_y,// Nova posi��o Y
            largura_imagem* escala, altura_imagem* escala,// Novo tamanho
            0);// Nenhuma rota��o
        al_flip_display();// Atualiza a tela
    }
    // Destr�i os recursos ap�s o fim do jogo
    al_destroy_bitmap(jogo2.background);
    al_destroy_bitmap(jogador2.sprite_sheet);
    al_destroy_timer(jogo2.timer);
    al_destroy_event_queue(jogo2.event_queue);
}