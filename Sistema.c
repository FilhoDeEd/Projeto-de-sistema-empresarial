///Bibliotecas utilizadas:
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

///Máximo de funcionários e projetos respectivamente:
#define MAX_f 500
#define MAX_p 2000

typedef struct f{
    int num_func;
    char nome_func[50];
    float salario;
}func;

typedef struct p{
    char nome_proj[50];
    int data_inc[3];
    int data_term[3];
    int tempo_estim;
    float valor_estim;
    int func_resp;
}proj;

void carregarFunc(func *funcionarios,int *qtdFunc);
void salvarFunc(func *funcionarios,int qtdFunc);
void carregarProj(proj *projetos,int *qtdProj);
void salvarProj(proj *projetos,int qtdProj);

void edicao_func(func *vet);
void edicao_proj(proj *vet);

void insercao_func(func *vet, int *qtdFunc);
void insercao_proj(proj *vet, int *qtdProj);

void interface(func *vet_func, proj *vet_proj, int *qtdFunc, int *qtdProj);
void interface_2(func *vet_func, proj *vet_proj, int i, int *qtdFunc, int *qtdProj);

void lista_func(func *vet, int *qtdFunc);
void lista_proj(proj *vet, int *qtdProj);

void remocao_func();
void remocao_proj();

///Interface em terminal
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
                    printf("\nEscolha inválida.\n");
                    system("pause");
                 }
        }

    }while(tecla!='q');
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
        printf("Pressione 'd' para listar dados\n");
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
        case 'd': i==1 ? lista_func(vet_func, qtdFunc) : lista_proj(vet_proj, qtdProj);
            break;
        case 'q':
            break;
        default: {
                    system("cls");
                    printf("\nEscolha inválida.\n");
                    system("pause");
                 }
        }
        
    }while(tecla!='q');
}

///Inserir um novo elemento
void insercao_func(func *vet, int *qtdFunc)
{
    system("cls");

    int i, j, k, num_func_in;
    char nome_func_in[50];
    float salario_in;

    //Coletando informações a de entrada
    printf("Declare o número funcional do funcionario: ");
    scanf("%d", &num_func_in);

    printf("Escreva o nome do funcionário: ");
    fflush(stdin);
    scanf("%[^\n]s",nome_func_in);

    printf("Declare o salário do funcionário: ");
    scanf("%f",&salario_in);

    system("cls");

    //Procura pela posição do valor a ser inserido no vetor
    for (i=0; i<*qtdFunc; i++)
    {
        if (vet[i].num_func>num_func_in) break;
    }

    //for para ajustar o vetor caso necessário
    for(k=*qtdFunc; k>i; k--)
    {
        vet[k].num_func = vet[k-1].num_func;
        vet[k].salario = vet[k-1].salario;
        strcpy(vet[k].nome_func, vet[k-1].nome_func);
    }

    //Inserindo os valores de entrada na posição correta:
    vet[i].num_func = num_func_in;
    vet[i].salario = salario_in;
    strcpy(vet[i].nome_func, nome_func_in);

    (*qtdFunc)++;
    system("cls");
    printf("Funcionário inserido com sucesso.\n");
    system("pause");
}

void insercao_proj(proj *vet, int *qtdProj)
{
    system("cls");

    int i,j,k;
    char nome_proj_in[50];
    int data_inc_in[3], data_term_in[3], tempo_estim_in, func_resp_in;
    float valor_estim_in;

    //Coletando informações a de entrada
    printf("Declare o nome do novo projeto: ");
    fflush(stdin);
    scanf("%[^\n]s", nome_proj_in);

    printf("Declare o funcionário responsável: ");
    scanf("%d",&func_resp_in);

    printf("Declare o valor estimado do projeto: ");
    scanf("%f",&valor_estim_in);

    printf("\tDigite a data de inicio: ");
    printf("\t\tDia: ");
    scanf("%d",&data_inc_in[0]);
    printf("\b\t\tMês: ");
    scanf("%d",&data_inc_in[1]);
    printf("\b\t\tAno: ");
    scanf("%d",&data_inc_in[2]);

    printf("\tDigite a data de termino:\n");
    printf("\t\tDia: ");
    scanf("%d",&data_term_in[0]);
    printf("\b\t\tMês: ");
    scanf("%d",&data_term_in[1]);
    printf("\b\t\tAno: ");
    scanf("%d",&data_term_in[2]);

    printf("Acrescente o tempo estimado em meses para conclusão de projeto: ");
    scanf("%d",&tempo_estim_in);

    system("cls");

    //Procura pela posição do valor a ser inserido no vetor
    for (i=0; i<*qtdProj; i++)
    {
        if(strcmp(vet[i].nome_proj, nome_proj_in)>0) break;
    }

    //for para ajustar o vetor caso necessário
    for(k=*qtdProj; k>i; k--)
    {
        strcpy(vet[k].nome_proj, vet[k-1].nome_proj);
        vet[k].valor_estim = vet[k-1].valor_estim;
        vet[k].func_resp = vet[k-1].func_resp;

        for (j=0; j<3; j++)
        {
            vet[k].data_inc[j] = vet[k-1].data_inc[j];
            vet[k].data_term[j] = vet[k-1].data_term[j];
        }
        vet[k].tempo_estim = vet[k-1].valor_estim;
    }

    //Inserindo os valores de entrada na posição correta:
    for(j=0; j<3; j++)
    {
        vet[i].data_inc[j] = data_inc_in[j];
        vet[i].data_term[j] = data_term_in[j];
    }
    vet[i].tempo_estim = tempo_estim_in;
    vet[i].func_resp = func_resp_in;
    strcpy(vet[i].nome_proj, nome_proj_in);
    vet[i].valor_estim = valor_estim_in;

    (*qtdProj)++;
    system("cls");
    printf("Projeto inserido com sucesso.\n");
    system("pause");
}

///Editar um elemento
void edicao_func(func *vet)
{
    system("cls");

    int i, num_func_chave;
    char tecla;

    //Busca sequencial pelo funcionário que se quer editar
    printf("Digite o número funcional do funcionário: ");
    scanf("%d",&num_func_chave);

    system("cls");

    for(i=0; i<MAX_f; i++)
    {
        if(vet[i].num_func == num_func_chave) break;
    }

    if(i==MAX_f)
    {
        printf("Funcionário não encontrado.\n");
        system("pause");
        return;
    }

    //Caso o funcionário seja encontrado, aqui você pode confirmar as informações sobre ele e escolher continuar
    printf("Você está editando as informações do(a) funcionário(a) %d:\n",vet[i].num_func);
    printf("\tFuncionário(a): %s\n",vet[i].nome_func);
    printf("\tSalário: %.2f\n\n",vet[i].salario);
    printf("Pressione qualquer tecla para continuar a edição ou 'q' para cancelar");

    tecla = getch();
    if(tecla=='q') return;

    system("cls");

    //Coletando as novas informações sobre o funcionário e já realizando as alterações
    printf("Funcionário(a) %d:\n",vet[i].num_func);
    fflush(stdin);
    printf("\tDigite o novo nome: ");
    scanf("%[^\n]s",vet[i].nome_func);
    printf("\tDigite o novo salário: ");
    scanf("%f",&vet[i].salario);

    system("cls");
    printf("Edição feita com sucesso.\n");
    system("pause");
}

void edicao_proj(proj *vet)
{
    system("cls");

    int i;
    char nome_proj_chave[50];
    char tecla;

    //Busca sequencial pelo projeto que se quer editar
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
        printf("Projeto não encontrado.\n");
        system("pause");
        return;
    }

    //Caso o projeto seja encontrado, aqui você pode confirmar as informações sobre ele e escolher continuar
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

    //Coletando as novas informações sobre o projeto e já realizando as alterações
    printf("Projeto: %s\n",vet[i].nome_proj);
    printf("\tDigite o novo número funcional do funcionário responsável: ");
    scanf("%d",&vet[i].func_resp);

    printf("\tDigite a nova data de início:\n");
    printf("\t\tDia:");
    scanf("%d",&vet[i].data_inc[0]);
    printf("\b\t\tMês:");
    scanf("%d",&vet[i].data_inc[1]);
    printf("\b\t\tAno:");
    scanf("%d",&vet[i].data_inc[2]);

    printf("\tDigite a nova data de término:\n");
    printf("\t\tDia:");
    scanf("%d",&vet[i].data_term[0]);
    printf("\b\t\tMês:");
    scanf("%d",&vet[i].data_term[1]);
    printf("\b\t\tAno:");
    scanf("%d",&vet[i].data_term[2]);

    printf("\tDigite o novo tempo estimado em meses: ");
    scanf("%d",&vet[i].tempo_estim);

    printf("\tDigite o novo valor estimado: ");
    scanf("%f",&vet[i].valor_estim);

    system("cls");
    printf("Edição feita com sucesso.\n");
    system("pause");
}

///Remover um elemento
void remocao_func()
{
    system("cls");
    printf("\nREMOCAO DE FUNCIONARIO.\n");
    system("pause");
}

void remocao_proj()
{
    system("cls");
    printf("\nREMOCAO DE PROJETO.\n");
    system("pause");
}

///Listar os elementos
void lista_func(func *vet, int *qtdFunc)
{
    system("cls");

    if(*qtdFunc==0)
    {
        printf("Não há funcionários(as) cadastrados(as).\n");
        system("pause");
        return;
    }

    int i;

    printf("Funcion�rios:\n");
    for(i=0; i<*qtdFunc; i++)
    {
        printf("\n\tNome: %s",vet[i].nome_func);
        printf("\n\tN�mero funcional: %d",vet[i].num_func);
        printf("\n\tSal�rio: %.2f\n",vet[i].salario);
    }

    system("pause");
}

void lista_proj(proj *vet, int *qtdProj)
{
    system("cls");

    if(*qtdProj==0)
    {
        printf("Não há projetos cadastrados.\n");
        system("pause");
        return;
    }

    int i;

    printf("Projetos:\n");
    for(i=0; i<*qtdProj; i++)
    {
        printf("\n\tNome: %s",vet[i].nome_proj);
        printf("\n\tFuncion�rio respons�vel: %d",vet[i].func_resp);
        printf("\n\tData de in�cio: %0.2d/%0.2d/%d",vet[i].data_inc[0],vet[i].data_inc[1],vet[i].data_inc[2]);
        printf("\n\tData de t�rmino: %0.2d/%0.2d/%d",vet[i].data_term[0],vet[i].data_term[1],vet[i].data_term[2]);
        printf("\n\tTempo estimado: %d meses",vet[i].tempo_estim);
        printf("\n\tValor estimado: R$ %.2f\n",vet[i].valor_estim);
    }

    system("pause");
}

///Carregar/Salvar os elementos em arquivos binários
void carregarFunc(func *funcionarios,int *qtdFunc)
{
    FILE *bin;
    bin = fopen("listaFunc","rb");
    if(!bin){
        printf("Não foi possível carregar as informações.\n");
        system("pause");
        return;
    }
    fread(qtdFunc,sizeof(int),1,bin);
    fread(funcionarios, sizeof(struct f), *qtdFunc, bin);

    fclose(bin);
}

void salvarFunc(func *funcionarios,int qtdFunc)
{
    FILE *bin;
    bin = fopen("listaFunc","wb");
    if(!bin){
        printf("Não foi possível salvar as informações.\n");
        system("pause");
        exit(1);
    }
    fwrite(&qtdFunc,sizeof(int),1,bin);
    fwrite(funcionarios, sizeof(struct f), qtdFunc, bin);

    fclose(bin);
}

void carregarProj(proj *projetos,int *qtdProj)
{
    FILE *bin;
    bin = fopen("listaProj","rb");
    if(!bin){
        printf("Não foi possível carregar as informações.\n");
        system("pause");
        return;
    }
    fread(qtdProj,sizeof(int),1,bin);
    fread(projetos, sizeof(struct p), *qtdProj, bin);

    fclose(bin);
}

void salvarProj(proj *projetos,int qtdProj)
{
    FILE *bin;
    bin = fopen("listaProj","wb");
    if(!bin){
        printf("Não foi possível salvar as informações.\n");
        system("pause");
        exit(1);
    }
    fwrite(&qtdProj,sizeof(int),1,bin);
    fwrite(projetos, sizeof(struct p), qtdProj, bin);

    fclose(bin);
}

int main()
{
    setlocale(LC_ALL,"Portuguese");

    func funcionarios[MAX_f];
    proj projetos[MAX_p];
    int qtdFunc=0;
    int qtdProj=0;

    carregarFunc(funcionarios, &qtdFunc);
    carregarProj(projetos, &qtdProj);
    
    interface(funcionarios, projetos, &qtdFunc, &qtdProj);

    salvarFunc(funcionarios, qtdFunc);
    salvarProj(projetos, qtdProj);

    printf("quantidade de projetos: %d quantidade de funcionarios: %d", qtdProj, qtdFunc);
    return 0;
}