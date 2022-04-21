#include <stdio.h>
#include <string.h>
#include <ctype.h>
//#include <stdio_ext.h> // __fpurge(stdin)

int main (void){

//declarações
int tamN = 20, tamS = 100, tami = 6;
int ra, i, vali;
char nome[tamN], sobrenome[tamS], idade[tami], resp;

//identificação
do
{
    printf("Nome: "); //perguntar o nome
    fgets(nome, tamN, stdin); //resposta do usuário com limitação de 20 caracteres
    nome[strcspn(nome, "\n")] = 0; //como o fgets já possui um \n, foi utilizado o strcspn para deleter esse \n
    vali = 1;

    for(i = 0; nome[i] != '\0'; i++)
    {
        if(!isalpha(nome[i]))
        {
            printf("\nInsira somente seu nome\n");
            vali = 0;
            break; // i = tamN
        }
    }

}while(vali == 0);

do
{
    printf("Sobrenome: "); //perguntar o sobrenome
    fgets(sobrenome, tamS, stdin); //resposta do usuário com limitação de 100 caracteres
    sobrenome[strcspn(sobrenome, "\n")] = 0;
    vali = 1;

    for(i = 0; sobrenome[i] != '\0'; i++)
    {
        if(!isalpha(sobrenome[i]) && sobrenome[i] != 32)
        {
            printf("\nInsira somente seu sobrenome\n");
            vali = 0;
            break;
        }
    }

}while(vali == 0);

do
{
    printf("Idade: "); //perguntar a idade
    fgets(idade, tami, stdin); //resposta do usuário
    vali = 1;

    for(i = 0; idade[i] != '\0'; i++)
    {
        if(isalpha(idade[i]))
        {
            printf("\nInsira sua idade usando somente numeros\n");
            vali = 0;
            break;
        }
    }

}while(vali == 0);

do
{
    printf("Deseja proseguir com a compra? Responda com 's' para prosseguir ou com 'n' para retornar ao menu\n"); //perguntar se o usuário tem o desejo de continuar utilizando o programa
    scanf(" %c", &resp); //resposta do usuário

    if(resp == 'n' || resp == 'N')
    {
        break;
    }

    else if(resp == 's' || resp == 'S')
    {
        printf("Qual o seu RA?\n");
        scanf("%d", &ra);
        break;
    }

}while(resp != 'n' || resp != 's' || resp != 'N' || resp != 'S');

return 0;
}