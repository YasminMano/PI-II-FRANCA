#ifndef TELA_INICIO_H
#define TELA_INICIO_H

#include <allegro5/allegro.h>

// Função que inicia a tela de menu do jogo, recebendo o display onde será exibido 
// e o background (imagem de fundo) que será desenhado na tela.
void iniciar_tela_menu(ALLEGRO_DISPLAY* display, ALLEGRO_BITMAP* background);

#endif

/*
Resumo:
O arquivo tela_inicio.h contém a declaração da função iniciar_tela_menu,
que é responsável por inicializar e desenhar a tela de menu do jogo.
Essa função utiliza o display do Allegro para exibir a interface gráfica
e desenha um fundo específico passado como parâmetro.
*/