#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "vector.h"

#define MAXV 10
#define MAXLINE 100

char line[MAXLINE];

// int v[MAXV]; vetor armazenado numa variável global

int main(int argc, char const *argv[]) {
    
    // int v[MAXV]; vetor armazenado numa variável automática
    int *v = calloc(MAXV, sizeof(int)); // vetor em memória alocada dinamicamente

    fill(v,MAXV,5);

    printf("[");
    for(int i = 0; i < MAXV - 1; i++)
        printf("%d,",v[i]);
    printf("%d]\n",v[MAXV - 1]);

    puts("Qual o valor a encontrar?");
    
    if(fgets(line,MAXLINE,stdin) == NULL) {
	    puts("ERROR READING INPUT!");
	    return 1;
    }

    line[strcspn(line,"\r\n")] = 0;

    int toFind = atoi(line);

    puts("\nPesquisa no vetor.");

    int found = find(v,MAXV,toFind);
    if(found == -1) printf("Valor %d não se encontra no vetor.\n",toFind);
    else printf("Valor %d encontrado na posição %d.\n",toFind,found);

    // Pesquisa apenas num segmento do vector:

    int start = 5;
    int end = 8;

    printf("\nPesquisa num segmento do vetor - posições %d a %d.\n",start,end);

    found = find(v + start,MAXV - end,toFind);
    if(found == -1) printf("Valor %d não se encontra no segmento do vetor.\n",toFind);
    else printf("Valor %d encontrado na posição %d + %d.\n",toFind,start,found);
    
    return 0;
}
