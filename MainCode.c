#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct NoDeArvore {

    float chave;
    long int linha;
    struct NoDeArvore * esquerda;
    struct NoDeArvore * direita;

} Arvore ;

void imprimirLinhas_OrdemCrescente(Arvore* no, long int vetorBytes[], FILE * arquivo){

    int caractere;

    if(no != NULL){
        imprimirLinhas_OrdemCrescente (no->esquerda,vetorBytes, arquivo);
        
        fseek(arquivo, vetorBytes[no->linha], SEEK_SET);

        while ((caractere = fgetc(arquivo)) != '\n'){
            printf ("%c", caractere);
        }
        printf("\n");

        if (no->direita != NULL){
            imprimirLinhas_OrdemCrescente (no->direita,vetorBytes, arquivo);
        }
        
    }

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

Arvore* registrarABP (Arvore * noPai, int linhaDeLeitura , float SomaLongitude_Latitude) {

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

    csvInfo = fopen ("Fire-incidents_semicolons.csv","r");
    if (csvInfo == NULL){
        printf("Erro ao abrir arquivo");
        exit(1);
    }

    int numLinhas = quantidadeDeLinhas (csvInfo);
    char bytes[800];
    long int nBytes = 0, posLinhaBytes[numLinhas];

    for (int i = 0; i < numLinhas; i++) {
        fscanf(csvInfo,"%[^\n]\n", bytes);
        nBytes = nBytes + strlen(bytes);  
        posLinhaBytes[i] = nBytes+1;
    }  

    char linhaDoArquivo[800];

    int localLinha = 1;
    float somaColunas = 0;

    while(fgets(linhaDoArquivo,sizeof(linhaDoArquivo)+1,csvInfo)){

        char * linhaSeparada;

        if (localLinha > 2){

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

            linhaSeparada[3]='.';
            somaColunas = atof(linhaSeparada);

            linhaSeparada = strtok(NULL,";");

            linhaSeparada[3]='.';
            somaColunas += atof(linhaSeparada);

            registrarABP(noPai,localLinha, somaColunas);

        }

        else {
            localLinha++;
        }
    }


// Printar - Excluir

    imprimirLinhas_OrdemCrescente (noPai, posLinhaBytes, csvInfo);

return 0;
}
