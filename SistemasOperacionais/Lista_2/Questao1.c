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

//Bibliotecas necessárias
#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char *argv[]){
    pid_t pid;

    pid = fork(); //Cria processo filho
    if(pid != 0){ //Verifica se é o processo pai
        printf("Alô do pai %d\n", getpid());
        wait(0);
        printf("Tchau do pai!\n");
    }else{ //Código do processo filho
        printf("Alô do filho %d\n", getpid());

        printf("Tchau do filho!\n"); //Para sinalizar fim código do filho
    }

    return 0;
}