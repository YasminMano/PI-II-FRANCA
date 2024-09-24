#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/keyboard.h>

int main1() {

    al_init();
    al_init_image_addon();
    al_install_keyboard();

    ALLEGRO_DISPLAY* display = al_create_display(1280, 720);
    al_set_window_position(display, 200, 200);
    al_set_window_title(display, "A Corrida Pela Liberdade!");

    ALLEGRO_TIMER* timer = al_create_timer(1.0 / 30.0);

    // Carregar a imagem do sprite sheet
    ALLEGRO_BITMAP* sprite_sheet = al_load_bitmap("./teste_personagem1.png");
    ALLEGRO_BITMAP* bg = al_load_bitmap("./cenario1.png");

    // Verifique se as imagens foram carregadas corretamente
    if (!bg || !sprite_sheet) {
        al_destroy_display(display);
        return -1;
    }

    // Configurar transparência (assumindo que o fundo do sprite é branco)
    al_convert_mask_to_alpha(sprite_sheet, al_map_rgb(255, 255, 255));

    ALLEGRO_EVENT_QUEUE* event_queue = al_create_event_queue();
    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_timer_event_source(timer));
    al_register_event_source(event_queue, al_get_keyboard_event_source());
    al_start_timer(timer);

    // Definir coordenadas específicas de cada sprite
    int frame_width = 320;  // Largura de cada sprite
    int frame_height = 320;  // Altura de cada sprite
    int frame_x[] = { 0, 320, 640 };  // Coordenadas x dos sprites (ajustar se necessário)
    int frame_y = 0;  // Todos os sprites estão na mesma linha vertical

    // Reduzir o tamanho do personagem para 60% do tamanho original
    float scale_factor = 0.6;

    // Posição inicial do personagem na tela
    int pos_x = 50; // Um pouco à esquerda
    int pos_y = al_get_display_height(display) - frame_height * scale_factor - 50; // Um pouco acima do chão
    int initial_pos_y = pos_y; // Para resetar o pulo

    bool jumping = false;
    float jump_velocity = -15.0f; // Velocidade inicial do pulo
    float gravity = 0.7f; // Gravidade
    bool facing_right = true; // Personagem começa virado para a direita

    bool move_left = false;
    bool move_right = false;
    bool moving = false; // Controle de movimento

    // Velocidade de movimento do personagem
    float movement_speed = 1.5;

    // Controle de animação
    int current_frame = 0;
    float frame_time = 0.2; // Tempo entre cada frame
    float frame_timer = 0;
    int total_moving_frames = 3; // Três frames no total

    while (true) {
        ALLEGRO_EVENT event;
        al_wait_for_event(event_queue, &event);

        // Detecta quando as teclas são pressionadas
        if (event.type == ALLEGRO_EVENT_KEY_DOWN) {
            if (event.keyboard.keycode == ALLEGRO_KEY_D) {
                move_right = true;
                facing_right = true;
                moving = true;
            }
            else if (event.keyboard.keycode == ALLEGRO_KEY_A) {
                move_left = true;
                facing_right = false;
                moving = true;
            }
            else if (event.keyboard.keycode == ALLEGRO_KEY_SPACE && !jumping) {
                jumping = true; // Inicia o pulo
            }
        }

        // Detecta quando as teclas são soltas
        else if (event.type == ALLEGRO_EVENT_KEY_UP) {
            if (event.keyboard.keycode == ALLEGRO_KEY_D) {
                move_right = false;
                if (!move_left) moving = false; // Parar se não estiver movendo para a esquerda
            }
            else if (event.keyboard.keycode == ALLEGRO_KEY_A) {
                move_left = false;
                if (!move_right) moving = false; // Parar se não estiver movendo para a direita
            }
        }

        // Lógica de movimento horizontal contínuo
        if (move_right) {
            pos_x += movement_speed; // Movimento para a direita
        }
        if (move_left) {
            pos_x -= movement_speed; // Movimento para a esquerda
        }

        // Lógica do pulo
        if (jumping) {
            pos_y += jump_velocity; // Aplicar a velocidade do pulo
            jump_velocity += gravity; // Aplicar gravidade para desacelerar o pulo

            // Quando o personagem atinge o chão, o pulo termina
            if (pos_y >= initial_pos_y) {
                pos_y = initial_pos_y;
                jumping = false;
                jump_velocity = -15.0f; // Reseta a velocidade do pulo
            }
        }

        // Atualizar o frame da animação se o personagem estiver se movendo
        if (moving) {
            frame_timer += 1.0 / 30.0;
            if (frame_timer >= frame_time) {
                current_frame = (current_frame + 1) % total_moving_frames;
                frame_timer = 0;
            }
        }
        else {
            current_frame = 0; // Parado, usar o primeiro frame
        }

        // Calcular o frame a ser desenhado
        int frame_cx = frame_x[current_frame];  // Coordenada x do frame atual
        int frame_cy = frame_y;  // Coordenada y do frame (fixo no topo da imagem)

        al_clear_to_color(al_map_rgb(255, 255, 255)); // Limpa a tela
        al_draw_scaled_bitmap(bg, 0, 0, al_get_bitmap_width(bg), al_get_bitmap_height(bg), 0, 0, al_get_display_width(display), al_get_display_height(display), 0);

        // Desenhar o personagem redimensionado com base no frame atual
        if (facing_right) {
            al_draw_scaled_bitmap(sprite_sheet, frame_cx, frame_cy, frame_width, frame_height, pos_x, pos_y, frame_width * scale_factor, frame_height * scale_factor, 0);
        }
        else {
            al_draw_scaled_bitmap(sprite_sheet, frame_cx, frame_cy, frame_width, frame_height, pos_x, pos_y, frame_width * scale_factor, frame_height * scale_factor, ALLEGRO_FLIP_HORIZONTAL);
        }

        al_flip_display();
    }

    al_destroy_bitmap(bg);
    al_destroy_bitmap(sprite_sheet);
    al_destroy_display(display);
    al_destroy_event_queue(event_queue);

    return 0;
}
