#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>

#define NOME_ARQUIVO "mercado.txt"
#define PRODUTOS_ARQUIVO "produtos.txt"
#define TAMANHO_BUFFER 100

typedef struct
{
    int id;
    char nome[30];
    float preco;
    int qtd_estoque;
    int tipo;

} Produto;

typedef struct
{
    int numero_caixa;
    float valor_abertura;

} info_caixa;

typedef struct
{
    int idProduto;
    int quantidade;
    float totalVenda;

} Venda;

Produto* cadastrarProduto(Produto *estoque, int *total, int *qtd_estoque, int *proximoId)
{
    Produto *novo = (Produto*) realloc(estoque, (*total + 1) * sizeof(Produto));
    if (novo == NULL)
    {
        fprintf(stderr, "Erro: sem memoria\n");
        system("pause");
        return estoque;
    }
    estoque = novo;

    do
    {
        printf("Tipo (1 - Mercado / 2 - Padaria): ");
        scanf("%d", &(estoque + *total)->tipo);
        if ((estoque + *total)->tipo != 1 && (estoque + *total)->tipo != 2)
            printf("\nTipo invalido.\n");
    }
    while ((estoque + *total)->tipo != 1 && (estoque + *total)->tipo != 2);

    printf("Nome do produto: ");
    getchar();
    fgets((estoque + *total)->nome, 30, stdin);
    (estoque + *total)->nome[strcspn((estoque + *total)->nome, "\n")] = '\0';

    printf("Quantidade em estoque: ");
    scanf("%d", &(estoque + *total)->qtd_estoque);

    printf("Preco: ");
    scanf("%f", &(estoque + *total)->preco);

    (estoque + *total)->id = *proximoId;

    printf("Produto cadastrado!\n");

    (*total)++;
    (*proximoId)++;

    system("pause");
    return estoque;
}

void editarProduto(Produto *estoque, int total)
{
    if (total == 0)
    {
        printf("\nNenhum produto cadastrado!\n");
        system("pause");
        return;
    }

    int id, encontrado = 0;
    printf("\nID do produto a editar: ");
    scanf("%d", &id);

    for (int i = 0; i < total; i++)
    {
        if (estoque[i].id == id)
        {
            encontrado = 1;
            int opcao;
            do
            {
                system("cls");
                printf("=== EDITAR PRODUTO ===\n");
                printf("----------------------------------------------\n");
                printf("Produto atual: %s\n", estoque[i].nome);
                if (estoque[i].tipo == 1)
                    printf("Tipo        : Mercado\n");
                else
                    printf("Tipo        : Padaria\n");
                printf("Preco       : R$%.2f\n", estoque[i].preco);
                printf("Estoque     : %d\n", estoque[i].qtd_estoque);
                printf("----------------------------------------------\n\n");
                printf("O que deseja editar?\n");
                printf("1 - Nome\n");
                printf("2 - Tipo\n");
                printf("3 - Preco\n");
                printf("4 - Quantidade em estoque\n");
                printf("5 - Voltar\n");
                scanf("%d", &opcao);

                switch (opcao)
                {
                case 1:
                    printf("Novo nome: ");
                    getchar();
                    fgets(estoque[i].nome, 30, stdin);
                    estoque[i].nome[strcspn(estoque[i].nome, "\n")] = '\0';
                    printf("Nome atualizado!\n");
                    system("pause");
                    break;

                case 2:
                    do
                    {
                        printf("Novo tipo (1 - Mercado / 2 - Padaria): ");
                        scanf("%d", &estoque[i].tipo);
                        if (estoque[i].tipo != 1 && estoque[i].tipo != 2)
                            printf("Tipo invalido.\n");
                    }
                    while (estoque[i].tipo != 1 && estoque[i].tipo != 2);
                    printf("Tipo atualizado!\n");
                    system("pause");
                    break;

                case 3:
                    printf("Novo preco: ");
                    scanf("%f", &estoque[i].preco);
                    printf("Preco atualizado!\n");
                    system("pause");
                    break;

                case 4:
                    printf("Nova quantidade em estoque: ");
                    scanf("%d", &estoque[i].qtd_estoque);
                    printf("Estoque atualizado!\n");
                    system("pause");
                    break;

                case 5:
                    break;

                default:
                    printf("Opcao invalida!\n");
                    system("pause");
                }

            }
            while (opcao != 5);
        }
    }

    if (encontrado == 0)
    {
        printf("\nProduto nao encontrado!\n");
        system("pause");
    }
}

void AbrirCaixa(int *caixa, float *valor_abertura, int valida_leitura, int *numero_caixa)
{
    if (*caixa >= 1)
    {
        printf("Ja esta aberto! \n");
        system("pause");
    }
    else
    {
        do
        {
            printf("Selecione o valor para abrir o caixa: ");
            valida_leitura = scanf("%f", valor_abertura);

            if (valida_leitura == 0)
            {
                printf("Erro: Voce digitou uma letra ou caractere invalido!\n");
                while (getchar() != '\n');
                system("pause");
            }

        }
        while (valida_leitura == 0);

        printf("\nO caixa foi aberto com o valor de: %.2f\n", *valor_abertura);

        *caixa = 1;

        system("pause");
    }
}

void venda(Produto *estoque, int total, float *total_caixa, int *qtd_estoque, Venda **historico, int *totalVendas)
{
    int id_produto, quantidade, encontrado = 0;

    printf("\nQual o Id do produto: ");
    scanf("%d", &id_produto);

    for (int i = 0; i < total; i++)
    {
        if (estoque[i].qtd_estoque == 0 && estoque[i].id == id_produto)
        {
            encontrado = 1;
            printf("\nProduto em falta\n");
            system("pause");
        }
        else if (estoque[i].id == id_produto)
        {
            encontrado = 1;
            printf("----------------------------------------------\n");
            printf("Produto : %s\n", estoque[i].nome);
            if (estoque[i].tipo == 1)
                printf("Origem  : Mercado\n");
            else
                printf("Origem  : Padaria\n");
            printf("Preco   : R$%.2f\n", estoque[i].preco);
            printf("----------------------------------------------\n");
            printf("Quantidade: ");
            scanf("%d", &quantidade);

            if (quantidade > estoque[i].qtd_estoque)
            {
                do
                {
                    printf("\nQuantidade indisponivel\n");
                    printf("Quantidade: ");
                    scanf("%d", &quantidade);
                }
                while (quantidade > estoque[i].qtd_estoque);
            }

            float total_compra = quantidade * estoque[i].preco;
            *total_caixa += total_compra;
            estoque[i].qtd_estoque -= quantidade;
            printf("----------------------------------------------\n");
            printf("Total da compra: R$%.2f\n", total_compra);
            printf("----------------------------------------------\n");

            (*totalVendas)++;
            Venda *novo_hist = realloc(*historico, *totalVendas * sizeof(Venda));
            if (novo_hist != NULL)
            {
                (*historico) = novo_hist;
                (*historico)[*totalVendas - 1].idProduto = id_produto;
                (*historico)[*totalVendas - 1].quantidade = quantidade;
                (*historico)[*totalVendas - 1].totalVenda = total_compra;
            }
            else
            {
                (*totalVendas)--;
                fprintf(stderr, "Erro: sem memoria para historico\n");
            }

            system("pause");
        }
    }

    if (encontrado == 0)
    {
        printf("\nId nao encontrado\n");
        system("pause");
    }
}

void relatorio(Produto *estoque, int total, Venda *historico, int totalVendas, float valor_abertura, float total_caixa)
{
    printf("\n=== RELATORIO DE VENDAS ===\n");
    printf("----------------------------------------------\n");
    printf("%-4s %-20s %6s %12s\n", "ID", "Produto", "Qtd", "Total");
    printf("----------------------------------------------\n");
    for (int i = 0; i < totalVendas; i++)
    {
        for (int j = 0; j < total; j++)
        {
            if (estoque[j].id == historico[i].idProduto)
            {
                printf("%-4d %-20s %6d %11s%.2f\n",
                       estoque[j].id,
                       estoque[j].nome,
                       historico[i].quantidade,
                       "R$",
                       historico[i].totalVenda);
            }
        }
    }
    printf("----------------------------------------------\n");
    printf("%-26s %11s%.2f\n", "Abertura:", "R$", valor_abertura);
    printf("%-26s %11s%.2f\n", "Vendas:",   "R$", total_caixa);
    printf("----------------------------------------------\n");
    printf("%-26s %11s%.2f\n", "Total:", "R$", valor_abertura + total_caixa);
    printf("----------------------------------------------\n");
    system("pause");
}

int lerUltimoCaixa()
{
    FILE *arquivo = fopen(NOME_ARQUIVO, "r");
    int ultimoCaixa = 0;
    int numero;
    char linha[200];

    if (arquivo == NULL)
    {
        return 1;
    }

    while (fgets(linha, sizeof(linha), arquivo) != NULL)
    {
        if (sscanf(linha, "Caixa %d fechado", &numero) == 1)
        {
            ultimoCaixa = numero;
        }
    }

    fclose(arquivo);

    return ultimoCaixa + 1;
}

int main()
{
    int numero_caixa = lerUltimoCaixa();
    Venda *historico = NULL;
    int proximoId = 1;
    int totalVendas = 0;
    Produto *estoque = NULL;
    int qtd_estoque = 0;
    float valor_abertura = 0;
    float total_caixa = 0;
    int valida_leitura;
    int caixa = 0;
    int total = 0;
    int opcao;

    FILE *produtos = fopen(PRODUTOS_ARQUIVO, "r");

    if (produtos != NULL)
    {
        Produto temp;
        char linha[200];

        while (fgets(linha, sizeof(linha), produtos) != NULL)
        {
            if (sscanf(linha,
                       "ID: %d | Tipo: %d | Nome: %29[^|] | Estoque: %d | Preco: %f",
                       &temp.id,
                       &temp.tipo,
                       temp.nome,
                       &temp.qtd_estoque,
                       &temp.preco) == 5)
            {
                Produto *novo = realloc(estoque, (total + 1) * sizeof(Produto));

                if (novo == NULL)
                {
                    printf("Erro de memoria!\n");
                    fclose(produtos);
                    break;
                }

                estoque = novo;
                estoque[total] = temp;

                int tam = strlen(estoque[total].nome);
                while (tam > 0 && estoque[total].nome[tam - 1] == ' ')
                {
                    estoque[total].nome[tam - 1] = '\0';
                    tam--;
                }

                if (temp.id >= proximoId)
                    proximoId = temp.id + 1;

                total++;
            }
        }

        fclose(produtos);
    }

    setlocale(LC_ALL, "Portuguese");

    do
    {
        system("cls");
        printf("================================\n");
        printf("         Super Muffatao\n");
        printf("================================\n\n");
        printf("1 - Abrir Caixa\n");
        printf("2 - Cadastro de Produtos\n");
        printf("3 - Realizar venda\n");
        printf("4 - Relatorio de Vendas\n");
        printf("5 - Lista de Produtos vendidos\n");
        printf("6 - Editar Produto\n");
        printf("7 - Fechar caixa\n");
        printf("8 - Sair\n");
        valida_leitura = scanf("%d", &opcao);

        if (valida_leitura == 0)
        {
            printf("Erro: Voce digitou uma letra ou caractere invalido!\n");
            while (getchar() != '\n');
            system("pause");
            opcao = -1;
        }
        else if (opcao < 1 || opcao > 8)
        {
            printf("Opcao invalida, Tente novamente!\n\n");
            system("pause");
        }

        switch (opcao)
        {
        case 1:
            AbrirCaixa(&caixa, &valor_abertura, valida_leitura, &numero_caixa);
            break;

        case 2:
            estoque = cadastrarProduto(estoque, &total, &qtd_estoque, &proximoId);
            break;

        case 3:
            if (caixa == 0)
            {
                printf("Abra o caixa primeiro!\n");
                system("pause");
            }
            else if (total == 0)
            {
                printf("Cadastre um produto primeiro!\n");
                system("pause");
            }
            else
            {
                printf("\n=== PRODUTOS DISPONIVEIS ===\n");
                printf("----------------------------------------------\n");
                printf("%-4s %-20s %-8s %6s %10s\n", "ID", "Nome", "Tipo", "Estq", "Preco");
                printf("----------------------------------------------\n");

                for (int i = 0; i < total; i++)
                {
                    printf("%-4d %-20s %-8s %6d %9s%.2f\n",
                           estoque[i].id,
                           estoque[i].nome,
                           estoque[i].tipo == 1 ? "Mercado" : "Padaria",
                           estoque[i].qtd_estoque,
                           "R$",
                           estoque[i].preco);
                }

                printf("----------------------------------------------\n");

                venda(estoque, total, &total_caixa, &qtd_estoque, &historico, &totalVendas);
            }
            break;

        case 4:
            relatorio(estoque, total, historico, totalVendas, valor_abertura, total_caixa);
            break;

        case 5:
        {
            if (totalVendas == 0)
            {
                printf("\nNenhuma venda registrada!\n");
                system("pause");
                break;
            }

            Venda *copia = malloc(totalVendas * sizeof(Venda));

            if (copia == NULL)
            {
                printf("Erro: sem memoria para criar a copia do historico!\n");
                system("pause");
                break;
            }

            memcpy(copia, historico, totalVendas * sizeof(Venda));

            for (int i = 0; i < totalVendas - 1; i++)
            {
                for (int j = 0; j < totalVendas - i - 1; j++)
                {
                    if (copia[j].totalVenda < copia[j + 1].totalVenda)
                    {
                        Venda temp = copia[j];
                        copia[j] = copia[j + 1];
                        copia[j + 1] = temp;
                    }
                }
            }

            printf("\n=== VENDAS (MAIOR PARA MENOR) ===\n");
            printf("----------------------------------------------\n");
            printf("%-4s %-20s %6s %12s\n", "#", "Produto", "Qtd", "Total");
            printf("----------------------------------------------\n");

            for (int i = 0; i < totalVendas; i++)
            {
                for (int j = 0; j < total; j++)
                {
                    if (estoque[j].id == copia[i].idProduto)
                    {
                        printf("%-4d %-20s %6d %11s%.2f\n",
                               i + 1,
                               estoque[j].nome,
                               copia[i].quantidade,
                               "R$",
                               copia[i].totalVenda);
                    }
                }
            }

            printf("----------------------------------------------\n");

            free(copia);
            system("pause");
            break;
        }

        case 6:
            editarProduto(estoque, total);
            break;

        case 7:
        {
            if (caixa == 0)
            {
                printf("Abra o caixa primeiro!\n");
                system("pause");
                break;
            }

            FILE *arquivo = fopen(NOME_ARQUIVO, "a");
            FILE *produtos = fopen(PRODUTOS_ARQUIVO, "w");

            if (arquivo == NULL || produtos == NULL)
            {
                perror("Erro ao abrir arquivo");

                if (arquivo != NULL)
                    fclose(arquivo);

                if (produtos != NULL)
                    fclose(produtos);

                system("pause");
                break;
            }

            fprintf(arquivo, "\n=== RELATORIO DE VENDAS ===      CAIXA %d\n", numero_caixa);

            for (int i = 0; i < totalVendas; i++)
            {
                for (int j = 0; j < total; j++)
                {
                    if (estoque[j].id == historico[i].idProduto)
                    {
                        fprintf(arquivo,
                                "Produto: %s | Quantidade: %d | Total: R$%.2f\n",
                                estoque[j].nome,
                                historico[i].quantidade,
                                historico[i].totalVenda);
                    }
                }
            }

            fprintf(arquivo, "\nValor de abertura: R$%.2f\n", valor_abertura);
            fprintf(arquivo, "Total em vendas:   R$%.2f\n", total_caixa);
            fprintf(arquivo, "Faturamento total: R$%.2f\n", valor_abertura + total_caixa);
            fprintf(arquivo, "Caixa %d fechado\n", numero_caixa);
            fprintf(arquivo, "----------------------------------------------\n");

            fprintf(produtos, "\n=== PRODUTOS CADASTRADOS ===\n");

            for (int i = 0; i < total; i++)
            {
                fprintf(produtos,
                        "ID: %d | Tipo: %d | Nome: %s | Estoque: %d | Preco: %.2f\n",
                        estoque[i].id,
                        estoque[i].tipo,
                        estoque[i].nome,
                        estoque[i].qtd_estoque,
                        estoque[i].preco);
            }

            fclose(arquivo);
            fclose(produtos);

            printf("\n=== FECHAMENTO DE CAIXA ===\n");
            printf("----------------------------------------------\n");
            printf("%-26s %11s%.2f\n", "Valor de abertura:", "R$", valor_abertura);
            printf("%-26s %11s%.2f\n", "Total em vendas:",   "R$", total_caixa);
            printf("----------------------------------------------\n");
            printf("%-26s %11s%.2f\n", "Faturamento total:", "R$", valor_abertura + total_caixa);
            printf("----------------------------------------------\n");
            printf("\nCaixa %d fechado com sucesso.\n", numero_caixa);

            free(historico);
            historico = NULL;

            totalVendas = 0;
            total_caixa = 0;
            valor_abertura = 0;
            caixa = 0;
            numero_caixa++;

            system("pause");
            break;
        }

        case 8:
        {
            printf("\nSaindo...\n");

            free(estoque);
            estoque = NULL;

            free(historico);
            historico = NULL;

            system("pause");
            break;
        }
        }

    } while (opcao != 8);

    return 0;
}
