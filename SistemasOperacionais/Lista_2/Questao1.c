/*
Aluno: José Lucas Araújo de Lima
Matrícula: 472137
Questão 1 - Crie um programa em C que gere um processo com 2 threads e execute a seguinte ação:
− O processo pai escreve na tela logo após ser criado "Alô do pai" e em seu último comando
escreve "Tchau do pai!"
− As threads filhas escrevem na tela logo após ser criado "Alô do filho" e em seu último comando
escreve "Tchau do filho!"
− Coloque entre os comandos de escrita alguns comandos para fazer com que os processos
demorem um pouco mais.
− Faça o mesmo programa com 100 threads filhos.
*/

//Bibliotecas necess�rias
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <windows.h>

#define TAMANHO 100

void * functionAloDoFilho (void *arg) {
    int *valor = (int *)(arg);
    printf("Alo do Filho %d\n", *valor);
    //wait(0);
    //sleep(1);
    printf("Tchau do Filho %d\n", *valor);
    pthread_exit(NULL);		
}

int main(int argc, char *argv[]){
    pid_t pid;
    pthread_t threads [TAMANHO];
    int i,status;
    
    if(pid != 0){ //Verifica se � o processo pai
        printf("Alo do pai %d\n", getpid());
        //wait(0);
        sleep(1);
        for (i = 0; i < TAMANHO; i++)
        {
            status = pthread_create(&threads[i], NULL, functionAloDoFilho, (void *) &i);
            if(status != 0){
                printf("Erro ao criar a thread. %d\n", status);
                return -1;
            }
        }
        //wait(0);
        sleep(1);
        printf("Tchau do pai!\n");
    }

    return 0;
}
