#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX 20000
typedef struct NoDeArvore {

    float chave;
    int linha;
    struct NoDeArvore * esquerda;
    struct NoDeArvore * direita;

} Arvore ;

void imprimirLinhas_OrdemCrescente(Arvore* no, long int vetorBytes[], FILE * arquivo){

    int caractere;
    char linhaFile [800];

    if(no != NULL){
        imprimirLinhas_OrdemCrescente (no->esquerda,vetorBytes, arquivo);

        //fseek(arquivo, vetorBytes[no->linha], SEEK_SET);

        //printf ("%s", fgets(linhaFile, sizeof(linhaFile), arquivo));
        //while ((caractere = fgetc(arquivo)) != '\n'){
        //    printf ("%c", caractere);
        //}
        //printf("\n");
        imprimirLinha(vetorBytes[no->linha], arquivo);

        if (no->direita != NULL){
            imprimirLinhas_OrdemCrescente (no->direita,vetorBytes, arquivo);
        }

    }

}

void imprimirLinha (int numBytes, FILE * arquivo){

    char linhaFile [800];

    fseek(arquivo, numBytes, SEEK_SET);

    printf ("%s", fgets(linhaFile, sizeof(linhaFile), arquivo));
    printf("\n");

}

int quantidadeDeLinhas (FILE * ptr_para_file){
int numLinhas = 0, letra;

while ((letra = fgetc(ptr_para_file)) != EOF ){
    if (letra == '\n'){
        numLinhas++;
    }
}

return numLinhas;
}

Arvore* registrarABP (Arvore * noPai, long int linhaDeLeitura , float SomaLongitude_Latitude) {

    if(noPai == NULL){
        noPai= (Arvore*)malloc(sizeof(Arvore));
        noPai->chave = SomaLongitude_Latitude;
        noPai->linha = linhaDeLeitura;
        noPai->esquerda = NULL;
        noPai->direita = NULL;
    }
    else if(SomaLongitude_Latitude <= noPai->chave){
        noPai->esquerda = registrarABP(noPai->esquerda,linhaDeLeitura,SomaLongitude_Latitude);
    }
    else{
        noPai->direita = registrarABP(noPai->direita,linhaDeLeitura,SomaLongitude_Latitude);
    }
    return noPai;
}

int main (void){

    FILE * csvInfo;

    Arvore * noPai = NULL;

    csvInfo = fopen ("Fire-Incidents_semicolon - Copy.csv","r");
    if (csvInfo == NULL){
        printf("Erro ao abrir arquivo");
        exit(1);
    }

    int numLinhas = quantidadeDeLinhas (csvInfo);
    int nBytes = 0;
    long int posLinhaBytes[MAX];
    posLinhaBytes[0]=0;

    char linhaDoArquivo[800];

    long int localLinha = 1;
    float somaColunas = 0;

    fseek(csvInfo,0,SEEK_SET);

    while(fgets(linhaDoArquivo,sizeof(linhaDoArquivo)+1,csvInfo)){
        
        nBytes = nBytes + strlen(linhaDoArquivo);
        posLinhaBytes[(localLinha)] = nBytes;

        char * linhaSeparada;

        if (localLinha > 1){

            somaColunas = 0;

            linhaSeparada = strtok(linhaDoArquivo,";");
            linhaSeparada = strtok(NULL,";");
            linhaSeparada = strtok(NULL,";");
            linhaSeparada = strtok(NULL,";");
            linhaSeparada = strtok(NULL,";");
            linhaSeparada = strtok(NULL,";");
            linhaSeparada = strtok(NULL,";");
            linhaSeparada = strtok(NULL,";");
            linhaSeparada = strtok(NULL,";");
            linhaSeparada = strtok(NULL,";");
            linhaSeparada = strtok(NULL,";");
            linhaSeparada = strtok(NULL,";");
            linhaSeparada = strtok(NULL,";");
            linhaSeparada = strtok(NULL,";");
            linhaSeparada = strtok(NULL,";");
            linhaSeparada = strtok(NULL,";");
            // Comando abaixo chega em Latitude
            linhaSeparada = strtok(NULL,";");

            linhaSeparada[2]='.';
            somaColunas = strtof(linhaSeparada,NULL);

            linhaSeparada = strtok(NULL,";");

            linhaSeparada[2]='.';
            somaColunas += strtof(linhaSeparada,NULL);

            noPai = registrarABP(noPai,localLinha, somaColunas);
            localLinha++;

        }

        else {
            localLinha++;
        }
    }


// Printar - Excluir

    imprimirLinhas_OrdemCrescente(noPai, posLinhaBytes, csvInfo);

    printf("fim?");

return 0;
}
