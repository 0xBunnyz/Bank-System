#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <string.h>
#include <time.h>

typedef struct {
    int codigo;
    char nome[50];
    char email[50];
    char cpf[20];
    char data_nascimento[20];
    char data_cadastro[20];
} Cliente;

typedef struct {
    int numero;
    Cliente cliente;
    float saldo;
    float limite;
    float saldo_total;
} Conta;

void menu();
void login_admin();
void info_cliente(Cliente cliente);
void info_conta(Conta conta);
void cria_conta();
void efetuar_deposito();
void efetuar_saque();
void efetuar_transferencia();
void listar_contas();
float atualizar_saldo_total(Conta conta);
Conta buscar_conta_por_numero(int numero);
void sacar(Conta conta, float valor);
void depositar(Conta conta, float valor);
void transferir(Conta conta_origem, Conta conta_destino, float valor);

static Conta contas[50];
static int contador_contas = 0;
static int contador_clientes = 0;

int main(){
    menu();
}

void menu(){
    system("cls");
    int opcao = 0;
    printf("=====================================\n");
    printf("================ ATM ================\n");
    printf("============= Bunny Bank ============\n");
    printf("Selecione uma opcao:\n");
    printf("1 - Criar conta\n");
    printf("2 - Efetuar saque\n");
    printf("3 - Efetuar deposito\n");
    printf("4 - Efetuar transferencia\n");
    printf("====== Administrativo ======\n");
    printf("5 - Listar Contas\n");
    printf("6 - Sair\n");
    printf("=====================================\n");

    scanf("%d", &opcao);
    getchar();

    switch(opcao){
        case 1:
            cria_conta();
            break;
        case 2:
            efetuar_saque();
            break;
        case 3:
            efetuar_deposito();
            break;
        case 4:
            efetuar_transferencia();
            break;
        case 5:
            login_admin();
            break;
        case 6:
            system("cls");
            printf("Até a proxima!");
            Sleep(2);
            exit(0);
        default:
            printf("Opcao invalida.\n");
            Sleep(2);
            menu();
    }
}


void login_admin(){
    char user[6] = "admin";
    int password = 123;
    char input_user[10];
    char input_password[16];

    system("cls");
    printf("===== Administrativo =====\n");
    printf("USER:");
    fgets(input_user, 10, stdin);
    printf("PASSWORD:");
    scanf("%d", &input_password);

    if(strcmp(user, input_password) == 0 && input_password == password){
        listar_contas();
    } else {
        MessageBox(NULL, "Usuario ou senha incorreta", "ERRO", MB_ICONERROR);
    }
}


void info_cliente(Cliente cliente){
    printf("Codigo: %d \nNome: %s \nData de nascimento: %s \nCadastro: %s", cliente.codigo, strtok(cliente.nome, "\n"), strtok(cliente.data_nascimento, "\n"), strtok(cliente.data_cadastro, "\n"));
}


void info_conta(Conta conta){
    printf("Conta: %d \ncliente: %s \nData de nascimento: %s \nData de cadastro: %s \nSaldo Total %.2f\n", conta.numero, strtok(conta.cliente.nome, "\n"), strtok(conta.cliente.data_nascimento, "\n"), strtok(conta.cliente.data_cadastro, "\n"), conta.saldo_total);
}


void cria_conta(){
    system("cls");
    Cliente cliente;
    char dia[3];
    char mes[3];
    char ano[5];
    char data_cadastro[20];
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);

    if(tm.tm_mday < 10){
        sprintf(dia, "0%d", tm.tm_mday);
    }else{
        sprintf(dia, "%d", tm.tm_mday);
    }

    if((tm.tm_mon + 1) < 10){
        sprintf(mes, "0%d", tm.tm_mon + 1);
    }else{
        sprintf(mes, "%d", tm.tm_mon);
    }

    sprintf(ano, "%d", tm.tm_year + 1900);

    strcpy(data_cadastro, "");
    strcat(data_cadastro, dia);
    strcat(data_cadastro, "/");
    strcat(data_cadastro, mes);
    strcat(data_cadastro, "/");
    strcat(data_cadastro, ano);
    strcat(data_cadastro, "\0");
    strcpy(cliente.data_cadastro, data_cadastro);

    printf("========== CRIAR CONTA ==========\n");
    printf("Informe os dados do cliente:\n");
    cliente.codigo = contador_clientes + 1;

    printf("NOME:");
    fgets(cliente.nome, 50, stdin);

    printf("EMAIL:");
    fgets(cliente.email, 50, stdin);

    printf("CPF:");
    fgets(cliente.cpf, 12, stdin);
    getchar();

    printf("DATA DE NASCIMENTO: ");
    fgets(cliente.data_nascimento, 20, stdin);
    contador_clientes ++;

    contas[contador_contas].numero = contador_contas + 1;
    contas[contador_contas].cliente = cliente;
    contas[contador_contas].saldo = 0.0;
    contas[contador_contas].limite = 0.0;
    contas[contador_contas].saldo_total = atualizar_saldo_total(contas[contador_contas]);

    printf("\n\nConta criada com sucesso!\n\n");
    printf("================ DADOS =================\n");
    info_conta(contas[contador_contas]);
    contador_contas ++;

    sleep(5);
    menu();

}


void efetuar_saque(){
    if(contador_contas > 0){
        int numero;
        printf("========== EFETUAR SAQUE ==========\n");
        printf("Informe o numero da conta:\n");
        scanf("%d", &numero);

        Conta conta = buscar_conta_por_numero(numero);

        if(conta.numero == numero){
            float valor;
            printf("Informe o valor do saque:\n");
            scanf("%f", &valor);

            sacar(conta, valor);
        } else {
            printf("Não foi possivel sacar!");
        }
    }else{
        printf("Ainda não existem contas para saques!");
    }
    sleep(2);
    menu();
}


void efetuar_deposito(){
    if(contador_contas > 0){
        int numero;
        printf("========== EFETUAR SAQUE ==========\n");
        printf("Informe o numero da conta:\n");
        scanf("%d", &numero);

        Conta conta = buscar_conta_por_numero(numero);

        if(conta.numero == numero){
            float valor;
            printf("Informe o valor do saque:\n");
            scanf("%f", &valor);

            depositar(conta, valor);
        } else {
            printf("Não foi encontrada uma conta com numero %d\n");
        }
    }else{
        printf("Ainda não existem contas para saques!");
    }
    sleep(2);
    menu();
}


void efetuar_transferencia(){
    if(contador_contas > 0){
        int numero_o, numero_d;
        printf("Informe o numero da sua conta: ");
        scanf("%d", &numero_o);

        Conta conta_o = buscar_conta_por_numero(numero_o);

        if(conta_o.numero == numero_o){
            printf("Informe o numero da conta destino:\n");
            scanf("%d", &numero_d);

            Conta conta_d = buscar_conta_por_numero(numero_d);

            if(conta_d.numero == numero_d){
                float valor;
                printf("Informe o valor para transferencia:\n");
                scanf("%f", &valor);

                transferir(conta_o, conta_d, valor);
            }else{
                printf("A conta destino com numero %d não foi encontrada!", numero_d);
            }
        }else{
            printf("A conta com o numero %d não foi encontrada!", numero_o);
        }
    }else{
        printf("Ainda não existem contas para transferencia.\n");
    }
    sleep(2);
    menu();
}


void listar_contas(){
    if(contador_contas > 0){
        for(int i = 0; i < contador_contas; i++){
            info_conta(contas[i]);
            printf("\n");
            sleep(1);
        }
    }else{
        printf("Não existem contas cadastradas ainda.\n");
    }
    sleep(2);
    menu();
}


float atualizar_saldo_total(Conta conta){
    return conta.saldo + conta.limite;
}


Conta buscar_conta_por_numero(int numero){
    Conta c;
    if(contador_contas > 0){
        for(int i = 0; i < contador_contas; i++){
            if(contas[i].numero == numero){
                c = contas[i];
            }
        }
    }
    return c;
}


void sacar(Conta conta, float valor){
    if(valor > 0 && conta.saldo_total >= valor){
        for(int i = 0; i < contador_contas; i++){
            if(contas[i].numero == conta.numero){
                if(contas[i].saldo >= valor){
                    contas[i].saldo = contas[i].saldo - valor;
                    contas[i].saldo_total = atualizar_saldo_total(contas[i]);
                    printf("Saque efetuado com sucesso!\n");
                    printf("============================\n");
                } else {
                    float restante = contas[i].saldo - valor;
                    contas[i].limite = contas[i].limite + restante;
                    contas[i].saldo = 0.0;
                    contas[i].saldo_total = atualizar_saldo_total(contas[i]);
                    printf("Saque efetuado com sucesso!\n");
                    printf("============================\n");
                }
            }
        }
    } else {
        printf("Saldo insuficiente!");
    }
}


void depositar(Conta conta, float valor){
    if(valor > 0){
        for(int i = 0; i < contador_contas; i++){
            if(contas[i].numero == conta.numero){
                contas[i].saldo = contas[i].saldo + valor;
                contas[i].saldo_total = atualizar_saldo_total(contas[i]);
                printf("Deposito efetuado com sucesso!");
            }
        }
    }else{
        printf("Erro ao efetuar deposito!");
    }
}


void transferir(Conta conta_origem, Conta conta_destino, float valor){
    if(valor > 0 && conta_origem.saldo_total >= valor){
        for(int co = 0; co < contador_contas; co++){
            if(contas[co].numero == conta_origem.numero){
                for(int cd = 0; cd < contador_contas; cd++){
                    if(contas[cd].numero == conta_destino.numero){
                        if(contas[co].saldo >= valor){
                            contas[co].saldo = contas[co].saldo - valor;
                            contas[cd].saldo = contas[cd].saldo + valor;
                            contas[co].saldo_total = atualizar_saldo_total(contas[co]);
                            contas[cd].saldo_total = atualizar_saldo_total(contas[cd]);
                            printf("Transferencia realizada com sucesso!");
                        } else {
                            float restante = contas[co].saldo - valor;
                            contas[co].limite = contas[co].limite + restante;
                            contas[co].saldo = 0.0;
                            contas[cd].saldo = contas[cd].saldo + valor;
                            contas[co].saldo_total = atualizar_saldo_total(contas[co]);
                            contas[cd].saldo_total = atualizar_saldo_total(contas[cd]);
                             printf("Transferencia realizada com sucesso!");
                        }
                    }
                }
            }
        }
    }else{
        printf("Transferencia não realizada!");
    }
}
