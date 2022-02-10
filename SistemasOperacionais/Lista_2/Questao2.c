/*
Aluno: Jos� Lucas Araújo de Lima
Matr�iula: 472137
Quest�o 2 - Escreve um Programa multithread em C para calcular o valor da fun��o y = sin3(x) + raiz(cos(x)).
Dever� criar duas threads novas, uma para calcular f1 = sin3(x) e a segunda para calcular f2 = raiz(cos(x)). 
A thread principal dever� depois calcular o valor final (f1+f2) depois de termina��o e jun��o dos duas threads.
*/
//Bibliotecas necess�rias
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <math.h>

//Declara��o das vari�veis globais utilizadas tanto na fun��o calcula quanto na main
float seno;
float cosseno;
float soma;
float x;

//Fun��o calcula que reune as threads que fazem o c�lculo das fun��es matem�ticas requisitadas na quest�o
void * calcula (void *arg) {//fun��o sem retorno tipo void
    int *valor = (int *)(arg);//atribuindo a convers�o de ponteiro void para ponteiro int na vari�vel do tipo ponteiro *valor
    
    switch(*valor){//switch para validar os valores poss�veis passados no par�metro *arg
	    case 1:
	        seno = powf(sinf(x),3);//atribuindo � vari�vel seno o resultado das opera��es utilizando as fun��es powf e sinf da biblioteca math.h
	    	break;
	    case 2:
	        cosseno = sqrtf(cosf(x));//atribuindo � vari�vel cosseno o resultado das opera��es utilizando as fun��es sqrtf e cosf da biblioteca math.h
	        break;
	    case 3:
	        soma = seno + cosseno;//atribuindo a vari�vel soma os valores de seno + cosseno
	        printf("Valor de x = %d\nf1 = %f\nf2 = %f\n(f1 + f2): %f\n",(int) x, seno, cosseno, soma);//exibindo na tela os valores
	        break;
	}
}

int main(){

	pthread_t thread1,thread2,thread3;//criando as threads
	
	int arg1 = 1, arg2 = 2, arg3 = 3;
	
    printf("Digite o valor de x: ");
    scanf("%f", &x);

    pthread_create(&thread1, NULL, calcula, &arg1); //Cria a primeira thread que realizar� o calculo de powf(sinf(x),3).
    pthread_join(thread1, NULL); //Aguarda o t�rmino da thread 1 para depois seguir a execu��o
    pthread_create(&thread2, NULL, calcula, &arg2); // Cria a segunda thread que realizar� o calculo de sqrtf(cosf(x)).
    pthread_join(thread2, NULL); //Aguarda o t�rmino da thread 2 para depois seguir a execu��o
    pthread_create(&thread3, NULL, calcula, &arg3); // Cria a terceira thread que realizar� a soma.
    pthread_join(thread3, NULL); //Aguarda o t�rmino da thread 3 para depois seguir a execu��o
    
    exit(0);
}
