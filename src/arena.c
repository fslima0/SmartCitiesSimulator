#include <stdio.h>
#include <stdlib.h>

#include "config_arena.h" // Contêm definicão de estruturas, protótipo das funções 
                          // e declaração de constantes. 

  /*  Protótipo de um simulador no qual os objetos (peças, robô, destinos)
   *  tem uma representação dentro da arena.
   */

int main(void)
{
    int opcao;           // Armazena a opção do usuário do Menu Principal.
    char resposta_acao;  // Armazena a opção de deseja continuar laço.
    TOBJETO objeto;      // Armazena o registro do objeto.
    TLISTA lista;        // Início da lista encadeada com registro dos objetos.
    
    inicializar_lista(&lista); // Inicializa a lista encadeada.
    inicializar_arena();       // Inicializa a arena preenchendo com pontos.
    
    do {
        opcao = menu_principal(); // Roda a função e retorna a opção do usuário.
    
        switch (opcao) {
            case 1: objeto = ler_objeto(PECA);       // Ler dados da peça
                    posicionar_obj(&lista, objeto);  // Posicionar peça
                    break;
            case 2: visualizar_lista_obj(lista);     // Visualizar lista de objetos
                    retirar_obj(&lista);             // Retirar peça
                    break;
            case 3: objeto = ler_objeto(ROBO);       // Ler dados do robô        
                    posicionar_obj(&lista, objeto);  // Posicionar robô
                    break;
            case 4: objeto = ler_objeto(DESTINO);    // Ler dados de um destino  
                    posicionar_obj(&lista, objeto);  // Posicionar destino
                    break;
            case 5: visualizar_arena();              // Visualizar arena
                    break;
            case 9: exit(0);                         // Finalizar aplicativo
            
            default: printf("\n Opção inválida. Por favor tente novamente.");
                    break;
        }
        printf("\n Você deseja voltar ao Menu Principal? (S)im ou (N)ao: ");
        scanf(" %c", &resposta_acao);
        
        system("clear");            // Chamada de sistema para limpar tela.
    } while (resposta_acao == 'S'); // Continuar laço caso resposta for sim.
    
    return EXIT_SUCCESS;            // Retorna sinal de sucesso para o SO.
}
