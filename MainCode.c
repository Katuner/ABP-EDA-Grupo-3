#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct _arvore {
   int cord;
   int posLinha[nlinhas];
   struct _arvore *esq;
   struct _arvore *dir;
} Arvore;

Arvore* cria_arv_vazia ();

Arvore* Remover (Arvore *a, int v);

void destroi_arv (Arvore *arv);

Arvore* constroi_arv (int elem, Arvore *esq, Arvore *dir);

int min (Arvore *a);

int max (Arvore *a);

void imprime_decrescente (Arvore *a);

/***************** Arvore.c *********************/

/*Cria uma arvore vazia!*/
Arvore* cria_arv_vazia () {
   return NULL;
}

/*Destroi uma arvore!*/
void destroi_arv (Arvore *arv) {
   if (arv != NULL) {
      destroi_arv (arv->esq);
      destroi_arv (arv->dir);
      free(arv);
   }
}

/*Cria um no em uma arvore!*/
Arvore* inserir (Arvore *a, float v){
    if(a == NULL){
        a=(Arvore*)malloc(sizeof(Arvore));
        a->cord = v;
        a->esq = NULL;
        a->dir = NULL;
    }
    else if(v < a->cord){
        a->esq = inserir(a->esq,v);
    }
    else{
        a->dir = inserir(a->dir,v);
    }
    return a;
}



void pre_ordem (Arvore *arv) {
    if (arv != NULL){
       printf ("%d, ", arv->cord);
       pre_ordem (arv->esq);
       pre_ordem (arv->dir);

    }
}

void in_ordem (Arvore *arv) {
   if (arv != NULL) {
      in_ordem (arv->esq);
      printf ("%d, ", arv->cord);
      in_ordem (arv->dir);
   }
}

void pos_ordem (Arvore *arv){
    if (arv != NULL){
        pos_ordem (arv->esq);
        pos_ordem (arv->dir);
        printf("%d, ", arv->cord);
    }
}

int buscar (Arvore *a, int v){
    if(a==NULL){
        return 0;
    }
    else if(v < a->cord){
        return buscar(a->esq,v);
    }
    else if(v > a->cord){
        return buscar(a->dir,v);
    }
    else{
        return 1;
    }
}

int min (Arvore *a){
    if( a->esq != NULL){
        return min(a->esq);
    }
    else{
         return a->cord;
    }
}

int max (Arvore *a){
    if (a->dir != NULL){
        return max(a->dir);
    }
    else{
        return a->cord;
    }
}

Arvore* Remover (Arvore *a, float v){
    if(a == NULL){
        return NULL;
    }
    else{
        if(a->cord >v){
            a->esq = Remover (a->esq,v);
        }
        else if (a->cord <v){
            a->dir = Remover (a->dir,v);
        }
        else{
            if((a->esq == NULL) && (a->dir == NULL)){
                free(a);
                a=NULL;
            }
            else if(a->dir == NULL){
                Arvore *tmp = a;
                a = a -> esq;
                free (tmp);
            }
            else if(a->esq == NULL){
                Arvore *tmp = a;
                a = a -> dir;
                free (tmp);
            }
            else{
                Arvore *tmp = a->esq;
                while(tmp->dir != NULL){
                    tmp=tmp->dir;
                }
                a->cord = tmp->cord;
                tmp->cord = v;
                a->esq = Remover(a->esq,v);
            }
        }
    }
    return a;
}


void imprime_decrescente (Arvore *arv){
    if (arv != NULL){
        printf("%d, ", max(arv));
        imprime_decrescente(Remover(arv, max(arv)));

    }
}


int contarNos(Arvore *a){
   if(a == NULL)
        return 0;
   else
        return 1 + contarNos(a->esq) + contarNos(a->dir);
}

int leLinha (void) {
int c;
int nlinhas = 1; 
FILE *fp;
fp = fopen("fire_incidents.csv","rt");
if (fp==NULL) {
printf("Não foi possivel abrir arquivo.\n");
return 1;
}
while ((c = fgetc(fp)) != EOF) {
if (c == '\n')
nlinhas++;
}
fclose(fp);
printf("Numero de linhas = %d\n", nlinhas);
return nlinhas;
}

int qntBytes(){

int c, nbytes = 0;
FILE *fp;
fp = fopen("fire_incidents.csv","rt");
if (fp==NULL) {
printf("Não foi possivel abrir arquivo.\n");
return 1;
}
  
while ((c = fgetc(fp)) != EOF) {
nbytes++;
}
printf("%d\n", nbytes);

return nbytes;
}

/****************** Prog.c **********************/

int main () {

Arvore *a = cria_arv_vazia ();  

int nlinha = leLinha();
int tam = qntBytes();
  
int nBytes = 0;  
char bytes[tam];
int posLinha[nlinha];
  
FILE *fp;
fp = fopen("fire_incidents.csv","rt");
if (fp==NULL) {
printf("Não foi possivel abrir arquivo.\n");
return 1;
} 

for(int i = 0; i < nlinha; i++){
fscanf(fp, "%[^\n]\n", bytes);
printf("%d\n", strlen(bytes));
//printf("%s\n", bytes);
nBytes = nBytes + strlen(bytes);
printf("%d\n", nBytes);  
posLinha[i] = nBytes;  
}  

return 0;
}
