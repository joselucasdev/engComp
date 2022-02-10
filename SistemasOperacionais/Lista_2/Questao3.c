/*
Aluno: Jos√© Lucas Ara√∫jo de Lima
Matr√≠cula: 472137
Quest√£o 3 - Implemente uma simula√ß√£o para os algoritmos de escalonamento FIFO, SJF e Round Robin em C.
Em sua implementa√ß√£o o usu√°rio deve fornecer a quantidade de processos que est√£o na fila para serem
executados, a ordem de chegada e o tempo de execu√ß√£o de cada processo. Durante a execu√ß√£o deve
ser informado ao usu√°rio qual o processo que est√° executando e esperado o tempo de cada processo
por segundo. Por exemplo, se um processo A demora 5 segundos, deve ser informado que ele est√°
sendo trabalhado e esperado o tempo de execu√ß√£o deste para poder iniciar o pr√≥ximo, para isso utilize
um temporizador em seu algoritmo.
Obs: Escrever um relat√≥rio explicando toda a carga te√≥rica dos algoritmos implementados
nos programas, explicando o c√≥digo e a l√≥gica utilizada. O relat√≥rio e os c√≥digos devem
ser enviados em uma pasta compactada.
*/
/*Simulador de Escalonamento de Processos*/
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <windows.h>

/*Estrutura do processo*/
struct processos {
    char id; //identifica processo
    int duracao; //tempo de duraÁ„o do processo
    int ordem; //Prioridade do processo
    struct processos* prox;
};

typedef struct processos Processos; //

//FunÁ„p de criaÁ„o: retorna processo vazio
Processos* proc_cria(void){
    return NULL;
}

/*FunÁ„o para liberar o processo*/
void proc_libera(Processos* proc){
    Processos* p = proc; //auxiliar para percorrer a lista de procesos
    while(p != NULL){
        Processos* tmp = p->prox;
        free(p);
        p = tmp;
    }
}

/*FunÁ„o para imprimir os processo da lista*/
void proc_imprime(Processos* proc){
    Processos* tmp;
    printf("Ordem dos processos por prioridade:\n");
    for(tmp = proc; tmp != NULL; tmp=tmp->prox){
        printf("%c -> ", tmp->id);
    }
    printf("FIM\n\n");
}

/*Insere um novo processo na ordem crescente(prioridade)*/
Processos* proc_insere(Processos* proc, int id, int duracao, int ordem){
    Processos* ant = NULL;  //Aponta para o processo anterior
    Processos* aux = proc;  //aux para percorrer os processos

    //Procura a ordem certa de chegada
    while(aux != NULL && aux->ordem < ordem){ //Enquanto n„o achar avanÁa na lista de processos
        ant = aux;
        aux = aux->prox;
    }

    /*Cria o novo processo*/
    Processos* novo = (Processos*) malloc(sizeof(Processos));

    if (novo == NULL){
        printf("Erro ao alocar memÛria.\n");
        exit(1);
    }
    novo->id = id; //Atribui os valores
    novo->duracao = duracao;
    novo->ordem = ordem;

    if(ant == NULL){
        novo->prox = proc; //Insere no inicio
        proc = novo;
    }else{ //Insere na ordem apropriada
        novo->prox = ant->prox;
        ant->prox = novo;
    }

    return proc;
};

/*Insere um processo numa lista de maneira ordenada pelo tempo(mesma lÛgica da funÁ„o acima)*/
Processos* insere_menor_tempo(Processos *proc, int id, int duracao, int ordem){
    Processos* ant = NULL;
    Processos* aux = proc;

    while(aux != NULL && aux->duracao < duracao){
        ant = aux;
        aux = aux->prox;
    }
    Processos* novo = (Processos*) malloc(sizeof(Processos));
    if (novo == NULL){printf("Erro ao alocar memÛria.\n"); exit(1);}
    novo->id = id;
    novo->duracao = duracao;
    novo->ordem = ordem;

    if(ant == NULL){
        novo->prox = proc; //Insere no inicio
        proc = novo;
    }else{ //Insere na ordem apropriada
        novo->prox = ant->prox;
        ant->prox = novo;
    }

    return proc;
}


/*FunÁ„o para transformar uma lista em lista circular*/
Processos* insere_circular(Processos* proc){
    Processos *ini = proc;
    Processos *atual = proc;

    while(atual->prox != NULL){
        atual = atual->prox;
    }
    atual->prox = ini; //Aponta para o inicio(circular)
    return ini;
}

//desfaz circular
void proc_libera_circular(Processos* proc){
	if (proc == NULL)
        return; //retorna original(NULL);

    // Inicia temp apontando para head
    Processos *temp = proc;

    // Faz temp pular elementos da lista at? que aponte para
    // o elemento anterior a head
    while (temp->prox != proc)
        temp = temp->prox;

    // Desaloca tudo enquanto temp n?o aponta para head
    while (temp != proc && proc->prox != temp)
    {
        temp->prox = proc->prox;
        free(proc); 
        proc = temp->prox; 
    }
    // Saiu do loop, temp finalmente aponta para head
    // Agora s? precisa desalocar o ?ltimo elemento
    
	proc->prox = NULL; 
    free(temp);
   	proc = NULL;
}

void proc_fifo(Processos* proc, int qtd){
	Processos* tmp = proc_cria();
	printf("\nINICIO FIFO\n\n");
    int t_med = 0, soma = 0;    
    for(tmp = proc; tmp != NULL; tmp=tmp->prox){ //Percorre a lista de processos
        printf("Processo %c executando...(%ds)\n", tmp->id, tmp->duracao);//Printa qual processo est· no "escalonador"
        //Sleep((tmp->duracao)*1000); //Temporizador
        if(tmp->prox != NULL){
        	soma += tmp->duracao;
        	t_med += soma;
		}
    }
    proc_libera(tmp); //Libera a memoria com a lista de processos ordenados por tempo
    printf("\nFIM FIFO\n\nTempo m?dio: %0.2f u.t\n",(float) t_med/qtd);
}

 /*FunÁ„o que simula o SJF*/
void sfj(Processos* proc){
    Processos *aux=proc; //Vari·vel aux que recebe o ponteiro para lista de processos
    Processos *menor_job, *tmp;
    menor_job = proc_cria(); //Cria uma lista de processos vazia

    while(aux != NULL){ //Vai inserir os processos na lista criada de maneira ordenada pelo tempo(menor->maior)
        menor_job = insere_menor_tempo(menor_job, aux->id, aux->duracao, aux->ordem);
        aux=aux->prox;
    }
    
    printf("INICIO SJF\n\n");
    int t_med = 0, soma = 0;    
    for(tmp = menor_job; tmp != NULL; tmp=tmp->prox){ //Percorre a lista de processos
        printf("Processo %c executando...(%ds)\n", tmp->id, tmp->duracao);//Printa qual processo est· no "escalonador"
        //Sleep((tmp->duracao)*1000); //Temporizador
        if(tmp->prox != NULL){
        	soma += tmp->duracao;
        	t_med += soma;
		}
    }
    proc_libera(menor_job); //Libera a memoria com a lista de processos ordenados por tempo
    printf("\nFIM SJF\n\nTempo m?dio: %0.2f u.t\n",(float) t_med/5);
}

/*FunÁ„o que simula o Round Robin*/
void round_robin(Processos* proc, int quantum, int qtd){
    Processos *aux = insere_circular(proc); //Cria uma lista de processo auxiliar que È circular
    int contem_proc;
    int stop = 0;
    int soma = 0; 

    while(aux != NULL && stop == 0){ //Percorre a lista circular de processo: Fica em Loop. :(
        if(aux->duracao <= quantum && aux->duracao != 0){ //Verifica se o processo È menor que o quantum e o processo ainda precisa ser executado(!=0)
            printf("id: %c executando...(%ds)\n",aux->id,aux->duracao); //Mostra que est· executando um determinado processo
            //Sleep((aux->duracao)*1000); //Simula o time-slice
            Processos *prox = aux->prox;
            int i = 0;
            while(aux->id != prox->id){
        		if(prox->duracao != 0){
        			soma += aux->duracao;
				}
				prox = prox->prox;
			}
            aux->duracao = 0; //Como o quantum È maior, executa o tempo do processo e atribui a ele 0 para n„o ser executado novamente
            
        }else if(aux->duracao > quantum){ //Caso quantum seja maior, È onde ficar· a parte mais interessante para o "escalonador"
            printf("id: %c executando...(%ds)\n",aux->id,aux->duracao); //Mostra qual processo est· executando e seu tempo
            //Sleep((quantum)*1000); //Simula o time-slice -> Executa o a parcela de tempo equivalente ao quantum
            Processos *prox = aux->prox;
            int i = 0;
            while(aux->id != prox->id){
        		if(prox->duracao != 0){
        			soma += quantum;
				}
				prox = prox->prox;
			}
            aux->duracao = aux->duracao - quantum; //Diminuimos do tempo do processo o seu tempo executado
        }
        else{ //Tentativa de sair, como È uma lista circular a funÁ„o fica em loop.
        	Processos *prox = aux->prox;
        	int i = 1;
        	while(aux->id != prox->id){
        		if(prox->duracao == 0){
        			i++;
				}
				prox = prox->prox;
			}
			if(qtd == i){	
				//proc_libera_circular(inicio); proc_libera_circular(prox);
				stop++;		
			}
        }
        aux = aux->prox; //AvanÁa para o prÛximo processo
    }
    proc_libera_circular(aux); //Libera a memoria com a lista de processos ordenados por tempo
    printf("\nFIM RR\n\nTempo m?dio: %0.2f u.t\n", (float) soma/5);
}

/*Programa Principal*/
int main(int arg, char* argv[]){
    setlocale(LC_ALL, "Portuguese");

    /*InicializaÁ„o de vari·veis*/
    Processos* proc;
    char id;
    int num, op, quantum, ordem, duracao, i;

    proc = proc_cria(); //Cria uma lista de processos vazia

    proc = proc_insere(proc,'A',15,1);
    proc = proc_insere(proc,'B',3,2);
    proc = proc_insere(proc,'C',10,3);
    proc = proc_insere(proc,'D',7,4);
    proc = proc_insere(proc,'E',13,5);

    /*printf("Quantos processos estao na fila: ");
    scanf("%d",&num);printf("\n"); //quantos processos est„o na fila(lista no nosso caso ;))

    for(i = 1; i <= num; i++){ //LaÁo para ler os valores
        printf("Digite um identificador para o %d∫ processo(char): ", i);
        scanf(" %c",&id);//ERROR no codeblocks -> n„o executa o scanf
        printf("Digite a ordem de chegada do processo(int): ");
        scanf("%d",&ordem);
        printf("Digite o tempo de execucao do processo(int): ");
        scanf("%d",&duracao);

        proc = proc_insere(proc, id, duracao, ordem); //Vai inserindo os processo na lista de processos
        printf("\n");
    }*/

    /*Menu para ultilizaÁ„o*/
    printf("[1] - FIFO\n");
    printf("[2] - SFJ\n");
    printf("[3] - RR\n");
    printf("\nQual algoritmo de escalonamento deseja: "); scanf("%d",&op);

    if(op == 1){
    	proc_imprime(proc);
    	proc_fifo(proc,5);
	}else if(op == 2){
        proc_imprime(proc);
        sfj(proc);
    }else if(op == 3){
        printf("\nquantum: "); scanf("%d",&quantum);
        round_robin(proc, quantum,5);
    }else{
        printf("OpÁ„o inv·lida"); exit(1);
    }
    proc_libera(proc);

    printf("\n");
    return 0;
}

