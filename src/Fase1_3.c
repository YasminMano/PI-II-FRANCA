#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/keyboard.h>
#include <allegro5/keycodes.h>
#include <stdio.h>
#include "fases.h"
#include "game.h"
#include "jogador.h"
#include "guarda.h"
#include "jogo.h"

void iniciar_fase1_3(ALLEGRO_DISPLAY* display, GameState* game_state) {
    Jogo jogo;
    jogo.display = display;
    init_jogo(&jogo);

    Jogador jogador;
    init_jogador(&jogador, al_get_display_height(display));

     // Carregar a imagem da tecla de pausa
    ALLEGRO_BITMAP* tecla_pause = al_load_bitmap("assets/images/tecle_pause.png");
    if (!tecla_pause) {
        printf("Falha ao carregar a imagem tecla_pause.png!\n");
        return;  // Se falhar em carregar a imagem, sair da função
    }


    bool running = true;

    // Loop principal do jogo
    while (running) {
        ALLEGRO_EVENT event;
        al_wait_for_event(jogo.event_queue, &event);

        // Fechar a janela do jogo
        if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
            running = false;
        }

        // Tratamento de pressionamento de teclas
        if (event.type == ALLEGRO_EVENT_KEY_DOWN) {
            if (!jogador.knocked_back) {
                if (event.keyboard.keycode == ALLEGRO_KEY_D) {  // Movimento para a direita
                    jogador.move_right = true;
                    jogador.facing_right = true;
                    jogador.moving = true;
                }
                else if (event.keyboard.keycode == ALLEGRO_KEY_A) {  // Movimento para a esquerda
                    jogador.move_left = true;
                    jogador.facing_right = false;
                    jogador.moving = true;
                }
                else if (event.keyboard.keycode == ALLEGRO_KEY_SPACE && !jogador.jumping) {  // Pulo
                    jogador.jumping = true;
                }
            }
        }

        // Tratamento de soltura de teclas
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

        // Atualiza o movimento do jogador
        if (!jogador.knocked_back) {
            if (jogador.move_right) jogador.pos_x += jogador.movement_speed;
            if (jogador.move_left) jogador.pos_x -= jogador.movement_speed;
        }

        // Atualiza o pulo do jogador
        if (jogador.jumping) {
            jogador.pos_y += jogador.jump_velocity;
            jogador.jump_velocity += jogador.gravity;
            if (jogador.pos_y >= jogador.initial_pos_y) {
                jogador.pos_y = jogador.initial_pos_y;  // Se o jogador atingir o solo
                jogador.jumping = false;
                jogador.jump_velocity = -12.0f;  // Reinicia o pulo
            }
        }

        // Atualiza a animação do jogador
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

        // Lógica de empurrão do jogador
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
                jogador.jump_velocity = -12.0f;
            }
        }

        // Se o jogo estiver pausado, ignore o restante da lógica
        if (*game_state == PAUSE_MENU) {
            continue;  // Ignora atualizações enquanto o jogo estiver em pausa
        }

        // Detecção de pressionamento da tecla 'P' para pausar
        if (event.type == ALLEGRO_EVENT_KEY_DOWN) {
            if (event.keyboard.keycode == ALLEGRO_KEY_P) {
                printf("Pausando o jogo.\n");
                *game_state = PAUSE_MENU;  // Altera o estado para PAUSE_MENU
                running = false;           // Finaliza a fase 1
            }
        }


        // Verifica se o jogador chegou à posição desejada para transitar para a próxima fase
        if (jogador.pos_x >= 1000) {
            *game_state = FASE1_2;  // Altera o estado do jogo para a próxima fase
            running = false;  // Encerra o loop da fase 1
        }


        // Verifica se o jogador chegou à posição desejada para transitar para a próxima fase
        if (jogador.pos_x >= 1000) {
            *game_state = MAPA;  // Altera o estado do jogo para a próxima fase
            running = false;
        }

        // Limpa a tela e desenha o fundo
        al_clear_to_color(al_map_rgb(255, 255, 255));
        al_draw_scaled_bitmap(jogo.background, 0, 0, al_get_bitmap_width(jogo.background),
            al_get_bitmap_height(jogo.background), 0, 0,
            al_get_display_width(display), al_get_display_height(display), 0);

        // Desenha a imagem da tecla de pausa no centro da tela (ajustada)
        // Fator de escala para diminuir a imagem
        float escala = 0.15f;  // Reduz a imagem para 50% do tamanho original
        int offset_x = 25; // Move para a direita
        int offset_y = 25; // Move para cima

        int largura_imagem = al_get_bitmap_width(tecla_pause);
        int altura_imagem = al_get_bitmap_height(tecla_pause);

        al_draw_scaled_bitmap(tecla_pause,
                       0, 0, largura_imagem, altura_imagem,  // Fonte da imagem
                       (al_get_display_width(display) - largura_imagem * escala) / 1.05 + offset_x,  // Nova posição X
                       (al_get_display_height(display) - altura_imagem * escala) / 8.5 - offset_y,  // Nova posição Y
                       largura_imagem * escala, altura_imagem * escala,  // Novo tamanho
                       0);  // Nenhuma rotação

        // Desenha o jogador
        desenha_jogador(&jogador);

        // Atualiza a tela
        al_flip_display();
    }

    // Libera recursos
    al_destroy_bitmap(jogo.background);
    al_destroy_bitmap(jogador.sprite_sheet);
    al_destroy_timer(jogo.timer);
    al_destroy_event_queue(jogo.event_queue);
}
