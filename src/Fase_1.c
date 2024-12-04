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

void iniciar_fase_1(ALLEGRO_DISPLAY* display, GameState* game_state) {
    Jogo jogo;
    jogo.display = display;
    init_jogo(&jogo);

    Jogador jogador;
    init_jogador(&jogador, al_get_display_height(display));

    Guarda guarda;
    init_guarda(&guarda, al_get_display_width(display), al_get_display_height(display));

    // Carregar a imagem da tecla de pausa
    ALLEGRO_BITMAP* tecla_pause = al_load_bitmap("assets/images/tecle_pause.png");
    if (!tecla_pause) {
        printf("Falha ao carregar a imagem tecla_pause.png!\n");
        return;  // Se falhar em carregar a imagem, sair da função
    }
    ALLEGRO_BITMAP* caixa_mensagem = al_load_bitmap("assets/images/caixa_mensagem_fase1.png");
    if (!caixa_mensagem) {
        printf("Falha ao carregar a imagem caixa_mensagem_fase1.png!\n");
        return;  // Se falhar em carregar a imagem, sair da função
    }


    bool running = true;
    bool mostrar_caixa_mensagem = true;

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

        // Atualiza o movimento do guarda
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

        // Verifica a colisão entre o jogador e o guarda
        if (detectar_colisao(&jogador, &guarda)) {
            printf("Colisão detectada!\n");

            // Se a colisão for com a parte superior do guarda, destrói o guarda
            if (jogador.pos_y + jogador.frame_height * jogador.scale_factor <= guarda.pos_y + 50) {
                printf("O guarda foi derrotado!\n");
                guarda.morto = true;  // Marca o guarda como morto
                guarda.pos_x = -guarda.frame_width * guarda.scale_factor;  // Reposiciona o guarda fora da tela
            }
            else {
                // Caso contrário, o jogador é empurrado
                jogador.knocked_back = true;
                jogador.knockback_velocity = 5.0f;  // Empurra o jogador
                jogador.jump_velocity = -5.5f;     // Impede o jogador de pular após ser empurrado

                jogador.vidas--;  // Perde uma vida
                printf("Vidas restantes: %d\n", jogador.vidas);

                if (jogador.vidas <= 0) {  // Game Over
                    printf("Game Over!\n");
                    running = false;
                }
            }
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
            jogador.knockback_velocity -= 0.2f;  // Diminui a velocidade do empurrão
            jogador.jump_velocity += jogador.gravity;

            if (jogador.pos_y >= jogador.initial_pos_y) {
                jogador.pos_y = jogador.initial_pos_y;  // O jogador volta ao chão
                jogador.knocked_back = false;
                jogador.jump_velocity = -12.0f;  // Reinicia o pulo
            }
        }

        // Atualiza a animação do guarda
        guarda.frame_timer += 1.0 / 30.0;
        if (guarda.frame_timer >= guarda.frame_time) {
            guarda.current_frame = (guarda.current_frame + 1) % guarda.total_frames;
            guarda.frame_timer = 0;
        }

        // Se o jogo estiver pausado, ignore o restante da lógica
        if (*game_state == PAUSE_MENU) {
            continue;  // Ignora atualizações enquanto o jogo estiver em pausa
        }

        // Detecção de pressionamento da tecla 'P' para pausar
        if (event.keyboard.keycode == ALLEGRO_KEY_P) {
            printf("Botão de pausa clicado. Voltando ao mapa.\n");
            running = false;
            *game_state = PAUSE_MENU; // Corrigido para atualizar o estado corretamente
        }

        if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
            running = false;
        }

        if (event.type == ALLEGRO_EVENT_KEY_DOWN) {
            switch (event.keyboard.keycode) {
            case ALLEGRO_KEY_A:
            case ALLEGRO_KEY_D:
            case ALLEGRO_KEY_SPACE:
                mostrar_caixa_mensagem = false;  // Não mostrar a caixa ao pressionar essas teclas
                break;


        

            case ALLEGRO_KEY_P:
                printf("Pausando o jogo.\n");
                *game_state = PAUSE_MENU;  // Altera o estado para PAUSE_MENU
                running = false;  // Finaliza a fase 1
                break;
            }
        }

        // Verifica se o jogador chegou à posição desejada para transitar para a próxima fase
        if (jogador.pos_x >= 1000) {
            *game_state = FASE1_2;  // Altera o estado do jogo para a próxima fase
            running = false;  // Encerra o loop da fase 1
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

        // Fator de escala aumentado para tamanho maior
        float escala_mensagem = 0.85f;

        // Obtendo as dimensões da imagem
        int largura_mensagem = al_get_bitmap_width(caixa_mensagem);
        int altura_mensagem = al_get_bitmap_height(caixa_mensagem);

        // Posições fixas no início do mapa para colocar a caixa na parte superior da tela
        int posicao_x_mensagem = 10;  // Posição X fixa no mapa, um pouco à direita para não ficar exatamente na borda
        int posicao_y_mensagem = -200;  // Posição Y fixa, suficientemente alta para estar na parte superior da tela

        // Desenhando a caixa de mensagem
        al_draw_scaled_bitmap(caixa_mensagem,
            0, 0, largura_mensagem, altura_mensagem,  // Coordenadas de origem e dimensões originais da imagem
            posicao_x_mensagem, posicao_y_mensagem,   // Coordenadas onde a imagem será desenhada na tela
            largura_mensagem* escala_mensagem, altura_mensagem* escala_mensagem,  // Dimensões escaladas da imagem
            0);  // Sem rotação

        if (mostrar_caixa_mensagem) {
            al_draw_scaled_bitmap(caixa_mensagem,
                0, 0, largura_mensagem, altura_mensagem,  // Coordenadas de origem e dimensões originais da imagem
                posicao_x_mensagem, posicao_y_mensagem,   // Coordenadas onde a imagem será desenhada na tela
                largura_mensagem * escala_mensagem, altura_mensagem * escala_mensagem,  // Dimensões escaladas da imagem
                0);  // Sem rotação
        }

        // Desenha o jogador e o guarda (se não estiver morto)
        desenha_jogador(&jogador);
        desenha_guarda(&guarda);

        // Atualiza a tela
        al_flip_display();
    }

    // Libera recursos
    al_destroy_bitmap(tecla_pause);  // Libera a imagem da tecla de pausa
    al_destroy_bitmap(jogo.background);
    al_destroy_bitmap(jogador.sprite_sheet);
    al_destroy_bitmap(guarda.sprite_sheet);
    al_destroy_timer(jogo.timer);
    al_destroy_event_queue(jogo.event_queue);
    al_destroy_bitmap(caixa_mensagem);
}
