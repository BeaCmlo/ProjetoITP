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
void inserirLinha(char *nome_tabela, int linha, int num_colunas, char *nome_colunas[], char separador) {
    char nome_arquivo[MAX_STRING_LENGTH];
    sprintf(nome_arquivo, "%s.txt", nome_tabela);

    FILE *arquivo = fopen(nome_arquivo, "a");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    for (int coluna = 0; coluna < num_colunas; coluna++) {
        char dado[MAX_STRING_LENGTH];
        printf("Digite o dado da coluna '%s': ", nome_colunas[coluna]);
        scanf("%s", dado);

        fprintf(arquivo, "%s", dado);
        if (coluna < num_colunas - 1) {
            fprintf(arquivo, "%c", separador);
        }
    }
    fprintf(arquivo, "\n");

    fclose(arquivo);
}

void listarTabelas() {
    // Listar todas as tabelas no diretório atual
    // (Você pode precisar de uma biblioteca ou API específica para listar arquivos)

    // Aqui, vou simular a existência de algumas tabelas
    wprintf(L"Tabelas disponíveis:\n");
    wprintf(L"1. tabela1\n");
    wprintf(L"2. tabela2\n");
    wprintf(L"3. tabela3\n");
}

void consultarTabela() {
    wchar_t nome_tabela[MAX_TABLE_NAME];
    int escolha;

    // Listar as tabelas disponíveis
    listarTabelas();

    // Solicitar ao usuário que escolha uma tabela
    wprintf(L"Escolha o número da tabela que deseja consultar: ");
    wscanf(L"%d", &escolha);

    // Mapear a escolha do usuário para o nome da tabela (simulado aqui)
    switch (escolha) {
        case 1:
            wcscpy(nome_tabela, L"tabela1");
            break;

        case 2:
            wcscpy(nome_tabela, L"tabela2");
            break;

        case 3:
            wcscpy(nome_tabela, L"tabela3");
            break;

        default:
            wprintf(L"Opção inválida.\n");
            return;
    }

    FILE *arquivo = _wfopen(nome_tabela, L"r, ccs=UTF-8");
    if (arquivo == NULL) {
        perror("Erro ao abrir o arquivo para leitura");
        return;
    }

    int num_colunas;
    fwscanf(arquivo, L"%d", &num_colunas);

    wprintf(L"Conteúdo da tabela '%ls':\n", nome_tabela);

    for (int i = 0; i < num_colunas; ++i) {
        wchar_t nome_coluna[MAX_STRING_LENGTH];
        fwscanf(arquivo, L"%ls", nome_coluna);
        wprintf(L"%-15ls", nome_coluna); // Adiciona espaçamento fixo para melhor alinhamento
    }
    wprintf(L"\n");

    wchar_t entrada[MAX_STRING_LENGTH];
    int coluna_atual = 0;

    while (fwscanf(arquivo, L"%ls", entrada) != EOF) {
        wprintf(L"%-15ls", entrada); // Adiciona espaçamento fixo para melhor alinhamento
        coluna_atual++;

        if (coluna_atual == num_colunas) {
            // Adiciona uma quebra de linha após cada linha da tabela
            wprintf(L"\n");
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
    fscanf(arquivo, "%d", &num_linhas);

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

    printf("Digite o nÃºmero inicial da linha cujos dados serão consultados: ");
    int linha_inicial;
    scanf("%d", &linha_inicial);

    printf("Digite o nÃºmero final da linha cujos dados serão consultados: ");
    int linha_final;
    scanf("%d", &linha_final);

    if (linha_inicial < 1 || linha_inicial > num_linhas || linha_final < 1 || linha_final > num_linhas) {
        printf("Erro: o nÃºmero da linha inserido Ã© invÃ¡lido.\n");
        fclose(arquivo);
        return;
    }

    // Percorre as linhas especificadas e imprime o dado na coluna especificada
    for (int linha = linha_inicial; linha <= linha_final; linha++) {
        int posicao_final = (linha - 1) * (num_colunas + 1) + coluna_atual;
        fseek(arquivo, posicao_final * MAX_STRING_LENGTH, SEEK_CUR);

        // Lê o dado na posição especificada
        char dado[MAX_STRING_LENGTH];
        fscanf(arquivo, "%s", dado);

        printf("O dado na linha %d e coluna '%s' Ã©: %s\n", linha, nome_coluna, dado);
    }

    fclose(arquivo);
}

void excluirTabela() {
    char nome_tabela[MAX_TABLE_NAME];
    printf("Digite o nome da tabela a ser excluÃ­da: ");
    scanf("%s", nome_tabela);

    if (access(nome_tabela, F_OK) == 0) {
        if (remove(nome_tabela) == 0) {
            printf("Tabela '%s' excluÃ­da com sucesso!\n", nome_tabela);
        } else {
            perror("Erro ao excluir a tabela");
        }
    } else {
        printf("Erro: Tabela '%s' nÃ£o encontrada.\n", nome_tabela);
    }
}
