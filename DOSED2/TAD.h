
struct pontlinha
{
	struct pontlinha *ant;
	struct pontlinha *prox;
	char letra;
}; typedef struct pontlinha PontLinha;

struct conteudoarquivo
{
    char letra;
    struct  conteudoarquivo *ant;
    struct  conteudoarquivo *prox;

};typedef struct conteudoarquivo ConteudoArquivo;

struct arquivo
{
	char nome[50];
    char data[11]; ///armazena apenas os numeros sem separador
    char hora [7]; ///armazena apenas os numeros sem separador
    struct arquivo *top;
    struct arquivo *bottom;
    struct ConteudoArquivo *linha;
    int letras;

};typedef struct arquivo Arquivo;

struct diretorio{
    /**
    *head aponta para baixo
    *tail para o lado
    *pai para cima, ou seja, todos os subdiretorios apontam para o mesmo pai
    */

    char nomeDir[50];
    char data[11]; ///armazena apenas os numeros sem separador
    char hora [7]; ///armazena apenas os numeros sem separador
    struct diretorio *head;
    struct diretorio *tail;
    struct diretorio *Ppai;
    struct Arquivo *LArq;


};typedef struct diretorio Diretorio;

struct unidade{
    char letraUnidade;
    Diretorio *iniDir;
    struct unidade *top;    ///acima
    struct unidade *bottom; ///abaixo

};typedef struct unidade Unidade;

struct comandos{
    char info[100];
    struct comandos *prox;
};typedef struct comandos Comandos;









/*****************Funcoes Unidades e Diretórios*****************/

void getDataHora(char data[], char horario[]){
	time_t now = time(NULL);
	struct tm *t = localtime(&now);
	char currentDate[13];
	char dia[3];
	char mes[3];
	char ano[5];
	char hora[3];
	char minuto[3];

	sprintf(dia, "%02d", t->tm_mday, sizeof(dia));
	sprintf(mes, "%02d", t->tm_mon+1, sizeof(mes));
	sprintf(ano, "%04d", t->tm_year + 1900, sizeof(ano));
	sprintf(hora, "%02d", t->tm_hour, sizeof(hora));
	sprintf(minuto, "%02d", t->tm_min, sizeof(minuto));

	strcpy(data, dia);
	strcat(data, "/");
	strcat(data, mes);
	strcat(data, "/");
	strcat(data, ano);

	strcpy(horario, hora);
	strcat(horario, ":");
	strcat(horario, minuto);
}

void insereConteudoArquivo(ConteudoArquivo **inicio, char c){
    ConteudoArquivo *NC = (ConteudoArquivo*)malloc(sizeof(ConteudoArquivo));
	NC->ant = NULL;
    NC->prox = NULL;
    NC->letra = c;

	if(*inicio == NULL)
        *inicio = NC;
    else
    {
        ConteudoArquivo *aux = *inicio;
        while (aux->prox != NULL)
            aux = aux->prox;

        aux->prox = NC;
        NC->ant = aux;
    }
}

void setConteudoArquivo(ConteudoArquivo **inicio, char conteudo[]){
	int i = 0;
	while(conteudo[i] != '\0')
    {
        insereConteudoArquivo(&(*inicio), conteudo[i]);
        i++;
    }
}

void setArquivo(Arquivo **inicio, char nome[], char conteudo[]){
	Arquivo *NCa = (Arquivo*)malloc(sizeof(Arquivo));
    NCa->letras = strlen(conteudo);
    NCa->top = NULL;
    NCa->bottom = NULL;
    NCa->linha = NULL;
    strcpy(NCa->nome, nome);
	getDataHora((NCa->data), (NCa->hora));
	if(conteudo != NULL)
	{
		 setConteudoArquivo(&(NCa->linha), conteudo);
	}

	if(*inicio == NULL)
	{
		*inicio = NCa;
	}
	else
	{
		NCa->bottom = *inicio;
		(*inicio)->top = NCa;
		*inicio = NCa;
	}
}

void setArquivo2(Arquivo **inicio, Arquivo *NCa){

	if(*inicio == NULL)
	{
		*inicio = NCa;
	}
	else
	{
		NCa->bottom = *inicio;
		(*inicio)->top = NCa;
		*inicio = NCa;
	}
}




void insereUnidade(Unidade **inicio, char letra){
    ///Sempre insere uma nova unidade ao final junto de uma cabeça de diretorio
    ///O diretorio raiz tem o nome de "raiz".
    Unidade *aux  = *inicio;
    Unidade *NC = (Unidade*)malloc(sizeof(Unidade));
    Diretorio *dir = (Diretorio*)malloc(sizeof(Diretorio));

    dir->head = NULL;
    dir->tail = NULL;
    dir->Ppai = NULL;
    dir->LArq = NULL;

    strcpy(dir->data,"");
    strcpy(dir->hora,"");
    strcpy(dir->nomeDir,"raiz");

    NC->iniDir = dir;
    NC->bottom = NULL;
    NC->top = NULL;
    NC->letraUnidade = letra;


    if(*inicio == NULL)
        *inicio = NC;
    else
    {
        while(aux->bottom != NULL)
            aux = aux->bottom;
        aux->bottom = NC;
        NC->top = aux;
    }
}

void initUnidades(Unidade **inicio, int count){
    char letras [24] = {'C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};

    int i;
    for (i = 0; i < count; i++)
        insereUnidade(&(*inicio), letras[i]);

}

void setUnidade(char letra, Unidade *unidades, Unidade **uniAtual, Diretorio **dirAtual){
    ///Faz a unidade atual apontar para a unidade digitada no console
    ///Assim como faz o diretorio atual apontar para a raiz da unidade
    ///Caso nao encontre, se mantem na mesma

    Unidade *aux = unidades;
    while(aux != NULL && aux->letraUnidade != toupper(letra))
        aux = aux->bottom;

    if(aux != NULL)
    {
        *uniAtual = aux;
        *dirAtual = aux->iniDir;
    }
}

void setDiretorio(Diretorio **dirAtual, char nome[]){
    /**
    *Posiciona o ponteiro em um diretorio informado existente
    dentro do diretorio atual.

    *Este método deve ser chamado para cada nivel de diretorio, o mesmo
    só observa se o diretorio existe naquele nivel, ao contrario de uma
    busca na qual percorre TODOS diretorios*/

    Diretorio *aux = (*dirAtual)->head;
    while(aux != NULL && stricmp(nome, aux->nomeDir) != 0)
        aux = aux->tail;

    if(aux != NULL)
        *dirAtual = aux;
}

void CD(Diretorio **dirAtual, char nome[]){

    setDiretorio(&(*dirAtual), nome);

}

void makeDir(Diretorio **dirAtual, char nome[]) {
    Diretorio *aux = *dirAtual;
    Diretorio *NC = (Diretorio*)malloc(sizeof(Diretorio));

    strcpy(NC->nomeDir,nome);
    getDataHora((NC->data), (NC->hora));
	NC->Ppai = *dirAtual;
    NC->head = NULL;
    NC->tail = NULL;
    NC->LArq = NULL;


    if(aux->head == NULL)
        aux->head = NC;
    else
    {
        aux = aux->head;
        while(aux->tail != NULL)
            aux = aux->tail;
        aux->tail = NC;
    }
}

void exibeConteudoArquivo(ConteudoArquivo *conteudo){
    ConteudoArquivo *aux = conteudo;
    while(aux != NULL)
    {
        printf("%c", aux->letra);
        aux = aux->prox;

    }

}

int exibeArquivos(Arquivo *inicio){
	int i = 0;
    while (inicio != NULL)
    {
        printf("%s\t%s\t%d\t%s\n", inicio->data, inicio->hora, inicio->letras, inicio->nome);
        //exibeConteudoArquivo(inicio->linha);
        //printf("\n");
        inicio = inicio->bottom;
        i++;
    }
	return i;
}

int exibeDiretorios(Diretorio *dirAtual){
    Diretorio *auxDir = dirAtual->head;
	int i = 0;

    while(auxDir!= NULL)
    {
        printf("%s\t%s\t<DIR>\t%s\n", auxDir->data, auxDir->hora, auxDir->nomeDir);
        auxDir = auxDir->tail;
        i++;
    }
    return i;
}

void dir (Diretorio *dirAtual){
	int qtDir;
	int qtArq;
	qtDir = exibeDiretorios(dirAtual);
	qtArq = exibeArquivos(dirAtual->LArq);

	printf("     %d arquivo(s)\n", qtArq);
	printf("     %d diretorio(s)\n", qtDir);
}

void CLS(){
	system("cls");
}

void type(Diretorio *dir, char nome[]){
    Arquivo *Inicio;

    if(dir->LArq != NULL)
    {
        Inicio = dir->LArq;

        //printf("%s",Inicio->nome)
        while(Inicio != NULL && stricmp(Inicio->nome, nome) != 0)
            Inicio = Inicio->bottom;

        if(Inicio != NULL)
            exibeConteudoArquivo(Inicio->linha);
        else
            printf("Arquivo nao encontrado!");
    }
    else
        printf("Arquivo nao encontrado!");

}

void killDiretorios(Diretorio **dir)
{
    Arquivo *auxArq, *antArq;
    //mandar a head de dir
    if(*dir != NULL)
    {
        if((*dir)->LArq != NULL)
        {
            auxArq = (*dir)->LArq;
            while(auxArq != NULL)
            {
                apagaConteudoArquivo(&auxArq->linha);
                antArq = auxArq;
                auxArq = auxArq->bottom;
                free(antArq);
            }
            (*dir)->LArq = NULL;
        }


        killDiretorios(&(*dir)->head);
        killDiretorios(&(*dir)->tail);

        free(*dir);
    }
}


void RD(Diretorio **dirAtual, char nome[]){
    ///Remove Diretorio e seus subdiretorios(remoçao a partir do dirAtual)
    ///tentar fazer iterativo com o uso de ant para religar os diretorios

    Diretorio *dirAux = *dirAtual;
    Diretorio *ant = NULL;

    while(dirAux!=NULL && stricmp(dirAux->nomeDir, nome)!=0)
    {
        ant = dirAux;
        dirAux = dirAux->tail;
    }


    if(dirAux!=NULL && ant == NULL)
    {
        *dirAtual = dirAux->tail;
        killDiretorios(&dirAux);
        free(dirAux);
    }
    else if(ant!=NULL && dirAux!= NULL)
    {
        ant->tail = dirAux->tail;
        killDiretorios(&dirAux);
        free(dirAux);
    }


}

void apagaConteudoArquivo(ConteudoArquivo **conteudo){
    ConteudoArquivo *aux = *conteudo;
    ConteudoArquivo *ant = NULL;

    while(aux != NULL)
    {
        ant = aux;
        aux = aux->prox;
        free(ant);
    }
    *conteudo = NULL;

}

void  del(Diretorio **dir, char nome[]){
	Diretorio *auxDir = (*dir)->head;
	Arquivo *auxArq, *antArq, *cabArquivo;

	while(auxDir!=NULL && stricmp(auxDir->nomeDir, nome)!=0)
        auxDir = auxDir->tail;

    if(auxDir != NULL)
    {
        //encontrou
        if(auxDir->LArq != NULL)
        {
            auxArq = auxDir->LArq;
            while(auxArq != NULL)
            {
                apagaConteudoArquivo(&auxArq->linha);
                antArq = auxArq;
                auxArq = auxArq->bottom;
                free(antArq);
            }
            auxDir->LArq = NULL;
        }

    }
    else
    {
        auxDir = *dir;
        auxArq  = auxDir->LArq;
        cabArquivo  = auxDir->LArq;

        while(auxArq!=NULL && stricmp(auxArq->nome, nome)!=0)
        {
            auxArq = auxArq->bottom;
        }


        if(auxArq != NULL)
        {
            if(auxArq->top==NULL && auxArq->bottom==NULL)//verifica se é a head da lista de arquivo (apenas 1 caixa)
            {
                auxDir->LArq=NULL;
            }
            else if(auxArq->top==NULL && auxArq->bottom!=NULL)//verifica se é a head da lista de arquivo
            {
                //cabArquivo->top = NULL;
                auxArq->bottom->top = NULL;
                (*dir)->LArq = auxArq->bottom;

            }
            else if(auxArq->bottom==NULL)// verifica se a caixa esta no final
            {
                auxArq->top->bottom = NULL;
            }
            else
            {
                auxArq->top->bottom = auxArq->bottom;
                auxArq->bottom->top = auxArq->top;

            }
            free(auxArq);
        }
        //else
        //{
         //   printf("Arquivo ou Diretorio nao encontrado!");
        //}
    }
}

void FC (Arquivo *arq, char nome1[], char nome2[]){
    /**Busca e compara a diferença entre dois arquivos,
    ex: FC arq1.txt arq2.txt, o que for diferente é mostrado,
    se nao houver diferenças retorna uma msg indicando que sao iguais*/

    ///busca arq1
    Arquivo *auxArq1 = arq;
    while(auxArq1 != NULL && stricmp(auxArq1->nome, nome1)!=0)
        auxArq1 = auxArq1->bottom;

    ///busca arq2
    Arquivo *auxArq2 = arq;
    while(auxArq2 != NULL && stricmp(auxArq2->nome, nome2)!=0)
        auxArq2 = auxArq2->bottom;

    if(auxArq1!=NULL && auxArq2!=NULL)
    {
        ConteudoArquivo *st1 = auxArq1->linha;
        ConteudoArquivo *st2 = auxArq2->linha;
        while(st1!=NULL && st2!=NULL && st1->letra == st2->letra)
        {
            st1 = st1->prox;
            st2 = st2->prox;
        }
        if(st1 == NULL && st2 == NULL)
            printf("Os arquivos possuem o mesmo conteudo.");
        else
        {
            printf("Os arquivos possuem conteudo diferente!:\n");
            exibeConteudoArquivo(auxArq1->linha);
            printf("\n");
            exibeConteudoArquivo(auxArq2->linha);
        }
    }
    else
    {
        if(auxArq1 == NULL)
            printf("\nArquivo %s nao encontrado!", nome1);
        if(auxArq2 == NULL)
            printf("\nArquivo %s nao encontrado!", nome2);
    }

}

void copycon(Arquivo **arq, char nome[]){
    ///Cria o arquivo e ja permite inserir conteudo, caso existir concatena com o atual.

	Arquivo *arqAux = *arq;
	char dado[100];

	while(arqAux != NULL && stricmp(arqAux->nome, nome) != 0)
        arqAux = arqAux->bottom;

    if(arqAux == NULL)
    {
        printf("\nArquivo %s nao existe e sera criado, insira o dado do arquivo!\n", nome);
        fflush(stdin);
        gets(dado);
        setArquivo(&(*arq), nome, dado);

    }
    else
    {
        printf("\n Arquivo %s existe, insira o dado a ser concatenado!\n", nome);
        fflush(stdin);
        gets(dado);
		setConteudoArquivo(&arqAux->linha, dado);
    }
}

void Copy(char nomeArq[], char caminho[], Unidade *unidades, Unidade **uniAtual, Diretorio **dirAtual)
{
    Unidade *uniAux = uniAtual;
    Diretorio *dirAux = dirAtual;


    Arquivo *arq = (*dirAtual)->LArq;
    while(arq!=NULL && stricmp(nomeArq, arq->nome)!=0)
        arq = arq->bottom;

    if(arq!=NULL)
    {
        posicionaDiretorio(caminho, unidades, &uniAux, &dirAux);
        //if(stricmp(dirAux->nomeDir,""));

        setArquivo2(&dirAux->LArq, arq);
        printf("\nArquivo copiado!", caminho);
    }
    else
        printf("  \nArquivo inexistente!");


}

void recuperaConteudoArquivo(ConteudoArquivo *conteudo, char s[]){
    ConteudoArquivo *aux = conteudo;

    int i = 0;

    while(aux != NULL)
    {
        s[i]=aux->letra;
        aux = aux->prox;
        i++;
    }
    s[i]='\0';
}

void Find(char conteudo[], char caminho[], Unidade *unidades, Unidade **uniAtual, Diretorio **dirAtual){

    Unidade *uniAux = uniAtual;
    Diretorio *dirAux = dirAtual;
    Arquivo *arqAux;
    char s[100];

    posicionaDiretorio(caminho, unidades, &uniAux, &dirAux);

    if(dirAux->LArq != NULL)
    {
        arqAux = dirAux->LArq;

        while(arqAux!=NULL)
        {

            recuperaConteudoArquivo(arqAux->linha, s);
            if(strstr(s, conteudo)!=NULL)
                printf("\n  %s", arqAux->nome);

            arqAux = arqAux->bottom;
        }
    }
}

void help(){
    printf("\n\nLISTA DE COMANDOS\n");
    printf("DIR\tExibe uma listagem de arquivos e subdiretorios presentes no diretorio atual.\n");
    printf("CLS\tLimpa a tela.\n");
    printf("CD\tAcessa o diretorio do caminho especificado, caso nao exista se mantem no mesmo.\n");
    printf("MD\tCria um diretorio dentro do diretorio atual.\n");
    printf("RD\tRemove um diretorio especificado pelo nome e todos os seus subdiretorios e arquivos.\n");
    printf("COPYCON\tCria um novo arquivo e permite ja adicionar o seu conteudo, caso exista concatena com o existente.\n");
    printf("DEL\tApaga um aquivo pelo nome, caso o nome informado seja um diretorio, apaga todos os arquivos do mesmo.\n");
    printf("TYPE\tExibe o arquivo especificado.\n");
    printf("FC\tCompara o conteudo de dois arquivos do mesmo diretorio, se diferentes exibe a diferenca.\n");
    printf("COPY\tCria uma copia de um arquivo no novo caminho especificado.\n");
    printf("FIND\tProcura trecho do conteudo de um arquivo no caminho especificado e devolve o nome do mesmo.\n");
    printf("DOSKEY\tHabilita a tecla F12\n");
    printf("F12\tExibe todos os comandos digitados(necessario usar o doskey antes de cada consulta)\n");
    printf("SAIR\tEncerra o programa.\n");
}

void sintaxe()
{
    printf("\n\nSINTAXE DOS COMANDOS COM PARAMETROS\n");

    printf("CD nomeDir ou CD unidade:\\diretorio\n");
    printf("MD nomedir\n");
    printf("RD nomeDir\n");
    printf("COPYCON nomeArq\n");
    printf("DEL nomeArq\n");
    printf("TYPE nomeArq\n");
    printf("FC nomeArq1 nomeArq2\n");
    printf("COPY nomeArq unidade:\\caminho....\n");
    printf("FIND palavraChave unidade:\\caminho...\n");
}


void exibeComandos(Comandos *L)
{
    int i = 1;
    while(L!=NULL)
    {
        printf("\n%d: %s", i,L->info);
        L = L->prox;
        i++;
    }
}

void insereComando(Comandos **L, char s[])
{
    Comandos *aux;
    Comandos *NC = (Comandos*)malloc(sizeof(Comandos));

    NC->prox = NULL;
    strcpy(NC->info, s);

    if(*L==NULL)
    {
        *L = NC;
    }
    else
    {
        aux = *L;
        while(aux->prox!=NULL)
            aux = aux->prox;

        aux->prox = NC;
    }
}

void percorrePai(Diretorio *dirAtual)
{
    if(dirAtual!=NULL && stricmp(dirAtual->nomeDir, "raiz")!=0)
    {
        percorrePai(dirAtual->Ppai);
        printf("\\%s", dirAtual->nomeDir);
    }
}
void caminhoAtual(Diretorio *dirAtual, Unidade *uni)
{
    printf("\n\n%c:", uni->letraUnidade);
    percorrePai(dirAtual);
    printf(">  ", uni->letraUnidade);
}

void separaComando(char linha[], char comando[])
{
    char aux[50];
    strcpy(aux, linha);

    if(stricmp(aux,"")!= 0 && stricmp(aux," ")!= 0)
    {
        char * pch;
        pch = strtok (aux," ");
        strcpy(comando, pch);
    }
}

void separaArgumento(char linha[], char argumento[])
{
    if(stricmp(linha,"")!= 0 && stricmp(linha," ")!= 0)
    {
        char aux[50];
        strcpy(aux, linha);

        char * pch;
        pch = strtok (aux," ");
        pch = strtok (NULL, " ");

        strcpy(argumento, pch);
    }
}

void separaSegundoArgumento(char linha[], char argumento[])
{
    if(stricmp(linha,"")!= 0 && stricmp(linha," ")!= 0)
    {
        char aux[50];
        strcpy(aux, linha);

        char * pch;
        pch = strtok (aux," ");
        pch = strtok (NULL, " ");
        pch = strtok (NULL, " ");

        strcpy(argumento, pch);
    }
}


void posicionaDiretorio(char caminho[], Unidade *unidades, Unidade **uniAtual, Diretorio **dirAtual)
{
    char str[50];
    strcpy(str, caminho);

    char * pch;
    pch = strtok (str,"\\");
    if(pch[1]==':')
    {
        setUnidade(pch[0], unidades, &(*uniAtual), &(*dirAtual));
        pch = strtok (NULL, "\\");
    }
    while (pch != NULL)
    {
        CD(&(*dirAtual),pch);
        pch = strtok (NULL, "\\");
    }
}

