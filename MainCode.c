#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void imprimirLinha(FILE * ptr_para_file , long int linha_a_ser_impressa_em_bytes){

    //fseek

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

typedef struct NoDeArvore {

    float chave;
    long int linha;
    struct NoDeArvore * esquerda;
    struct NoDeArvore * direita;

} Arvore ;

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



return 0;
}
