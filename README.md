# Lista Encadeada Heterogênea

**Dupla:** Leonardo Rodrigues e Roberth Guimarro

## O que o programa faz

Lista encadeada simples em que cada nó guarda um dado de tipo diferente (`void *`) junto com um código do tipo. Pelo menu é possível:

1. Inserir um elemento no fim da lista
2. Remover a primeira ocorrência de um elemento
3. Buscar um elemento e mostrar a posição dele
4. Imprimir a lista
5. Salvar a lista no arquivo binário `lista.bin`
6. Carregar a lista de `lista.bin` (os elementos são adicionados ao fim da lista atual)
0. Sair

## Codificação dos tipos

| Código | Tipo  |
|--------|-------|
| 1      | int   |
| 2      | float |
| 3      | char  |
| 4      | Aluno (nome com até 49 caracteres, sem espaços, e idade) |

## Como compilar e rodar

```bash
gcc trabs.c -o trabs
./trabs
```

No Windows (PowerShell): `gcc trabs.c -o trabs.exe` e depois `.\trabs.exe`.
