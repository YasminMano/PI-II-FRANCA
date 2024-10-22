#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <stdio.h>
#include "headers/game.h"  // Inclui a definição de GameState e a estrutura AllegroGame
#include "headers/Tela_inicio.h"  // Inclui a função para inicializar a tela de menu

// Declaração da função de iniciar a fase 1, já que não há um arquivo de cabeçalho `Fase_1.h`
void iniciar_fase_1(ALLEGRO_DISPLAY* display);

int main() {
    // Inicializa o Allegro e verifica se a inicialização foi bem-sucedida
    if (!al_init()) {
        printf("Erro ao inicializar Allegro!\n");
        return -1;  // Retorna -1 se houver erro
    }

    // Inicializa o addon de imagens e o suporte ao mouse, e adiciona primitivas como formas geométricas
    al_init_image_addon();  // Para carregar e manipular imagens
    al_install_mouse();  // Para usar eventos de mouse
    al_init_primitives_addon();  // Para desenhar formas simples como linhas e círculos

    // Cria uma janela de 1280x720 para o jogo
    ALLEGRO_DISPLAY* display = al_create_display(1280, 720);
    if (!display) {
        printf("Erro ao criar o display!\n");
        return -1;  // Retorna -1 se houver erro ao criar a janela
    }

    // Define o título da janela
    al_set_window_title(display, "A Revolucao Francesa");

    // Carrega a imagem de fundo que será usada no menu
    ALLEGRO_BITMAP* background = al_load_bitmap("assets/images/telainicio.png");
    if (!background) {
        printf("Erro ao carregar a imagem de fundo!\n");
        al_destroy_display(display);  // Se não carregar a imagem, fecha a janela
        return -1;  // Retorna -1 se houver erro ao carregar a imagem
    }

    // Chama a função que inicializa a tela de menu e passa o display e a imagem de fundo
    iniciar_tela_menu(display, background);

    // Libera a memória ocupada pela imagem de fundo e o display após o uso
    al_destroy_bitmap(background);
    al_destroy_display(display);

    return 0;  // Retorna 0 para indicar que o programa terminou sem erros
}
