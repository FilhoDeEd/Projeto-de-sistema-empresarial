#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
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

void insercao_func(func *vet, int *qtdFunc) {
    system("cls");

    int i, j, k, num_func_in, zero;
    char nome_func_in[50];
    float salario_in;

    printf ("Declare o n�mero funcional do funcionario:\n");
    scanf ("%d", &num_func_in);

    printf("Escreva o nome do funcion�rio:\n");
    fflush(stdin);
    scanf ("%[^\n]s",nome_func_in);

    printf ("Declare o sal�rio do funcion�rio:\n");
    scanf ("%f",&salario_in);

    

    system ("cls");

    for (i=0;i<MAX_f;i++)
    {
        if (vet[i].num_func==0)break;
        if (vet[i].num_func>num_func_in)break;
    }

    if (vet[i].num_func==0){
        vet[i].num_func=num_func_in;
        vet[i].salario=salario_in;
        strcpy(vet[i].nome_func,nome_func_in);

        system("cls");
        (*qtdFunc)++;
        printf("Funcion�rio inserido com sucesso\n");
        system ("pause");
        return;
     }

    for (j=0;j<MAX_f;j++){  //procura da posição de valor 0
        if (vet[j].num_func==0){
            zero=j;
            break;
        }
    }

    vet[zero+1].num_func=0; 

    for(k=zero;k>i;k--){
        vet[k].num_func=vet[k-1].num_func;
        vet[k].salario=vet[k-1].salario;
        strcpy(vet[k].nome_func,vet[k-1].nome_func);
     }

    vet[i].num_func=num_func_in;
    vet[i].salario=salario_in;
    strcpy(vet[i].nome_func,nome_func_in);

    system("cls");
    (*qtdFunc)++;
    printf("Funcion�rio inserido com sucesso\n");
    system("pause");
}

void insercao_proj(proj *vet, int *qtdProj) {
    system("cls");

    char nome_proj_in[50];
    int data_inc_in[3], data_term_in[3], tempo_estim_in, func_resp_in;
    int i,j,k, fim;
    float valor_estim_in;
    
    printf ("Declare o nome do novo projeto:\n");
    fflush(stdin);
    scanf ("%[^\n]s", nome_proj_in);

    printf("Declare o funcion�rio responsável:\n");
    fflush(stdin);
    scanf ("%d",func_resp_in);

    printf ("Declare o valor estimado do projeto:\n");
    scanf ("%f",&valor_estim_in);

    printf("\tDigite a data de inicio:\n");
    printf("\t\tDia:");
    scanf("%d",&vet[i].data_inc[0]);
    printf("\b\t\tMes:");
    scanf("%d",&vet[i].data_inc[1]);
    printf("\b\t\tAno:");
    scanf("%d",&vet[i].data_inc[2]);

    printf("\tDigite a data de termino:\n");
    printf("\t\tDia:");
    scanf("%d",&vet[i].data_term[0]);
    printf("\b\t\tMes:");
    scanf("%d",&vet[i].data_term[1]);
    printf("\b\t\tAno:");
    scanf("%d",&vet[i].data_term[2]);

    printf ("Acrescente o tempo estimado em meses para conclusão de projeto:");
    scanf ("%d",&tempo_estim_in);

    system ("cls");

    for (i=0;i<MAX_p;i++){
        if (strcmp(vet[i].nome_proj,"Fim")==0) break;
        if (strcmp(vet[i].nome_proj,nome_proj_in)>0) break;
    }
        if (strcmp(vet[i].nome_proj,"Fim")==0) {
            vet[i].valor_estim=valor_estim_in;
            strcpy(vet[i].nome_proj,nome_proj_in);

            for ( j = 0; j < 3; j++) //inserir datas de entrada na posição correta
            {
                vet[i].data_inc[j]=data_inc_in[j];
                vet[i].data_term[j]=data_term_in[j];
            }
            vet[i].tempo_estim=tempo_estim_in;
            vet[i].func_resp=func_resp_in;

        system("cls");
        (qtdProj)++;
        printf("Projeto inserido com sucesso\n");
        system ("pause");
        return;
        }

        fim=qtdProj;

    for(k = fim;k > i;k--){
        strcpy(vet[k].nome_proj,vet[k-1].nome_proj);
        vet[k].valor_estim=vet[k-1].valor_estim;
        vet[k].func_resp=vet[k-1].func_resp;
        
    for (j = 0;j < 3;j++)
        {
            vet[k].data_inc[j]=vet[k-1].data_inc[j];
            vet[k].data_term[j]=vet[k-1].data_term[j];
        }
    vet[k].tempo_estim=vet[k-1].valor_estim;
    }

    for ( j = 0; j < 3; j++){
        vet[i].data_inc[j]=data_inc_in[j];
        vet[i].data_term[j]=data_term_in[j];
    }
    vet[i].tempo_estim=tempo_estim_in;
    vet[i].func_resp=func_resp_in;
    strcpy (vet[i].nome_proj,nome_proj_in);
    vet[i].valor_estim=valor_estim_in;
    
    system("cls");
    (qtdProj)++;
    printf("Funcion�rio inserido com sucesso\n");
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
    printf("Pressione qualquer tecla para continuar a edicao ou 'q' para cancelar");

    tecla = getch();

    if(tecla=='q') return;

    system("cls");

    printf("Funcionario(a) %d:\n",vet[i].num_func);
    fflush(stdin);
    printf("\tDigite o novo nome: ");
    scanf("%[^\n]s",vet[i].nome_func);
    printf("\tDigite o novo salario: ");
    scanf("%f",&vet[i].salario);

    system("cls");

    printf("Edicao feita com sucesso.\n");

    system("pause");
}

void edicao_proj(proj *vet){
    system("cls");

    int i;
    char nome_proj_chave[50];
    char tecla;

    printf("Digite o nome do projeto: ");
    fflush(stdin);
    scanf("%[^\n]s",nome_proj_chave);

    system("cls");

    for(i=0; i<MAX_p; i++)
    {
        if(strcmp(nome_proj_chave, vet[i].nome_proj)==0) break;
    }
    if(i==MAX_p)
    {
        printf("Projeto n�o encontrado.");
        system("pause");
        return;
    }

    printf("Voce esta editando as informacoes do projeto %s:\n",vet[i].nome_proj);
    printf("\tFuncionario responsavel: %d\n",vet[i].func_resp);
    printf("\tData de inicio: %0.2d/%0.2d/%d\n\n",vet[i].data_inc[0],vet[i].data_inc[1],vet[i].data_inc[2]);
    printf("\tData de termino: %0.2d/%0.2d/%d\n\n",vet[i].data_term[0],vet[i].data_term[1],vet[i].data_term[2]);
    printf("\tTempo estimado: %d meses\n",vet[i].tempo_estim);
    printf("\tValor estimado: %.2f\n",vet[i].valor_estim);
    printf("Pressione qualquer tecla para continuar a edicao ou 'q' para cancelar");

    tecla = getch();

    if(tecla=='q') return;

    system("cls");

    printf("Projeto: %s\n",vet[i].nome_proj);
    printf("\tDigite o numero funcional do funcionario responsavel:");
    scanf("%d",&vet[i].func_resp);

    printf("\tDigite a data de inicio:\n");
    printf("\t\tDia:");
    scanf("%d",&vet[i].data_inc[0]);
    printf("\b\t\tMes:");
    scanf("%d",&vet[i].data_inc[1]);
    printf("\b\t\tAno:");
    scanf("%d",&vet[i].data_inc[2]);

    printf("\tDigite a data de termino:\n");
    printf("\t\tDia:");
    scanf("%d",&vet[i].data_term[0]);
    printf("\b\t\tMes:");
    scanf("%d",&vet[i].data_term[1]);
    printf("\b\t\tAno:");
    scanf("%d",&vet[i].data_term[2]);

    printf("\tDigite o tempo estimado em meses:\n");
    scanf("%d",&vet[i].tempo_estim);

    printf("\tDigite o vamor estimado:\n");
    scanf("%f",&vet[i].valor_estim);

    system("cls");

    printf("Edicao feita com sucesso.\n");

    system("pause");
}

void interface_2(func *vet_func, proj *vet_proj, int i, int *qtdFunc, int *qtdProj)
{
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
        case 'b': i==1 ? insercao_func(vet_func, qtdFunc) : insercao_proj(vet_proj, qtdProj);
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

void interface(func *vet_func, proj *vet_proj, int *qtdFunc, int *qtdProj)
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
        case 'a': interface_2(vet_func, vet_proj, 1, qtdFunc, qtdProj);
            break;
        case 'b': interface_2(vet_func, vet_proj, 2, qtdFunc, qtdProj);
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

void carregarFunc(struct f funcionarios[],int *qtdFunc)
{
    FILE *bin;
    bin = fopen("listaFunc","rb");
    if(!bin){
        printf("Nao foi possivel carregar as informacoes do disco.\n");
        return;
    }
    fread(qtdFunc,sizeof(int),1,bin);
    fread(funcionarios, sizeof(struct f), *qtdFunc, bin);

    fclose(bin);
}

void salvarFunc(struct f funcionarios[],int qtdFunc)
{
    FILE *bin;
    bin = fopen("listaFunc","wb");
    if(!bin){
        printf("Nao foi possivel salvar as informacoes do estoque em disco.\n");
        exit(1);
    }
    fwrite(&qtdFunc,sizeof(int),1,bin);
    fwrite(funcionarios, sizeof(struct f), qtdFunc, bin);

    fclose(bin);
}

int main()
{
    setlocale (LC_ALL,"Portuguese");
    func funcionarios[MAX_f];
    proj projetos[MAX_p];
    int qtdFunc;
    int qtdProj;

    carregarFunc(funcionarios, &qtdFunc);
    //carregarProj(projetos, &qtdProj);
    
    interface(funcionarios, projetos, &qtdFunc, &qtdProj);
    salvarFunc(funcionarios, qtdFunc);
    return 0;
}
