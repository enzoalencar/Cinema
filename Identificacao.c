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

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//Bibliotecas
#include <stdio.h>//Blioteca Padrão Entrada e Saida
#include <windows.h>//Biblioteca Funções do Terminal Windows
#include <conio.h>//Biblioteca para Manipular Caracteres na Tela
#include <ctype.h>//Biblioteca para Classificar Caracteres
#include <string.h>

//Cores
#define RST  "\x1B[0m"//Cor Resetar
#define RED  "\e[31;1m"//Cor Vermelho
#define GRN "\e[32;1m"//Cor Verde
#define YEL "\e[33;1m"//Cor Amarelo
#define BLU  "\x1B[34m"//Cor Azul
#define MAG  "\x1B[35m"//Cor Magenta
#define CYN  "\x1B[36m"//Cor Cyano
#define WHT  "\e[38;1m"//Cor Branca
#define REDB  "\e[31;7m"//Vermelho Back Ground
#define REDN  "\e[31;1m"// negrito
//Função Principal
int main()
{
	int tamN = 100, tami = 15;
    int i = 0, vali, cont = 0;
    char nome[tamN], idade[tami];
    char letra;
    int comprimento;

    
	system("color 00");//Setar Padrão Cor do Terminal

    printf(RED"Nome Completo:"RST);

    do
    {
		nome[i] = '\0';
        letra = getch();
        if(!isalpha(letra) || letra == 32)
        {
        	nome[i] = letra;
        	i++;
			printf("%c", letra);
		}
		
		else if(letra == 8 && i)//se for pressionada a tecla BACKSPACE e houver caracteres já digitados
       {
          nome[i]='\0';//o índice atual do vetor de caracteres recebe a terminação da string
          i--;//o índice do vetor de caracteres é decrementado
          printf("\b \b");//o caractere digitado é apagado da tela
       }
       
	comprimento = strlen(nome);
	
	}while(letra != 13 || comprimento < 1);
	
	
	printf("\n%d\n", comprimento);

	printf("\n");
		
			printf("%s", nome);
		
}
