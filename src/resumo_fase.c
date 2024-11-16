#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <stdio.h>
#include "headers/resumo_fase.h"
#include "headers/game.h"  // Inclua o game.h para acessar GameState e FASE_1

void init_resumo_fase_1(ALLEGRO_DISPLAY* display, GameState* game_state) {
    // Cria uma fonte embutida do Allegro
    ALLEGRO_FONT* font = al_create_builtin_font();
    if (!font) {
        printf("Falha ao criar a fonte embutida do Allegro.\n");
        return;
    }

    bool running = true;
    ALLEGRO_EVENT_QUEUE* queue = al_create_event_queue();
    ALLEGRO_EVENT event;

    // Registra as fontes de eventos
    al_register_event_source(queue, al_get_display_event_source(display));
    al_register_event_source(queue, al_get_mouse_event_source());

    while (running) {
        al_wait_for_event(queue, &event);

        // Fecha a janela se necessário
        if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
            running = false;
        }

        // Verifica cliques no botão "Continuar"
        if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
            int mouse_x = event.mouse.x;
            int mouse_y = event.mouse.y;

            // Verifica se o botão "Continuar" foi clicado
            if (mouse_x >= 550 && mouse_x <= 730 && mouse_y >= 600 && mouse_y <= 650) {
                running = false; // Sai da tela de resumo
                *game_state = FASE_1; // Atualiza o estado para FASE_1
            }
        }

        // Desenha a tela de resumo
        al_clear_to_color(al_map_rgb(0, 0, 0)); // Fundo preto

        // Configuração do texto
        ALLEGRO_COLOR white = al_map_rgb(255, 255, 255);
        int x = al_get_display_width(display) / 2;
        int y = 50; // Posição inicial do texto na tela

        // Texto do resumo
        al_draw_text(font, white, x, y, ALLEGRO_ALIGN_CENTER, "Resumo da Fase 1:");
        y += 40;
        al_draw_text(font, white, x, y, ALLEGRO_ALIGN_CENTER, "Na Fase 1, você enfrentará desafios perigosos.");
        y += 20;
        al_draw_text(font, white, x, y, ALLEGRO_ALIGN_CENTER, "Enfrente os guardas e avance na Revolução!");
        y += 40; // Espaço maior entre as seções

        // Texto sobre a Queda da Bastilha
        al_draw_text(font, white, x, y, ALLEGRO_ALIGN_CENTER, "A Queda da Bastilha, ocorrida em 14 de julho de 1789,");
        y += 20;
        al_draw_text(font, white, x, y, ALLEGRO_ALIGN_CENTER, "é um dos eventos mais emblemáticos da Revolução Francesa.");
        y += 20;
        al_draw_text(font, white, x, y, ALLEGRO_ALIGN_CENTER, "A Bastilha era uma fortaleza-prisão em Paris que");
        y += 20;
        al_draw_text(font, white, x, y, ALLEGRO_ALIGN_CENTER, "representava o poder arbitrário e a opressão do Antigo Regime,");
        y += 20;
        al_draw_text(font, white, x, y, ALLEGRO_ALIGN_CENTER, "sob o reinado de Luís XVI.");
        y += 20;
        al_draw_text(font, white, x, y, ALLEGRO_ALIGN_CENTER, "Embora contivesse apenas alguns prisioneiros na época,");
        y += 20;
        al_draw_text(font, white, x, y, ALLEGRO_ALIGN_CENTER, "sua captura foi simbolicamente importante.");
        y += 20;
        al_draw_text(font, white, x, y, ALLEGRO_ALIGN_CENTER, "Nesse dia, uma multidão revoltosa, em busca de armas e pólvora,");
        y += 20;
        al_draw_text(font, white, x, y, ALLEGRO_ALIGN_CENTER, "cercou e invadiu a Bastilha.");
        y += 20;
        al_draw_text(font, white, x, y, ALLEGRO_ALIGN_CENTER, "A queda da Bastilha sinalizou o início do colapso da autoridade real");
        y += 20;
        al_draw_text(font, white, x, y, ALLEGRO_ALIGN_CENTER, "e provocou uma onda de violência e revolta por toda a França.");
        y += 40; // Espaço maior antes das instruções

        // Instruções de controle do personagem
        al_draw_text(font, white, x, y, ALLEGRO_ALIGN_CENTER, "Controles do Personagem:");
        y += 40;
        al_draw_text(font, white, x, y, ALLEGRO_ALIGN_CENTER, "Pressione A para andar para a esquerda");
        y += 20;
        al_draw_text(font, white, x, y, ALLEGRO_ALIGN_CENTER, "Pressione D para andar para a direita");
        y += 20;
        al_draw_text(font, white, x, y, ALLEGRO_ALIGN_CENTER, "Pressione ESPAÇO para pular");

        // Botão "Continuar"
        al_draw_filled_rectangle(550, 600, 730, 650, al_map_rgb(100, 100, 100)); // Fundo cinza
        al_draw_text(font, white, 640, 615, ALLEGRO_ALIGN_CENTER, "Continuar");

        al_flip_display();
    }

    // Libera os recursos
    al_destroy_font(font);
    al_destroy_event_queue(queue);
}
