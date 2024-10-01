#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>//para receber imagens

int main8() {

    al_init();//inicia o allegro
    al_init_image_addon();//inicia as imagens

    ALLEGRO_DISPLAY* display = al_create_display(640, 480);//cria o tamanho da janela
    al_set_window_position(display, 1280, 720);//fala onde é para a janela ser criada
    al_set_window_title(display, "Revolução Francesa");
    ALLEGRO_BITMAP* homem = al_load_bitmap("./homem.png");
    ALLEGRO_TIMER* timer = al_create_timer(1.0 / 60.0);

    ALLEGRO_EVENT_QUEUE* event_queue = al_create_event_queue();
    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_timer_event_source(timer));
    al_start_timer(timer);

    while (true) {
        ALLEGRO_EVENT event;
        al_wait_for_event(event_queue, &event);
        if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
            break;
        }

        al_clear_to_color(al_map_rgb(255, 0, 0));
        al_draw_bitmap(homem, 0, 0, 0);
        al_flip_display();
    }

    al_destroy_display(display);
    al_destroy_event_queue(event_queue);
    al_destroy_bitmap(homem);

    return 0;
} 