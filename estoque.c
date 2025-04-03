#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

#define MAX_PESSOAS 2
#define MAX_PRODUTOS 3

// Definição de structs

struct cadastros {
    char nome[100];
    int cpf;
    char endereco[100];
    int telefone;
    char dataNasc[12];
};

struct produtos {
    int codigo;
    char nomeProduto[100];
    float valor;
    char validade[10];
};

typedef struct produtos material;
typedef struct cadastros pessoas;

//FUNÇÃO PARA CRIAR STRUCT
void criaPessoas(pessoas Cliente[], int *numPessoas);
void criaMaterial(material produto[], int *numMaterial);

//VERIFICAÇÃO PARA VER SE EXISTEM DADOS
bool verificacaoPessoa(int cpf, int *numPessoas, pessoas Cliente[]);
bool verificacaoMaterial(int codigo, int *numMaterial, material produtos[]);

//CONSULTA DE DADOS
void consulta(pessoas Cliente[], int *numPessoas, material produto[], int *numMaterial);
void consultaPessoas(pessoas Cliente[], int *numPessoas);
void consultaMaterial(material produto[], int *numMaterial);
    //CONSULTA ENVOLVENDO CONSULTA DO MATERIAL
    void consultaDias(material produto[], int *numMaterial);
    void produtoVencido(material produto[], int *numMaterial);
    void consultaEstoque(material produto[], int *numMaterial);

//VENDA DE PRODUTOS
void vendaMaterial(material produto[], int *numMaterial);


//MANIPULAÇÃO DA DATA 
struct tm converteData(char *data) {
    struct tm tm_data = {0};
    sscanf(data, "%d/%d/%d", &tm_data.tm_mday, &tm_data.tm_mon, &tm_data.tm_year);
    tm_data.tm_mon--;
    tm_data.tm_year -= 1900;
    return tm_data;
}
int main() {
    int numPessoas = 0;
    int numMaterial = 0;

    pessoas Cliente[MAX_PESSOAS];
    material Produto[MAX_PRODUTOS];
    
    int num;
    do {
        printf(" [1] CADASTRO DE CLIENTES\n [2] CADASTRO DE PRODUTOS \n [3] CONSULTAS\n [4] VENDA \n [5] BAIXA EM ESTOQUE\n [6] SAIR\n");
        scanf("%d", &num);

        switch (num) {
            case 1:
                criaPessoas(Cliente, &numPessoas);
                break;
            case 2:
                criaMaterial(Produto, &numMaterial);
                break;
            case 3:
                consulta(Cliente, &numPessoas, Produto, &numMaterial);
                break;
            case 4:
                vendaMaterial(Produto,&numMaterial);
        }
    } while (num > 0 && num < 6);


}

// Funções
void criaPessoas(pessoas Cliente[], int *numPessoas) {
    if (*numPessoas < MAX_PESSOAS) {
        int cpf;
        printf("Insira seu cpf: ");
        scanf("%d", &cpf);
        setbuf(stdin, NULL); 
        if (verificacaoPessoa(cpf, numPessoas, Cliente)) {
            printf("Insira seu nome: ");
            fgets(Cliente[*numPessoas].nome, 100, stdin);
            Cliente[*numPessoas].cpf = cpf;  

            printf("Insira seu endereço: ");
            fgets(Cliente[*numPessoas].endereco, 100, stdin);

            printf("Insira sua data de nascimento: DD/MM/YYYY: ");
            scanf("%s", Cliente[*numPessoas].dataNasc);

            (*numPessoas)++;  
        } else {
            printf("\nCPF JÁ CADASTRADO\n");
        }
    } else {
        printf("MAXIMO DE USUARIOS JÁ CADASTRADO\n\n");
    }
}

void criaMaterial(material produto[], int *numMaterial) {
    if (*numMaterial < MAX_PRODUTOS) {
        int codigo;
        printf("Insira o codigo do produto: ");
        scanf("%d", &codigo);
        setbuf(stdin, NULL); 
        if (verificacaoMaterial(codigo, numMaterial, produto)) {
            produto[*numMaterial].codigo = codigo;

            printf("Insira o nome do produto: ");
            fgets(produto[*numMaterial].nomeProduto, 100, stdin);

            printf("Insira o valor do produto: ");
            scanf("%f", &produto[*numMaterial].valor);

            printf("Insira a validade do produto: ");
            scanf("%s", produto[*numMaterial].validade);

            (*numMaterial)++;
        } else {
            printf("\n[CODIGO DO PRODUTO JÁ CADASTRADO]\n");
        }
    } else {
        printf("\n[MAXIMO DE PRODUTOS JÁ CADASTRADO]\n");
    }
}

bool verificacaoPessoa(int cpf, int *numPessoas, pessoas Cliente[]) {
    bool retorno = true;
    for (int i = 0; i < *numPessoas; i++) {
        if (Cliente[i].cpf == cpf) {
            retorno= false; 
        }
    }
    return retorno; 
}

bool verificacaoMaterial(int codigo, int *numMaterial, material produtos[]) {
    bool retorno = true;
    for (int i = 0; i < *numMaterial; i++) {
        if (produtos[i].codigo == codigo) {
            return false; 
        }
    }
    return retorno; 
}

void consulta(pessoas Cliente[], int *numPessoas, material produto[], int *numMaterial) {
    int num;
    printf("DESEJA CONSULTAR:\n");
    printf("[1] PESSOAS\n");
    printf("[2] MATERIAL\n");
    scanf("%d", &num);

    switch (num) {
        case 1:
            consultaPessoas(Cliente, numPessoas);
            break;
        case 2:
            consultaMaterial(produto, numMaterial);
            break;
        
    }
}

void consultaPessoas(pessoas Cliente[], int *numPessoas) {
    char verificacao[2];
    verificacao[0] = 's';
    int num;
    printf("\n");
    if(*numPessoas>0){
        do {
            for (int i = 0; i < *numPessoas; i++) {
                printf("[%d] %s", i, Cliente[i].nome);
            }

            printf("Escolha a pessoa a ser consultada: ");
            scanf("%d", &num);

            if (num >= 0 && num < *numPessoas) {
                printf("\nCPF: %d\n", Cliente[num].cpf);
                printf("Nome: %s", Cliente[num].nome);
                printf("Endereço: %s", Cliente[num].endereco);
                printf("Data de Nascimento: %s\n", Cliente[num].dataNasc);
            } else {
                printf("Opção inválida!\n");
            }

            printf("Você quer continuar a consulta? S/N\n");
            scanf("%s", verificacao);
        } while (verificacao[0] == 's' || verificacao[0] == 'S');
    }
    else{
        printf("\n[NÃO TEM PESSOAS PARA SEREM CONSULTADAS]\n");
    }
}

void consultaMaterial(material produto[], int *numMaterial) {
   int num;
   printf("\nDESEJA CONSULTAR POR:\n");
   printf("\n[1]PRODUTOS COM X DIAS PARA VENCER");
   printf("\n[2]PRODUTOS VENCIDOS EM ESTOQUE");
   printf("\n[3] VERIFICAR QUANTO DE UM PRODUTO TEM ESTOQUE\n");

    scanf("%d",&num);

    switch (num)
    {
    case 1:
        consultaDias(produto, numMaterial);
        break;

    case 2: 
        produtoVencido(produto, numMaterial);
        break;

    case 3:
        consultaEstoque(produto, numMaterial);
        break;
    
    }
}


void consultaEstoque(material produto[], int *numMaterial){
    int num;
    int qtdEstoque=0;
    if(*numMaterial>0){
        printf("\nINSIRA O CODIGO DO PRODUTO QUE DESEJA CONSULTA O ESTOQUE: \n");
        scanf("%d",&num);

        for (int i = 0; i < *numMaterial; i++)
        {
            if(produto[i].codigo==num){
                qtdEstoque++;
            }
        }
        printf("\nO produto do codigo %d tem %d em nosso estoque\n",num,qtdEstoque);
    }
    else{
        printf("Não há produto algum em nosso estoque\n");
    }
    
}

void produtoVencido(material produto[], int *numMaterial) {
    int verificador=0;
    time_t agora = time(NULL);
    struct tm *data_atual = localtime(&agora);
    if(*numMaterial>0){

        for (int i = 0; i < *numMaterial; i++) {
            struct tm data_validade = converteData(produto[i].validade);

            time_t validade_t = mktime(&data_validade);
            time_t atual_t = mktime(data_atual);

            if (validade_t < atual_t) {
                printf("[PRODUTOS QUE JÁ VENCERAM]\n");
                    printf("Nome do produto: %s",produto[i].nomeProduto);
                    printf("Codigo do produto: %d\n",produto[i].codigo);
                    printf("Validade do produto: %s\n",produto[i].validade);
                    printf("Valor do produto: %.2f\n",produto[i].valor);
                    verificador++;
            } 
        }
    }  
    else if(verificador==0){
        printf("\n[NÃO HÁ NENHUM PRODUTO VENCIDO]\n");
    }
     else{
          printf("\n[NÃO TEM NENHUM MATERIAL PARA SER CONSULTADO]\n");
     }
}
void consultaDias(material produto[], int *numMaterial){
    int num;
    int encontrou=0;
    if(*numMaterial>0){
        printf("\nINSIRA O VALOR DE DIAS PARA O VENCIMENTO QUE DESEJA CONSULTAR:\n");
        scanf("%d",&num);
        int teste=0;
        time_t agora = time(NULL);
        struct tm *data_atual = localtime(&agora);

        for (int i = 0; i < *numMaterial; i++) {
            struct tm data_validade = converteData(produto[i].validade);

            time_t validade_t = mktime(&data_validade);
            time_t atual_t = mktime(data_atual);
             teste = difftime(validade_t, atual_t);
                teste = teste /(60 * 60 * 24);
                teste++;
            if (teste==num) {
               printf("[PRODUTOS QUE FALTAM %d DIAS PARA VENCER]\n",num);
                printf("Nome do produto: %s",produto[i].nomeProduto);
                printf("Codigo do produto: %d\n",produto[i].codigo);
                printf("Validade do produto: %s\n",produto[i].validade);
                printf("Valor do produto: %.2f\n",produto[i].valor);
            } 
            else if(encontrou==0){
                printf("NÃO HÁ NENHUM PRODUTO NESSA FAIXA DE DIAS\n");
            }
        }
    }
    else{
        printf("\n[NÃO TEM NENHUM MATERIAL PARA SER CONSULTADO]\n");
    }
}

void vendaMaterial(material produto[], int *numMaterial){
    int contaValores=0;
    int maximo;
    int achou = 0;
    if(*numMaterial>0){
         printf("\nMATERIAIS A SEREM VENDIDOS:\n");
        for (int i = 0; i < *numMaterial; i++)
        {
            printf("CODIGO %d, ",produto[i].codigo);
            printf("NOME: %s \n",produto[i].nomeProduto);
        }
        do{
            printf("QUANTOS PRODUTOS DESEJA COMPRAR? \n");
            scanf("%d",&maximo);
            maximo-=1;
            if(maximo<=*numMaterial){
                int contador =0;
                int vetor[maximo-1];
                int valor;
                while(contador<=maximo+1){
                    printf("INSIRA O CODIGO DE CADA PRODUTO QUE DESEJA COMPRAR: ");
                    scanf("%d",&valor);
                    for (int i = 0; i < *numMaterial; i++)
                    {
                        if(valor==produto[i].codigo){
                            vetor[contador]=valor;
                            contador++;
                            achou++;
                            contaValores+=achou;
                        }
                    }
                    if(achou==0){
                        printf("\n[O CODIGO QUE VOCE DIGITOU NÃO EXISTE, INSIRA NOVAMENTE]\n");
                    }
                    else{
                        contador++;
                        achou--;
                    }
                }
                
            }
            else{
                printf("\n[NUMERO DE PRODUTOS MAIOR DO QUE ESTOQUE]\n");
            }
        }while(contaValores<=maximo);
    }
    else{
        printf("[NÃO TEM MATERIAIS PARA SEREM VENDIDOS]\n");
    }
}