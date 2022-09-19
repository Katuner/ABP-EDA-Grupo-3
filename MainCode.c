#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void imprimirLinha(FILE * ptr_para_file , long int linha_a_ser_impressa_em_bytes){

    //fseek

}

int quantidadeDeLinhas (FILE * ptr_para_file){
int numLinhas = 0;


return numLinhas;
}

typedef struct NoDeArvore {

    float chave;
    int linha;
    struct NoDeArvore * esquerda;
    struct NoDeArvore * Direita;

};

void registrarABP (struct NoDeArvore * NoPai , int linhaDeLeitura , float SomaLongitude_Latitude) {



}

int main (void){

    FILE * csvInfo;

    csvInfo = fopen ("Fire-incidents_semicolons.csv","r");
    if (csvInfo == NULL){
        printf("Erro ao abrir arquivo");
        exit(1);
    }

    int numLinhas = quantidadeDeLinhas (csvInfo);

    float chaves [numLinhas];


return 0;
}
