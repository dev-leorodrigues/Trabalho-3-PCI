#include <stdio.h>  
#include <stdlib.h>

#define INT 1   
#define FLOAT 2
#define CHAR 3
#define ALUNO 4


typedef struct Aluno {
    char nome [50]; 
    int idade;
} Aluno;

typedef struct No {
    struct No *proximo;
    int tipo;
    void *dados;
} No;

int tamanho(int tipo) {
    if (tipo == INT)
        return sizeof(int);
    if (tipo == FLOAT)
        return sizeof(float);
    if (tipo == CHAR)
        return sizeof(char);
    if (tipo == ALUNO)
        return sizeof(Aluno);
    return 0;
}

int nomesIguais(char a[], char b[]) {
    int i = 0;
    while (a[i] != '\0' || b[i] != '\0') {
        if (a[i] != b[i])
            return 0;
        i++;
    }
    return 1;
}

int iguais(int tipo, void *a, void *b) {
    if (tipo == INT)
        return *(int *)a == *(int *)b;
    if (tipo == FLOAT)
        return *(float *)a == *(float *)b;
    if (tipo == CHAR)
        return *(char *)a == *(char *)b;
    if (tipo == ALUNO) {
        Aluno *x = (Aluno *)a;
        Aluno *y = (Aluno *)b;
        return nomesIguais(x->nome, y->nome) && x->idade == y->idade;
    }
    return 0;
}
    void *ler_valor(int tipo) {
    void *p = malloc(tamanho(tipo));

    if (tipo == INT) {
        printf("Digite um inteiro: ");
        scanf("%d", (int *)p);
    } else if (tipo == FLOAT) {
        printf("Digite um float: ");
        scanf("%f", (float *)p);
    } else if (tipo == CHAR) {
        printf("Digite um caractere: ");
        scanf(" %c", (char *)p);
    } else if (tipo == ALUNO) {
        Aluno *a = (Aluno *)p;
        printf("Nome do aluno: ");
        scanf("%49s", a->nome);
        printf("Idade: ");
        scanf("%d", &a->idade);
    }

    return p;
}

void mostraValor(int tipo, void *dados) {
    if (tipo == INT)
        printf("%d (int)\n", *(int *)dados);
    else if (tipo == FLOAT)
        printf("%.2f (float)\n", *(float *)dados);
    else if (tipo == CHAR)
        printf("%c (char)\n", *(char *)dados);
    else if (tipo == ALUNO) {
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

No *remover(No *lista, int tipo, void *valor) {
    No *anterior = NULL;
    No *aux = lista;

    while (aux != NULL) {
        if (aux->tipo == tipo && iguais(tipo, aux->dados, valor)) {
            if (anterior == NULL) 
                lista = aux->proximo;
            else
                anterior->proximo = aux->proximo;

            free(aux->dados);
            free(aux);
            printf("Removido!\n");
            return lista;
        }
        anterior = aux;
        aux = aux->proximo;
    }

    printf("Nao achei esse elemento.\n");
    return lista;
}

int buscar(No *lista, int tipo, void *valor) {
    int pos = 1;
    No *aux = lista;

    while (aux != NULL) {
        if (aux->tipo == tipo && iguais(tipo, aux->dados, valor))
            return pos;
        aux = aux->proximo;
        pos++;
    }
    return 0;
}

void imprimir(No *lista) {
    int pos = 1;
    No *aux = lista;

    if (lista == NULL) {
        printf("Lista vazia\n");
        return;
    }

    while (aux != NULL) {
        printf("%d - ", pos);
        mostraValor(aux->tipo, aux->dados);
        aux = aux->proximo;
        pos++;
    }
}
