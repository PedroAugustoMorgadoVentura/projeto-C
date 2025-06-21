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


typedef struct{

  int id;
  char nome[MAX_NOMES_CLIENTES];
  char telefone[15];
  char endereco[20];
  char cpf[MAX_CPF];
  char email[20];
  int id_cliente;

}clientes;

typedef struct{
   int id;
   char nome[MAX_PRODUTOS];
   char descricao[50];
   float preco;
   char nome_funcionario [MAX_NOMES_FUNCIONARIOS];

}chegada;

typedef struct{
  int id;
  char data[20];
  char hora[20];
  int qnt_produto;
  float preco_entrada;
  char nome[MAX_NOMES_FUNCIONARIOS];

}entrada_estoque;

typedef struct{
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


entrada_estoque estoque[MAX_PRODUTOS];  // Vetor para armazenar os produtos cadastrados
int total_produtos = 0;                 // Contador de quantos produtos foram cadastrados


venda nota[MAX_NOTAS];
int total_notas = 0;

int verificarLogin (){
    setlocale (LC_ALL, "portuguese");
    char matricula[20];
    char senha[20];
    int tentativas = 0;
    int max_tentativas = 3;

    printf("Seja muito bem vindo a empresa BKEP materiais de construção\n");
    printf("\nPara acessar o sistema preciso que realize o loguin...\n");

    while (tentativas < max_tentativas) {
        printf("\nDigite sua matrícula: ");
        scanf(" %s", matricula);

        printf("\nDigite sua senha: ");
        scanf(" %s", senha);

        if ((strcmp(matricula, MATRICULA_ADMIN) == 0 && strcmp(senha, SENHA_ADMIN) == 0)){

            printf("\n Login realizado com sucesso!\n"); // verificação de loguin.

            return 1; // loguin confirmado.

            }else {
            tentativas++;
            printf("\n Matrícula ou senha incorreta!\n");

            if (tentativas < max_tentativas) {
                printf("Tentativas restantes: %d\n\n", max_tentativas - tentativas);
            }
        }
    }

    printf("\n Número máximo de tentativas excedido!\n");
    printf("Seu acesso ao sistema foi negado. Encerrando programa...\n");

    return 0; // Login falhou
}


void cadastrarProdutos(){
    chegada p;

        printf("\n==== CHEGADA DOS PRODUTOS NA EMPRESA ====\n");
        printf("ID do produto: ");
        scanf("%d", &p.id);
        getchar();  // Limpa o ENTER que sobra


        printf("\nNome: ");
        scanf(" %[^\n]", p.nome);

        printf("\nDescrição: ");
        scanf(" %[^\n]", p.descricao);

        printf("\nPreço unitário: R$");
        scanf("%f", &p.preco);
        getchar();  // Limpa o ENTER que sobra

        printf("\nNome do funcionário(a) que cadastrou: ");
        scanf(" %[^\n]", p.nome_funcionario);

        printf("\nProduto notificado com sucesso!\n");


}


void entradaEstoque(){

     if (total_produtos >= MAX_PRODUTOS) {
        printf("\nEstoque cheio! Não é possível cadastrar mais produtos.\n");
        return;
    }

    entrada_estoque p;

        printf("\n==== CADASTRAMENTO DE PRODUTOS NO ESTOQUE ====\n");
        printf("ID: ");
        scanf("%d", &p.id);
        getchar();  // Limpa o ENTER que sobra


        printf("\nNome: ");
        scanf(" %[^\n]", p.nome);

        printf("\nHora do cadastramento: ");
        scanf(" %[^\n]", p.hora);

        printf("\nData do cadastramento: ");
        scanf(" %[^\n]", p.data);

        printf("\nQuantidade do produto: ");
        scanf("%d", &p.qnt_produto);
        getchar();  // Limpa o ENTER que sobra

        printf("\nPreço pago pelo produto: R$ ");
        scanf("%f", &p.preco_entrada);
        getchar();  // Limpa o ENTER que sobra

         estoque[total_produtos] = p; // parte adicionada.
    total_produtos++;

        printf("\nProduto cadastrado no estoque com sucesso!\n");


}

void cadastroClietes(){

    clientes p;

    printf("\n==== CADASTRAMENTO DE CLIENTES ====\n");

    printf("Nome do cliente: ");
    scanf(" %[^\n]", p.nome);


    printf("\nCPF: ");
    scanf(" %[^\n]", p.cpf);

    printf("\nE-mail: ");
    scanf(" %[^\n]", p.email);

    printf("\nTelefone: ");
    scanf(" %[^\n]", p.telefone);

    printf("\nEndereço: ");
    scanf(" %[^\n]", p.endereco);

    printf("\nID do novo cliente: ");
    scanf("%d", &p.id_cliente);
    getchar();  // Limpa o ENTER que sobra

    printf("\nCliente cadastrado com sucesso!\n");


}

void vendaProdutos(){

    venda p;


     printf("\n==== NOTA FISCAL DE VENDA ====\n");

     printf("Número da nota: ");
     scanf("%d", &p.numero_nota);
     getchar();  // Limpa o ENTER que sobra

     printf("\nID do produto: ");
     scanf("%d", &p.id);
     getchar();  // Limpa o ENTER que sobra

     printf("\nNome: ");
     scanf(" %[^\n]", p.nome);

     printf("\nQuantidade: ");
     scanf("%d", &p.qnt_produto_saida);
     getchar();  // Limpa o ENTER que sobra

     printf("\nHora da venda: ");
     scanf(" %[^\n]", p.hora_saida);

     printf("\nData da venda: ");
     scanf(" %[^\n]", p.data_saida);

     printf("\nPreço da venda por unidade: R$ ");
     scanf("%f", &p.preco_venda);
     getchar();  // Limpa o ENTER que sobra

    printf("\nNome do comprador: ");
    scanf(" %[^\n]", p.nome_cliente);

     printf("\nCPF do comprador: ");
     scanf(" %[^\n]", p.cpf);


     printf("\nFuncionário(a) que realizou a venda: ");
     scanf(" %[^\n]", p.nome_funcionario);

     float soma=0;
     soma += (float) p.qnt_produto_saida * p.preco_venda;

     p.subtotal = soma;

     printf("Valor total da venda: R$%.2f\n", p.subtotal);

     nota[total_notas] = p; // parte adicionada que tenho que tirar dúvidas
     total_notas++;

     printf("\nNota fiscal de venda salva com sucesso");

}

void ConsultaProdutos(){

  printf("\n===== PRODUTOS CADASTRADOS NO ESTOQUE =====\n");

        if (total_produtos == 0) {
        printf("Nenhum produto cadastrado no estoque ainda.\n");
        return;
    }

      for (int i = 0; i < total_produtos; i++) {
        printf("\nProduto %d:\n", i + 1);
        printf("ID: %d\n", estoque[i].id);
        printf("Nome: %s\n", estoque[i].nome);
        printf("Hora do cadastramento: %s\n", estoque[i].hora);
        printf("Data do cadastramento: %s\n", estoque[i].data);
        printf("Quantidade: %d\n", estoque[i].qnt_produto);
        printf("Preço pago: R$ %.2f\n", estoque[i].preco_entrada);
    }
}


void emitirNotas(){

    printf("\n===== NOTAS FISCAIS EMITIDAS =====\n");

    if (total_notas == 0) {
        printf("Nenhuma nota emitida ainda.\n");
        return;
    }
    for (int i = 0; i < total_notas; i++) {
        printf("\nNOTA FISCAL %d:\n", i + 1);
        printf("\nNúmero da nota: %d", nota[i].numero_nota);
        printf("ID: %d\n", nota[i].id);
        printf("Nome: %s\n", nota[i].nome);
        printf("Hora da venda: %s\n", nota[i].hora_saida);
        printf("Data da venda: %s\n", nota[i].data_saida);
        printf("Quantidade: %d\n", nota[i].qnt_produto_saida);
        printf("Preço da venda por unidade: R$ %.2f\n", nota[i].preco_venda);
        printf("Nome do comprador: %s\n", nota[i].nome_cliente);
        printf("CPF do comprador: %s\n", nota[i].cpf);
        printf("Funcionário(a) que realizou a venda: %s\n", nota[i].nome_funcionario);
        printf("Valor total da venda: R$%.2f\n", nota[i].subtotal);

    }
}
int main() {
    // Teste do sistema de login
    if (!verificarLogin()) {
        return 1; // Sai do programa se login for errado
    }
    int opcao=0;
     while (1){
    printf("\n BEM VINDO AO SISTEMA DA BKEP MATERIAIS DE CONSTRUÇÃO\n");

    printf("\n1. Chegada de produtos.");
    printf("\n2. Cadastro do produto no estoque.");
    printf("\n3. Consulta de produtos.");
    printf("\n4. Cadastro de cliente.");
    printf("\n5. Nova venda.");
    printf("\n6. Emissão de notas fiscais.");
    printf("\n7. SAIR.");
    printf("\nQual sua escolha: ");
    scanf("%d", &opcao);

    switch (opcao){

    case 1:
        cadastrarProdutos();
        break;

    case 2:
        entradaEstoque();
        break;

    case 3:
       ConsultaProdutos();
        break;

    case 4:
        cadastroClietes();
        break;

    case 5:
        vendaProdutos();
        break;

    case 6:
        emitirNotas();
        break;

    case 7:
        printf("\nVocê escolheu sair do programa. Estamos encerrando...");
        return 0;  // Aqui o programa realmente encerra.

    default:
        printf("Opção inválida! Por favor digite novamente outra opção.");
        break;


    }
     }
    return 0;
}
