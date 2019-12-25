#ifndef MODULO1_CABECALHO_H
#define MODULO1_CABECALHO_H

#define  LINHAS 6       // Protótipo da arena é uma matrix de 10x10. 
#define COLUNAS 6

#define RED   "\x1B[31m"  // Solução de colorir para terminais Linux.
#define GRN   "\x1B[32m" 
#define BLU   "\x1B[34m"
#define RESET "\x1B[0m"
#define YEL   "\x1B[33m"

enum TIPOS_OBJETOS { PECA = 0, ROBO, DESTINO };
enum DESTINOS { VERMELHO = '1', VERDE, AZUL };

typedef struct {    // Definição de um novo tipo de dado chamado TOBJETO.
    int x, y;       // Coordenadas X e Y para posicionar peças. 
    char cor;       // Cor da peça: R para vermelho, G para verde e B para azul. 
    int tipo;       // Tipo: 0 para peça, 1 para robô, 2 para destino.
} TOBJETO;

typedef struct TNO { // Implementação de uma lista encadeada para armazenar objetos. 
    TOBJETO objeto;
    struct TNO *prox;
} *TLISTA;

char arena[LINHAS][COLUNAS]; // Variável global que representa a matrix da arena.

void inicializar_lista(TLISTA *pLista);              // Inicializa a lista encadeada.
void inicializar_arena(void);                        // Inicializa matrix com pontos.
int menu_principal(void);                            // Mostra Menu Principal ao usuário
void posicionar_obj(TLISTA *pLista, TOBJETO pObj);   // Lista encadeada insere objeto no início.
TOBJETO ler_objeto(int tipo);                        // Ler dados do objeto.
void retirar_obj(TLISTA *pLista);                    // Retira algum objeto.
void posicionar_destinos(void);                      // Posiciona destinos.
void visualizar_arena(void);                         // Visualiza arena formatada.
void visualizar_lista_obj(TLISTA pLista);            // Visualiza lista de todos objetos.
void colorir_obj_arena(int i, int j);                // Mostra objetos com cores. Funciona somente no Linux.
char *retornar_nome(int tipo);                       // Retorna nomes dos objetos. Utilizado pelo visualizar_lista_obj
char *retornar_nome_cor(int cor);                    // Retorna nome das cores dos objetos.
#endif
