#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include "TAD.h"


int main()
{
    ///Alexandre Oliveira - RA 101730527

    Unidade *unidades = NULL;
    Diretorio *dirAtual = NULL;
    Unidade *uniAtual = NULL;
    Comandos *listaComandos = NULL;
    char linhacomando[100];
    char argumento[50];
    char argumento2[50];
    char comando[50];
    char tecla;
    char c1, c2;
    int doskey = 0;

    printf("Seja bem vindo ao Gerenciador de diretorios [versao 1.0] \n(c) 2020 FIPP - Unoeste. Todos os direitos reservados.\n");
    printf("Alexandre Oliveira\\ Paulo Barreto\n");
    printf("\nVoce pode escolher ate 24 unidades de disco, quantas deseja gerenciar?\n");
    int qtUn = 0;


    while(scanf("%d", &qtUn)!=0 && (qtUn < 1 || qtUn >24))
        printf("So e permitido entre 1 e 24 unidades de disco!\n");


	initUnidades(&unidades, qtUn);
	setUnidade('C', unidades, &uniAtual, &dirAtual);//inicia-se em c:
    CLS();
    printf("Seja bem vindo ao Gerenciador de diretorios [versao 1.0] \n(c) 2020 FIPP - Unoeste. Todos os direitos reservados.\n");
    help();
    //sintaxe();
    printf("\nPressione enter para continuar>  ");
    getch();
    CLS();

    printf("Duvidas Sobre os comandos? Digite '/help'.");
    printf("\nPara visualizar a sintaxe digite '/sintaxe'.");
    caminhoAtual(dirAtual, uniAtual);
    fflush(stdin);
    gets(linhacomando);
    while(stricmp(linhacomando,"sair")!=0)
    {
        separaComando(linhacomando, comando);

        if(stricmp(comando, "md") == 0)
        {
            insereComando(&listaComandos, linhacomando);//lista de comandos validos digitados

            separaArgumento(linhacomando, argumento);
            makeDir(&dirAtual, argumento);
        }
        else if(stricmp(comando, "dir") == 0)
        {
            insereComando(&listaComandos, linhacomando);//lista de comandos validos digitados
            dir(dirAtual);
        }
        else if(stricmp(comando, "copy") == 0)
        {
            insereComando(&listaComandos, linhacomando);//lista de comandos validos digitados
            separaArgumento(linhacomando, argumento);
            separaSegundoArgumento(linhacomando, argumento2);


            Copy(argumento, argumento2, unidades, &uniAtual, &dirAtual);
        }
        else if(stricmp(comando, "copycon") == 0)
        {
            insereComando(&listaComandos, linhacomando);//lista de comandos validos digitados
            separaArgumento(linhacomando, argumento);
            copycon(&dirAtual->LArq, argumento);
        }
        else if(stricmp(comando, "cd") == 0)
        {
            insereComando(&listaComandos, linhacomando);//lista de comandos validos digitados
            separaArgumento(linhacomando, argumento);
            posicionaDiretorio(argumento, unidades, &uniAtual, &dirAtual);
        }
        else if(stricmp(comando, "del") == 0)
        {
            insereComando(&listaComandos, linhacomando);//lista de comandos validos digitados
            separaArgumento(linhacomando, argumento);
            del(&dirAtual, argumento);
        }
        else if(stricmp(comando, "type") == 0)
        {
            insereComando(&listaComandos, linhacomando);//lista de comandos validos digitados
            separaArgumento(linhacomando, argumento);
            type(dirAtual, argumento);
        }
        else if(stricmp(comando, "fc") == 0)
        {
            insereComando(&listaComandos, linhacomando);//lista de comandos validos digitados
            separaArgumento(linhacomando, argumento);
            separaSegundoArgumento(linhacomando, argumento2);
            FC(dirAtual->LArq, argumento, argumento2);
        }
        else if(stricmp(comando, "rd") == 0)
        {
            insereComando(&listaComandos, linhacomando);//lista de comandos validos digitados
            separaArgumento(linhacomando, argumento);
            RD(&dirAtual->head, argumento);

        }
        else if(stricmp(comando, "/help")==0)
        {
            insereComando(&listaComandos, linhacomando);//lista de comandos validos digitados
            help();
        }
         else if(stricmp(comando, "/sintaxe")==0)
        {
            insereComando(&listaComandos, linhacomando);//lista de comandos validos digitados
            sintaxe();
        }
        else if(stricmp(comando, "cls")==0)
        {
            insereComando(&listaComandos, linhacomando);//lista de comandos validos digitados
            CLS();
            printf("Duvidas Sobre os comandos? Digite '/help'.");
            printf("\nPara visualizar a sintaxe digite '/sintaxe'.");
        }
        else if(stricmp(comando, "doskey")==0)
        {
            insereComando(&listaComandos, linhacomando);//lista de comandos validos digitados
            doskey = !doskey;

        }
        else if(stricmp(comando, "find")==0)
        {
            insereComando(&listaComandos, linhacomando);//lista de comandos validos digitados
            separaArgumento(linhacomando, argumento);
            separaSegundoArgumento(linhacomando, argumento2);

            Find(argumento, argumento2, unidades, &uniAtual, &dirAtual);

        }
        if(doskey)
        {
            printf("\n     F12 habilitado!");
            c1 = getch();
            c2 = getch();
            if(c1 == -32 && c2 == -122) //tecla f12
            {
                exibeComandos(listaComandos);
            }
            doskey = !doskey;
        }

        caminhoAtual(dirAtual, uniAtual);
        fflush(stdin);
        gets(linhacomando);
    }

    return 0;
}
