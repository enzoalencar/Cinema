	//Bibliotecas
#include <stdio.h> //Blioteca padr?o de entrada e saida
#include <windows.h> //Biblioteca com fun??es do terminal do Windows
#include <conio.h> //Biblioteca de manipula??o de caracteres na Tela
#include <ctype.h> //Biblioteca para classificar caracteres

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
#define BRO  "\e[33;2m" // Amarelo-Escuro

//Funçoess auxiliares
void moverxy(int coord_x, int coord_y); //Fun??o que possibilita a personaliza??o localizada no terminal, atrav?s de coordenadas
void retangulo( int ho, int vo, int larg, int alt ); //Gera um ret?ngulo na tela
void com_cursor();
void sem_cursor();
//Funçoes de desenho no menu
void desenhoUm();
void desenhoDois();
void desenhoTres();
//Funçoes de desenho no catalogo
void desenhoCatalogoUm();
void desenhoCatalogoDois();
void desenhoCatalogoTres();
//Funcoes de inicio e encerramento
void load(); //Fun??o da tela de loading de inicializa??o
void encerrando();//Fun?ao da tela de loading de encerramento
void bilhete(char nome[30], int idade, char assentos[14][23],int horario, int filme);
//Menus
void inicio(); //Fun??o do menu inicial
void catalogo(); //Fun??o do cat?logo de filmes
void filmesmenu(int filme); //Fun??o do filme especificado
void login(int filme, int horario); //Fun??o de identifica??o
void assentos(int filme, int horario, char nome[30], int idade); //Fun??o das cadeiras do hor?rio especificado
//Validaçoes
int valinum(int compri);
int valiletra(int compri);
//Funçoes arquivos
int criar(const char* file_name);
int ler(int *rL,int *rC,int *rB, const char* file_name); //Ler os assentos j? ocupados no arquivo
int gravar(int linha, int coluna, const char* file_name); //Fun??o que grava os novos assentos ocupados
int vazio(const char* file_name); //Fun?ao que Verifica se o arquivo esta vazio

//Fun??o Principal
int main()
{
	system("MODE con cols=92 lines=31");
	sem_cursor();
	load();
	inicio();
	return 0;
}

void moverxy(int coord_x, int coord_y)
{
	//Envia o parâmetro escolhido para o windows, posicionando o cursor nas respectivas coordenadas do console, como se ele fosse uma matriz
    HANDLE hCon;
    COORD dwPos;

    dwPos.X = coord_x;
    dwPos.Y = coord_y;
    hCon = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(hCon,dwPos);
}

void retangulo(int horizontal_inicial, int vertical_inicial, int larg, int alt)
{
    int horizontal, vertical;

    //Linhas horizontais
     for (horizontal = horizontal_inicial; horizontal < horizontal_inicial + larg; horizontal++)
	 {
        moverxy(horizontal, vertical_inicial);
        printf(RED"%c", 205); //Imprime o caracter especial com retorno 205

        moverxy(horizontal, vertical_inicial + alt);
        printf(RED"%c", 205);
     }

     //Linhas verticais
     for (vertical = vertical_inicial; vertical < vertical_inicial + alt; vertical++)
	 {
        moverxy(horizontal_inicial, vertical);
        printf(RED"%c", 186); //Imprime o Caracter Especial com retorno 186

        moverxy(horizontal_inicial + larg, vertical);
        printf(RED"%c", 186);
     }

     // Cantos
     moverxy(horizontal_inicial, vertical_inicial);
     printf(YEL"%c", 201); //Imprime o caracter especial com retorno 201

     moverxy(horizontal_inicial, vertical_inicial + alt);
     printf(YEL"%c", 200); //Imprime o caracter especial com retorno 200

     moverxy(horizontal_inicial + larg, vertical_inicial);
     printf(YEL"%c", 187); //Imprime o caracter especial com retorno 187

     moverxy(horizontal_inicial + larg, vertical_inicial + alt);
     printf(YEL"%c", 188); //Imprime o caracter especial com retorno 188
}

void load()
{
	system("color 00"); //Redefine a sistema para a cor padrao

	moverxy(39, 11);
	printf("Iniciando...");

	retangulo(0, 0, 90, 30); //Retangulo externo
	retangulo(16, 12, 59, 4); //Retangulo interno

	int i=0;
	while (i<=50)
	{
		moverxy(i + 18,14);
		printf(REDB" "REDN); //Imprime um espaco vermelho

		moverxy(70,14);
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

	int altura = 1; //Variavel que aponta a coordenada de altura do cursor(altura e inversa ao sentido convencional)
	char tecla; //Variavel para armazenar as teclas pressionadas

	retangulo(0, 0, 90, 30); //Retangulo externo
	retangulo(36, 8, 17, 10); //Retangulo interno

    moverxy(42, 10);
    printf(YEL"CINEMA"RST);
     moverxy(42, 16);
    printf(YEL"FACENS"RST);

	do
	{
    	moverxy(41, 12);
    	if (altura == 1)
    		printf(RED"Catalogo"RST);

    	else if (altura != 1)
 			printf(RST"Catalogo"RST);

 		moverxy(43, 14);
 		if (altura == 2)
 			printf(RED"Sair"RST);

 		else if (altura != 2)
 			printf(RST"Sair"RST);


		fflush(stdin); //Limpa o buffer
		tecla = getch(); //Le um caracter

		switch(tecla)
		{
			case 72: //Caso pressione a seta para cima
				if(altura > 1)
					altura -= 1 ;

				else
					altura = 2; //Se o limite for excedido ele volta ao ultimo valor de altura
				break;

			case 80: //Caso pressione a seta para baixo
				if(altura < 2)
					altura += 1;

				else
					altura = 1 ; //Se o limite for excedido ele volta ao primeiro valor de altura
				break;
		}
	}while (tecla != 13); //Finaliza ao pressionar Enter

	Beep(349, 100);
	system("cls");

	switch(altura)
	{
	    case 1: //Caso selecione "Catalogo"
			catalogo();
			break;

		case 2: //Caso selecione "Sair"
			encerrando();
			break;
	}
}

void catalogo()
{
	int largura = 2; //Variavel que aponta a coordenada de largura do cursor
	char tecla; //Variavel para armazenar as teclas pressionadas

    moverxy(42, 6);
	printf(YEL"FILMES"RST);

	retangulo(0, 0, 90, 30);//Ret?ngulo externo

	int i, espacamento = 0;

	desenhoUm();
	desenhoDois();
	desenhoTres();

	for (i = 1; i < 4; i++) //Constr?i 3 ret?ngulos internos
	{
		espacamento += 20;
		retangulo(espacamento, 10, 8, 5);
	}

	do
	{
        moverxy(5, 25);
		if (largura == 1)
			printf(RED"Voltar"RST); //Imprime Voltar vermelho

		else if (largura != 1)
			printf(RST"Voltar"RST); //Imprime Voltar branco

		moverxy(21, 16);
		if (largura == 2)
			printf(RED"La Rosa "RST); //Imprime Filme 1 vermelho

		else if (largura != 2)
			printf(RST"La Rosa "RST); //Imprime Filme 1 branco

		moverxy(42, 16);
		if (largura == 3)
			printf(RED"Roque "RST); //Imprime Filme 2 vermelho

		else if (largura != 3)
			printf(RST"Roque "RST); //Imprime Filme 2 branco

		moverxy(59, 16);
		if (largura == 4)
			printf(RED"Brinquinhos "RST); //Imprime Filme 3 vermelho

		else if (largura != 4)
			printf(RST"Brinquinhos "RST); //Imprime Filme 3 branco

		moverxy(80, 25);
		if (largura == 5)
			printf(RED"Sair "RST); //Imprime Sair vermelho

		else if (largura != 5)
			printf(RST"Sair "RST); //Imprime Sair branco

		fflush(stdin);
		tecla = getch();

		switch(tecla)
		{
			case 75: //Move ao pressionar seta para esquerda
				if(largura > 1)
					largura -= 1;

				else
					largura = 5; //Se o limite for excedido ele volta ao ?ltimo valor de largura
				break;

			case 77: //Move ao pressionar seta para direita
				if(largura < 5)
					largura += 1;

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

		case 2: //Caso selecione Filme 1
			filmesmenu(1);
			break;

		case 3: //Caso selecione Filme 2
			filmesmenu(2);
			break;

		case 4: //Caso selecione Filme 3
			filmesmenu(3);
			break;

		case 5: //Caso selecione Sair
			encerrando();
			break;
	}
}

void filmesmenu(int filme)
{
    int largura = 2; //Variavel que aponta a coordenada de largura do cursor
    char tecla;


    retangulo(0, 0, 90, 30); //retangulo externo
    retangulo(5, 3, 14, 8); //retangulo interno da foto
    retangulo(29, 3, 51, 12); //retangulo interno da descricao
    retangulo(18, 23, 50, 4); //retangulo externo dos horarios

    if(filme == 1)
    {
    	moverxy(9,12);
    	printf(YEL"La Rosa"RST, filme);
    	moverxy(3,13);
        printf(RED"MAIORIDADE NECESSARIA"WHT);
        desenhoCatalogoUm();
        moverxy(30,5);
        printf(WHT" Romance mexicano que acompanha a vida de Rosa,"WHT);
        moverxy(30,6);
        printf(WHT" uma jovem mulher que descobre o verdadeiro"WHT);
        moverxy(30,7);
        printf(WHT" significado de uma paixao caliente."RST);
	}
	if(filme == 2)
    {
    	moverxy(10,12);
    	printf(YEL"Roque"RST, filme);
    	moverxy(3,13);
        desenhoCatalogoDois();
        moverxy(30,5);
        printf(" O Suspense sobre a historia de uma partida de ");
        moverxy(30,6);
        printf(" xadrez que mudou o rumo da guerra fria e ");
        moverxy(30,7);
        printf(" estremeceu a geopolitica mundial.");
	}
	if(filme == 3)
    {
    	moverxy(7,12);
    	printf(YEL"Brinquinhos"RST, filme);
    	moverxy(3,13);
        desenhoCatalogoTres();
        moverxy(30,5);
        printf(" Documentario sobre a vida de Brinquinhos Malone,");
        moverxy(30,6);
        printf(" desde a sua infancia, ajudando seu pai Brinconis,");
        moverxy(30,7);
        printf(" no ramo da pintura ate sua consagracao como um");
        moverxy(30,8);
        printf(" dos maiores futebolistas da historia.");
	}

    moverxy(40,22);
    printf(YEL"HORARIOS"RST);

    do
    {
        moverxy(5,25);
        if (largura == 1)
            printf(RED"Voltar"RST);

        else if (largura != 1)
            printf(RST"Voltar"RST);

        moverxy(21, 25);
        if (largura == 2)
            printf(RED"18:00 "RST);

        else if (largura != 2)
            printf(RST"18:00 "RST);

        moverxy(41, 25);
        if (largura == 3)
            printf(RED"20:00 "RST);

        else if (largura != 3)
            printf(RST"20:00 "RST);

        moverxy(61, 25);
        if (largura == 4)
            printf(RED"22:00 "RST);

        else if (largura != 4)
            printf(RST"22:00 "RST);

        moverxy(80, 25);
        if (largura == 5)
            printf(RED"Sair "RST);

        else if (largura != 5)
            printf(RST"Sair "RST);

        fflush(stdin);
        tecla = getch();

        switch(tecla)
        {
            case 75:
                if (largura > 1)
                    largura -= 1;

                else
                    largura = 5;
                break;

            case 77:
                if (largura < 5)
                    largura += 1;

                else
                    largura = 1;
                break;
        }
    }while (tecla != 13);

    Beep(349, 100);
    system("cls");

    if (largura == 1)
        catalogo();

    else if (largura == 2)
        login(filme, 1);

    else if (largura == 3)
        login(filme, 2);

    else if (largura == 4)
        login(filme, 3);

    else if (largura == 5)
        encerrando();
}

void login(int filme, int horario)
{
    int i = 0;
    char nome[30], idade[4];
    char letra, num;

	system("color 00");//Setar Padrao Cor do Terminal
	com_cursor();
    retangulo(0,0,90,30);//retangulo Principal
    retangulo(28,8,34,10);//retangulo Mini Menu

    moverxy(42,10);
    printf(YEL"LOGIN"RST);

    moverxy(31,12);
    printf(YEL"Nome Completo:"RST);

    moverxy(31,13);
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
            moverxy(31, 14);
            printf(RED"Maximo de caracteres atingido"RST);
            nome[i]='\0';
            i--;
            moverxy(61, 13);
            printf("\b \b");
        }
	}while(letra != 13 || strlen(nome) < 1 || nome[i - 1] == 32);

	fflush(stdin);
	i = 0;

    moverxy(31, 14);
    printf("                               ");

	moverxy(31,15);
    printf(YEL"Idade:"RST);

    moverxy(31,16);
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
        if(num == 8 && i || atoi(idade) > 120 || strlen(idade) > 29)// 8 = backspace e i -> se houver caracteres ja digitados
        {
          idade[i] = '\0';
          i--;
          printf("\b \b");
        }

    }while(num != 13  || strlen(idade) < 1 || atoi(idade) == 0);

	if(filme == 1 && atoi(idade) < 18)
	{
		moverxy(31,16);
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
	retangulo(0, 0, 90, 30); //Retangulo externo
	retangulo(2, 1, 86, 15); //Retangulo dos assentos
	retangulo(38, 17, 13, 2); //Retangulo da bilheteria
	retangulo(2, 20, 86, 2); //Retangulo interno de menu
	retangulo(2, 23, 86, 6); //Retangulo de interacao com o usuario
	char Cinema[14][23]; //Matriz que armazena as cadeiras ocupadas
	char file_name[4];
	char PCinema[14][23]; // Matriz copia
    char vali_ingressos[5];
    char num;
    int largura = 1; //Variavel que aponta a coordenada de largura do cursor
	int tecla; //Variavel para armazenar as teclas pressionadas
	int i = 0; //Contador generico
    int k = 0; //Contador alternativo
    int colunasP[322];
	int linhasP[322];
    int pause;
    int linha, coluna;

    sem_cursor();

	//Amostra de sala vazia
	for (linha = 0; linha < 14; linha++)
    {
		for (coluna = 0; coluna < 23; coluna++)
        {
			Cinema[linha][coluna]=0; //Tranforma todas as cadeiras em vazias
			PCinema[linha][coluna] = 0;
        }
    }

    sprintf(file_name, "%i-%i", filme, horario); //Cria uma string a partir do numero da sala e do horario
    criar(file_name);
	ler(linhasP, colunasP, &pause, file_name); //Chama a funcao apontando para 3 ponteiros

	if (pause != 0) //Se o ponteiro retorna 0 que significa que o arquivo esta vazio, logo ele nao tenta gravar nenhuma matriz
	{
		while (i < pause) //Grava ate o valor contado dentro da funcao que define a quantidade de cadeira armazenadas
		{
			int a = linhasP[i];
			int b = colunasP[i];
			Cinema[a][b] = 1; //Transforma a cadeira em ocupada
			i++;
		}
	}

	for (linha = 0; linha < 14; linha++)//Imprime a matriz na tela
	{
		moverxy(5, 2 + linha);
		for (coluna = 0; coluna < 23; coluna++)
		{
			if (Cinema[linha][coluna] == 1) //Se estiver ocupada imprime vermelho
				printf(RED"%c%d "RST, linha + 65, coluna);

			else if (Cinema[linha][coluna] == 0) //Se estiver livre imprime verde
				printf(GRNN"%c%d "RST, linha + 65, coluna);
		}
	}

    moverxy(40, 18);
	printf(YEL"BILHETERIA"RST);

	do
	{
        moverxy(5, 21);
		if (largura == 1)
			printf(RED"Voltar"RST);

		if (largura != 1)
			printf(RST"Voltar"RST);

		moverxy(36, 21);
		if (largura == 2)
			printf(RED"Escolher assentos"RST);

		if (largura != 2)
			printf(RST"Escolher assentos"RST);

		moverxy(80, 21);
		if (largura == 3)
			printf(RED"Sair "RST);

		if (largura != 3)
			printf(RST"Sair "RST);

		fflush(stdin);
		tecla = getch();

		switch(tecla)
		{
            case 75:
                if (largura > 1)
                    largura -= 1;

                else
                    largura = 3;
                break;

            case 77:
                if (largura < 3)
                    largura += 1;

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

	else if (largura == 3)
	{
		system("cls");
		encerrando();
	}

	moverxy(3, 21);
	printf("                                                                                  "RST);
	moverxy(39,21);
	printf("Escolhendo");
	Sleep(150);
	printf(".");
	Sleep(150);
	printf(".");
	Sleep(150);
	printf(".");

    i=0;
    com_cursor();

	moverxy(4, 24);
	printf(YEL"Quantos ingressos voce deseja?"RST);
	moverxy(4, 25);
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
        if(num == 8 && i || atoi(vali_ingressos) > 25 || strlen(vali_ingressos) > 5)// 8 = backspace e i -> se houver caracteres ja digitados
        {
          vali_ingressos[i] = '\0';
          i--;
          printf("\b \b");
        }

    }while(num != 13  || strlen(vali_ingressos) < 1  || atoi(vali_ingressos) == 0);

	Beep(349, 100);

	for (i = 0, k = 0; i < atoi(vali_ingressos); i++)
	{
		moverxy(4, 26);
		printf(YEL"Escolha as cadeiras:"RST);
        do
        {
        linha = valiletra(k);
        coluna = valinum(k);
        if(Cinema[linha][coluna] == 1)
        {
            moverxy(4 + k, 27);
            printf("         ");
            moverxy(4,28);
            printf(RED"Assento ocupado"RST);
        }
        }while(Cinema[linha][coluna] == 1);
        moverxy(4,28);
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
		moverxy(5, 2 + linha);
		for (coluna = 0; coluna < 23; coluna++)
		{
			if (Cinema[linha][coluna] == 1) //Se tiver ocupada imprime veremlho
			{
				printf(RED"%c%d "RST, linha + 65, coluna);
			}


			else if (Cinema[linha][coluna] == 0) //Livre imprime verde
				printf(GRNN"%c%d "GRN, linha + 65, coluna);
		}
	}

    sem_cursor();

	do
	{
		moverxy(78, 28);
		printf(RED"Confirmar"RST);
		tecla = getch();
	}while (tecla != 13);

	Beep(349, 100);
	system("cls");
	bilhete(nome, idade, PCinema, horario,filme);
}

int ler(int *rL, int *rC, int *rB, const char* file_name)
{
	FILE *cine; //Ponteiro para o arquivo
	int linhas, colunas; //Variaveis para leitura

	int i = 0, cont = 0; //Variaveis para Contagem
	cine = fopen(file_name, "r"); //Aponta o ponteiro para o arquivo aberto em modo leitura

	if (cine == NULL) //Se o arquivo nao for encontrado
		encerrando();

	if (vazio(file_name) == 0)//Se o arquivo estiver Vazio
	{
		*rB = 0;
		return 0;
	}
	while (fscanf(cine, "%d", &linhas) != -1 && fscanf(cine, "%d", &colunas) != -1) //Repete at? o arquivo acabar
	{
		*rL = linhas; //Passa o par?metro de linhas para o ponteiro
		*rC = colunas; //Passa o par?metro de colunas para o ponteiro
		++rL; //Move o ponteiro para o proximo vetor
		++rC; //Move o ponteiro para o proximo espa?o de memoria em seu vetor
		cont++;
		*rB = cont;
	}

	fclose(cine);//Fecha o Arquivo
	return 0;
}

int gravar(int linha, int coluna, const char* file_name)
{
	FILE *cine;
	cine = fopen(file_name, "a+");//Aponta o ponteiro para o arquivo aberto em modo escrita, por?m se precisar criar o arquivo ele cria

	if (cine == NULL)
		encerrando();

	fprintf(cine, "%d %d\n", linha, coluna); //Grava no arquivo a linha e a coluna recebida pela fun??o
	fclose(cine);
}

int criar(const char* file_name)
{
	FILE *cine;
	cine = fopen(file_name, "a+");//Aponta o ponteiro para o arquivo aberto em modo escrita, por?m se precisar criar o arquivo ele cria
	fclose(cine);
}

int vazio(const char* file_name)
{
    FILE *cine;
	cine = fopen(file_name, "r");

    if (cine == NULL)
    	encerrando();

    fseek(cine, 0, SEEK_END); //Inicia o arquivo com o ponteiro na posi??o final

    int tamanho = ftell(cine); //Passa o tamanho do arquivo para a vari?vel tamanho;

    fclose(cine);
    return tamanho;
}

void encerrando()
{
	system("color 00");

    retangulo(0, 0, 90, 30);//retangulo Principal
	retangulo(16, 12, 59, 4);//retangulo Principal

	moverxy(39,11);
	printf("Encerrando...");

    int i = 0;
	while (i <= 50)
	{
		moverxy(i + 18, 14);
		printf(REDB" "REDN); //Imprime os espa?os em vermelho

		moverxy(70, 14);
		printf(RST"%d%%"REDN, i * 2); //Imprime a porcentagem de carregamento

		i++;

		Sleep(15);//Delay de 15ms
	}

	Beep(349,100);
	system("cls");
	exit(0); //Encerra o progama
}

void desenhoUm()
{
moverxy(22,11);printf(RED"\xDB\xDC\xDB\xDC\xDB"BLU);
moverxy(22,12);printf(RED"\xDF   \xDF"BLU);
moverxy(23,12);printf(RED"\xDB\xDB\xDB"GRN);
moverxy(24,13);printf(GRN"\xDB"GRN);
moverxy(24,14);printf(GRN"\xDB"RED);
}

void desenhoDois()
{
moverxy(42,11);printf(GRY"\xDB\xDC\xDB\xDC\xDB"GRY);
moverxy(42,12);printf(GRY"      "GRY);
moverxy(42,12);printf(GRY" \xDB\xDB\xDB "GRY);
moverxy(42,13);printf(GRY" \xDB\xDB\xDB "GRY);
moverxy(42,14);printf(GRY"\xDB\xDB\xDB\xDB\xDB"YEL);
}

void desenhoTres()
{
moverxy(62,11);printf(BLU" \xDB\xDB\xDB "YEL);
moverxy(62,12);printf(BLU"\xDB\xDB\xDB\xDB\xDB"RST);
moverxy(62,12);printf(" \xDF\xDB\xDF ");
moverxy(62,13);printf("  \xDB");
moverxy(62,14);printf("  \xDB"RST);
}

void desenhoCatalogoUm()
{
moverxy(10,5);printf(RED"\xDB\xDC\xDB\xDC\xDB"BLU);
moverxy(10,6);printf(RED"\xDF   \xDF"BLU);
moverxy(10,6);printf(RED"\xDB\xDB\xDB\xDB\xDB"GRY);
moverxy(11,7);printf(RED"\xDB\xDB\xDB"GRN);
moverxy(12,8);printf(GRN"\xDB"GRN);
moverxy(12,9);printf(GRN"\xDB"RST);
}

void desenhoCatalogoDois()
{
moverxy(10,5);printf(GRY"\xDB\xDC\xDB\xDC\xDB"GRY);
moverxy(10,6);printf(GRY"      "GRY);
moverxy(10,6);printf(GRY" \xDB\xDB\xDB "GRY);
moverxy(10,7);printf(GRY" \xDB\xDB\xDB "GRY);
moverxy(10,8);printf(GRY"\xDB\xDB\xDB\xDB\xDB"GRY);
moverxy(10,9);printf(GRY"\xDF\xDF\xDF\xDF\xDF"RST);
}

void desenhoCatalogoTres()
{
moverxy(11,5);printf(BLU"\xDB\xDB\xDB "GRY);
moverxy(11,6);printf(BLU"\xDB\xDB\xDB\xDB"RST);
moverxy(11,6);printf("\xDF\xDB\xDF ");
moverxy(12,7);printf("\xDB");
moverxy(12,8);printf("\xDB");
moverxy(12,9);printf("\xDB"RST);
}

void bilhete(char nome[30], int idade, char assentos[14][23],int horario, int filme)
{
	int linha;
	int coluna;
	int jumpline=0;

	system("color 00");
	retangulo(19,8,51,12);//PRINCIPAL
	int i;
	moverxy(21,9);
	printf("%c",4);
	moverxy(68,9);
	printf("%c",4);
	moverxy(21,19);
	printf("%c",4);
	moverxy(68,19);
	printf("%c",4);

	for(i = 9; i < 20; i++)
    {
        moverxy(66, i);
        printf("|");
    }

	 if(filme == 1)
    {
    	moverxy(41,9);
    	printf(YEL"La Rosa"RST, filme);
	}

	if(filme == 2)
    {
    	moverxy(42,9);
    	printf(YEL"Roque"RST, filme);
	}
	if(filme == 3)
    {
    	moverxy(39,9);
    	printf(YEL"Brinquinhos"RST, filme);
	}

	moverxy(42, 10);
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

	moverxy(21, 12);
	printf(YEL"%s"RST, nome);

	moverxy(21, 13);
	printf(YEL"%d anos"RST, idade);

	moverxy(21, 15);
	printf(YEL"Assento(s) comprado(s):"RST);

	moverxy(21, 16);
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
                moverxy(21, 17);
			}
		}
	}
	moverxy(40, 19);
	printf(YEL"BOM FILME!"RST);
	getch();
	Beep(349,100);
	system("cls");
	inicio();
}

int valinum(int compri)
{
	char vali_coluna[4],num;
	int i=0;
    moverxy(5 + compri, 27);
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
    moverxy(4 + compri, 27);
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

void com_cursor() //funcao para aparecer o cursor da tela
{
    CONSOLE_CURSOR_INFO cursor = {1, TRUE};
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor);
}

void sem_cursor() //funcao para aparecer o cursor da tela
{
    CONSOLE_CURSOR_INFO cursor = {1, FALSE};
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor);
}
