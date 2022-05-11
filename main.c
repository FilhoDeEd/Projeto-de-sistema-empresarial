#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_f 500
#define MAX_p 2000

typedef struct f{
    int num_func;
    char nome_func[50];
    float salario;
}func;

typedef struct p {
    char nome_proj[50];
    int data_inc[3];
    int data_term[3];
    int tempo_estim;
    float valor_estim;
    int func_resp;
}proj;

void remocao_func() {
    system("cls");
    printf("\nREMOCAO DE FUNCIONARIO.\n");
    system("pause");
}

void remocao_proj() {
    system("cls");
    printf("\nREMOCAO DE PROJETO.\n");
    system("pause");
}

void insercao_func() {
    system("cls");
    printf("\nINSERCAO DE FUNCIONARIO.\n");
    system("pause");
}

void insercao_proj() {
    system("cls");
    printf("\nINSERCAO DE PROJETO.\n");
    system("pause");
}

void edicao_func(func *vet) {
    system("cls");

    int i, num_func_chave;
    char tecla;

    printf("Digite o numero funcional do funcionario: ");
    scanf("%d",&num_func_chave);

    system("cls");

    for(i=0; i<MAX_f; i++)
    {
        if(vet[i].num_func == num_func_chave) break;
    }
    if(i==MAX_f)
    {
        printf("Funcionario nao encontrado.");
        system("pause");
        return;
    }

    printf("Voce esta editando as informacoes do(a) funcionario(a) %d:\n",vet[i].num_func);
    printf("\tFuncionario(a): %s\n",vet[i].nome_func);
    printf("\tSalario: %.2f\n\n",vet[i].salario);
    printf("Pressione qualquer tecla para continuar a edicao ou 'q' para cancelar...");

    tecla = getch();

    if(tecla=='q') return;

    system("cls");

    printf("Funcionario(a) %d:\n",vet[i].num_func);
    fflush(stdin);
    printf("\tDigite o novo nome: ");
    scanf("%[^\n]s",&vet[i].nome_func);
    printf("\tDigite o novo salario: ");
    scanf("%f",&vet[i].salario);

    system("cls");

    printf("Edicao feita com sucesso.\n");

    system("pause");
}

void edicao_proj(proj *vet){
    system("cls");

    int i;
    char *nome_proj_chave;
    char tecla;

    printf("Digite o nome do projeto: ");
    scanf("%[^\n]s",nome_proj_chave);


    system("pause");
}

void interface_2(func *vet_func, proj *vet_proj, int i){
    char tecla;
    do{
        system("cls");
        printf("Escolha uma funcao: \n");
        printf("Pressione 'a' para alterar dados\n");
        printf("Pressione 'b' para inserir dados\n");
        printf("Pressione 'c' para remover dados\n");
        printf("Pressione 'q' para retornar a inferface inicial\n");

        tecla = getch();

        switch(tecla)
        {
        case 'a': i==1 ? edicao_func(vet_func) : edicao_proj(vet_proj);
            break;
        case 'b': i==1 ? insercao_func() : insercao_proj();
            break;
        case 'c': i==1 ? remocao_func() : remocao_proj();
            break;
        case 'q':
            break;
        default: {
                    system("cls");
                    printf("\nEscolha invalida.\n");
                    system("pause");
                 }
        }
    }while(tecla!='q');
}

void interface(func *vet_func, proj *vet_proj)
{
    char tecla;

    do{
        system("cls");
        printf("Escolha entre funcionario e projeto: \n");
        printf("Pressione 'a' para funcionarios\n");
        printf("Pressione 'b' para projetos\n");
        printf("Pressione 'q' para sair\n");

        tecla = getch();

        switch(tecla)
        {
        case 'a': interface_2(vet_func, vet_proj, 1);
            break;
        case 'b': interface_2(vet_func, vet_proj, 2);
            break;
        case 'q':  printf("\nPrograma encerrado.\n");
            break;
        default: {
                    system("cls");
                    printf("\nEscolha invalida.\n");
                    system("pause");
                 }
        }

    }while(tecla!='q');
}

int main()
{
    int abc = 32;
    func funcionarios[MAX_f];
    proj projetos[MAX_p];

    funcionarios[5].num_func = 344;
    strcpy(funcionarios[5].nome_func,"Rafaela");
    funcionarios[5].salario = 3500.89;

    interface(funcionarios, projetos);
    return 0;
}
