#include <stdio.h>
#include <stdlib.h>

#include "config_arena.h"

void inicializar_lista(TLISTA *pLista)
{
    (*pLista) = NULL;
}

void inicializar_arena(void)
{
    int i, j;

    for (i = 0; i < LINHAS; i++) {
        for (j = 0; j < COLUNAS; j++) {
            arena[i][j] = '.';
        }
    }
}

int menu_principal(void)
{
    int opcao;
    
    printf("\n -- Menu Principal -- \n");
    printf(" (1) Posicionar peças \n");
    printf(" (2) Retirar peças \n");
    printf(" (3) Posicionar robô inicial \n");
    printf(" (4) Posicionar destinos \n");
    printf(" (5) Visualizar arena \n");
    printf(" (9) Sair \n\n");

    printf(" Opção : ");
    scanf(" %d", &opcao);

    return opcao;
}

void visualizar_arena(void)
{
    int i, j;
    
    printf("\t\t    0  1  2  3  4  5\n");
    
    for (i = 0; i < LINHAS; i++) {
        printf("\t\t%2d", i); 
        
        for (j = 0; j < COLUNAS; j++) {
            colorir_obj_arena(i, j);
        }
        putchar('\n');
    }
}

void posicionar_obj(TLISTA *pLista, TOBJETO pObj)
{
    struct TNO *novo;

    novo = (struct TNO *) malloc(sizeof (struct TNO));
    novo->objeto = pObj;
    novo->prox = NULL;

    if (*pLista == NULL) {
        (*pLista) = novo;
    }
    else {
        novo->prox = (*pLista);
        (*pLista) = novo;
    }
}

void retirar_obj(TLISTA *pLista)
{
    struct TNO *aux1, *aux2;
    int num_obj, cont;
    int x, y;
    
    aux2 = (*pLista);
    aux1 = NULL;
    
    if (aux2 == NULL) {
        printf("\n Não há objetos para serem retirados.\n");
        return;
    }
    
    printf("\n Qual objeto deseja retirar: ");
    scanf(" %d", &num_obj);
    
    cont = 1;
    while ((aux2 != NULL) && (cont != num_obj)) {
        aux1 = aux2;
        aux2 = aux2->prox;
        
        cont += 1;
    }
	
    if (aux2 == NULL)  {   
        printf("\n Registro não existe.\n");
        return;
    }
    else if (aux1 == NULL) {    
        aux2 = (*pLista); 
        (*pLista) = aux2->prox;
        
         x = aux2->objeto.x;
         y = aux2->objeto.y;

        free(aux2);      
    }                                     
    else {					 
        aux1->prox = aux2->prox;
        
        x = aux2->objeto.x;
        y = aux2->objeto.y;
        
        free(aux2);
    }
    arena[x][y] = '.';     // Retira objeto da arena
}

TOBJETO ler_objeto(int tipo)					
{
    TOBJETO o;
    
    do {
        switch (tipo) {
            case PECA:
                printf("\n 1. Coordenadas da peça\n");
                printf("    Digite X: ");
                scanf(" %d", &o.x);
                
                printf("    Digite Y: ");
                scanf(" %d", &o.y);
            
                printf("\n 2. Cor da peça\n");
                printf(" <R> para vermelho, <G> para verde, <B> para azul\n");
                printf("    Digite a cor: ");
                scanf(" %c", &o.cor);
             
                o.tipo = PECA;
                break;
            case ROBO:
                printf("\n 1. Coordenadas do robô\n");
                printf("    Digite X: ");
                scanf(" %d", &o.x);
                
                printf("    Digite Y: ");
                scanf(" %d", &o.y);
                
                o.cor = 'Y';
                o.tipo = ROBO;
                break;
            case DESTINO:
                printf("\n 1. Coordenadas do destino\n");
                printf("    Digite X: ");
                scanf(" %d", &o.x);
                
                printf("    Digite Y: ");
                scanf(" %d", &o.y);
                
                printf("\n 2. Cor do destino\n");
                printf(" <R> para vermelho, <G> para verde, <B> para azul\n");
                printf("    Digite a cor: ");
                scanf(" %c", &o.cor);
                
                o.tipo = DESTINO;
                
                if (o.cor == 'R') {
                    o.cor = VERMELHO;
                }
                else if (o.cor == 'G') {
                    o.cor = VERDE;
                }
                else if (o.cor == 'B') {
                    o.cor = AZUL;
                }
                break;
        }
        
        if (arena[o.x][o.y] != '.') {
            printf("\n Peça já existente neste local. Tente novamente.\n");
        }
    } while (arena[o.x][o.y] != '.');
    
    if (tipo == PECA || tipo == DESTINO) {
        arena[o.x][o.y] = o.cor;
    }
    else if (tipo == ROBO) {
        arena[o.x][o.y] = 'O';
    }
    
    return o;          
}

void visualizar_lista_obj(TLISTA pLista) 
{
    TLISTA aux1 = pLista;
    int cont = 1;

    while (aux1 != NULL) {
        printf(" %d. (%d, %d, %s, %s)\n", cont, aux1->objeto.x, aux1->objeto.y, 
                                          retornar_nome(aux1->objeto.tipo), 
                                          retornar_nome_cor(aux1->objeto.cor));
        
        aux1 = aux1->prox;
        cont += 1;
    }                                             
}

void colorir_obj_arena(int i, int j)
{
    switch (arena[i][j]) {
        case 'R': printf("%s  %c%s", RED, arena[i][j], RESET);
                  break;
        case 'B': printf("%s  %c%s", BLU, arena[i][j], RESET);
                  break;
        case 'G': printf("%s  %c%s", GRN, arena[i][j], RESET);
                  break;
        case 'O': printf("%s  %c%s", YEL, arena[i][j], RESET);
                  break;
        case '1': printf("%s  D%s", RED, RESET);
                  break;
        case '2': printf("%s  D%s", GRN, RESET);
                  break;
        case '3': printf("%s  D%s", BLU, RESET);
                  break;
        default: printf("  %c", arena[i][j]);
    }
}

char *retornar_nome(int tipo)
{
    char *nome;
    
    switch (tipo) {
        case PECA:
            nome = "PEÇA";
            break;
        case ROBO:
            nome = "ROBÔ";
            break;
        case DESTINO:
            nome = "DESTINO";
            break;
    }
    return nome;
}

char *retornar_nome_cor(int cor)
{
    char *nome_cor;
    
    switch (cor) {
        case 'R': case VERMELHO:
            nome_cor = "VERMELHO";
            break;
        case 'G': case VERDE:
            nome_cor = "VERDE";
            break;
        case 'B': case AZUL:
            nome_cor = "AZUL";
            break;
        case 'Y':
            nome_cor = "AMARELO";
            break;
    }
    return nome_cor;
}
