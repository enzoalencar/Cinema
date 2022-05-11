	//Bibliotecas
#include <stdio.h> //Blioteca padr�o de entrada e saida
#include <windows.h> //Biblioteca com fun��es do terminal do Windows
#include <conio.h> //Biblioteca de manipula��o de caracteres na Tela
#include <ctype.h> //Biblioteca para classificar caracteres
#include <iostream>
#include <fstream>

//Cores
#define RST  "\x1B[0m" //Reset da cor
#define RED  "\e[31;1m" //Cor vermelha
#define GRN "\e[32;10m" //Cor verde
#define GRNN  "\e[32;1m" //Cor verde negrito
#define YEL "\e[33;1m" //Cor amarela
#define BLU  "\e[34;10m" //Cor azul
#define MAG  "\x1B[35m" //Cor magenta
#define CYN  "\x1B[36m" //Cor ciano
#define WHT  "\e[38;1m" //Cor branca
#define REDB  "\e[31;7m" //Vermelho
#define REDN  "\e[31;1m" //Em negrito
#define GRY  "\e[30;1m" // Cinza
#define BRO  "\e[33;2m" // Marrom

using namespace std;
//Fun��es auxiliares
void Gotoxy(int coord_x, int coord_y); //Fun��o que possibilita a personaliza��o localizada no terminal, atrav�s de coordenadas
void Retangulo( int ho, int vo, int larg, int alt ); //Gera um ret�ngulo na tela

void desenhoUm();
void desenhoDois();
void desenhoTres();

void desenhoCatalogoUm();
void desenhoCatalogoDois();
void desenhoCatalogoTres();

void load(); //Fun��o da tela de loading de inicializa��o
void encerrando();//Fun�ao da tela de loading de encerramento
void bilhete(char nome[30], int idade, char assentos[14][23],int horario, int filme);

void inicio(); //Fun��o do menu inicial
void catalogo(); //Fun��o do cat�logo de filmes
void filmesmenu(int filme); //Fun��o do filme especificado
void login(int filme, int horario); //Fun��o de identifica��o
void assentos(int filme, int horario, char nome[30], int idade); //Fun��o das cadeiras do hor�rio especificado
int valinum(int compri);
int valiletra(int compri);

int criar(const char* file_name);
int ler(int *rL,int *rC,int *rB, const char* file_name); //Ler os assentos j� ocupados no arquivo
int gravar(int linha, int coluna, const char* file_name); //Fun��o que grava os novos assentos ocupados

int vazio(const char* file_name); //Fun�ao que Verifica se o arquivo esta vazio


//Fun��o Principal
int main()
{
	system("MODE con cols=92 lines=31");
	load();
	inicio();
	return 0;
}

void Gotoxy(int coord_x, int coord_y)
{
	//Envia o parâmetro escolhido para o windows, posicionando o cursor nas respectivas coordenadas do console, como se ele fosse uma matriz
    HANDLE hCon;
    COORD dwPos;

    dwPos.X = coord_x;
    dwPos.Y = coord_y;
    hCon = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(hCon,dwPos);
}

void Retangulo(int horizontal_inicial, int vertical_inicial, int larg, int alt)
{
    int horizontal, vertical;

    //Linhas horizontais
     for (horizontal = horizontal_inicial; horizontal < horizontal_inicial + larg; horizontal++)
	 {
        Gotoxy(horizontal, vertical_inicial);
        printf(RED"%c", 205); //Imprime o caracter especial com retorno 206

        Gotoxy(horizontal, vertical_inicial + alt);
        printf(RED"%c", 205);
     }

     //Linhas verticais
     for (vertical = vertical_inicial; vertical < vertical_inicial + alt; vertical++)
	 {
        Gotoxy(horizontal_inicial, vertical);
        printf(RED"%c", 186); //Imprime o Caracter Especial com retorno 186

        Gotoxy(horizontal_inicial + larg, vertical);
        printf(RED"%c", 186);
     }

     // Cantos
     Gotoxy(horizontal_inicial, vertical_inicial);
     printf(YEL"%c", 201); //Imprime o caracter especial com retorno 201

     Gotoxy(horizontal_inicial, vertical_inicial + alt);
     printf(YEL"%c", 200); //Imprime o caracter especial com retorno 200

     Gotoxy(horizontal_inicial + larg, vertical_inicial);
     printf(YEL"%c", 187); //Imprime o caracter especial com retorno 187

     Gotoxy(horizontal_inicial + larg, vertical_inicial + alt);
     printf(YEL"%c", 188); //Imprime o caracter especial com retorno 188
}

void load()
{
	system("color 00"); //Redefine a sistema para a cor padr�o

	Gotoxy(39, 11);
	printf("Iniciando...");

	Retangulo(0, 0, 90, 30); //Ret�ngulo externo
	Retangulo(16, 12, 59, 4); //Ret�ngulo interno

	int i=0;
	while (i<=50)
	{
		Gotoxy(i + 18,14);
		printf(REDB" "REDN); //Imprime um espa�o vermelho

		Gotoxy(70,14);
		printf(RST"%d%%"REDN,i*2); //Imprime a porcetagem do carregamento

		i++;

		Sleep(15); //Delay de 15ms
	}

	Beep(349, 100);//Gera um som a 349 hz por 100 ms
	system("cls"); //Limpa o terminal
}

void inicio()
{
	system("color 00");

	int altura = 3; //Vari�vel que aponta a coordenada de altura do cursor(altura � inversa ao sentido convencional)
	char tecla; //Vari�vel para armazenar as teclas pressionadas

	Retangulo(0, 0, 90, 30); //Ret�ngulo externo
	Retangulo(36, 8, 17, 10); //Ret�ngulo interno

    Gotoxy(42, 10);
    printf(YEL"CINEMA"RST);
     Gotoxy(42, 16);
    printf(YEL"FACENS"RST);

	do
	{
    	Gotoxy(41, 12);
    	if (altura == 3)
    		printf(RED"Catalogo\n\n\n"RST);

    	else if (altura != 3)
 			printf(RST"Catalogo\n\n\n"RST);

 		Gotoxy(43, 14);
 		if (altura == 5)
 			printf(RED"Sair"RST);

 		else if (altura != 5)
 			printf(RST"Sair\n\n\n"RST);

		fflush(stdin); //Limpa o buffer
		tecla = getch(); //L� um caracter

		switch(tecla)
		{
			case 72: //Move ao pressionar seta para cima
				if(altura > 3)
					altura -= 2 ;

				else
					altura = 5; //Se o limite for excedido ele volta ao �ltimo valor de altura
				break;

			case 80:
				if(altura < 5) //Move ao pressionar seta para baixo
					altura += 2;

				else
					altura = 3 ; //Se o limite for excedido ele volta ao primeiro valor de altura
				break;
		}
	}while (tecla != 13); //Finaliza ao pressionar Enter

	Beep(349, 100);
	system("cls");

	switch(altura)
	{
		case 5: //Caso selecione "Sair"
			encerrando();
			break;

		case 3: //Caso selecione "Catalogo"
			catalogo();
			break;
	}
}

void catalogo()
{
	int largura = 21; //Vari�vel que aponta a coordenada de largura do cursor
	char tecla; //Vari�vel para armazenar as teclas pressionadas

    Gotoxy(42, 6);
	printf(YEL"FILMES"RST);

	Retangulo(0, 0, 90, 30);//Ret�ngulo externo

	int i, espacamento = 0;

	desenhoUm();
	desenhoDois();
	desenhoTres();

	for (i = 1; i < 4; i++) //Constr�i 3 ret�ngulos internos
	{
		espacamento += 20;
		Retangulo(espacamento, 10, 8, 5);
	}

	do
	{
        Gotoxy(5, 25);
		if (largura == 1)
			printf(RED"Voltar"RST); //Imprime Voltar vermelho

		else if (largura != 1)
			printf(RST"Voltar"RST); //Imprime Voltar branco

		Gotoxy(21, 16);
		if (largura == 21)
			printf(RED"La Rosa "RST); //Imprime Filme 1 vermelho

		else if (largura != 21)
			printf(RST"La Rosa "RST); //Imprime Filme 1 branco

		Gotoxy(42, 16);
		if (largura == 41)
			printf(RED"Roque "RST); //Imprime Filme 2 vermelho

		else if (largura != 41)
			printf(RST"Roque "RST); //Imprime Filme 2 branco

		Gotoxy(59, 16);
		if (largura == 61)
			printf(RED"Brinquinhos "RST); //Imprime Filme 3 vermelho

		else if (largura != 61)
			printf(RST"Brinquinhos "RST); //Imprime Filme 3 branco

		Gotoxy(80, 25);
		if (largura == 81)
			printf(RED"Sair "RST); //Imprime Sair vermelho

		else if (largura != 81)
			printf(RST"Sair "RST); //Imprime Sair branco

		fflush(stdin);
		tecla = getch();

		switch(tecla)
		{
			case 75: //Move ao pressionar seta para esquerda
				if(largura > 1)
					largura -= 20;

				else
					largura = 81; //Se o limite for excedido ele volta ao �ltimo valor de largura
				break;

			case 77: //Move ao pressionar seta para direita
				if(largura < 81)
					largura += 20;

				else
					largura = 1; //Se o limite for excedido ele volta ao primeiro valor de largura
				break;
		}
	}while (tecla != 13); //Finaliza ao pressionar Enter

	Beep(349, 100);
	system("cls");

	switch(largura)
	{
		case 1: //Caso selecione Voltar
			inicio();
			break;

		case 21: //Caso selecione Filme 1
			filmesmenu(1);
			break;

		case 41: //Caso selecione Filme 2
			filmesmenu(2);
			break;

		case 61: //Caso selecione Filme 3
			filmesmenu(3);
			break;

		case 81: //Caso selecione Sair
			encerrando();
			break;
	}
}

void filmesmenu(int filme)
{
    int largura = 21; //Vari�vel que aponta a coordenada de largura do cursor
    char tecla;


    Retangulo(0, 0, 90, 30); //Retangulo externo
    Retangulo(5, 3, 14, 8); //Retangulo interno da foto
    Retangulo(29, 3, 50, 12); //Retangulo interno da descri��o
    Retangulo(18, 23, 50, 4); //Retangulo externo dos hor�rios


    if (filme == 3)
    {
        Gotoxy(3,13);
        desenhoCatalogoTres();
    }

    if (filme == 2)
    {
        Gotoxy(3,13);
        desenhoCatalogoDois();
    }

    if (filme == 1)
    {
        Gotoxy(3,13);
        printf(RED"MAIORIDADE NECESSARIA"RST);
        desenhoCatalogoUm();
    }

    if(filme == 1)
    {
    	Gotoxy(9,12);
    	printf(YEL"La Rosa"RST, filme);
	}
	if(filme == 2)
    {
    	Gotoxy(10,12);
    	printf(YEL"Roque"RST, filme);
	}
	if(filme == 3)
    {
    	Gotoxy(7,12);
    	printf(YEL"Brinquinhos"RST, filme);
	}

    Gotoxy(40,22);
    printf(YEL"HORARIOS"RST);

    do
    {
        Gotoxy(21, 25);
        if (largura == 21)
            printf(RED"18:00 "RST);

        else if (largura != 21)
            printf(RST"18:00 "RST);

        Gotoxy(41, 25);
        if (largura == 41)
            printf(RED"20:00 "RST);

        else if (largura != 41)
            printf(RST"20:00 "RST);

        Gotoxy(61, 25);
        if (largura == 61)
            printf(RED"22:00 "RST);

        else if (largura != 61)
            printf(RST"22:00 "RST);

        Gotoxy(80, 25);
        if (largura == 81)
            printf(RED"Sair "RST);

        else if (largura != 81)
            printf(RST"Sair "RST);

        Gotoxy(5,25);
        if (largura == 1)
            printf(RED"Voltar"RST);

        else if (largura != 1)
            printf(RST"Voltar"RST);

        fflush(stdin);
        tecla = getch();

        switch(tecla)
        {
            case 75:
                if (largura > 1)
                    largura -= 20;

                else
                    largura = 81;
                break;

            case 77:
                if (largura < 81)
                    largura += 20;

                else
                    largura = 1;
                break;
        }
    }while (tecla != 13);

    Beep(349, 100);
    system("cls");

    if (largura == 1)
        catalogo();

    else if (largura == 21)
        login(filme, 1);

    else if (largura == 41)
        login(filme, 2);

    else if (largura == 61)
        login(filme, 3);

    else if (largura == 81)
        encerrando();
}

void login(int filme, int horario)
{
    int i = 0;
    char nome[30], idade[4];
    char letra, num;

	system("color 00");//Setar Padrão Cor do Terminal
    Retangulo(0,0,90,30);//Retangulo Principal
    Retangulo(28,8,34,10);//Retangulo Mini Menu

    Gotoxy(42,10);
    printf(YEL"LOGIN"RST);

    Gotoxy(31,12);
    printf(YEL"Nome Completo:"RST);

    Gotoxy(31,13);
    do
    {
        nome[i] = '\0';
        letra = getch();
        letra = toupper(letra);
        if(isalpha(letra) || letra == 32)
        {
            nome[i] = letra;
            i++;
            printf("%c", letra);
        }
        if(letra == 8 && i)// 8 = backspace e i -> se houver caracteres ja digitados
        {
          nome[i] = '\0';
          i--;
          printf("\b \b");
        }

        if(strlen(nome) > 29)
        {
            Gotoxy(31, 14);
            printf(RED"Maximo de caracteres atingido"RST);
            nome[i]='\0';
            i--;
            Gotoxy(61, 13);
            printf("\b \b");
        }
	}while(letra != 13 || strlen(nome) < 1 || nome[i - 1] == 32);

	fflush(stdin);
	i = 0;

    Gotoxy(31, 14);
    printf("                               ");

	Gotoxy(31,15);
    printf(YEL"Idade:"RST);

    Gotoxy(31,16);
    do
    {
        idade[i] = '\0';
        num = getch();
        if(isdigit(num))
        {
            idade[i] = num;
            i++;
            printf("%c", num);
        }
        if(num == 8 && i || atoi(idade) > 120)// 8 = backspace e i -> se houver caracteres ja digitados
        {
          idade[i] = '\0';
          i--;
          printf("\b \b");
        }

    }while(num != 13  || strlen(idade) < 1);

	if(filme == 1 && atoi(idade) < 18)
	{
		Gotoxy(31,16);
		printf(RED"MAIORIDADE NECESSARIA"RST);
		Sleep(250);
		system("cls");
		filmesmenu(1);
	}
    system("cls");
    Beep(349,100);//Gera um Som a 349 hz por 100 ms
    assentos(filme, horario, nome, atoi(idade));
}
void assentos(int filme, int horario, char nome[30], int idade)
{
	Retangulo(0, 0, 90, 30); //Ret�ngulo externo
	Retangulo(2, 1, 86, 15); //Ret�ngulo dos assentos
	Retangulo(38, 17, 13, 2); //Ret�ngulo da bilheteria
	Retangulo(2, 20, 86, 2); //Ret�ngulo interno de menu
	Retangulo(2, 23, 86, 6); //Ret�ngulo de intera��o com o usu�rio
	char Cinema[14][23];
	char file_name[4];
	char PCinema[14][23];
    char vali_ingressos[5];
    char num;
    char num2;
	int num_ingressos = 0;
    int largura = 1; //Vari�vel que aponta a coordenada de largura do cursor
	int tecla; //Vari�vel para armazenar as teclas pressionadas
	int i = 0; //Contador gen�rico
	int linha_convertida;
    int k = 0; //Contador alternativo
    char vali_coluna[4];

    int linha, coluna;
	//Amostra de sala vazia
	for (linha = 0; linha < 14; linha++)
    {
		for (coluna = 0; coluna < 23; coluna++)
        {
			Cinema[linha][coluna]=0; //Tranforma todas as cadeiras em vazias
			PCinema[linha][coluna] = 0;
        }
    }

    int colunasP[322];
	int linhasP[322];
    int pause;

    sprintf(file_name, "%i-%i", filme, horario); //Cria uma string a partir do n�mero da sala e do hor�rio
    criar(file_name);
	ler(linhasP, colunasP, &pause, file_name); //Chama a fun��o apontando para 3 ponteiros

	if (pause != 0) //Se o ponteiro retorna 0 que significa que o arquivo est� vazio, logo ele n�o tenta gravar nenhuma matriz
	{
		while (i < pause) //Grava at� o valor contado dentro da fun�ao que define a quantidade de cadeira armazenadas
		{
			int a = linhasP[i];
			int b = colunasP[i];
			Cinema[a][b] = 1; //Transforma a cadeira em ocupada
			i++;
		}
	}

	for (linha = 0; linha < 14; linha++)//Imprime a matriz na tela
	{
		Gotoxy(5, 2 + linha);
		for (coluna = 0; coluna < 23; coluna++)
		{
			if (Cinema[linha][coluna] == 1) //Se estiver ocupada imprime vermelho
				printf(RED"%c%d "RST, linha + 65, coluna);

			else if (Cinema[linha][coluna] == 0) //Se estiver livre imprime verde
				printf(GRNN"%c%d "RST, linha + 65, coluna);
		}
		printf("\n");
	}

    Gotoxy(40, 18);
	printf(YEL"BILHETERIA"RST);

	do
	{
        Gotoxy(5, 21);
		if (largura == 1)
			printf(RED"Voltar"RST);

		if (largura != 1)
			printf(RST"Voltar"RST);

		Gotoxy(36, 21);
		if (largura == 21)
			printf(RED"Escolher assentos"RST);

		if (largura != 21)
			printf(RST"Escolher assentos"RST);

		Gotoxy(80, 21);
		if (largura == 41)
			printf(RED"Sair "RST);

		if (largura != 41)
			printf(RST"Sair "RST);

		fflush(stdin);
		tecla = getch();

		switch(tecla)
		{
            case 75:
                if (largura > 1)
                    largura -= 20;

                else
                    largura = 41;
                break;

            case 77:
                if (largura < 41)
                    largura += 20;

                else
                    largura = 1;
                break;
		}
	}while (tecla != 13);

	Beep(349, 100);

    if (largura == 1)
	{
		system("cls");
		filmesmenu(filme);
	}

	else if (largura == 41)
	{
		system("cls");
		encerrando();
	}

	Gotoxy(36, 21);
	printf(RST"Escolher assentos"RST);

    i=0;

	Gotoxy(4, 24);
	printf(YEL"Quantos ingressos voce deseja?"RST);
	Gotoxy(4, 25);
	do
    {
        vali_ingressos[i] = '\0';
        num = getch();
        if(isdigit(num))
        {
            vali_ingressos[i] = num;
            i++;
            printf("%c", num);
        }
        if(num == 8 && i || atoi(vali_ingressos) > 25)// 8 = backspace e i -> se houver caracteres ja digitados
        {
          vali_ingressos[i] = '\0';
          i--;
          printf("\b \b");
        }

    }while(num != 13  || strlen(vali_ingressos) < 1 );

	Beep(349, 100);

	for (i = 0, k = 0; i < atoi(vali_ingressos); i++)
	{
		Gotoxy(4, 26);
		printf(YEL"Escolha as cadeiras:"RST);
        do
        {
        linha = valiletra(k);
        coluna = valinum(k);
        if(Cinema[linha][coluna] == 1)
        {
            Gotoxy(4 + k, 27);
            printf("         ");
            Gotoxy(4,28);
            printf(RED"Assento ocupado"RST);
        }
        }while(Cinema[linha][coluna] == 1);
        Gotoxy(4,28);
        printf("                ");
		Cinema[linha][coluna] = 1;
		PCinema[linha][coluna] = 1;

		if (coluna < 23 && coluna >= 0 && linha < 14 && linha >= 0)
		{
			gravar(linha, coluna, file_name);
		}
		k += 5;
	}

	for (linha = 0; linha < 14; linha++)
	{
		Gotoxy(5, 2 + linha);
		for (coluna = 0; coluna < 23; coluna++)
		{
			if (Cinema[linha][coluna] == 1) //Se tiver ocupada imprime veremlho
				printf(RED"%c%d "RST, linha + 65, coluna);

			else if (Cinema[linha][coluna] == 0) //Livre imprime verde
				printf(GRNN"%c%d "GRN, linha + 65, coluna);
		}
		printf("\n");
	}

	largura = 1;

	do
	{
        Gotoxy(78, 28);
		if(largura == 1)
			printf(RED"Confirmar"RST);

		else if(largura != 1)
			printf(RST"Confirmar"RST);

        Gotoxy(5, 21);
		if(largura == 21)
			printf(RED"Voltar"RST);

		else if(largura != 21)
			printf(RST"Voltar"RST);

		Gotoxy(80, 21);
		if(largura == 41)
			printf(RED"Sair "RST);

		else if(largura != 41)
			printf(RST"Sair "RST);

		fflush(stdin);
		tecla = getch();

		switch(tecla)
		{
			case 75:
				if (largura > 1)
					largura -= 20;

				else
					largura = 41;
				break;

			case 77:
				if (largura < 41)
					largura += 20;

				else
					largura = 1;
				break;
		}
	}while (tecla != 13);

	Beep(349, 100);

    if (largura == 1)
	{
		system("cls");
		bilhete(nome, idade, PCinema, horario,filme);
	}

	if (largura == 21)
	{
		system("cls");
		filmesmenu(filme);
	}

    if (largura == 41)
		encerrando();
}

int ler(int *rL, int *rC, int *rB, const char* file_name)
{
	FILE *cine; //Ponteiro para o arquivo
	int linhas, colunas; //Vari�veis para leitura

	int i = 0, cont = 0; //Vari�veis para Contagem
	cine = fopen(file_name, "r"); //Aponta o ponteiro para o arquivo aberto em modo leitura

	if (cine == NULL) //Se o arquivo nao for encontrado
		encerrando();

	if (vazio(file_name) == 0)//Se o arquivo estiver Vazio
	{
		*rB = 0;
		return 0;
	}
	while (fscanf(cine, "%d", &linhas) != -1 && fscanf(cine, "%d", &colunas) != -1) //Repete at� o arquivo acabar
	{
		*rL = linhas; //Passa o par�metro de linhas para o ponteiro
		*rC = colunas; //Passa o par�metro de colunas para o ponteiro
		++rL; //Move o ponteiro para o proximo vetor
		++rC; //Move o ponteiro para o proximo espa�o de memoria em seu vetor
		cont++;
		*rB = cont;
	}

	fclose(cine);//Fecha o Arquivo
	return 0;
}

int gravar(int linha, int coluna, const char* file_name)
{
	FILE *cine;
	cine = fopen(file_name, "a+");//Aponta o ponteiro para o arquivo aberto em modo escrita, por�m se precisar criar o arquivo ele cria

	if (cine == NULL)
		encerrando();

	fprintf(cine, "%d %d\n", linha, coluna); //Grava no arquivo a linha e a coluna recebida pela fun��o
	fclose(cine);
}
int criar(const char* file_name)
{
	FILE *cine;
	cine = fopen(file_name, "a+");//Aponta o ponteiro para o arquivo aberto em modo escrita, por�m se precisar criar o arquivo ele cria
	fclose(cine);
}
int vazio(const char* file_name)
{
    FILE *cine;
	cine = fopen(file_name, "r");

    if (cine == NULL)
    	encerrando();

    fseek(cine, 0, SEEK_END); //Inicia o arquivo com o ponteiro na posi��o final

    int tamanho = ftell(cine); //Passa o tamanho do arquivo para a vari�vel tamanho;

    fclose(cine);
    return tamanho;
}

void encerrando()
{
	system("color 00");

    Retangulo(0, 0, 90, 30);//Retangulo Principal
	Retangulo(16, 12, 59, 4);//Retangulo Principal

	Gotoxy(39,11);
	printf("Encerrando...");

    int i = 0;
	while (i <= 50)
	{
		Gotoxy(i + 18, 14);
		printf(REDB" "REDN); //Imprime os espa�os em vermelho

		Gotoxy(70, 14);
		printf(RST"%d%%"REDN, i * 2); //Imprime a porcentagem de carregamento

		i++;

		Sleep(15);//Delay de 15ms
	}

	Beep(349,100);
	system("cls");
	exit(1); //Encerra o progama
}

void desenhoUm()
{
Gotoxy(22,11);printf(RED"\xDB\xDC\xDB\xDC\xDB"BLU);
Gotoxy(22,12);printf(RED"\xDF   \xDF"BLU);
Gotoxy(23,12);printf(RED"\xDB\xDB\xDB"GRN);
Gotoxy(24,13);printf(GRN"\xDB"GRN);
Gotoxy(24,14);printf(GRN"\xDB"RED);
}

void desenhoDois()
{
Gotoxy(42,11);printf(GRY"\xDB\xDC\xDB\xDC\xDB"GRY);
Gotoxy(42,12);printf(GRY"      "GRY);
Gotoxy(42,12);printf(GRY" \xDB\xDB\xDB "GRY);
Gotoxy(42,13);printf(GRY" \xDB\xDB\xDB "GRY);
Gotoxy(42,14);printf(GRY"\xDB\xDB\xDB\xDB\xDB"YEL);
}

void desenhoTres()
{
Gotoxy(62,11);printf(BLU" \xDB\xDB\xDB "YEL);
Gotoxy(62,12);printf(BLU"\xDB\xDB\xDB\xDB\xDB"RST);
Gotoxy(62,12);printf(" \xDF\xDB\xDF ");
Gotoxy(62,13);printf("  \xDB");
Gotoxy(62,14);printf("  \xDB"RST);
}

void desenhoCatalogoUm()
{
Gotoxy(10,5);printf(RED"\xDB\xDC\xDB\xDC\xDB"BLU);
Gotoxy(10,6);printf(RED"\xDF   \xDF"BLU);
Gotoxy(10,6);printf(RED"\xDB\xDB\xDB\xDB\xDB"GRY);
Gotoxy(11,7);printf(RED"\xDB\xDB\xDB"GRN);
Gotoxy(12,8);printf(GRN"\xDB"GRN);
Gotoxy(12,9);printf(GRN"\xDB"RED);
}

void desenhoCatalogoDois()
{
Gotoxy(10,5);printf(GRY"\xDB\xDC\xDB\xDC\xDB"GRY);
Gotoxy(10,6);printf(GRY"      "GRY);
Gotoxy(10,6);printf(GRY" \xDB\xDB\xDB "GRY);
Gotoxy(10,7);printf(GRY" \xDB\xDB\xDB "GRY);
Gotoxy(10,8);printf(GRY"\xDB\xDB\xDB\xDB\xDB"GRY);
Gotoxy(10,9);printf(GRY"\xDF\xDF\xDF\xDF\xDF"GRY);
}

void desenhoCatalogoTres()
{
Gotoxy(11,5);printf(BLU"\xDB\xDB\xDB "GRY);
Gotoxy(11,6);printf(BLU"\xDB\xDB\xDB\xDB"RST);
Gotoxy(11,6);printf("\xDF\xDB\xDF ");
Gotoxy(12,7);printf("\xDB");
Gotoxy(12,8);printf("\xDB");
Gotoxy(12,9);printf("\xDB");
}

void bilhete(char nome[30], int idade, char assentos[14][23],int horario, int filme)
{
	int linha;
	int coluna;
	int jumpline=0;

	system("color 00");
	Retangulo(19,8,51,12);//PRINCI
	int i;
	Gotoxy(21,9);
	printf("%c",4);
	Gotoxy(68,9);
	printf("%c",4);
	Gotoxy(21,19);
	printf("%c",4);
	Gotoxy(68,19);
	printf("%c",4);

	for(i = 9; i < 20; i++)
    {
        Gotoxy(66, i);
        printf("|");
    }

	 if(filme == 1)
    {
    	Gotoxy(41,9);
    	printf(YEL"La Rosa"RST, filme);
	}

	if(filme == 2)
    {
    	Gotoxy(42,9);
    	printf(YEL"Roque"RST, filme);
	}
	if(filme == 3)
    {
    	Gotoxy(39,9);
    	printf(YEL"Brinquinhos"RST, filme);
	}

	Gotoxy(42, 10);
	if(horario == 1)
	{
		printf(YEL"18:00"RST);
	}
	else if(horario == 2)
	{
		printf(YEL"20:00"RST);
	}
	else if(horario == 3)
	{
		printf(YEL"22:00"RST);
	}

	Gotoxy(21, 12);
	printf(YEL"%s"RST, nome);

	Gotoxy(21, 13);
	printf(YEL"%d anos"RST, idade);

	Gotoxy(21, 15);
	printf(YEL"Assento(s) comprado(s):"RST);

	Gotoxy(21, 16);
	for(linha=0;linha<14;linha++)
	{
		for(coluna=0;coluna<23;coluna++)
		{
			if(assentos[linha][coluna] == 1)
			{
				printf(YEL"%c%i "RST,linha+65,coluna);
				jumpline++;
			}
			if(jumpline == 13)
			{
                Gotoxy(21, 17);
			}
		}
	}
	Gotoxy(40, 19);
	printf(YEL"BOM FILME!"RST);
	getch();
	system("cls");
	main();
}

int valinum(int compri)
{
	char vali_coluna[4],num;
	int i=0;
    Gotoxy(5 + compri, 27);
	do
    {
        vali_coluna[i] = '\0';
        num = getch();
        if(isdigit(num))
        {
            vali_coluna[i] = num;
            i++;
            printf("%c", num);
        }
        vali_coluna[i] = '\0';
        if(num == 8 && i || atoi(vali_coluna) > 22)// 8 = backspace e i -> se houver caracteres ja digitados
        {
          vali_coluna[i] = '\0';
          i--;
          printf("\b \b");
        }
    }while(num != 13  || strlen(vali_coluna) < 1);
return atoi(vali_coluna);
}

int valiletra(int compri)
{
	char letra,vali_letra[3];
	int i=0;
    Gotoxy(4 + compri, 27);
	do
    {
        vali_letra[i] = '\0';
        letra = getch();
        letra = toupper(letra);
        if(isalpha(letra))
        {
            vali_letra[i] = letra;
            i++;
            printf("%c", letra);
        }
        vali_letra[i] = '\0';
        if(letra == 8 && i || strlen(vali_letra) > 1 || letra - 65 > 13)// 8 = backspace e i -> se houver caracteres ja digitados
        {
          vali_letra[i] = '\0';
          i--;
          printf("\b \b");
        }
	}while(letra != 13 || strlen(vali_letra) < 1 || vali_letra[i - 1] == 32);
	letra = vali_letra[0];
	letra = letra - 65;
	return letra;
}
