# DOSGen
Simula um DOS capaz de gerenciar várias unidades de disco(de C:\ até Z:\), assim como comandos básicos para criar, visualizar, copiar e apagar diretórios e arquivos. 

O projeto conta com uma estrutura de dados baseada em listas encadeadas e listas generelizadas pra representar os sitema de diretórios.

![img](https://github.com/AlekOliveira/DOSGen/blob/master/5.png)

### Comandos Implementados
**DIR**     Exibe uma listagem de arquivos e subdiretorios presentes no diretorio atual.

**CLS**     Limpa a tela.

**CD**     Acessa o diretorio do caminho especificado, caso nao exista se mantem no mesmo.

**MD**      Cria um diretorio dentro do diretorio atual.

**RD**      Remove um diretorio especificado pelo nome e todos os seus subdiretorios e arquivos.

**COPYCON** Cria um novo arquivo e permite ja adicionar o seu conteudo, caso exista concatena com o existente.

**DEL**     Apaga um aquivo pelo nome, caso o nome informado seja um diretorio, apaga todos os arquivos do mesmo.

**TYPE**    Exibe o arquivo especificado.

**FC**      Compara o conteudo de dois arquivos do mesmo diretorio, se diferentes exibe a diferenca.

**COPY**    Cria uma copia de um arquivo no novo caminho especificado.

**FIND**    Procura trecho do conteudo de um arquivo no caminho especificado e devolve o nome do mesmo.

**DOSKEY**  Habilita a tecla F12.

**F12**     Exibe todos os comandos digitados(necessario usar o doskey antes de cada consulta).

**SAIR**    Encerra o programa.

### Sintaxe dos Comandos com Parâmetros

CD nomeDir ou CD unidade:\diretorio
MD nomedir

RD nomeDir

COPYCON nomeArq

DEL nomeArq

TYPE nomeArq

FC nomeArq1 nomeArq2

COPY nomeArq unidade:\caminho...

FIND palavraChave unidade:\caminho...

