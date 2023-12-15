#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

#define MAX_TABLE_NAME 50
#define MAX_COLUMNS 10
#define MAX_STRING_LENGTH 256

// ProtÃ³tipos das funÃ§Ãµes
void criarInserirTabela();
void consultarTabela();
void excluirTabela();
void consultarDados();
void inserirLinha();

int main() {
    int opcao;
    setlocale(LC_ALL, "Portuguese");
    do {
        printf("\nEscolha uma opÃ§Ã£o:\n");
        printf("1. Criar e Inserir Tabela\n");
        printf("2. Inserir Dados em Tabela Existente\n");
        printf("3. Consultar Tabela\n");
        printf("4. Consultar Dados\n");
        printf("5. Excluir Tabela\n");
        printf("6. Sair\n");

        printf("OpÃ§Ã£o: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                criarInserirTabela();
                break;
            case 2:
                inserirLinha();
                break;
            case 3:
                consultarTabela();
                break;
            case 4:
                consultarDados();
                break;
            case 5:
                excluirTabela();
                break;

            case 6:
                printf("Saindo do programa.\n");
                break;

            default:
                printf("OpÃ§Ã£o invÃ¡lida. Tente novamente.\n");
        }
    } while (opcao != 4);

    return 0;
}

void criarInserirTabela() {
    char nome_tabela[MAX_TABLE_NAME];
    printf("Digite o nome da tabela: ");
    scanf("%s", nome_tabela);

    FILE *arquivo = fopen(nome_tabela, "w");
    if (arquivo == NULL) {
        perror("Erro ao criar a tabela");
        return;
    }

    int num_colunas;
    printf("Digite o nÃºmero de colunas (atÃ© %d): ", MAX_COLUMNS);
    scanf("%d", &num_colunas);

    fprintf(arquivo, "%d\n", num_colunas);

    for (int i = 0; i < num_colunas; ++i) {
        char nome_coluna[MAX_STRING_LENGTH];
        printf("Digite o nome da coluna %d: ", i + 1);
        scanf("%s", nome_coluna);
        fprintf(arquivo, "%s\t", nome_coluna);
    }
    fprintf(arquivo, "\n");

    printf("Digite o nÃºmero de linhas: ");
    int num_linhas;
    scanf("%d", &num_linhas);

    for (int i = 0; i < num_linhas; ++i) {
        for (int j = 0; j < num_colunas; ++j) {
            char dado[MAX_STRING_LENGTH];
            printf("Digite o dado para a coluna %d da linha %d: ", j + 1, i + 1);
            scanf("%s", dado);
            fprintf(arquivo, "%s\t", dado);
        }
        fprintf(arquivo, "\n");
    }

    fclose(arquivo);
    printf("Tabela '%s' criada e dados inseridos com sucesso!\n", nome_tabela);
}
void inserirLinha() {
    char nome_tabela[MAX_TABLE_NAME];
    printf("Digite o nome da tabela: ");
    scanf("%s", nome_tabela);

    FILE *arquivo = fopen(nome_tabela, "r+");
    if (arquivo == NULL) {
        perror("Erro ao abrir o arquivo para leitura e escrita");
        return;
    }

    int num_colunas, num_linhas;
    fscanf(arquivo, "%d", &num_colunas);

    printf("Digite o nÃºmero da linha a ser inserida: ");
    int linha;
    scanf("%d", &linha);

    if (linha > num_linhas) {
        printf("Linha '%d' invÃ¡lida!\n", linha);
        fclose(arquivo);
        return;
    }

    // Avança o cursor para a posição desejada (linha)
    fseek(arquivo, (linha - 1) * (num_colunas + 1) * MAX_STRING_LENGTH, SEEK_CUR);

    // Lê a linha existente
    char linha_existente[MAX_STRING_LENGTH * (num_colunas + 1)];
    fgets(linha_existente, MAX_STRING_LENGTH * (num_colunas + 1), arquivo);

    // Lê a nova linha do usuário
    char nova_linha[MAX_STRING_LENGTH * (num_colunas + 1)];
    printf("Digite a nova linha: ");
    scanf("%s", nova_linha);

    // Escreve a nova linha no arquivo
    fseek(arquivo, -(num_colunas + 1) * MAX_STRING_LENGTH, SEEK_CUR);
    fputs(nova_linha, arquivo);

    printf("Linha '%d' inserida com sucesso!\n", linha);

    fclose(arquivo);
}

void consultarTabela() {
    char nome_tabela[MAX_TABLE_NAME];
    printf("Digite o nome da tabela: ");
    scanf("%s", nome_tabela);

    FILE *arquivo = fopen(nome_tabela, "r");
    if (arquivo == NULL) {
        perror("Erro ao abrir o arquivo para leitura");
        return;
    }

    int num_colunas;
    fscanf(arquivo, "%d", &num_colunas);

    printf("ConteÃºdo da tabela '%s':\n", nome_tabela);

    for (int i = 0; i < num_colunas; ++i) {
        char nome_coluna[MAX_STRING_LENGTH];
        fscanf(arquivo, "%s", nome_coluna);
        printf("%-15s", nome_coluna); // Adiciona espaÃ§amento fixo para melhor alinhamento
    }
    printf("\n");

    char entrada[MAX_STRING_LENGTH];
    int coluna_atual = 0;

    while (fscanf(arquivo, "%s", entrada) != EOF) {
        printf("%-15s", entrada); // Adiciona espaÃ§amento fixo para melhor alinhamento
        coluna_atual++;

        if (coluna_atual == num_colunas) {
            // Adiciona uma quebra de linha apÃ³s cada linha da tabela
            printf("\n");
            coluna_atual = 0; // Reinicia o contador de colunas
        }
    }

    fclose(arquivo);
}
void consultarDados() {
    char nome_tabela[MAX_TABLE_NAME];
    printf("Digite o nome da tabela: ");
    scanf("%s", nome_tabela);

    FILE *arquivo = fopen(nome_tabela, "r");
    if (arquivo == NULL) {
        perror("Erro ao abrir o arquivo para leitura");
        return;
    }

    int num_colunas, num_linhas;
    fscanf(arquivo, "%d", &num_colunas);

    char nome_coluna[MAX_STRING_LENGTH];
    printf("Digite o nome da coluna cujos dados serão consultados: ");
    scanf("%s", nome_coluna);

    char coluna[MAX_STRING_LENGTH];
    int coluna_atual = 0;

    // Percorre as colunas e encontra a posição da coluna especificada
    while (fscanf(arquivo, "%s", coluna) != EOF) {
        if (strcmp(coluna, nome_coluna) == 0) {
            break;
        }
        coluna_atual++;
    }

    if (coluna_atual == num_colunas) {
        printf("Coluna '%s' nÃ£o encontrada!\n", nome_coluna);
        fclose(arquivo);
        return;
    }

    printf("Digite o nÃºmero da linha cujos dados serão consultados: ");
    int linha;
    scanf("%d", &linha);

    // Avança o cursor para a posição desejada (coluna e linha)
    int posicao_final = (linha - 1) * (num_colunas + 1) + coluna_atual;
    fseek(arquivo, posicao_final * MAX_STRING_LENGTH, SEEK_CUR);

    // Lê o dado na posição especificada
    char dado[MAX_STRING_LENGTH];
    fscanf(arquivo, "%s", dado);

    printf("O dado na linha %d e coluna '%s' Ã©: %s\n", linha, nome_coluna, dado);

    fclose(arquivo);
}

void excluirTabela() {
    char nome_tabela[MAX_TABLE_NAME];
    printf("Digite o nome da tabela a ser excluÃ­da: ");
    scanf("%s", nome_tabela);

    if (remove(nome_tabela) == 0) {
        printf("Tabela '%s' excluÃ­da com sucesso!\n", nome_tabela);
    } else {
        perror("Erro ao excluir a tabela");
    }
}
