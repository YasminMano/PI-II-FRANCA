#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <stdio.h>
#include "resumo_fase.h"
#include "game.h"

void init_resumo_fase_1(ALLEGRO_DISPLAY* display, GameState* game_state) {
    ALLEGRO_FONT* font = al_create_builtin_font();
    if (!font) {
        printf("Falha ao criar a fonte embutida do Allegro.\n");
        return;
    }

    ALLEGRO_BITMAP* bg = al_load_bitmap("assets/images/fundo_inicio.png");
    if (!bg) {
        al_destroy_display(display);
        return;
    }

    bool running = true;
    ALLEGRO_EVENT_QUEUE* queue = al_create_event_queue();
    ALLEGRO_EVENT event;

    al_register_event_source(queue, al_get_display_event_source(display));
    al_register_event_source(queue, al_get_mouse_event_source());

    while (running) {
        al_wait_for_event(queue, &event);

        if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
            running = false;
        }

        if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
            int mouse_x = event.mouse.x;
            int mouse_y = event.mouse.y;

            if (mouse_x >= 550 && mouse_x <= 730 && mouse_y >= 600 && mouse_y <= 650) {
                running = false;
                *game_state = MAPA;
            }
        }

        al_clear_to_color(al_map_rgb(0, 0, 0));

        ALLEGRO_COLOR white = al_map_rgb(0, 0, 0);
        int x = al_get_display_width(display) / 2;
        int y = 50;

        al_clear_to_color(al_map_rgb(255, 255, 255));
        al_draw_scaled_bitmap(bg, 0, 0, al_get_bitmap_width(bg), al_get_bitmap_height(bg), 0, 0, al_get_display_width(display), al_get_display_height(display), 0);

        al_draw_filled_rectangle(550, 600, 730, 650, al_map_rgb(100, 100, 100));
        al_draw_text(font, white, 640, 615, ALLEGRO_ALIGN_CENTER, "Voltar");

        al_draw_text(font, white, x, y, ALLEGRO_ALIGN_CENTER, "Resumo da Fase 1:");
        y += 40;
        al_draw_text(font, white, x, y, ALLEGRO_ALIGN_CENTER, "Na Fase 1, você enfrentará desafios perigosos.");
        y += 20;
        al_draw_text(font, white, x, y, ALLEGRO_ALIGN_CENTER, "Enfrente os guardas e avance na Revolução!");
        y += 40;

        al_draw_text(font, white, x, y, ALLEGRO_ALIGN_CENTER, "A Queda da Bastilha, ocorrida em 14 de julho de 1789,");
        y += 20;
        al_draw_text(font, white, x, y, ALLEGRO_ALIGN_CENTER, "foi um dos eventos mais emblemáticos da Revolução Francesa.");
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
        y += 40;

        al_draw_text(font, white, x, y, ALLEGRO_ALIGN_CENTER, "Objetivos:");
        y += 20;
        al_draw_text(font, white, x, y, ALLEGRO_ALIGN_CENTER, "Encontre a camponesa presa pelos guardas");
        y += 20;
        al_draw_text(font, white, x, y, ALLEGRO_ALIGN_CENTER, "e a liberte para irem a Versalhes encontrar o rei!");
        y += 40;

        al_draw_text(font, white, x, y, ALLEGRO_ALIGN_CENTER, "Controles do Personagem:");
        y += 40;
        al_draw_text(font, white, x, y, ALLEGRO_ALIGN_CENTER, "Pressione A para andar para a esquerda");
        y += 20;
        al_draw_text(font, white, x, y, ALLEGRO_ALIGN_CENTER, "Pressione D para andar para a direita");
        y += 20;
        al_draw_text(font, white, x, y, ALLEGRO_ALIGN_CENTER, "Pressione F para interagir");
        y += 20;
        al_draw_text(font, white, x, y, ALLEGRO_ALIGN_CENTER, "Pressione ESPAÇO para pular");
        al_flip_display();
    }

    al_destroy_font(font);
    al_destroy_event_queue(queue);
    al_destroy_bitmap(bg);
}

void init_resumo_fase_2(ALLEGRO_DISPLAY* display, GameState* game_state) {
    // Cria uma fonte embutida do Allegro
    ALLEGRO_FONT* font = al_create_builtin_font();
    if (!font) {
        printf("Falha ao criar a fonte embutida do Allegro.\n");
        return;
    }

    ALLEGRO_BITMAP* bg = al_load_bitmap("assets/images/fundo_inicio.png");
    if (!bg) {
        al_destroy_display(display);
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

        // Fecha a janela se necess�rio
        if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
            running = false;
        }

        // Verifica cliques no bot�o "Voltar"
        if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
            int mouse_x = event.mouse.x;
            int mouse_y = event.mouse.y;

            // Verifica se o bot�o "Voltar" foi clicado
            if (mouse_x >= 550 && mouse_x <= 730 && mouse_y >= 600 && mouse_y <= 650) {
                running = false; // Sai da tela de resumo
                *game_state = MAPA; // Atualiza o estado para MAPA
            }
        }

        // Desenha a tela de resumo
        al_clear_to_color(al_map_rgb(0, 0, 0)); // Fundo preto

        // Configura��o do texto
        ALLEGRO_COLOR white = al_map_rgb(0, 0, 0);
        int x = al_get_display_width(display) / 2;
        int y = 80; // Posicao inicial do texto na tela

        al_clear_to_color(al_map_rgb(255, 255, 255));
        al_draw_scaled_bitmap(bg, 0, 0, al_get_bitmap_width(bg), al_get_bitmap_height(bg), 0, 0, al_get_display_width(display), al_get_display_height(display), 0);
        al_draw_filled_rectangle(550, 600, 730, 650, al_map_rgb(100, 100, 100)); // Fundo cinza
        al_draw_text(font, white, 640, 615, ALLEGRO_ALIGN_CENTER, "Voltar");
        // Texto do resumo
        al_draw_text(font, white, x, y, ALLEGRO_ALIGN_CENTER, "Resumo da Fase 2:");
        y += 40;
        al_draw_text(font, white, x, y, ALLEGRO_ALIGN_CENTER, "Na Fase 2, voce ira para o palacio de Versalhes");
        y += 20;
        al_draw_text(font, white, x, y, ALLEGRO_ALIGN_CENTER, "Chegue ao palacio de Versalhes e encontre as chaves para ir a sala do rei!");
        y += 40; // Espa�o maior entre as se��es

        // Texto sobre a Marcha das mulheres
        al_draw_text(font, white, x, y, ALLEGRO_ALIGN_CENTER, "A Marcha das Mulheres a Versalhes foi um protesto em outubro de 1789");
        y += 20;
        al_draw_text(font, white, x, y, ALLEGRO_ALIGN_CENTER, "durante a Revolucao, liderado principalmente por mulheres de Paris.");
        y += 20;
        al_draw_text(font, white, x, y, ALLEGRO_ALIGN_CENTER, "Insatisfeitas com a escassez de pão e os altos preços,");
        y += 20;
        al_draw_text(font, white, x, y, ALLEGRO_ALIGN_CENTER, "elas marcharam até o Palácio de Versalhes para exigir ações do rei Luis XVI");
        y += 20;
        al_draw_text(font, white, x, y, ALLEGRO_ALIGN_CENTER, "O movimento resultou na transferência da família real para Paris,");
        y += 20;
        al_draw_text(font, white, x, y, ALLEGRO_ALIGN_CENTER, "marcando um momento simbólico de poder popular e influência feminina na revolução.");
        y += 40; // Espa�o maior antes das instru��es

        al_draw_text(font, white, x, y, ALLEGRO_ALIGN_CENTER, "Objetivos:");
        y += 20;
        al_draw_text(font, white, x, y, ALLEGRO_ALIGN_CENTER, "Chegue ao palacio de Versalhes e encontre a chave escondida");
        y += 20;
        al_draw_text(font, white, x, y, ALLEGRO_ALIGN_CENTER, "para acessar a sala do Rei Luis XVI!");
        y += 40;

        // Instru��es de controle do personagem
        al_draw_text(font, white, x, y, ALLEGRO_ALIGN_CENTER, "Controles do Personagem:");
        y += 40;
        al_draw_text(font, white, x, y, ALLEGRO_ALIGN_CENTER, "Pressione A para andar para a esquerda");
        y += 20;
        al_draw_text(font, white, x, y, ALLEGRO_ALIGN_CENTER, "Pressione D para andar para a direita");
        y += 20;
        al_draw_text(font, white, x, y, ALLEGRO_ALIGN_CENTER, "Pressione F para interagir");
        y += 20;
        al_draw_text(font, white, x, y, ALLEGRO_ALIGN_CENTER, "Pressione E para abrir");
        y += 20;
        al_draw_text(font, white, x, y, ALLEGRO_ALIGN_CENTER, "Pressione ESPACO para pular");
        y += 20;
        al_flip_display();
    }
    // Libera os recursos
    al_destroy_font(font);
    al_destroy_event_queue(queue);
    al_destroy_bitmap(bg);
}

void init_resumo_fase_3(ALLEGRO_DISPLAY* display, GameState* game_state) {
    // Cria uma fonte embutida do Allegro
    ALLEGRO_FONT* font = al_create_builtin_font();
    if (!font) {
        printf("Falha ao criar a fonte embutida do Allegro.\n");
        return;
    }

    ALLEGRO_BITMAP* bg = al_load_bitmap("assets/images/fundo_inicio.png");
    if (!bg) {
        al_destroy_display(display);
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

        // Fecha a janela se necess�rio
        if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
            running = false;
        }

        // Verifica cliques no bot�o "Voltar"
        if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
            int mouse_x = event.mouse.x;
            int mouse_y = event.mouse.y;

            // Verifica se o bot�o "Voltar" foi clicado
            if (mouse_x >= 550 && mouse_x <= 730 && mouse_y >= 600 && mouse_y <= 650) {
                running = false; // Sai da tela de resumo
                *game_state = MAPA; // Atualiza o estado para MAPA
            }
        }

        // Desenha a tela de resumo
        al_clear_to_color(al_map_rgb(0, 0, 0)); // Fundo preto

        // Configura��o do texto
        ALLEGRO_COLOR white = al_map_rgb(0, 0, 0);
        int x = al_get_display_width(display) / 2;
        int y = 80; // Posicao inicial do texto na tela

        al_clear_to_color(al_map_rgb(255, 255, 255));
        al_draw_scaled_bitmap(bg, 0, 0, al_get_bitmap_width(bg), al_get_bitmap_height(bg), 0, 0, al_get_display_width(display), al_get_display_height(display), 0);
        al_draw_filled_rectangle(550, 600, 730, 650, al_map_rgb(100, 100, 100)); // Fundo cinza
        al_draw_text(font, white, 640, 615, ALLEGRO_ALIGN_CENTER, "Voltar");
        // Texto do resumo
        al_draw_text(font, white, x, y, ALLEGRO_ALIGN_CENTER, "Resumo da Fase 3:");
        y += 40;
        al_draw_text(font, white, x, y, ALLEGRO_ALIGN_CENTER, "Na Fase 3, você enfrentara o causador da revolucao, Luis XVI");
        y += 20;
        al_draw_text(font, white, x, y, ALLEGRO_ALIGN_CENTER, "Enfrente-o e conquiste a Franca!");
        y += 40; // Espa�o maior entre as se��es
        // Texto sobre a Queda da Bastilha
        al_draw_text(font, white, x, y, ALLEGRO_ALIGN_CENTER, "A queda de Luis XVI culminou em sua execucao em 21 de janeiro de 1793.");
        y += 20;
        al_draw_text(font, white, x, y, ALLEGRO_ALIGN_CENTER, "pos a descoberta de documentos que comprovaram sua conspiração contra a Revolução,");
        y += 20;
        al_draw_text(font, white, x, y, ALLEGRO_ALIGN_CENTER, "ele foi julgado pela Convenção Nacional e condenado por traição.");
        y += 20;
        al_draw_text(font, white, x, y, ALLEGRO_ALIGN_CENTER, "A execução por guilhotina na Praça da Revolucao simbolizou o fim definitivo");
        y += 20;
        al_draw_text(font, white, x, y, ALLEGRO_ALIGN_CENTER, "da monarquia absolutista na Franca e consolidou a Republica, intensificando");
        y += 20;
        al_draw_text(font, white, x, y, ALLEGRO_ALIGN_CENTER, "os conflitos internos e externos que marcariam o periodo revolucionario.");
        y += 40; // Espa�o maior antes das instru��es
        al_draw_text(font, white, x, y, ALLEGRO_ALIGN_CENTER, "Objetivos:");
        y += 20;
        al_draw_text(font, white, x, y, ALLEGRO_ALIGN_CENTER, "Resolva os enigmas do rei e");
        y += 20;
        al_draw_text(font, white, x, y, ALLEGRO_ALIGN_CENTER, "acabe com o reinado de Luis e retome a Franca para o povo!");
        y += 40;
        // Instru��es de controle do personagem
        al_draw_text(font, white, x, y, ALLEGRO_ALIGN_CENTER, "Controles do Personagem:");
        y += 40;
        al_draw_text(font, white, x, y, ALLEGRO_ALIGN_CENTER, "Pressione A para andar para a esquerda");
        y += 20;
        al_draw_text(font, white, x, y, ALLEGRO_ALIGN_CENTER, "Pressione D para andar para a direita");
        y += 20;
        al_draw_text(font, white, x, y, ALLEGRO_ALIGN_CENTER, "Pressione F para interagir");
        y += 20;
        al_draw_text(font, white, x, y, ALLEGRO_ALIGN_CENTER, "Pressione ESPACO para pular");
        al_flip_display();
    }
    // Libera os recursos
    al_destroy_font(font);
    al_destroy_event_queue(queue);
    al_destroy_bitmap(bg);
}