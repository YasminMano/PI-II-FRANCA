#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/keyboard.h>
#include <allegro5/keycodes.h>
#include <stdio.h>
#include "headers/fases.h"
#include "headers/game.h"
#include "headers/jogador.h"
#include "headers/guarda.h"
#include "headers/jogo.h"

void iniciar_fase1_3(ALLEGRO_DISPLAY* display, GameState* game_state) {
    Jogo jogo;
    jogo.display = display;
    init_jogo(&jogo);

    Jogador jogador;
    init_jogador(&jogador, al_get_display_height(display));

    Guarda guarda3;
    init_guarda(&guarda3, al_get_display_width(display) - 400, al_get_display_height(display));


    // Carregar a imagem da tecla de pausa
    ALLEGRO_BITMAP* tecla_pause = al_load_bitmap("assets/images/tecle_pause.png");
    if (!tecla_pause) {
        printf("Falha ao carregar a imagem tecla_pause.png!\n");
        return;  // Se falhar em carregar a imagem, sair da função
    }

    ALLEGRO_BITMAP* chave = al_load_bitmap("assets/images/chave.png");
    if (!chave) {
        printf("Falha ao carregar a imagem chave.png!\n");
        return -1;  // Se falhar em carregar a imagem, sair da função
    }


    ALLEGRO_BITMAP* gaiola = al_load_bitmap("assets/images/gaiola.png");
    if (!gaiola) {
        printf("Falha ao carregar a imagem gaiola.png!\n");
        return -1;  // Se falhar em carregar a imagem, sair da função
    }

    ALLEGRO_BITMAP* sprite_sheet = al_load_bitmap("assets/images/mulher_fase1.png");
    if (!sprite_sheet) {
        fprintf(stderr, "Falha ao carregar a imagem do sprite 'mulher.png'\n");
        return -1; // Tratamento de erro adequado
    }

    ALLEGRO_BITMAP* caixa_mensagem3 = al_load_bitmap("assets/images/caixa_mensagem_fase1_3.png");
    if (!caixa_mensagem3) {
        fprintf(stderr, "Falha ao carregar a imagem do sprite 'mulher.png'\n");
        return -1; // Tratamento de erro adequado
    }


    ALLEGRO_BITMAP* sprite_atual = gaiola;  // Começa com a gaiola visível


    bool running = true;
    bool chave_coletada = false;
    bool mostrar_caixa_mensagem3 = true;
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

        // Atualiza o movimento do segundo guarda
        if (guarda3.move_right) {
            guarda3.pos_x += guarda3.movement_speed;
            if (guarda3.pos_x >= guarda3.max_x) {
                guarda3.move_right = false;
            }
        }
        else {
            guarda3.pos_x -= guarda3.movement_speed;
            if (guarda3.pos_x <= guarda3.min_x) {
                guarda3.move_right = true;
            }
        }


        // Verifica a colisão entre o jogador e o primeiro guarda
        if (detectar_colisao(&jogador, &guarda3)) {
            printf("Colisao com o guarda detectada!\n");

            if (jogador.pos_y + jogador.frame_height * jogador.scale_factor <= guarda3.pos_y + 50) {
                printf("O ultimo guarda foi derrotado!\n");
                guarda3.morto = true;
                guarda3.pos_x = -guarda3.frame_width * guarda3.scale_factor;
            }
            else {
                jogador.knocked_back = true;
                jogador.knockback_velocity = 5.0f;
                jogador.jump_velocity = -5.5f;
                jogador.vidas--;
                printf("Vidas restantes: %d\n", jogador.vidas);

                if (jogador.vidas <= 0) {
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
            jogador.knockback_velocity -= 0.2f;
            jogador.jump_velocity += jogador.gravity;

            if (jogador.pos_y >= jogador.initial_pos_y) {
                jogador.pos_y = jogador.initial_pos_y;
                jogador.knocked_back = false;
                jogador.jump_velocity = -12.0f;
            }
        }

        // Atualiza a animação do primeiro guarda
        guarda3.frame_timer += 1.0 / 30.0;
        if (guarda3.frame_timer >= guarda3.frame_time) {
            guarda3.current_frame = (guarda3.current_frame + 1) % guarda3.total_frames;
            guarda3.frame_timer = 0;
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

        // No tratamento de eventos do teclado
        if (event.type == ALLEGRO_EVENT_KEY_DOWN) {
            switch (event.keyboard.keycode) {
            case ALLEGRO_KEY_F:
                if (sprite_atual == gaiola) {
                    sprite_atual = sprite_sheet;  // Troca para a imagem da mulher
                }
                else {
                    sprite_atual = gaiola;  // Troca de volta para a gaiola
                }
                break;
                // Outras teclas podem ser tratadas aqui
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


        // GAIOLA
        float escala_gaiola = 0.95f;  // Ajustar escala conforme necessário
        int offset_x_gaiola = -10;     // Positivo para mover mais para a direita
        int offset_y_gaiola = 70;     // Positivo para mover mais para baixo

        int largura_gaiola = al_get_bitmap_width(gaiola);
        int altura_gaiola = al_get_bitmap_height(gaiola);

        // Calcular as posições X e Y com base no tamanho da tela e nas dimensões da imagem ajustadas pela escala
        int posicao_x_gaiola = al_get_display_width(display) - largura_gaiola * escala_gaiola - offset_x_gaiola;
        int posicao_y_gaiola = al_get_display_height(display) - altura_gaiola * escala_gaiola + offset_y_gaiola;  // Adicionando o offset para mover para baixo

        float escala_mulher = 0.6; // Ajuste conforme necessário para o tamanho desejado

        // Calculando a altura ajustada da mulher
        int altura_mulher_ajustada = al_get_bitmap_height(sprite_sheet) * escala_mulher;

        // Calculando a posição Y para que a mulher toque o chão
        int offsetY = 200;  // Altere este valor para mover a mulher para cima (-) ou para baixo (+)
        int pos_y_mulher = posicao_y_gaiola + offsetY;
        // Ajuste fino da posição x, se necessário (ajustar o valor de offsetX se necessário)
        int offsetX = 300;  // Altere este valor para mover a mulher para esquerda (-) ou direita (+)
        int pos_x_mulher = posicao_x_gaiola + offsetX;

        // Desenhando a mulher na tela na posição x ajustada e y ajustada
        if (sprite_atual == sprite_sheet) {
            al_draw_scaled_bitmap(sprite_sheet,
                0, 0,  // Coordenadas do canto superior esquerdo para começar a cortar a imagem
                al_get_bitmap_width(sprite_sheet), al_get_bitmap_height(sprite_sheet),  // Usar a largura e altura completas do bitmap da mulher
                pos_x_mulher, pos_y_mulher,  // Posições x e y ajustadas
                al_get_bitmap_width(sprite_sheet) * escala_mulher, al_get_bitmap_height(sprite_sheet) * escala_mulher,  // Largura e altura escaladas
                0);  // Sem rotação
        }
        else {
            // Se o sprite atual for a gaiola ou qualquer outro sprite, desenhá-lo normalmente
            al_draw_scaled_bitmap(sprite_atual,
                0, 0,
                al_get_bitmap_width(sprite_atual), al_get_bitmap_height(sprite_atual),
                posicao_x_gaiola, posicao_y_gaiola,
                al_get_bitmap_width(sprite_atual) * escala_gaiola, al_get_bitmap_height(sprite_atual) * escala_gaiola,
                0);
        }


        //CHAVE
        float escala_chave = 0.08f;  // Ajuste de escala para a chave
        int offset_x_chave = 100;    // Offset para a chave aparecer antes da gaiola
        int offset_y_chave = 70;     // Mantém o mesmo offset vertical da gaiola para alinhamento

        int largura_chave = al_get_bitmap_width(chave);
        int altura_chave = al_get_bitmap_height(chave);

        // Posição X da chave: Alinhar para que a chave apareça antes da gaiola
        int posicao_x_chave = posicao_x_gaiola - largura_chave * escala_chave - offset_x_chave;
        int posicao_y_chave = posicao_y_gaiola;  // Mesma altura da gaiola para simplicidade

        // Desenhar a chave
        al_draw_scaled_bitmap(chave,
            0, 0, largura_chave, altura_chave,
            posicao_x_chave, posicao_y_chave,
            largura_chave * escala_chave, altura_chave * escala_chave,
            0);


        // Supondo que estas são as coordenadas e tamanhos usados para detecção de colisão
        float jogador_left = jogador.pos_x;
        float jogador_right = jogador.pos_x + jogador.frame_width * jogador.scale_factor;
        float jogador_top = jogador.pos_y;
        float jogador_bottom = jogador.pos_y + jogador.frame_height * jogador.scale_factor;

        float chave_left = posicao_x_chave;
        float chave_right = posicao_x_chave + largura_chave * escala_chave;
        float chave_top = posicao_y_chave;
        float chave_bottom = posicao_y_chave + altura_chave * escala_chave;

        if (!chave_coletada &&
            jogador_right > chave_left &&
            jogador_left < chave_right &&
            jogador_bottom > chave_top &&
            jogador_top < chave_bottom) {
            chave_coletada = true;
            printf("Chave coletada!\n");
            // Não destrua a chave aqui


        }

        // Desenha a chave se não foi coletada
        if (!chave_coletada) {
            al_draw_scaled_bitmap(chave,
                0, 0, largura_chave, altura_chave,
                posicao_x_chave, posicao_y_chave,
                largura_chave * escala_chave, altura_chave * escala_chave,
                0);

        }

        // Fator de escala aumentado para tamanho maior
        float escala_mensagem3 = 0.85f;

        // Obtendo as dimensões da imagem
        int largura_mensagem3 = al_get_bitmap_width(caixa_mensagem3);
        int altura_mensagem3 = al_get_bitmap_height(caixa_mensagem3);

        // Posições fixas no início do mapa para colocar a caixa na parte superior da tela
        int posicao_x_mensagem3 = 10;  // Posição X fixa no mapa, um pouco à direita para não ficar exatamente na borda
        int posicao_y_mensagem3 = -200;  // Posição Y fixa, suficientemente alta para estar na parte superior da tela

        // Desenhando a caixa de mensagem
        al_draw_scaled_bitmap(caixa_mensagem3,
            0, 0, largura_mensagem3, altura_mensagem3,  // Coordenadas de origem e dimensões originais da imagem
            posicao_x_mensagem3, posicao_y_mensagem3,   // Coordenadas onde a imagem será desenhada na tela
            largura_mensagem3 * escala_mensagem3, altura_mensagem3 * escala_mensagem3,  // Dimensões escaladas da imagem
            0);  // Sem rotação

        if (mostrar_caixa_mensagem3) {
            al_draw_scaled_bitmap(caixa_mensagem3,
                0, 0, largura_mensagem3, altura_mensagem3,  // Coordenadas de origem e dimensões originais da imagem
                posicao_x_mensagem3, posicao_y_mensagem3,   // Coordenadas onde a imagem será desenhada na tela
                largura_mensagem3 * escala_mensagem3, altura_mensagem3 * escala_mensagem3,  // Dimensões escaladas da imagem
                0);  // Sem rotação
        }

        // Desenha o jogador
        desenha_jogador(&jogador);
        desenha_guarda(&guarda3);
        // Atualiza a tela
        al_flip_display();
    }

    // Libera recursos
    al_destroy_bitmap(jogo.background);
    al_destroy_bitmap(jogador.sprite_sheet);
    al_destroy_timer(jogo.timer);
    al_destroy_event_queue(jogo.event_queue);
    al_destroy_bitmap(chave);
    al_destroy_bitmap(caixa_mensagem3);
}