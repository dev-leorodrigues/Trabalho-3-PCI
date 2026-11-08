#include <stdio.h>  
#include <stdlib.h>

#define Int 1   
#define Float 2
#define Char 3
#define ALuno 4


typedef struct Aluno {
    char nome [50]; 
    int idade;
} Aluno;

typedef struct No {
    struct No *proximo;
    int tipo;
    void *dados;
} No;

int tamannho(int tipo) {
    if (tipo == Int)
        return sizeof(int);
    if (tipo == Float)
        return sizeof(float);
    if (tipo == Char)
        return sizeof(char);
    if (tipo == ALuno)
        return sizeof(Aluno);
    return 0;
}

int nomesiguais(char a[], char b[]) {
    int i = 0;
    while (a[i] != '\0' || b[i] != '\0') {
        if (a[i] != b[i])
            return 0;
        i++;
    }
    return 1;
}

int iguais(int tipo, void *a, void *b) {
    if (tipo == Int)
        return *(int *)a == *(int *)b;
    if (tipo == Float)
        return *(float *)a == *(float *)b;
    if (tipo == Char)
        return *(char *)a == *(char *)b;
    if (tipo == ALuno) {
        Aluno *x = (Aluno *)a;
        Aluno *y = (Aluno *)b;
        return nomesiguais(x->nome, y->nome) && x->idade == y->idade;
    }
    return 0;
}
    void *ler_valor(int tipo) {
    void *p = malloc(tamanho(tipo));

    if (tipo == Int) {
        printf("Digite um inteiro: ");
        scanf("%d", (int *)p);
    } else if (tipo == Float) {
        printf("Digite um float: ");
        scanf("%f", (float *)p);
    } else if (tipo == Char) {
        printf("Digite um caractere: ");
        scanf(" %c", (char *)p);
    } else if (tipo == ALuno) {
        Aluno *a = (Aluno *)p;
        printf("Nome do aluno: ");
        scanf("%s", a->nome);
        printf("Idade: ");
        scanf("%d", &a->idade);
    }

    return p;
}

void mostravalor(int tipo, void *dados) {
    if (tipo == Int)
        printf("%d (int)\n", *(int *)dados);
    else if (tipo == Float)
        printf("%.2f (float)\n", *(float *)dados);
    else if (tipo == Char)
        printf("%c (char)\n", *(char *)dados);
    else if (tipo == ALuno) {
        Aluno *a = (Aluno *)dados;
        printf("%s, %d anos (aluno)\n", a->nome, a->idade);
    }
}
    No *inserir(No *lista, int tipo, void *dados) {
    No *novo = (No *)malloc(sizeof(No));
    No *aux;

    novo->tipo = tipo;
    novo->dados = dados;
    novo->proximo = NULL;

    if (lista == NULL) 
        return novo;

    aux = lista;
    while (aux->proximo != NULL)
        aux = aux->proximo;
    aux->proximo = novo;

    return lista;
}
