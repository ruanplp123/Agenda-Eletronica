#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <locale.h>
#include <windows.h>

void gravacao(void);
void lista(void);
void apagar(void);
void apagarContatoPorLinha(void);
void consulta(void);
void gotoxy(int x, int y);
void imprimirTexto(int x, int y, const char* texto);


struct ficha_telefonica
{
    char nome[50];
    char telefone[10];
};


struct ficha_telefonica listaContatos[100]; 
int totalContatos = 0; 


int main(void)
{
	
	int x = 10;
	int y = 5;
	
    setlocale(LC_ALL, "Portuguese");

    char opcao;


    do
    {
    	system("color 0A");
        system("cls");
        imprimirTexto(59, 1, " _____________Menu_______________\n");
        imprimirTexto(60, 2, "\x7C 1 - Inserção de dados        \x7C\n ");
        imprimirTexto(60, 3, "\x7C 2 - Lista de dados           \x7C\n");
        imprimirTexto(60, 4, "\x7C 3 - Apagar dados             \x7C\n");
        imprimirTexto(60, 5, "\x7C 4 - Apagar contato por linha \x7C\n");
        imprimirTexto(60, 6, "\x7C 5 - Consultar contato        \x7C\n");
        imprimirTexto(60, 7, "\x7C 6 - Sair                     \x7C\n");
        imprimirTexto(60, 9, " Digite uma opção:");
        scanf("%c", &opcao);
        fflush(stdin);

        switch (opcao)
        {
        case '1':
            gravacao();
            break;
        case '2':
            lista();
            break;
        case '3':
            apagar();
            break;
        case '4':
            apagarContatoPorLinha();
            break;
        case '5':
            consulta();
            break;
        case '6':
            imprimirTexto(60, 12, "Até logo...");
            break;
        default:
        	system("color 0C");
            system("cls");      
            printf("Opção inválida \n(Por favor pressione qualquer tecla para continuar)");
            getch();
            break;
        }
    } while (opcao != '6');

    return 0;
}

void gravacao(void)
{
	system("color 0D");
    FILE *arquivo;
    arquivo = fopen("nomes.txt", "a");
    struct ficha_telefonica novoContato;
    system("cls");
    printf("Digite um nome: ");
    fflush(stdin);
    gets(novoContato.nome);
    printf("Digite seu telefone: ");
    fflush(stdin);
    gets(novoContato.telefone);
    fprintf(arquivo, "Nome: %s | Numero de Telefone: %s\n", novoContato.nome, novoContato.telefone);
    fclose(arquivo);
    printf("Contato adicionado com sucesso \n(Por favor pressione qualquer tecla para continuar)");
    getch();
}

void lista(void)
{
	system("color 0E");
    FILE *arquivo;
    arquivo = fopen("nomes.txt", "r");
    char texto[100];

    system("cls");
    while (fgets(texto, sizeof(texto), arquivo))
    {
        printf("%s", texto);
    }

    fclose(arquivo);
    printf("\n Por favor pressione qualquer tecla para continuar");
    getch();
}

void apagar(void)
{
    FILE *arquivo;
    arquivo = fopen("nomes.txt", "w");
    fclose(arquivo);
    system("cls");
    printf("Conteúdo apagado \n(Por favor pressione qualquer tecla para continuar)");
    getch();
}

void apagarContatoPorLinha(void)
{
	system("color 0A");
    FILE *arquivo;
    FILE *temp;
    arquivo = fopen("nomes.txt", "r");
    temp = fopen("temp.txt", "w");
    char texto[100];
    int linha, cont = 1;
    bool encontrado = false;

    system("cls");
    printf("Digite o número da linha do contato a ser apagado: ");
    scanf("%d", &linha);

    while (fgets(texto, sizeof(texto), arquivo))
    {
        if (cont != linha)
        {
            fprintf(temp, "%s", texto);
        }
        else
        {
            encontrado = true;
        }

        cont++;
    }

    fclose(arquivo);
    fclose(temp);

    if (encontrado)
    {
        remove("nomes.txt");
        rename("temp.txt", "nomes.txt");
        printf("Contato apagado com sucesso! \n(Por favor pressione qualquer tecla para continuar)");
    }
    else
    {
    	system("color 0C");
        remove("temp.txt");
        printf("Linha não encontrada \n(Por favor pressione qualquer tecla para continuar)");
    }

    getch();
}

void consulta(void)
{
    FILE *arquivo;
    arquivo = fopen("nomes.txt", "r");
    char nomeProcurado[50], texto[100];
    int cont = 1;
    bool encontrado = false;

    system("cls");
    printf("Por favor digite o nome do contato que deseja consultar: ");
    fflush(stdin);
    gets(nomeProcurado);

    while (fgets(texto, sizeof(texto), arquivo))
    {
        if (strstr(texto, nomeProcurado) != NULL)
        {
            encontrado = true;
            printf("%i - %s", cont, texto);
        }

        cont++;
    }

    fclose(arquivo);

    if (!encontrado)
    {
    	system("color 0C");
        printf("Contato '%s' nao encontrado.\n(Por favor pressione qualquer tecla para continuar)", nomeProcurado);
    }

    getch();
}

void gotoxy(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void imprimirTexto(int x, int y, const char* texto) {
    gotoxy(x, y);
    printf("%s", texto);
}
