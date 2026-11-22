#include <stdio.h>
#include <stdlib.h>

/* Codificacao dos tipos guardados em cada No:
    1 = int
    2 = float
    3 = char
    4 = Aluno
*/

typedef struct Aluno
{
    char nome[50];
    int idade;
} Aluno;

typedef struct No
{
    struct No *proximo;
    int tipo;
    void *dados;
} No;

int tamanho(int tipo)
{
    if (tipo == 1)
        return sizeof(int);
    if (tipo == 2)
        return sizeof(float);
    if (tipo == 3)
        return sizeof(char);
    if (tipo == 4)
        return sizeof(Aluno);
    return 0;
}

int nomesIguais(char a[], char b[])
{
    int i = 0;
    while (a[i] != '\0' || b[i] != '\0')
    {
        if (a[i] != b[i])
            return 0;
        i++;
    }
    return 1;
}

int iguais(int tipo, void *a, void *b)
{
    if (tipo == 1)
        return *(int *)a == *(int *)b;
    if (tipo == 2)
        return *(float *)a == *(float *)b;
    if (tipo == 3)
        return *(char *)a == *(char *)b;
    if (tipo == 4)
    {
        Aluno *x = (Aluno *)a;
        Aluno *y = (Aluno *)b;
        return nomesIguais(x->nome, y->nome) && x->idade == y->idade;
    }
    return 0;
}
void *ler_valor(int tipo)
{
    void *p = malloc(tamanho(tipo));

    if (tipo == 1)
    {
        printf("Digite um inteiro: ");
        scanf("%d", (int *)p);
    }
    else if (tipo == 2)
    {
        printf("Digite um float: ");
        scanf("%f", (float *)p);
    }
    else if (tipo == 3)
    {
        printf("Digite um caractere: ");
        scanf(" %c", (char *)p);
    }
    else if (tipo == 4)
    {
        Aluno *a = (Aluno *)p;
        printf("Nome do aluno: ");
        scanf("%49s", a->nome);
        printf("Idade: ");
        scanf("%d", &a->idade);
    }

    return p;
}

void mostraValor(int tipo, void *dados)
{
    if (tipo == 1)
        printf("%d (int)\n", *(int *)dados);
    else if (tipo == 2)
        printf("%.2f (float)\n", *(float *)dados);
    else if (tipo == 3)
        printf("%c (char)\n", *(char *)dados);
    else if (tipo == 4)
    {
        Aluno *a = (Aluno *)dados;
        printf("%s, %d anos (aluno)\n", a->nome, a->idade);
    }
}
No *inserir(No *lista, int tipo, void *dados)
{
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

No *remover(No *lista, int tipo, void *valor)
{
    No *anterior = NULL;
    No *aux = lista;

    while (aux != NULL)
    {
        if (aux->tipo == tipo && iguais(tipo, aux->dados, valor))
        {
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

int buscar(No *lista, int tipo, void *valor)
{
    int pos = 1;
    No *aux = lista;

    while (aux != NULL)
    {
        if (aux->tipo == tipo && iguais(tipo, aux->dados, valor))
            return pos;
        aux = aux->proximo;
        pos++;
    }
    return 0;
}

void imprimir(No *lista)
{
    int pos = 1;
    No *aux = lista;

    if (lista == NULL)
    {
        printf("Lista vazia\n");
        return;
    }

    while (aux != NULL)
    {
        printf("%d - ", pos);
        mostraValor(aux->tipo, aux->dados);
        aux = aux->proximo;
        pos++;
    }
}

int contar(No *lista)
{
    int qtd = 0;
    No *aux = lista;

    while (aux != NULL)
    {
        qtd++;
        aux = aux->proximo;
    }
    return qtd;
}

void salvar(No *lista) {
    FILE *arq = fopen("lista.bin", "wb");
    No *aux = lista;
    int qtd;

    if (!arq) {
        printf("Erro ao criar o arquivo.\n");
        return;
    }

    qtd = contar(lista);

    fwrite(&qtd, sizeof(int), 1, arq);

    while (aux != NULL) {
        fwrite(&aux->tipo, sizeof(int), 1, arq);
        fwrite(aux->dados, tamanho(aux->tipo), 1, arq);
        aux = aux->proximo;
    }

    fclose(arq);
    printf("Lista salva!\n");
}

No *carregar(No *lista) {
    FILE *arq = fopen("lista.bin", "rb");
    int qtd, tipo;
    void *dados;

    if (!arq) {
        printf("Arquivo nao encontrado.\n");
        return lista;
    }

    fread(&qtd, sizeof(int), 1, arq);

    for (int i = 0; i < qtd; i++) {
        fread(&tipo, sizeof(int), 1, arq);
        dados = malloc(tamanho(tipo));
        fread(dados, tamanho(tipo), 1, arq);
        lista = inserir(lista, tipo, dados);
    }

    fclose(arq);
    printf("Lista carregada!\n");
    return lista;
}

int lerTipo()
{
    int t;
    printf("Tipo (1-int, 2-float, 3-char, 4-aluno): ");
    scanf("%d", &t);

    while (t < 1 || t > 4)
    {
        printf("Tipo invalido! Digite de novo: ");
        scanf("%d", &t);
    }
    return t;
}

int main()
{
    No *lista = NULL;
    int op, tipo, pos;
    void *valor;

    do
    {
        printf("\n1-Inserir 2-Remover 3-Buscar 4-Imprimir 5-Salvar 6-Carregar 0-Sair\n");
        printf("Opcao: ");
        scanf("%d", &op);

        if (op == 1)
        {
            tipo = lerTipo();
            valor = ler_valor(tipo);
            lista = inserir(lista, tipo, valor);
        }
        else if (op == 2)
        {
            tipo = lerTipo();
            valor = ler_valor(tipo);
            lista = remover(lista, tipo, valor);
            free(valor);
        }
        else if (op == 3)
        {
            tipo = lerTipo();
            valor = ler_valor(tipo);
            pos = buscar(lista, tipo, valor);
            if (pos == 0)
                printf("Nao encontrado.\n");
            else
                printf("Encontrado na posicao %d\n", pos);
            free(valor);
        }
        else if (op == 4)
        {
            imprimir(lista);
        }
        else if (op == 5) {
            salvar(lista);
        }
        else if (op == 6) {
            lista = carregar(lista);
        }
        else if (op != 0)
        {
            printf("Opcao invalida!\n");
        }

    } while (op != 0);

    return 0;
}
