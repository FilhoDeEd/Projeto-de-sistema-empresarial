#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <wchar.h>
#include <conio.h>

#define MAX_f 500
#define MAX_p 2000

typedef struct f{
    int num_func;
    char nome_func[50];
    float salario;
    int deletado_func;
}func;

typedef struct p{
    char nome_proj[50];
    int data_inc[3];
    int data_term[3];
    int tempo_estim;
    float valor_estim;
    int func_resp;
    int deletado_proj;
}proj;

void carregarFunc(func *funcionarios,int *qtdFunc);
void salvarFunc(func *funcionarios,int qtdFunc);
void carregarProj(proj *projetos,int *qtdProj);
void salvarProj(proj *projetos,int qtdProj);

void edicao_func(func *vet, int *qtdFunc);
void edicao_proj(proj *vet, int *qtdProj);

void insercao_func(func *vet, int *qtdFunc);
void insercao_proj(proj *vet, int *qtdProj);

void interface(func *vet_func, proj *vet_proj, int *qtdFunc, int *qtdProj);
void interface_2(func *vet_func, proj *vet_proj, int i, int *qtdFunc, int *qtdProj);

void listar_func(func *vet, int *qtdFunc);
void listar_proj(proj *vet, int *qtdProj);

void remocao_func(func *vet, int *qtdFunc);
void remocao_proj(proj *vet, int *qtdProj);

///Interface em terminal
void interface(func *vet_func, proj *vet_proj, int *qtdFunc, int *qtdProj)
{
    char tecla;

    do{
        system("cls");
        wprintf(L"Escolha entre funcionários ou projetos: \n");
        wprintf(L"Pressione 'a' para funcionários\n");
        wprintf(L"Pressione 'b' para projetos\n");
        wprintf(L"Pressione 'q' para sair\n");

        tecla = getch();

        switch(tecla)
        {
        case 'a': interface_2(vet_func, vet_proj, 1, qtdFunc, qtdProj);
            break;
        case 'b': interface_2(vet_func, vet_proj, 2, qtdFunc, qtdProj);
            break;
        case 'q':  wprintf(L"\nPrograma encerrado.\n");
            break;
        default: {
                    system("cls");
                    wprintf(L"\nEscolha inválida.\n");
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
        if(i==1) wprintf(L"Funcionários\n\n");
        else wprintf(L"Projetos\n\n");
        wprintf(L"Escolha uma função: \n");
        wprintf(L"Pressione 'a' para alterar dados\n");
        wprintf(L"Pressione 'b' para inserir dados\n");
        wprintf(L"Pressione 'c' para remover dados\n");
        wprintf(L"Pressione 'd' para listar dados\n");
        wprintf(L"Pressione 'q' para retornar a inferface inicial\n");

        tecla = getch();

        switch(tecla)
        {
        case 'a': i==1 ? edicao_func(vet_func, qtdFunc) : edicao_proj(vet_proj, qtdProj);
            break;
        case 'b': i==1 ? insercao_func(vet_func, qtdFunc) : insercao_proj(vet_proj, qtdProj);
            break;
        case 'c': i==1 ? remocao_func(vet_func, qtdFunc) : remocao_proj(vet_proj, qtdProj);
            break;
        case 'd': i==1 ? listar_func(vet_func, qtdFunc) : listar_proj(vet_proj, qtdProj);
            break;
        case 'q':
            break;
        default: {
                    system("cls");
                    wprintf(L"\nEscolha inválida.\n");
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
    wprintf(L"Declare o número funcional do(a) funcionário(a): ");
    fflush(stdin);
    scanf("%d", &num_func_in);

    wprintf(L"Escreva o nome do(a) funcionário(a): ");
    fflush(stdin);
    scanf("%[^\n]s",nome_func_in);

    wprintf(L"Declare o salário do(a) funcionário(a): ");
    scanf("%f",&salario_in);

    system("cls");

    //Procura pela posição do valor a ser inserido no vetor
    for(i=0; i<*qtdFunc; i++)
    {
        if(vet[i].num_func>num_func_in) break;
    }

    //for para ajustar o vetor caso necessário
    for(k=*qtdFunc; k>i; k--)
    {
        vet[k].num_func = vet[k-1].num_func;
        vet[k].salario = vet[k-1].salario;
        strcpy(vet[k].nome_func, vet[k-1].nome_func);
        vet[k].deletado_func = vet[k-1].deletado_func;
    }

    //Inserindo os valores de entrada na posição correta:
    vet[i].num_func = num_func_in;
    vet[i].salario = salario_in;
    strcpy(vet[i].nome_func, nome_func_in);
    vet[i].deletado_func = 0;

    (*qtdFunc)++;
    system("cls");
    wprintf(L"Funcionário(a) cadastrado(a) com sucesso.\n\n");
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
    wprintf(L"Declare o nome do projeto: ");
    fflush(stdin);
    scanf("%[^\n]s", nome_proj_in);

    wprintf(L"Declare o funcionário(a) responsável: ");
    scanf("%d",&func_resp_in);

    wprintf(L"Declare o valor estimado do projeto: ");
    scanf("%f",&valor_estim_in);

    wprintf(L"Digite a data de início:\n");
    wprintf(L"\tDia: ");
    scanf("%d",&data_inc_in[0]);
    wprintf(L"\tMês: ");
    scanf("%d",&data_inc_in[1]);
    wprintf(L"\tAno: ");
    scanf("%d",&data_inc_in[2]);

    wprintf(L"Digite a data de término:\n");
    wprintf(L"\tDia: ");
    scanf("%d",&data_term_in[0]);
    wprintf(L"\tMês: ");
    scanf("%d",&data_term_in[1]);
    wprintf(L"\tAno: ");
    scanf("%d",&data_term_in[2]);

    wprintf(L"Acrescente o tempo estimado em meses para conclusão do projeto: ");
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
        vet[k].tempo_estim = vet[k-1].valor_estim;
        vet[k].deletado_proj = vet[k-1].deletado_proj;

        for(j=0; j<3; j++)
        {
            vet[k].data_inc[j] = vet[k-1].data_inc[j];
            vet[k].data_term[j] = vet[k-1].data_term[j];
        }
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
    vet[i].deletado_proj = 0;

    (*qtdProj)++;
    system("cls");
    wprintf(L"Projeto cadastrado com sucesso.\n\n");
    system("pause");
}

///Editar um elemento
void edicao_func(func *vet, int *qtdFunc)
{
    system("cls");

    int i, num_func_chave;
    char tecla;

    //Busca sequencial pelo funcionário que se quer editar
    wprintf(L"Digite o número funcional do(a) funcionário(a): ");
    fflush(stdin);
    scanf("%d",&num_func_chave);

    system("cls");

    for(i=0; i<*qtdFunc; i++)
    {
        if(!vet[i].deletado_func && vet[i].num_func == num_func_chave) break;
    }

    if(i==*qtdFunc)
    {
        wprintf(L"Funcionário(a) não encontrado(a).\n");
        system("pause");
        return;
    }

    //Caso o funcionário seja encontrado, aqui você pode confirmar as informações sobre ele e escolher continuar
    wprintf(L"Você está editando as informações do(a) funcionário(a) %d:\n",vet[i].num_func);
    wprintf(L"\tFuncionário(a): %S\n",vet[i].nome_func);
    wprintf(L"\tSalário: %.2f\n\n",vet[i].salario);
    wprintf(L"Pressione qualquer tecla para continuar a edição ou 'q' para cancelar");

    tecla = getch();
    if(tecla=='q') return;

    system("cls");

    //Coletando as novas informações sobre o funcionário e já realizando as alterações
    wprintf(L"Funcionário(a) %d:\n",vet[i].num_func);
    fflush(stdin);
    wprintf(L"\tEscreva o novo nome: ");
    scanf("%[^\n]s",vet[i].nome_func);
    wprintf(L"\tDeclare o novo salário: ");
    scanf("%f",&vet[i].salario);

    system("cls");
    wprintf(L"Edição feita com sucesso.\n");
    system("pause");
}

void edicao_proj(proj *vet, int *qtdProj)
{
    system("cls");

    int i, j, achoAlgo = 0, valido = 1;
    char tecla, nome_proj_chave[50];

    wprintf(L"Escreva o nome do projeto ou uma parte desse: ");
    fflush(stdin);
    scanf("%[^\n]s",nome_proj_chave);

    //Interface de procura de projetos melhorada (não é preciso saber o nome exato do projeto)
    for(i=0; i<*qtdProj; i++)
    {
        if(!vet[i].deletado_proj && strstr(vet[i].nome_proj, nome_proj_chave)!=NULL)
        {
            //Esse if garante que eu só vou printar uma vez "Projetos encontrados"
            if(achoAlgo==0)
            {
                wprintf(L"Projetos encontrados:\n\n");
                achoAlgo++;
            }
            wprintf(L"\t%S (%d)\n",vet[i].nome_proj, i);
        }
    }

    if(!achoAlgo)
    {
        wprintf(L"Não foi encontrado nenhum projeto correspondente.\n\n");
        system("pause");
        return;
    }
    else
    {
        wprintf(L"\nEscolha um projeto através do código numérico: ");
        do
        {
            scanf("%d",&i);
            if(vet[i].deletado_proj || i>*qtdProj) valido = 0;
            else valido = 1;
            if(!valido) wprintf(L"\nDigite um valor válido: ");

        }while(!valido);
        system("cls");
    }

    //Caso o projeto seja encontrado, aqui você pode confirmar as informações sobre ele e escolher continuar
    wprintf(L"Você está editando as informações do projeto %S:\n",vet[i].nome_proj);
    wprintf(L"\tFuncionário(a) responsável: %d\n",vet[i].func_resp);
    wprintf(L"\tData de início: %0.2d/%0.2d/%d\n",vet[i].data_inc[0],vet[i].data_inc[1],vet[i].data_inc[2]);
    wprintf(L"\tData de término: %0.2d/%0.2d/%d\n",vet[i].data_term[0],vet[i].data_term[1],vet[i].data_term[2]);
    wprintf(L"\tTempo estimado: %d meses\n",vet[i].tempo_estim);
    wprintf(L"\tValor estimado: R$ %.2f\n\n",vet[i].valor_estim);
    wprintf(L"Pressione qualquer tecla para continuar a edicao ou 'q' para cancelar");

    tecla = getch();
    if(tecla=='q') return;

    system("cls");

    //Coletando as novas informações sobre o projeto e já realizando as alterações
    wprintf(L"Projeto: %S\n",vet[i].nome_proj);
    wprintf(L"\tDeclare o novo número funcional do(a) funcionário(a) responsável: ");
    scanf("%d",&vet[i].func_resp);

    wprintf(L"\tDigite a nova data de início:\n");
    wprintf(L"\t\tDia:");
    scanf("%d",&vet[i].data_inc[0]);
    wprintf(L"\t\tMês:");
    scanf("%d",&vet[i].data_inc[1]);
    wprintf(L"\t\tAno:");
    scanf("%d",&vet[i].data_inc[2]);

    wprintf(L"\tDigite a nova data de término:\n");
    wprintf(L"\t\tDia:");
    scanf("%d",&vet[i].data_term[0]);
    wprintf(L"\t\tMês:");
    scanf("%d",&vet[i].data_term[1]);
    wprintf(L"\t\tAno:");
    scanf("%d",&vet[i].data_term[2]);

    wprintf(L"\tDeclare o novo tempo estimado em meses: ");
    scanf("%d",&vet[i].tempo_estim);

    wprintf(L"\tDeclare o novo valor estimado: ");
    scanf("%f",&vet[i].valor_estim);

    system("cls");
    wprintf(L"Edição feita com sucesso.\n");
    system("pause");
}

///Remover um elemento
void remocao_func(func *vet, int *qtdFunc)
{
    system("cls");

    int i, num_func_chave;
    char tecla;

    //Busca sequencial pelo funcionário que se quer deletar
    wprintf(L"Digite o número funcional do(a) funcionário(a): ");
    fflush(stdin);
    scanf("%d",&num_func_chave);

    system("cls");

    for(i=0; i<*qtdFunc; i++)
    {
        if(!vet[i].deletado_func && vet[i].num_func == num_func_chave) break;
    }

    if(i==*qtdFunc)
    {
        wprintf(L"Funcionário(a) não encontrado(a).\n");
        system("pause");
        return;
    }

    //Caso o funcionário seja encontrado, aqui você pode confirmar as informações sobre ele e escolher continuar
    wprintf(L"Você está excluindo as informações do(a) funcionário(a) %d:\n",vet[i].num_func);
    wprintf(L"\tFuncionário(a): %S\n",vet[i].nome_func);
    wprintf(L"\tSalário: %.2f\n\n",vet[i].salario);
    wprintf(L"Pressione qualquer tecla para continuar a exclusão ou 'q' para cancelar");

    tecla = getch();
    if(tecla=='q') return;

    vet[i].deletado_func = 1;

    system("cls");
    wprintf(L"Exclusão feita com sucesso.\n\n");
    system("pause");
}

void remocao_proj(proj *vet, int *qtdProj)
{
    system("cls");

    int i, j, achoAlgo = 0, valido = 1;
    char tecla, nome_proj_chave[50];

    wprintf(L"Escreva o nome do projeto ou uma parte desse: ");
    fflush(stdin);
    scanf("%[^\n]s",nome_proj_chave);

    //Interface de procura de projetos melhorada (não é preciso saber o nome exato do projeto)
    for(i=0; i<*qtdProj; i++)
    {
        if(!vet[i].deletado_proj && strstr(vet[i].nome_proj, nome_proj_chave)!=NULL)
        {
            //Esse if garante que eu só vou printar uma vez "Projetos encontrados"
            if(achoAlgo==0)
            {
                wprintf(L"Projetos encontrados:\n\n");
                achoAlgo++;
            }
            wprintf(L"\t%S (%d)\n",vet[i].nome_proj, i);
        }
    }

    if(!achoAlgo)
    {
        wprintf(L"Não foi encontrado nenhum projeto correspondente.\n\n");
        system("pause");
        return;
    }
    else
    {
        wprintf(L"\nEscolha um projeto através do código numérico: ");
        do
        {
            scanf("%d",&i);
            if(vet[i].deletado_proj || i>*qtdProj) valido = 0;
            else valido = 1;
            if(!valido) wprintf(L"\nDigite um valor válido: ");

        }while(!valido);
        system("cls");
    }

    //Caso o projeto seja encontrado, aqui você pode confirmar as informações sobre ele e escolher continuar
    wprintf(L"Você está excluindo as informações do projeto %S:\n",vet[i].nome_proj);
    wprintf(L"\tFuncionário(a) responsável: %d\n",vet[i].func_resp);
    wprintf(L"\tData de início: %0.2d/%0.2d/%d\n",vet[i].data_inc[0],vet[i].data_inc[1],vet[i].data_inc[2]);
    wprintf(L"\tData de término: %0.2d/%0.2d/%d\n",vet[i].data_term[0],vet[i].data_term[1],vet[i].data_term[2]);
    wprintf(L"\tTempo estimado: %d meses\n",vet[i].tempo_estim);
    wprintf(L"\tValor estimado: R$ %.2f\n\n",vet[i].valor_estim);
    wprintf(L"Pressione qualquer tecla para continuar a exclusão ou 'q' para cancelar");

    tecla = getch();
    if(tecla=='q') return;

    vet[i].deletado_proj = 1;

    system("cls");
    wprintf(L"Exclusão feita com sucesso.\n\n");
    system("pause");
}

///Listar os elementos
void listar_func(func *vet, int *qtdFunc)
{
    system("cls");

    if(*qtdFunc==0)
    {
        wprintf(L"Não há funcionários(as) cadastrados(as).\n\n");
        system("pause");
        return;
    }

    int i;

    wprintf(L"Funcionários:\n");
    for(i=0; i<*qtdFunc; i++)
    {
        if(!vet[i].deletado_func)
        {
            wprintf(L"\n\tNúmero funcional: %d",vet[i].num_func);
            wprintf(L"\n\tNome: %S",vet[i].nome_func);
            wprintf(L"\n\tSalário: %.2f\n\n",vet[i].salario);
        }
    }

    system("pause");
}

void listar_proj(proj *vet, int *qtdProj)
{
    system("cls");

    if(*qtdProj==0)
    {
        wprintf(L"Não há projetos cadastrados.\n\n");
        system("pause");
        return;
    }

    int i;

    wprintf(L"Projetos:\n");
    for(i=0; i<*qtdProj; i++)
    {
        if(!vet[i].deletado_proj)
        {
            wprintf(L"\n\tNome: %S",vet[i].nome_proj);
            wprintf(L"\n\tFuncionário responsável: %d",vet[i].func_resp);
            wprintf(L"\n\tData de início: %0.2d/%0.2d/%d",vet[i].data_inc[0],vet[i].data_inc[1],vet[i].data_inc[2]);
            wprintf(L"\n\tData de término: %0.2d/%0.2d/%d",vet[i].data_term[0],vet[i].data_term[1],vet[i].data_term[2]);
            wprintf(L"\n\tTempo estimado: %d meses",vet[i].tempo_estim);
            wprintf(L"\n\tValor estimado: R$ %.2f\n\n",vet[i].valor_estim);
        }
    }

    system("pause");
}

///Carregar/Salvar os elementos em arquivos binários
void carregarFunc(func *funcionarios,int *qtdFunc)
{
    FILE *bin;
    bin = fopen("listaFunc","rb");
    if(!bin){
        wprintf(L"Não foi possível carregar as informações.\n");
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
        wprintf(L"Não foi possível salvar as informações.\n");
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
        wprintf(L"Não foi possível carregar as informações.\n");
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
        wprintf(L"Não foi possível salvar as informações.\n");
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

    wprintf(L"quantidade de projetos: %d quantidade de funcionarios: %d\n\n", qtdProj, qtdFunc);

    system("pause");
    system("cls");

    return 0;
}