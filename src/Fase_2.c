#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/keyboard.h>
#include <allegro5/keycodes.h>

// Função que inicia a fase 3 do jogo
void iniciar_fase_2(ALLEGRO_DISPLAY* display) {
    al_init();  // Inicializa a biblioteca Allegro
    al_install_keyboard();  // Instala o suporte ao teclado

    ALLEGRO_TIMER* timer = al_create_timer(1.0 / 30.0);  // Cria um timer para controlar a taxa de atualização do jogo

    // Carregar as imagens do personagem e do cenário
    ALLEGRO_BITMAP* sprite_sheet = al_load_bitmap("assets/images/teste_personagem.png");
    ALLEGRO_BITMAP* bg = al_load_bitmap("assets/images/fundo_provisorio_fase2.png");

    // Verifica se as imagens foram carregadas corretamente, caso contrário, destrói o display e encerra
    if (!bg || !sprite_sheet) {
        al_destroy_display(display);
        return;
    }

    // Define a cor branca como transparente para o sprite
    al_convert_mask_to_alpha(sprite_sheet, al_map_rgb(255, 255, 255));

    // Configura a fila de eventos para receber eventos de teclado, timer e display
    ALLEGRO_EVENT_QUEUE* event_queue = al_create_event_queue();
    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_timer_event_source(timer));
    al_register_event_source(event_queue, al_get_keyboard_event_source());
    al_start_timer(timer); // Inicia o timer

    // Configuração dos frames do personagem (animação)
    int frame_width = 265;  // Largura de cada frame do personagem
    int frame_height = 376;  // Altura de cada frame do personagem

    // Coordenadas X dos frames (3 frames por linha)
    int frame_x[] = { 0, 265, 530 };

    // Coordenadas Y para duas linhas
    int frame_y[] = { 0, 376 };

    float scale_factor = 0.7;  // Escala do personagem ajustada

    // Posição inicial do personagem (ajustando para que fique no chão)
    int pos_x = 10;  // Posição X inicial
    int pos_y = al_get_display_height(display) - frame_height * scale_factor + 10;  // Ajuste para que o personagem toque o chão
    int initial_pos_y = pos_y;  // Armazena a posição inicial do personagem para controlar o pulo

    // Controle do pulo
    bool jumping = false;  // Indica se o personagem está pulando
    float jump_velocity = -15.0f;  // Velocidade inicial do pulo
    float gravity = 0.7f;  // Gravidade para desacelerar o pulo

    bool facing_right = true;  // Indica a direção que o personagem está virado
    bool move_left = false;  // Indica se o personagem está se movendo para a esquerda
    bool move_right = false;  // Indica se o personagem está se movendo para a direita
    bool moving = false;  // Indica se o personagem está se movendo

    // Velocidade de movimento
    float movement_speed = 2.0;

    // Controle da animação do personagem
    int current_frame = 0;  // Frame atual
    float frame_time = 0.2;  // Tempo de cada frame
    float frame_timer = 0;
    int total_moving_frames = 3;  // Total de frames da animação (3 por linha)

    bool running = true;  // Indica se o loop do jogo está rodando

    // Loop principal do jogo
    while (running) {
        ALLEGRO_EVENT event;
        al_wait_for_event(event_queue, &event);  // Espera por um evento (teclado, timer, etc.)

        if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {  // Se o usuário fechar a janela, encerra o jogo
            running = false;
        }

        if (event.type == ALLEGRO_EVENT_KEY_DOWN) {  // Detecta quando uma tecla é pressionada
            if (event.keyboard.keycode == ALLEGRO_KEY_D) {  // Move para a direita
                move_right = true;
                facing_right = true;
                moving = true;
            }
            else if (event.keyboard.keycode == ALLEGRO_KEY_A) {  // Move para a esquerda
                move_left = true;
                facing_right = false;
                moving = true;
            }
            else if (event.keyboard.keycode == ALLEGRO_KEY_SPACE && !jumping) {  // Pulo
                jumping = true;
            }
            else if (event.keyboard.keycode == ALLEGRO_KEY_F && (pos_x >= 178 && pos_x <= 272 || pos_x >= 530 && pos_x <= 642 || pos_x >= 875 && pos_x <= 980)) {  //Quando clica F abri a porta
                jumping = true;
            }
            else if (event.type == ALLEGRO_EVENT_KEY_UP) {  // Detecta quando uma tecla é solta
                if (event.keyboard.keycode == ALLEGRO_KEY_D) {  // Para de se mover para a direita
                    move_right = false;
                    if (!move_left) moving = false;
                }
                else if (event.keyboard.keycode == ALLEGRO_KEY_A) {  // Para de se mover para a esquerda
                    move_left = false;
                    if (!move_right) moving = false;
                }
            }

            // Movimento horizontal
            if (move_right) pos_x += movement_speed;
            if (move_left) pos_x -= movement_speed;

            // Lógica de pulo
            if (jumping) {
                pos_y += jump_velocity;
                jump_velocity += gravity;
                if (pos_y >= initial_pos_y) {  // Se o personagem tocar o chão, o pulo termina
                    pos_y = initial_pos_y;
                    jumping = false;
                    jump_velocity = -15.0f;
                }
            }

            // Controle da animação do movimento
            if (moving) {
                frame_timer += 1.0 / 30.0;
                if (frame_timer >= frame_time) {
                    current_frame = (current_frame + 1) % total_moving_frames;
                    frame_timer = 0;
                }
            }
            else {
                current_frame = 0;  // Se não estiver se movendo, exibe o primeiro frame
            }

            // Desenho dos frames do personagem
            int frame_cx = frame_x[current_frame];  // Frame atual (X)
            int frame_cy = frame_y[0];  // Usando apenas a primeira linha de sprites por enquanto

            // Limpa a tela e desenha o cenário e o personagem
            al_clear_to_color(al_map_rgb(255, 255, 255));  // Limpa a tela com a cor branca
            al_draw_scaled_bitmap(bg, 0, 0, al_get_bitmap_width(bg), al_get_bitmap_height(bg), 0, 0, al_get_display_width(display), al_get_display_height(display), 0);

            // Desenha o personagem na direção correta com ajuste de escala
            if (facing_right) {
                al_draw_scaled_bitmap(sprite_sheet, frame_cx, frame_cy, frame_width, frame_height, pos_x, pos_y, frame_width * scale_factor, frame_height * scale_factor, 0);
            }
            else {
                al_draw_scaled_bitmap(sprite_sheet, frame_cx, frame_cy, frame_width, frame_height, pos_x, pos_y, frame_width * scale_factor, frame_height * scale_factor, ALLEGRO_FLIP_HORIZONTAL);
            }

            al_flip_display();  // Atualiza a tela
        }

        // Destrói os recursos após o fim do jogo
        al_destroy_bitmap(bg);
        al_destroy_bitmap(sprite_sheet);
        al_destroy_timer(timer);
        al_destroy_event_queue(event_queue);
    }