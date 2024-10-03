// #include <allegro5/allegro.h>
// #include <allegro5/allegro_image.h>
// #include <allegro5/allegro_primitives.h>
// #include <stdio.h>

// // Definir el enum GameState
// typedef enum { MENU, RESUMO, FASE_1 } GameState;

// // Funciones de las distintas fases
// void iniciar_tela_menu(ALLEGRO_DISPLAY* display, ALLEGRO_BITMAP* background);
// void iniciar_fase_1(ALLEGRO_DISPLAY* display);

// int main() {
//     // Inicializar Allegro y sus addons
//     if (!al_init()) {
//         printf("Error al inicializar Allegro!\n");
//         return -1;
//     }
//     al_init_image_addon();
//     al_install_mouse();
//     al_init_primitives_addon();

//     // Crear display de 1280x720
//     ALLEGRO_DISPLAY* display = al_create_display(1280, 720);
//     if (!display) {
//         printf("Error al crear el display!\n");
//         return -1;
//     }
//     al_set_window_title(display, "A Revolu��o Francesa");

//     // Cargar imagen de fondo
//     ALLEGRO_BITMAP* background = al_load_bitmap("./telainicio.png");
//     if (!background) {
//         printf("Error al cargar la imagen de fondo!\n");
//         al_destroy_display(display);
//         return -1;
//     }

//     // Iniciar la pantalla de men�
//     iniciar_tela_menu(display, background);

//     // Limpiar recursos
//     al_destroy_bitmap(background);
//     al_destroy_display(display);

//     return 0;
// }

// // Funci�n para iniciar la pantalla de men�
// void iniciar_tela_menu(ALLEGRO_DISPLAY* display, ALLEGRO_BITMAP* background) {
//     // Variable para controlar el estado del juego
//     GameState game_state = MENU;

//     ALLEGRO_EVENT_QUEUE* event_queue = al_create_event_queue();
//     ALLEGRO_TIMER* timer = al_create_timer(1.0 / 60.0);

//     al_register_event_source(event_queue, al_get_display_event_source(display));
//     al_register_event_source(event_queue, al_get_timer_event_source(timer));
//     al_register_event_source(event_queue, al_get_mouse_event_source());

//     al_start_timer(timer);

//     bool running = true; // Controla el ciclo principal del juego

//     while (running) {
//         ALLEGRO_EVENT event;
//         al_wait_for_event(event_queue, &event);

//         if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
//             running = false;  // Salir del programa
//         }

//         if (game_state == MENU) {
//             // Pantalla de inicio
//             if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
//                 int mouse_x = event.mouse.x;
//                 int mouse_y = event.mouse.y;

//                 // Verificar clic en el bot�n "Iniciar Juego"
//                 if (mouse_x >= 456 && mouse_x <= 813 && mouse_y >= 604 && mouse_y <= 647) {
//                     printf("Iniciar Jogo fue clicado!\n");
//                     game_state = FASE_1;  // Cambiar estado a FASE_1
//                 }

//                 // Verificar clic en el bot�n "Salir"
//                 if (mouse_x >= 879 && mouse_x <= 1184 && mouse_y >= 599 && mouse_y <= 654) {
//                     printf("Sair fue clicado!\n");
//                     running = false;  // Salir del ciclo principal
//                 }

//                 // Verificar clic en el bot�n "Resumen"
//                 if (mouse_x >= 120 && mouse_x <= 380 && mouse_y >= 561 && mouse_y <= 695) {
//                     printf("Resumo fue clicado!\n");
//                     game_state = RESUMO;
//                 }
//             }

//             // Dibujar la imagen de fondo que cubre toda la pantalla
//             al_draw_scaled_bitmap(background, 0, 0, al_get_bitmap_width(background), al_get_bitmap_height(background), 0, 0, al_get_display_width(display), al_get_display_height(display), 0);

//             al_flip_display();
//         }
//         else if (game_state == RESUMO) {
//             // Pantalla de resumen (s�lo fondo negro ahora)
//             al_clear_to_color(al_map_rgb(0, 0, 0));

//             // Verificar si el usuario hizo clic para volver al men�
//             if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
//                 game_state = MENU;  // Volver al men�
//             }

//             al_flip_display();
//         }
//         else if (game_state == FASE_1) {
//             iniciar_fase_1(display);  // Iniciar Fase 1
//             game_state = MENU;  // Despu�s de la Fase 1, volver al men�
//         }
//     }

//     // Limpiar recursos
//     al_destroy_timer(timer);
//     al_destroy_event_queue(event_queue);
// }

// // Funci�n para iniciar la Fase 1
// void iniciar_fase_1(ALLEGRO_DISPLAY* display) {
//     // Aqu� puedes poner la l�gica de la Fase 1
//     ALLEGRO_EVENT_QUEUE* event_queue = al_create_event_queue();
//     ALLEGRO_TIMER* timer = al_create_timer(1.0 / 60.0);

//     al_register_event_source(event_queue, al_get_display_event_source(display));
//     al_register_event_source(event_queue, al_get_timer_event_source(timer));

//     al_start_timer(timer);

//     bool running = true; // Controla la ejecuci�n de la Fase 1

//     while (running) {
//         ALLEGRO_EVENT event;
//         al_wait_for_event(event_queue, &event);

//         if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
//             running = false;  // Salir de la Fase 1
//         }

//         // L�gica de la Fase 1
//         al_clear_to_color(al_map_rgb(0, 255, 0)); // Aqu� puedes cambiar el color o la l�gica a tu gusto
//         al_flip_display(); // Actualizar la pantalla

//         al_rest(0.01);  // Pausa para no sobrecargar el ciclo
//     }

//     al_destroy_timer(timer);
//     al_destroy_event_queue(event_queue);
// }