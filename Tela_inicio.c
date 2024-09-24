#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <stdio.h>

// Definir o enum GameState
typedef enum { MENU, RESUMO } GameState;

// Função para iniciar a tela de menu
void iniciar_tela_menu();

int main() {
    // Chamar a função de inicialização da tela de menu
    iniciar_tela_menu();
    return 0;
}

void iniciar_tela_menu() {
    // Inicializar Allegro e seus addons
    al_init();
    al_init_image_addon();
    al_install_mouse();
    al_init_primitives_addon();
    al_init_font_addon();
    al_init_ttf_addon();

    // Carregar a fonte
    ALLEGRO_FONT* font = al_load_ttf_font("pixel_arial_11/PIXEARG_.TTF", 18, 0);
    if (!font) {
        printf("Falha ao carregar a fonte!\n");
        return;
    }

    // Criar display em tela cheia
    ALLEGRO_DISPLAY* display = al_create_display(1280, 720);
    al_set_window_title(display, "A Revolução Francesa");

    // Carregar imagem da tela de início
    ALLEGRO_BITMAP* background = al_load_bitmap("./telainicio.png");

    // Verificar se a imagem foi carregada corretamente
    if (!background) {
        printf("Falha ao carregar a imagem de fundo!\n");
        return;
    }

    // Variável para controlar o estado do jogo
    GameState game_state = MENU;

    ALLEGRO_EVENT_QUEUE* event_queue = al_create_event_queue();
    ALLEGRO_TIMER* timer = al_create_timer(1.0 / 60.0);

    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_timer_event_source(timer));
    al_register_event_source(event_queue, al_get_mouse_event_source());

    al_start_timer(timer);

    bool running = true; // Variável de controle para manter o loop ativo

    while (running) {
        ALLEGRO_EVENT event;
        al_wait_for_event(event_queue, &event);

        if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
            running = false;  // Fechar o programa
        }

        if (game_state == MENU) {
            // Tela de início
            if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
                int mouse_x = event.mouse.x;
                int mouse_y = event.mouse.y;

                // Verificar clique na área do botão "Iniciar Jogo"
                if (mouse_x >= 456 && mouse_x <= 813 && mouse_y >= 604 && mouse_y <= 647) {
                    printf("Iniciar Jogo foi clicado!\n");
                    // Aqui você pode adicionar a lógica para iniciar o jogo
                }

                // Verificar clique na área do botão "Sair"
                if (mouse_x >= 879 && mouse_x <= 1184 && mouse_y >= 599 && mouse_y <= 654) {
                    printf("Sair foi clicado!\n");
                    running = false;  // Sair do loop principal e fechar o programa
                }

                // Verificar clique na área do botão "Resumo"
                if (mouse_x >= 120 && mouse_x <= 380 && mouse_y >= 561 && mouse_y <= 695) {
                    printf("Resumo foi clicado!\n");
                    game_state = RESUMO;
                }
            }

            // Desenhar a imagem de fundo que cobre toda a tela
            al_draw_scaled_bitmap(background, 0, 0, al_get_bitmap_width(background), al_get_bitmap_height(background), 0, 0, al_get_display_width(display), al_get_display_height(display), 0);

            al_flip_display();
        }
        else if (game_state == RESUMO) {
            // Tela de resumo (texto da revolução)
            al_clear_to_color(al_map_rgb(0, 0, 0));
            al_draw_text(font, al_map_rgb(255, 255, 255), 50, 50, 0, "A Revolução Francesa, um dos marcos mais significativos da história moderna,");
            al_draw_text(font, al_map_rgb(255, 255, 255), 50, 70, 0, "ocorreu entre 1789 e 1799. Ela começou com profundas crises econômicas, sociais");
            al_draw_text(font, al_map_rgb(255, 255, 255), 50, 90, 0, "e políticas na França monárquica, exacerbadas por dívidas nacionais e fome.");

            // Aqui você pode adicionar o resto do texto, ajustando as coordenadas y conforme necessário

            // Verificar se o usuário clicou para voltar ao menu
            if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
                game_state = MENU;  // Voltar ao menu
            }

            al_flip_display();
        }
    }

    // Limpar recursos
    al_destroy_bitmap(background);
    al_destroy_timer(timer);
    al_destroy_font(font);
    al_destroy_display(display);
    al_destroy_event_queue(event_queue);
}
