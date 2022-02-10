/*
Aluno: José Lucas AraÃºjo de Lima
Matríiula: 472137
Questão 2 - Escreve um Programa multithread em C para calcular o valor da função y = sin3(x) + raiz(cos(x)).
Deverá criar duas threads novas, uma para calcular f1 = sin3(x) e a segunda para calcular f2 = raiz(cos(x)). 
A thread principal deverá depois calcular o valor final (f1+f2) depois de terminação e junção dos duas threads.
*/
//Bibliotecas necessárias
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <math.h>

//Declaração das variáveis globais utilizadas tanto na função calcula quanto na main
float seno;
float cosseno;
float soma;
float x;

//Função calcula que reune as threads que fazem o cálculo das funções matemáticas requisitadas na questão
void * calcula (void *arg) {//função sem retorno tipo void
    int *valor = (int *)(arg);//atribuindo a conversão de ponteiro void para ponteiro int na variável do tipo ponteiro *valor
    
    switch(*valor){//switch para validar os valores possíveis passados no parâmetro *arg
	    case 1:
	        seno = powf(sinf(x),3);//atribuindo à variável seno o resultado das operações utilizando as funções powf e sinf da biblioteca math.h
	    	break;
	    case 2:
	        cosseno = sqrtf(cosf(x));//atribuindo à variável cosseno o resultado das operações utilizando as funções sqrtf e cosf da biblioteca math.h
	        break;
	    case 3:
	        soma = seno + cosseno;//atribuindo a variável soma os valores de seno + cosseno
	        printf("Valor de x = %d\nf1 = %f\nf2 = %f\n(f1 + f2): %f\n",(int) x, seno, cosseno, soma);//exibindo na tela os valores
	        break;
	}
}

int main(){

	pthread_t thread1,thread2,thread3;//criando as threads
	
	int arg1 = 1, arg2 = 2, arg3 = 3;
	
    printf("Digite o valor de x: ");
    scanf("%f", &x);

    pthread_create(&thread1, NULL, calcula, &arg1); //Cria a primeira thread que realizará o calculo de powf(sinf(x),3).
    pthread_join(thread1, NULL); //Aguarda o término da thread 1 para depois seguir a execução
    pthread_create(&thread2, NULL, calcula, &arg2); // Cria a segunda thread que realizará o calculo de sqrtf(cosf(x)).
    pthread_join(thread2, NULL); //Aguarda o término da thread 2 para depois seguir a execução
    pthread_create(&thread3, NULL, calcula, &arg3); // Cria a terceira thread que realizará a soma.
    pthread_join(thread3, NULL); //Aguarda o término da thread 3 para depois seguir a execução
    
    exit(0);
}
