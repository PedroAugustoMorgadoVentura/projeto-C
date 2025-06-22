#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <locale.h>
#include <math.h>

#define MAX_NOMES_FUNCIONARIOS 50
#define MAX_NOMES_CLIENTES 50
#define MAX_CPF 11
#define MAX_PRODUTOS 1000
#define MAX_NOTAS 1000
#define MATRICULA_ADMIN "123456"
#define SENHA_ADMIN "admin123"

typedef struct {
    int id;
    char nome[MAX_NOMES_CLIENTES];
    char telefone[15];
    char endereco[20];
    char cpf[MAX_CPF];
    char email[20];
    int id_cliente;
} clientes;

typedef struct {
    int id;
    char nome[MAX_PRODUTOS];
    char descricao[50];
    float preco;
    char nome_funcionario[MAX_NOMES_FUNCIONARIOS];
} chegada;

typedef struct {
    int id;
    char nome[MAX_NOMES_FUNCIONARIOS];
    char data[20];
    char hora[20];
    int qnt_produto;
    float preco_entrada;
} entrada_estoque;

typedef struct {
    int numero_nota;
    int id;
    int qnt_produto_saida;
    char nome[20];
    char data_saida[20];
    char hora_saida[20];
    float preco_venda;
    float subtotal;
    char cpf[MAX_CPF];
    char nome_cliente[20];
    char nome_funcionario[MAX_NOMES_FUNCIONARIOS];
} venda;

entrada_estoque estoque[MAX_PRODUTOS];
int total_produtos = 0;
venda nota[MAX_NOTAS];
int total_notas = 0;


void gravarArquivo() {
    FILE *arquivo;
    char registro1[100], registro2[100];

    arquivo = fopen("dados.txt", "w");
    if (arquivo == NULL) {
        printf("Erro ao abrir arquivo para escrita!\n");
        return;
    }

    printf("Digite o primeiro registro: ");
    fgets(registro1, sizeof(registro1), stdin);
    registro1[strcspn(registro1, "\n")] = 0;

    printf("Digite o segundo registro: ");
    fgets(registro2, sizeof(registro2), stdin);
    registro2[strcspn(registro2, "\n")] = 0;

    fprintf(arquivo, "%s;%s\n", registro1, registro2);

    fclose(arquivo);
    printf("Dados gravados com sucesso!\n");
}

void lerArquivo() {
    FILE *arquivo;
    char linha[200];
    char *registro1, *registro2;
    int numeroLinha = 1;

    arquivo = fopen("dados.txt", "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo para leitura! Verifique se o arquivo existe.\n");
        return;
    }

    printf("\nConteúdo do arquivo:\n");
    printf("--------------------\n");

    while (fgets(linha, sizeof(linha), arquivo) != NULL) {
        linha[strcspn(linha, "\n")] = 0;
        registro1 = strtok(linha, ";");
        registro2 = strtok(NULL, ";");

        if (registro1 != NULL && registro2 != NULL) {
            printf("Linha %d:\n", numeroLinha);
            printf("Registro 1: %s\n", registro1);
            printf("Registro 2: %s\n", registro2);
        } else {
            printf("Linha %d: %s (formato inválido)\n", numeroLinha, linha);
        }
        numeroLinha++;
    }
    printf("--------------------\n");
    fclose(arquivo);
}

void adicionarAoArquivo() {
    FILE *arquivo;
    char registro1[100], registro2[100];

    arquivo = fopen("dados.txt", "a");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo para adicionar dados!\n");
        return;
    }

    printf("Digite o primeiro registro: ");
    fgets(registro1, sizeof(registro1), stdin);
    registro1[strcspn(registro1, "\n")] = 0;

    printf("Digite o segundo registro: ");
    fgets(registro2, sizeof(registro2), stdin);
    registro2[strcspn(registro2, "\n")] = 0;

    fprintf(arquivo, "%s;%s\n", registro1, registro2);

    fclose(arquivo);
    printf("Dados adicionados com sucesso!\n");
}



int verificarLogin() {
    setlocale(LC_ALL, "portuguese");
    char matricula[20];
    char senha[20];
    int tentativas = 0;
    int max_tentativas = 3;

    printf("Seja muito bem-vindo à empresa BKEP Materiais de Construção\n");
    printf("\nPara acessar o sistema, realize o login...\n");

    while (tentativas < max_tentativas) {

        printf("Digite sua matrícula: ");
        fgets(matricula, sizeof(matricula), stdin);
        matricula[strcspn(matricula, "\n")] = 0;

        printf("Digite sua senha: ");
        fgets(senha, sizeof(senha), stdin);
        senha[strcspn(senha, "\n")] = 0;


        if ((strcmp(matricula, MATRICULA_ADMIN) == 0 && strcmp(senha, SENHA_ADMIN) == 0)) {
            printf("\nLogin realizado com sucesso!\n");
            return 1;
        } else {
            tentativas++;
            printf("\nMatrícula ou senha incorreta!\n");
            if (tentativas < max_tentativas) {
                printf("Tentativas restantes: %d\n", max_tentativas - tentativas);
            }
        }
    }
    printf("\nNúmero máximo de tentativas excedido!\n");
    printf("Seu acesso foi negado. Encerrando...\n");
    return 0;
}



void cadastrarProdutos() {
    chegada p;
    printf("\n==== CHEGADA DOS PRODUTOS ====\n");
    printf("ID do produto: ");
    scanf("%d", &p.id);
    getchar();
    printf("Nome: ");
    scanf("%[^\n]", p.nome);
    getchar();
    printf("Descrição: ");
    scanf("%[^\n]", p.descricao);
    getchar();
    printf("Preço unitário: R$ ");
    scanf("%f", &p.preco);
    getchar();
    printf("Nome do funcionário que cadastrou: ");
    scanf("%[^\n]", p.nome_funcionario);
    getchar();
    printf("Produto cadastrado com sucesso!\n");
}

void entradaEstoque() {
    if (total_produtos >= MAX_PRODUTOS) {
        printf("\nEstoque cheio! Não é possível cadastrar mais produtos.\n");
        return;
    }
    entrada_estoque p;
    printf("\n==== CADASTRO NO ESTOQUE ====\n");
    printf("ID: ");
    scanf("%d", &p.id);
    getchar();
    printf("Nome: ");
    scanf("%[^\n]", p.nome);
    getchar();
    printf("Hora do cadastro: ");
    scanf("%[^\n]", p.hora);
    getchar();
    printf("Data do cadastro: ");
    scanf("%[^\n]", p.data);
    getchar();
    printf("Quantidade: ");
    scanf("%d", &p.qnt_produto);
    getchar();
    printf("Preço pago: R$ ");
    scanf("%f", &p.preco_entrada);
    getchar();
    estoque[total_produtos] = p;
    total_produtos++;
    printf("Produto cadastrado no estoque com sucesso!\n");
}

void atualizarProduto() {
    int id, encontrado = 0;
    printf("\n==== ATUALIZAR PRODUTO ====\n");
    printf("Digite o ID do produto: ");
    scanf("%d", &id);
    getchar();

    for (int i = 0; i < total_produtos; i++) {
        if (estoque[i].id == id) {
            printf("Produto encontrado. Informe os novos dados:\n");
            printf("Novo nome: ");
            scanf("%[^\n]", estoque[i].nome);
            getchar();
            printf("Nova hora: ");
            scanf("%[^\n]", estoque[i].hora);
            getchar();
            printf("Nova data: ");
            scanf("%[^\n]", estoque[i].data);
            getchar();
            printf("Nova quantidade: ");
            scanf("%d", &estoque[i].qnt_produto);
            getchar();
            printf("Novo preço pago: R$ ");
            scanf("%f", &estoque[i].preco_entrada);
            getchar();
            printf("Produto atualizado com sucesso!\n");
            encontrado = 1;
            break;
        }
    }
    if (!encontrado) {
        printf("Produto não encontrado.\n");
    }
}

void removerProduto() {
    int id, encontrado = 0;
    printf("\n==== REMOVER PRODUTO ====\n");
    printf("Digite o ID do produto: ");
    scanf("%d", &id);
    getchar();

    for (int i = 0; i < total_produtos; i++) {
        if (estoque[i].id == id) {
            for (int j = i; j < total_produtos - 1; j++) {
                estoque[j] = estoque[j + 1];
            }
            total_produtos--;
            printf("Produto removido com sucesso!\n");
            encontrado = 1;
            break;
        }
    }
    if (!encontrado) {
        printf("Produto não encontrado.\n");
    }
}

void buscarProdutoPorNome() {
    char nomeBusca[50];
    int encontrado = 0;
    printf("\n==== BUSCAR PRODUTO POR NOME ====\n");
    printf("Digite o nome do produto: ");
    scanf("%[^\n]", nomeBusca);
    getchar();

    for (int i = 0; i < total_produtos; i++) {
        if (strstr(estoque[i].nome, nomeBusca) != NULL) {
            printf("\nProduto encontrado:\n");
            printf("ID: %d\n", estoque[i].id);
            printf("Nome: %s\n", estoque[i].nome);
            printf("Data: %s\n", estoque[i].data);
            printf("Hora: %s\n", estoque[i].hora);
            printf("Quantidade: %d\n", estoque[i].qnt_produto);
            printf("Preço pago: R$ %.2f\n", estoque[i].preco_entrada);
            encontrado = 1;
        }
    }
    if (!encontrado) {
        printf("Nenhum produto encontrado.\n");
    }
}

void ConsultaProdutos() {
    printf("\n===== PRODUTOS NO ESTOQUE =====\n");
    if (total_produtos == 0) {
        printf("Nenhum produto cadastrado.\n");
        return;
    }
    for (int i = 0; i < total_produtos; i++) {
        printf("\nProduto %d:\n", i + 1);
        printf("ID: %d\n", estoque[i].id);
        printf("Nome: %s\n", estoque[i].nome);
        printf("Hora: %s\n", estoque[i].hora);
        printf("Data: %s\n", estoque[i].data);
        printf("Quantidade: %d\n", estoque[i].qnt_produto);
        printf("Preço pago: R$ %.2f\n", estoque[i].preco_entrada);
    }
}



void cadastroClietes() {
    clientes p;
    printf("\n==== CADASTRO DE CLIENTE ====\n");
    printf("Nome do cliente: ");
    scanf("%[^\n]", p.nome);
    getchar();
    printf("CPF: ");
    scanf("%[^\n]", p.cpf);
    getchar();
    printf("Email: ");
    scanf("%[^\n]", p.email);
    getchar();
    printf("Telefone: ");
    scanf("%[^\n]", p.telefone);
    getchar();
    printf("Endereço: ");
    scanf("%[^\n]", p.endereco);
    getchar();
    printf("ID do cliente: ");
    scanf("%d", &p.id_cliente);
    getchar();
    printf("Cliente cadastrado com sucesso!\n");
}

void vendaProdutos() {
    venda p;
    printf("\n==== VENDA ====\n");
    printf("Número da nota: ");
    scanf("%d", &p.numero_nota);
    getchar();
    printf("ID do produto: ");
    scanf("%d", &p.id);
    getchar();
    printf("Nome do produto: ");
    scanf("%[^\n]", p.nome);
    getchar();
    printf("Quantidade: ");
    scanf("%d", &p.qnt_produto_saida);
    getchar();
    printf("Hora da venda: ");
    scanf("%[^\n]", p.hora_saida);
    getchar();
    printf("Data da venda: ");
    scanf("%[^\n]", p.data_saida);
    getchar();
    printf("Preço de venda por unidade: R$ ");
    scanf("%f", &p.preco_venda);
    getchar();
    printf("Nome do comprador: ");
    scanf("%[^\n]", p.nome_cliente);
    getchar();
    printf("CPF do comprador: ");
    scanf("%[^\n]", p.cpf);
    getchar();
    printf("Funcionário que realizou a venda: ");
    scanf("%[^\n]", p.nome_funcionario);
    getchar();

    p.subtotal = p.qnt_produto_saida * p.preco_venda;
    printf("Valor total da venda: R$ %.2f\n", p.subtotal);
    nota[total_notas] = p;
    total_notas++;
    printf("Nota fiscal gerada e salva com sucesso!\n");
}

void emitirNotas() {
    printf("\n===== NOTAS FISCAIS EMITIDAS =====\n");
    if (total_notas == 0) {
        printf("Nenhuma nota emitida.\n");
        return;
    }
    for (int i = 0; i < total_notas; i++) {
        printf("\nNota Fiscal %d:\n", i + 1);
        printf("Número da nota: %d\n", nota[i].numero_nota);
        printf("Produto: %s\n", nota[i].nome);
        printf("Quantidade: %d\n", nota[i].qnt_produto_saida);
        printf("Valor total: R$ %.2f\n", nota[i].subtotal);
    }
}

void consultarClientes() {
    printf("\n==== CLIENTES CADASTRADOS ====\n");
    if (total_notas == 0) {
        printf("Nenhum cliente cadastrado.\n");
        return;
    }
    for (int i = 0; i < total_notas; i++) {
        printf("\nCliente %d:\n", i + 1);
        printf("Nome: %s\n", nota[i].nome_cliente);
        printf("CPF: %s\n", nota[i].cpf);
    }
}

void relatorioDeVendas() {
    printf("\n==== RELATÓRIO DE VENDAS ====\n");
    if (total_notas == 0) {
        printf("Nenhuma venda registrada.\n");
        return;
    }

    float totalGeral = 0;
    for (int i = 0; i < total_notas; i++) {
        printf("\nVenda %d:\n", i + 1);
        printf("Nota: %d | Produto: %s | Quantidade: %d | Total: R$%.2f\n",
               nota[i].numero_nota, nota[i].nome, nota[i].qnt_produto_saida, nota[i].subtotal);
        totalGeral += nota[i].subtotal;
    }

    printf("\nTOTAL GERAL DAS VENDAS: R$ %.2f\n", totalGeral);
}

void sobre() {
    printf("\n==== SOBRE O SISTEMA ====\n");
    printf("Sistema de Gestão - BKEP Materiais de Construção\n");
    printf("Versão: 1.0\n");
    printf("Desenvolvido por:Breno, Enzo, Kaique e Pedro Augusto\n");
    printf("Funções: Controle de estoque, clientes, vendas e notas fiscais.\n");
    printf("Ano: 2025\n");
}



int main() {
    if (!verificarLogin()) {
        return 1;
    }

    int opcao = 0;
    while (1) {
        printf("\n==== MENU BKEP MATERIAIS DE CONSTRUÇÃO ====\n");
        printf("1. Chegada de produtos\n");
        printf("2. Cadastro no estoque\n");
        printf("3. Consulta de produtos\n");
        printf("4. Cadastro de clientes\n");
        printf("5. Nova venda\n");
        printf("6. Emissão de notas fiscais\n");
        printf("7. Gravar dados no arquivo\n");
        printf("8. Ler dados do arquivo\n");
        printf("9. Adicionar dados ao arquivo\n");
        printf("10. Atualizar produto\n");
        printf("11. Remover produto\n");
        printf("12. Buscar produto por nome\n");
        printf("13. Consultar clientes\n");
        printf("14. Relatório de vendas\n");
        printf("15. Sobre o sistema\n");
        printf("16. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);
        getchar();

        switch (opcao) {
            case 1: cadastrarProdutos(); break;
            case 2: entradaEstoque(); break;
            case 3: ConsultaProdutos(); break;
            case 4: cadastroClietes(); break;
            case 5: vendaProdutos(); break;
            case 6: emitirNotas(); break;
            case 7: gravarArquivo(); break;
            case 8: lerArquivo(); break;
            case 9: adicionarAoArquivo(); break;
            case 10: atualizarProduto(); break;
            case 11: removerProduto(); break;
            case 12: buscarProdutoPorNome(); break;
            case 13: consultarClientes(); break;
            case 14: relatorioDeVendas(); break;
            case 15: sobre(); break;
            case 16: printf("Encerrando o programa...\n"); return 0;
            default: printf("Opção inválida. Tente novamente.\n"); break;
        }
    }
    return 0;
}
