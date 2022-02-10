/*
Aluno: José Lucas Araújo de Lima
Matrícula: 472137
Questão 2 - Escreve um Programa multithread em C para calcular o valor da função y = sin3(x) + √cos (x).
Deverá criar duas threads novas, uma para calcular f1 = sin3(x) e a segunda para calcular f2 =√cons(x). 
A thread principal deverá depois calcular o valor final (f1+f2) depois de terminação e junção dos duas threads.
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <pthread.h>

#define N 9 //para fazer os loops e evitar estouro de memória

double termo_soma = 0, termo_subtracao = 0;

// Calculo do fatorial de maneira recursiva
unsigned long long int fatorial(int valor){ //usado tipo long long pois o fatorial grande muito rápido
    unsigned long long int fat; 
    if (valor == 0 || valor == 1){
        return 1;
    }else{
        fat = valor * fatorial(valor - 1);
        return fat; //retorna o fatorial
    }
}

void *soma_taylor(void *ard){ //Função para a parte da soma
    int *x = (int *) ard; //cast para int

    int cont = 0; double termos, numerador;
    unsigned long long int denominador; //denominador da nossa equação

    while (cont < N){
        numerador = pow( -1, cont ) * pow( (*x), (2*cont+1) ); //equação de taylor parte do numerador
        denominador = fatorial( 2*cont + 1 ); //equação de taylor parte do denominador
        termos = numerador/denominador; //equação de taylor

        termo_soma += termos; //adciona o valor obtido na variável global(região crítica)

        cont += 2; //numeros posiivos da série começam no índice 0 e avança de 2 em 2
    }
    //printf("%f\n", termo_soma);
}

void *subtracao_taylor(void *ard){
    int *x = (int *) ard;

    int cont = 1; double termos, numerador;
    unsigned long long int denominador;

    while (cont < N){ //contador que vai até define N
        numerador = pow( -1, cont ) * pow( (*x), (2*cont+1) ); //equação de taylor parte do numerador
        denominador = fatorial( 2*cont + 1 ); //equação de taylor parte do denominador
        termos = numerador/denominador; //equação de taylor 

        termo_subtracao += termos; //adciona o valor obtido na variável global(região crítica)

        cont += 2; //os numeros negativos são aqueles e que o índice n começa em 1 e avança de 2 em 2
    }
    //printf("%f\n", termo_subtracao);
    
}

int main(int argc, char argv[]){
    int x;
    pthread_t thread1, thread2; // Handle para pthread, isto é, um valor que permite identificar o thread

    printf("Digite um valor para x: ");
    scanf("%d", &x);

    pthread_create(&thread1, NULL, soma_taylor, &x); // inicializar a thread1 passando endereço de x como parâmetro para a função
    pthread_create(&thread2, NULL, subtracao_taylor, &x); // inicializar a thread2 passando endereço de x como parâmetro para a função
    pthread_join(thread1, NULL); //Aguarda as threads executarem
    pthread_join(thread2, NULL);

    printf("%f\n", (termo_subtracao + termo_soma)); //Soma os numeros negaivos e os positivos da série
    
    return 0;
}