#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <wchar.h>
#include <conio.h>
#include <time.h>

#define MAX_f 500
#define MAX_p 2000
#define MAX_e 499

typedef struct f
{
    int num_func;
    char nome_func[50];
    float salario;
    int deletado_func;
}func;

typedef struct p
{
    char nome_proj[50];
    int data_inc[3];
    int data_term[3];
    int tempo_estim;
    float valor_estim;
    int func_resp;
    int deletado_proj;
}proj;

typedef struct e
{
    int num_func;
    char email[30];
}email_f;


//Algoritmos específicos:
int busca_binaria_func(func *vet, int alvo, int n);
    //Merge Sort:
    void merge_sort(proj *vet, int n);
    void merge_sortR(proj *vet, proj *aux, int ini, int fim);
    void intercala_ordenado(proj *vet, proj *aux, int ini, int meio, int fim);
    //Quick Sort: - Adaptado de "Marcos Castro. Implementação do QuickSort em C" - GitHub: marcoscastro / quick_sort.c
    void quick_sort(proj vet[], int inicio, int fim);
    int particiona_random(proj vet[], int inicio, int fim);
    int particiona(proj vet[], int inicio, int fim);
    void troca(proj vet[], int i, int j);
void listar_proj_atrasados(proj *vet, int *data_atual, int *qtdProj);

//Interface:
void interface(func *vet_func, proj *vet_proj, email_f *vet_email, int *qtdFunc, int *qtdProj, int *qtdEmail);
void interface_2(func *vet_func, proj *vet_proj, email_f *vet_email, int *qtdFunc, int *qtdProj, int *qtdEmail, int i);
void interface_3(func *vet_func, proj *vet_proj, email_f *vet_email, int *qtdFunc, int *qtdProj, int *qtdEmail, int i);

//Funções principais:
void insercao_func(func *vet, int *qtdFunc);
void insercao_proj(proj *vet, func *vet_func, email_f *vet_email, int *qtdFunc, int *qtdProj, int *qtdEmail);
void edicao_func(func *vet, int *qtdFunc);
void edicao_proj(proj *vet, func *vet_func, email_f *vet_email, int *qtdFunc, int *qtdProj, int *qtdEmail);
void remocao_func(func *vet, int *qtdFunc);
void remocao_proj(proj *vet, email_f *vet_email, int *qtdProj, int *qtdEmail);
void listar_func(func *vet, int *qtdFunc);
void listar_proj(proj *vet, int *qtdProj);

//Persistência de dados:
void carregarFunc(func *funcionarios,int *qtdFunc);
void salvarFunc(func *funcionarios,int qtdFunc);
void carregarProj(proj *projetos,int *qtdProj);
void salvarProj(proj *projetos,int qtdProj);

//Funções secundárias:
void busca_func_BB(func *vet, int *qtdFunc);
void coleta_func(func *vet, int *qtdFunc);
void coleta_proj(proj *vet, int *qtdProj);
void verificar_atrasados(proj *vet, int *qtdProj);
void coleta_func_proj(func *vet, proj *array, email_f *tabela, int *qtdProj, int *qtdFunc);
    //Hashing
    void insercao_email(email_f *tabela, int num_func, char *email_func, int *qtdEmail);
    int encontrar_email(email_f *tabela, int num_func);
    void remocao_email(email_f *tabela, int num_func, int *qtdEmail);
    void inicializa_tabela(email_f *tabela);
    

///Fim do Header

///Algoritmos de busca binária
int busca_binaria_func(func *vet, int alvo, int n)
{
    int inf, sup, meio;

    inf = 0;
    sup = n-1;

    while(inf<=sup)
    {
        meio = (inf + sup)/2;

        if(vet[meio].num_func == alvo) return meio;
        else
        {
            if(vet[meio].num_func > alvo) sup = meio - 1;
            else inf = meio + 1;
        }
    }

    return -1;
}

///Merge Sort
void merge_sort(proj *vet, int n)
{
    proj *aux;

    aux = (proj*) malloc(n*sizeof(proj));
    if(aux==NULL) exit(-1);

    merge_sortR(vet, aux, 0, n-1);
}

void merge_sortR(proj *vet, proj *aux, int ini, int fim)
{
    if(ini!=fim)
    {
        int meio;

        meio = (ini+fim)/2;
        merge_sortR(vet, aux, ini, meio);
        merge_sortR(vet, aux, meio+1, fim);
        intercala_ordenado(vet, aux, ini, meio, fim);
    }
}

void intercala_ordenado(proj *vet, proj *aux, int ini, int meio, int fim)
{
    int inicio_v1, inicio_v2, i;
    int num_data_term_v1, num_data_term_v2;

    inicio_v1 = ini;
    inicio_v2 = meio+1;
    i = ini;

    while(inicio_v1<=meio && inicio_v2<=fim)
    {
        num_data_term_v1 = 10000*vet[inicio_v1].data_term[2] + 100*vet[inicio_v1].data_term[1] + vet[inicio_v1].data_term[0];
        num_data_term_v2 = 10000*vet[inicio_v2].data_term[2] + 100*vet[inicio_v2].data_term[1] + vet[inicio_v2].data_term[0];

        if(num_data_term_v1 <= num_data_term_v2)
        {
            aux[i] = vet[inicio_v1];
            inicio_v1++;
        }
        else
        {

            aux[i] = vet[inicio_v2];
            inicio_v2++;
        }

        i++;
    }

    if(inicio_v1 <= meio)
    {
        for(;inicio_v1<=meio; i++, inicio_v1++)
        {

            aux[i] = vet[inicio_v1];
        }
    }

    if(inicio_v2 <= fim)
    {
        for(;inicio_v2<=fim; i++, inicio_v2++)
        {

            aux[i] = vet[inicio_v2];
        }
    }

    for(i=ini; i<=fim; i++)
    {

        vet[i] = aux[i];
    }
}

///Quick Sort
void quick_sort(proj vet[], int inicio, int fim)
{
	if(inicio < fim)
	{
		// função particionar retorna o índice do pivô
		int pivo_indice = particiona_random(vet, inicio, fim);
		
		// chamadas recursivas quick_sort
		quick_sort(vet, inicio, pivo_indice - 1);
		quick_sort(vet, pivo_indice + 1, fim);
	}
}

int particiona_random(proj vet[], int inicio, int fim)
{
	// seleciona um número entre fim (inclusive) e inicio (inclusive)
	int pivo_indice = (rand() % (fim - inicio + 1)) + inicio;
	
	// faz a troca para colocar o pivô no fim
	troca(vet, pivo_indice, fim);
	// chama a particiona
	return particiona(vet, inicio, fim);
}

int particiona(proj vet[], int inicio, int fim)
{
	int pivo_indice, i;
    proj pivo;
	
	pivo = vet[fim]; // o pivô é sempre o último elemento
	pivo_indice = inicio;
	
	for(i = inicio; i < fim; i++)
	{
		// verifica se o elemento é <= ao pivô
		if(vet[i].valor_estim <= pivo.valor_estim)
		{
			// realiza a troca
			troca(vet, i, pivo_indice);
			// incrementa o pivo_indice
			pivo_indice++;
		}
	}
	
	// troca o pivô
	troca(vet, pivo_indice, fim);
	
	// retorna o índice do pivô
	return pivo_indice;
}

void troca(proj vet[], int i, int j)
{
	proj aux = vet[i];
	vet[i] = vet[j];
	vet[j] = aux;
}

///Interface em terminal
void interface(func *vet_func, proj *vet_proj, email_f *vet_email, int *qtdFunc, int *qtdProj, int *qtdEmail)
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
        case 'a': interface_2(vet_func, vet_proj, vet_email, qtdFunc, qtdProj, qtdEmail, 1);
            break;
        case 'b': interface_2(vet_func, vet_proj, vet_email, qtdFunc, qtdProj, qtdEmail, 2);
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

void interface_2(func *vet_func, proj *vet_proj, email_f *vet_email, int *qtdFunc, int *qtdProj, int *qtdEmail, int i)
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
        wprintf(L"Pressione 'e' para ver outras funções\n");
        wprintf(L"Pressione 'q' para retornar a inferface inicial\n");

        tecla = getch();

        switch(tecla)
        {
        case 'a': i==1 ? edicao_func(vet_func, qtdFunc) : edicao_proj(vet_proj, vet_func, vet_email, qtdFunc, qtdProj, qtdEmail);
            break;
        case 'b': i==1 ? insercao_func(vet_func, qtdFunc) : insercao_proj(vet_proj, vet_func, vet_email, qtdFunc, qtdProj, qtdEmail);
            break;
        case 'c': i==1 ? remocao_func(vet_func, qtdFunc) : remocao_proj(vet_proj, vet_email, qtdProj, qtdEmail);
            break;
        case 'd': i==1 ? listar_func(vet_func, qtdFunc) : listar_proj(vet_proj, qtdProj);
            break;
        case 'e': i==1 ? interface_3(vet_func, vet_proj, vet_email, qtdFunc, qtdProj, qtdEmail, 1) 
                        : interface_3(vet_func, vet_proj, vet_email, qtdFunc ,qtdProj, qtdEmail, 2);
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

void interface_3(func *vet_func, proj *vet_proj, email_f *vet_email, int *qtdFunc, int *qtdProj, int *qtdEmail, int i)
{
    char tecla;

    if(i==1)
    {
        do
        {
            system("cls");
            wprintf(L"Funcionários - Outras funções\n\n");
            wprintf(L"Escolha uma função: \n");
            wprintf(L"Pressione 'a' para realizar uma busca binária por um(a) funcionário(a)\n");
            wprintf(L"Pressione 'b' para verificar os funcionários(as) com maiores salários\n");
            wprintf(L"Pressione 'c' para verificar os funcionários(as) responsaveis por projetos\n");
            wprintf(L"Pressione 'q' para retornar a inferface inicial\n");

            tecla = getch();

            switch(tecla)
            {
            case 'a': busca_func_BB(vet_func, qtdFunc);
                break;
            case 'b': coleta_func(vet_func, qtdFunc);
                break;
            case 'c': coleta_func_proj(vet_func, vet_proj, vet_email, qtdProj, qtdFunc);
                break;
            case 'q':
                break;
            default: {
                        system("cls");
                        wprintf(L"\nEscolha inválida.\n");
                        system("pause");
                     }
                break;
            }

        }while(tecla!='q');
    }
    else
    {
        do
        {
            system("cls");
            wprintf(L"Projetos - Outras funções\n\n");
            wprintf(L"Escolha uma função: \n");
            wprintf(L"Pressione 'a' para verificar os projetos com valor estimado acima de R$ 500.000,00\n");
            wprintf(L"Pressione 'b' para verificar os projetos que estão ou foram atrasados\n");
            wprintf(L"Pressione 'q' para retornar a interface inicial.\n");

            tecla = getch();
            
            switch (tecla)
            {
            case 'a': coleta_proj(vet_proj, qtdProj);
                break;
            case 'b': verificar_atrasados(vet_proj, qtdProj);
                break;
            case 'q':
                break;
            }

        }while(tecla!='q');
    }
}

///Inserir um novo elemento
void insercao_func(func *vet, int *qtdFunc)
{
    system("cls");

    int i, k, num_func_in, emUso=0;
    char nome_func_in[50];
    float salario_in;

    //Coletando informações a de entrada
    wprintf(L"Declare o número funcional do(a) funcionário(a): ");
    fflush(stdin);

    //Verificando se o número funcional já não está em uso
    do
    {
        scanf("%d", &num_func_in);
        for(i=0; i<*qtdFunc; i++)
        {
            if(!vet[i].deletado_func && num_func_in==vet[i].num_func)
            {
                system("cls");
                wprintf(L"Esse número funcional já está em uso.\n");
                wprintf(L"Declare outro número funcional: ");
                emUso = 1;
                break;
            }
            else emUso = 0;
        }

    }while(emUso);

    wprintf(L"Escreva o nome do(a) funcionário(a): ");
    fflush(stdin);
    scanf("%[^\n]s",nome_func_in);

    wprintf(L"Declare o salário do(a) funcionário(a): ");
    scanf("%f",&salario_in);

    //Verificando se o número funcional declarado já não foi utilizado em um elemento deletado
    //Caso positivo, a inserção se resume em sobrescrever os campos do deletado com os valores de entrada
    for(i=0; i<*qtdFunc; i++)
    {
        if(vet[i].deletado_func && num_func_in==vet[i].num_func)
        {
            strcpy(vet[i].nome_func, nome_func_in);
            vet[i].salario = salario_in;
            vet[i].deletado_func = 0;

            //Não deve ter (*qtdFunc)++ aqui! Nós sobrescrevemos um elemento, não adicionamos um novo
            system("cls");
            wprintf(L"Funcionário(a) cadastrado(a) com sucesso.\n\n");
            system("pause");
            return;
        }
    }
    
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
        strcpy(vet[k].nome_func, vet[k-1].nome_func);
        vet[k].salario = vet[k-1].salario;
        vet[k].deletado_func = vet[k-1].deletado_func;
    }

    //Inserindo os valores de entrada na posição correta:
    vet[i].num_func = num_func_in;
    strcpy(vet[i].nome_func, nome_func_in);
    vet[i].salario = salario_in;
    vet[i].deletado_func = 0;

    (*qtdFunc)++;
    system("cls");
    wprintf(L"Funcionário(a) cadastrado(a) com sucesso.\n\n");
    system("pause");
}

void insercao_proj(proj *vet, func *vet_func, email_f *vet_email, int *qtdFunc, int *qtdProj, int *qtdEmail)
{
    system("cls");

    int i, j, k, emUso, existe=-2, cadastrarEmail=1;
    char nome_proj_in[50];
    char email_func_in[30];
    int data_inc_in[3], data_term_in[3], tempo_estim_in, func_resp_in;
    float valor_estim_in;

    //Coletando informações a de entrada
        //Verificando se o funcionário responsável existe de fato
    do
    {
        system("cls");
        if(existe==-1)
        {
            wprintf(L"Esse(a) funcionário(a) não está cadastrado(a).\n");
            wprintf(L"Digite 0 caso deseje rever os(as) funcionários(as) cadastrados(as).\n");
            wprintf(L"Declare o funcionário(a) responsável: ");
        }
        else wprintf(L"Declare o funcionário(a) responsável: ");
        scanf("%d",&func_resp_in);
        if(func_resp_in==0)
        {
            listar_func(vet_func, qtdFunc);
            system("cls");
        }
        if(func_resp_in!=0) existe = busca_binaria_func(vet_func, func_resp_in, *qtdFunc);
        else existe = -1;

    }while(existe==-1);

        //Verificando se esse funcionário é um novo gerente
        //Em caso afirmativo, é necessário incluir o email da pessoa
    for(i=0; i<*qtdProj; i++)
    {
        if(!vet[i].deletado_proj && vet[i].func_resp==func_resp_in)
        {    
            cadastrarEmail = 0;
            break;
        }
    }
    
    if(cadastrarEmail)
    {
        wprintf(L"Você está cadastrando um novo gerente.\n");
        wprintf(L"Por isso, declare o email desse funcionário sem incluir o domínio: ");
        fflush(stdin);
        scanf("%[^\n]s",email_func_in);

        insercao_email(vet_email, func_resp_in, email_func_in, qtdEmail);
    }

    wprintf(L"Declare o nome do projeto: ");

    //Verificando se o nome de projeto já não está em uso
    do
    {
        fflush(stdin);
        scanf("%[^\n]s", nome_proj_in);
        for(i=0; i<*qtdProj; i++)
        {
            if(!vet[i].deletado_proj && strcmp(vet[i].nome_proj, nome_proj_in)==0)
            {
                system("cls");
                wprintf(L"Declare o funcionário(a) responsável: %d\n",func_resp_in);
                wprintf(L"Esse nome já está em uso.\n");
                wprintf(L"Declare outro nome para o projeto: ");
                emUso = 1;
                break;
            }
            else emUso = 0;
        }

    }while(emUso);

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

    wprintf(L"Declare o valor estimado do projeto: ");
    scanf("%f",&valor_estim_in);

    //Verificando se o nome de projeto declarado já não foi utilizado em um elemento deletado
    //Caso positivo, a inserção se resume em sobrescrever os campos do deletado com os valores de entrada
    for(i=0; i<*qtdProj; i++)
    {
        if(vet[i].deletado_proj && strcmp(vet[i].nome_proj, nome_proj_in)==0)
        {
            vet[i].func_resp = func_resp_in;
            strcpy(vet[i].nome_proj, nome_proj_in);
            for(j=0; j<3; j++)
            {
                vet[i].data_inc[j] = data_inc_in[j];
                vet[i].data_term[j] = data_term_in[j];
            }
            vet[i].tempo_estim = tempo_estim_in;
            vet[i].valor_estim = valor_estim_in;
            vet[i].deletado_proj = 0;

            //Não deve ter (*qtdProj)++ aqui! Nós sobrescrevemos um elemento, não adicionamos um novo
            system("cls");
            wprintf(L"projeto cadastrado com sucesso.\n\n");
            system("pause");
            return;
        }
    }

    system("cls");

    //Procura pela posição do valor a ser inserido no vetor
    for (i=0; i<*qtdProj; i++)
    {
        if(strcmp(vet[i].nome_proj, nome_proj_in)>0) break;
    }

    //for para ajustar o vetor caso necessário
    for(k=*qtdProj; k>i; k--)
    {
        vet[k].func_resp = vet[k-1].func_resp;
        strcpy(vet[k].nome_proj, vet[k-1].nome_proj);
        for(j=0; j<3; j++)
        {
            vet[k].data_inc[j] = vet[k-1].data_inc[j];
            vet[k].data_term[j] = vet[k-1].data_term[j];
        }
        vet[k].tempo_estim = vet[k-1].valor_estim;
        vet[k].valor_estim = vet[k-1].valor_estim;
        vet[k].deletado_proj = vet[k-1].deletado_proj;
    }

    //Inserindo os valores de entrada na posição correta:
    vet[i].func_resp = func_resp_in;
    strcpy(vet[i].nome_proj, nome_proj_in);
    for(j=0; j<3; j++)
    {
        vet[i].data_inc[j] = data_inc_in[j];
        vet[i].data_term[j] = data_term_in[j];
    }
    vet[i].tempo_estim = tempo_estim_in;
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

void edicao_proj(proj *vet, func *vet_func, email_f *vet_email, int *qtdFunc, int *qtdProj, int *qtdEmail)
{
    system("cls");

    int i, j, achoAlgo = 0, valido = 1, novo_func_resp_in, existe, cadastrarEmail=1, excluirEmail=1;
    char tecla, nome_proj_chave[50], email_func_in[30];

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
        //Verificando se o funcionário responsável existe de fato
    do
    {
        system("cls");
        if(existe==-1)
        {
            wprintf(L"Esse(a) funcionário(a) não está cadastrado(a).\n");
            wprintf(L"Digite 0 caso deseje rever os(as) funcionários(as) cadastrados(as).\n");
            wprintf(L"Declare o funcionário(a) responsável: ");
        }
        else wprintf(L"\tDeclare o novo número funcional do(a) funcionário(a) responsável: ");
        scanf("%d",&novo_func_resp_in);
        if(novo_func_resp_in==0)
        {
            listar_func(vet_func, qtdFunc);
            system("cls");
        }
        if(novo_func_resp_in!=0) existe = busca_binaria_func(vet_func, novo_func_resp_in, *qtdFunc);
        else existe = -1;

    }while(existe==-1);

        //Verificando se o funcionário substituido deixou de ser gerente e se o novo acabou de se tornar gerente
    for(j=0; j<*qtdProj; j++)
    {
        if(!vet[j].deletado_proj)
        {
            if(vet[j].func_resp==novo_func_resp_in) cadastrarEmail = 0;

            if(j!=i && vet[j].func_resp==vet[i].func_resp) excluirEmail = 0;

            if(!cadastrarEmail && !excluirEmail) break;
        }
    }

    if(cadastrarEmail)
    {
        wprintf(L"Você está cadastrando um novo gerente.\n");
        wprintf(L"Por isso, declare o email desse funcionário sem incluir o domínio: ");
        fflush(stdin);
        scanf("%[^\n]s",email_func_in);

        insercao_email(vet_email, novo_func_resp_in, email_func_in, qtdEmail); 
    }

    if(excluirEmail)
    {
        remocao_email(vet_email, vet[i].func_resp, qtdEmail);
    }

    vet[i].func_resp = novo_func_resp_in;

    wprintf(L"Projeto: %S\n",vet[i].nome_proj);

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

void remocao_proj(proj *vet, email_f *vet_email, int *qtdProj, int *qtdEmail)
{
    system("cls");

    int i, j, achoAlgo = 0, valido = 1, excluirEmail=1;
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

    //Verificando se o até então gerente desse projeto deixou de ser gerente
    for(j=0; j<*qtdProj; j++)
    {
        if(!vet[j].deletado_proj)
        {
            if(vet[j].func_resp==vet[i].func_resp) 
            {
                excluirEmail = 0;
                break;
            }
        }
    }

    if(excluirEmail)
    {
        remocao_email(vet_email, vet[i].func_resp, qtdEmail);
    }

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

    int i, j, page, firstEleInc, lastEleExc, maxPage, contadorEle = 0;
    char tecla;
    int listar[MAX_f];

    //Contagem de quantos funcionários devem ser printados
    for(i=0; i<*qtdFunc; i++) if(!vet[i].deletado_func) contadorEle++;

    //O vetor listar armazena os indíces dos elementos que devem ser printados
    for(i=0, j=0; j<contadorEle && i<*qtdFunc; i++)
    {
        if(!vet[i].deletado_func)
        {
            listar[j] = i;
            j++;
        } 
    }

    //Estados inicial das variáveis que controlam a listagem
    page = 0;

    maxPage = contadorEle/5 - 1;
    if(contadorEle%5 != 0) maxPage++;

    firstEleInc = 0;
    lastEleExc = 5;

    do
    {
        system("cls");
        wprintf(L"Funcionários:\n");

        for (i=firstEleInc; i<contadorEle && i<lastEleExc; i++)
        {
            wprintf(L"\n\tNúmero funcional: %d",vet[listar[i]].num_func);
            wprintf(L"\n\tNome: %S",vet[listar[i]].nome_func);
            wprintf(L"\n\tSalário: %.2f\n",vet[listar[i]].salario);
        }

        if(page==0) wprintf(L"\n\t    \t\t(%d/%d)\t\td>>\n\n",page+1,maxPage+1);
        else if(page==maxPage) wprintf(L"\n\t<<a\t\t(%d/%d)\n\n",page+1,maxPage+1);
            else wprintf(L"\n\t<<a\t\t(%d/%d)\t\td>>\n\n",page+1,maxPage+1);
        wprintf(L"\tPressione 'q' para retornar");
        
        tecla = getch();

        switch(tecla)
        {
            case 'a': if(page>0) page--;
                break;
            case 'd': if(page<maxPage) page++;
                break;
            case 'q':
                break;
            default: {
                        system("cls");
                        wprintf(L"\nFaça uma escolha válida.\n\n");
                        system("pause");
                    }
                break;
        }
        
        firstEleInc = 5*page;
        lastEleExc = 5*page + 5;

    }while(tecla!='q');
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

    int i, j, page, firstEleInc, lastEleExc, maxPage, contadorEle = 0, ind;
    char tecla;
    int listar[MAX_p];

    //Contagem de quantos funcionários devem ser printados
    for(i=0; i<*qtdProj; i++) if(!vet[i].deletado_proj) contadorEle++;

    //O vetor listar armazena os indíces dos elementos que devem ser printados
    for(i=0, j=0; j<contadorEle && i<*qtdProj; i++)
    {
        if(!vet[i].deletado_proj)
        {
            listar[j] = i;
            j++;
        } 
    }

    //Estados inicial das variáveis que controlam a listagem
    page = 0;

    maxPage = contadorEle/5 - 1;
    if(contadorEle%5 != 0) maxPage++;

    firstEleInc = 0;
    lastEleExc = 5;

    do
    {
        system("cls");
        wprintf(L"Projetos:\n");

        for (i=firstEleInc; i<contadorEle && i<lastEleExc; i++)
        {
            ind = listar[i];

            wprintf(L"\n\tNome: %S",vet[ind].nome_proj);
            wprintf(L"\n\tFuncionário responsável: %d",vet[ind].func_resp);
            wprintf(L"\n\tData de início: %0.2d/%0.2d/%d",vet[ind].data_inc[0],vet[ind].data_inc[1],vet[ind].data_inc[2]);
            wprintf(L"\n\tData de término: %0.2d/%0.2d/%d",vet[ind].data_term[0],vet[ind].data_term[1],vet[ind].data_term[2]);
            wprintf(L"\n\tTempo estimado: %d meses",vet[ind].tempo_estim);
            wprintf(L"\n\tValor estimado: R$ %.2f\n",vet[ind].valor_estim);
        }

        if(page==0) wprintf(L"\n\t    \t\t(%d/%d)\t\td>>\n\n",page+1,maxPage+1);
        else if(page==maxPage) wprintf(L"\n\t<<a\t\t(%d/%d)\n\n",page+1,maxPage+1);
            else wprintf(L"\n\t<<a\t\t(%d/%d)\t\td>>\n\n",page+1,maxPage+1);
        wprintf(L"\tPressione 'q' para retornar");
        
        tecla = getch();

        switch(tecla)
        {
            case 'a': if(page>0) page--;
                break;
            case 'd': if(page<maxPage) page++;
                break;
            case 'q':
                break;
            default: {
                        system("cls");
                        wprintf(L"\nFaça uma escolha válida.\n\n");
                        system("pause");
                    }
                break;
        }
        
        firstEleInc = 5*page;
        lastEleExc = 5*page + 5;

    }while(tecla!='q');
}

void listar_proj_atrasados(proj *vet, int *data_atual, int *qtdProj)
{
    system("cls");

    if(*qtdProj==0)
    {
        wprintf(L"Não há projetos atrasados.\n\n");
        system("pause");
        return;
    }

    int i, page, firstEleInc, lastEleExc, maxPage, atraso[3];
    char tecla;

    //Estados inicial das variáveis que controlam a listagem
    page = 0;

    maxPage = *qtdProj/4 - 1;
    if(*qtdProj%4 != 0) maxPage++;

    firstEleInc = 0;
    lastEleExc = 4;

    do
    {
        system("cls");
        wprintf(L"Projetos Atrasados:\n");

        for (i=firstEleInc; i<*qtdProj && i<lastEleExc; i++)
        {
            wprintf(L"\n\tNome: %S",vet[i].nome_proj);
            wprintf(L"\n\tFuncionário responsável: %d",vet[i].func_resp);
            wprintf(L"\n\tData de início: %0.2d/%0.2d/%d",vet[i].data_inc[0],vet[i].data_inc[1],vet[i].data_inc[2]);
            wprintf(L"\n\tData de término: %0.2d/%0.2d/%d",vet[i].data_term[0],vet[i].data_term[1],vet[i].data_term[2]);
            wprintf(L"\n\tTempo estimado: %d meses",vet[i].tempo_estim);
            if(vet[i].tempo_estim==0) wprintf(L"\n\tProjeto finalizado");
            else wprintf(L"\n\tProjeto em andamento");

            atraso[2] = data_atual[2] - vet[i].data_term[2];
            atraso[1] = 12*atraso[2] + data_atual[1] - vet[i].data_term[1];
            atraso[0] = data_atual[0] - vet[i].data_term[0];
            if(atraso[0]<0)
            {
                atraso[1]--;
                atraso[0]+=30;
            }

            if(atraso[1]!=0 && atraso[0]!=0) wprintf(L"\n\tTempo de atraso: %d meses e %d dias",atraso[1],atraso[0]);
            if(atraso[1]!=0 && atraso[0]==0) wprintf(L"\n\tTempo de atraso: %d meses",atraso[1]);
            if(atraso[1]==0 && atraso[0]!=0) wprintf(L"\n\tTempo de atraso: %d dias",atraso[0]);

            wprintf(L"\n\tValor estimado: R$ %.2f\n",vet[i].valor_estim);
        }

        if(page==0) wprintf(L"\n\t    \t\t\t(%d/%d)\t\t\td>>\n\n",page+1,maxPage+1);
        else if(page==maxPage) wprintf(L"\n\t<<a\t\t\t(%d/%d)\n\n",page+1,maxPage+1);
            else wprintf(L"\n\t<< a\t\t\t(%d/%d)\t\t\td>>\n\n",page+1,maxPage+1);
        wprintf(L"\tPressione 'q' para retornar");
        
        tecla = getch();

        switch(tecla)
        {
            case 'a': if(page>0) page--;
                break;
            case 'd': if(page<maxPage) page++;
                break;
            case 'q':
                break;
            default: {
                        system("cls");
                        wprintf(L"\nFaça uma escolha válida.\n\n");
                        system("pause");
                    }
                break;
        }
        
        firstEleInc = 4*page;
        lastEleExc = 4*page + 4;

    }while(tecla!='q');

    wprintf(L"\n\n");
    system("pause");
}

void listar_func_resp_proj(func *vet, email_f *tabela, int *qtdFunc)
{
    system("cls");

    if(*qtdFunc==0)
    {
        wprintf(L"Não há funcionários(as) como responsáveis por projetos.\n\n");
        system("pause");
        return;
    }

    int i, page, firstEleInc, lastEleExc, maxPage, index;
    char tecla;

    //Estados inicial das variáveis que controlam a listagem
    page = 0;

    maxPage = *qtdFunc/5 - 1;
    if(*qtdFunc%5 != 0) maxPage++;

    firstEleInc = 0;
    lastEleExc = 5;

    do
    {
        system("cls");
        wprintf(L"Funcionários:\n");

        for (i=firstEleInc; i<*qtdFunc && i<lastEleExc; i++)
        {
            wprintf(L"\n\tNúmero funcional: %d",vet[i].num_func);
            wprintf(L"\n\tNome: %S",vet[i].nome_func);
            wprintf(L"\n\tSalário: %.2f",vet[i].salario);

            index = encontrar_email(tabela, vet[i].num_func);

            wprintf(L"\n\tEmail: %S@func.SuperMachines.com\n",tabela[index].email);
        }

        if(page==0) wprintf(L"\n\t    \t\t(%d/%d)\t\td>>\n\n",page+1,maxPage+1);
        else if(page==maxPage) wprintf(L"\n\t<<a\t\t(%d/%d)\n\n",page+1,maxPage+1);
            else wprintf(L"\n\t<<a\t\t(%d/%d)\t\td>>\n\n",page+1,maxPage+1);
        wprintf(L"\tPressione 'q' para retornar");
        
        tecla = getch();

        switch(tecla)
        {
            case 'a': if(page>0) page--;
                break;
            case 'd': if(page<maxPage) page++;
                break;
            case 'q':
                break;
            default: {
                        system("cls");
                        wprintf(L"\nFaça uma escolha válida.\n\n");
                        system("pause");
                    }
                break;
        }
        
        firstEleInc = 5*page;
        lastEleExc = 5*page + 5;

    }while(tecla!='q');
}

///Carregar/Salvar os elementos em arquivos binários
void carregarFunc(func *funcionarios, int *qtdFunc)
{
    FILE *bin;
    bin = fopen("listaFunc","rb");
    if(!bin){
        wprintf(L"Não foi possível carregar as informações dos funcionários.\n");
        system("pause");
        return;
    }
    fread(qtdFunc,sizeof(int),1,bin);
    fread(funcionarios, sizeof(struct f), *qtdFunc, bin);

    fclose(bin);
}

void salvarFunc(func *funcionarios, int qtdFunc)
{
    FILE *bin;
    bin = fopen("listaFunc","wb");
    if(!bin){
        wprintf(L"Não foi possível salvar as informações dos funcionários.\n");
        system("pause");
        exit(1);
    }
    fwrite(&qtdFunc,sizeof(int),1,bin);
    fwrite(funcionarios, sizeof(struct f), qtdFunc, bin);

    fclose(bin);
}

void carregarProj(proj *projetos, int *qtdProj)
{
    FILE *bin;
    bin = fopen("listaProj","rb");
    if(!bin){
        wprintf(L"Não foi possível carregar as informações dos projetos.\n");
        system("pause");
        return;
    }
    fread(qtdProj,sizeof(int),1,bin);
    fread(projetos, sizeof(struct p), *qtdProj, bin);

    fclose(bin);
}

void salvarProj(proj *projetos, int qtdProj)
{
    FILE *bin;
    bin = fopen("listaProj","wb");
    if(!bin){
        wprintf(L"Não foi possível salvar as informações dos projetos.\n");
        system("pause");
        exit(1);
    }
    fwrite(&qtdProj, sizeof(int), 1, bin);
    fwrite(projetos, sizeof(struct p), qtdProj, bin);

    fclose(bin);
}

void carregarEmail(email_f *emails_funcionarios, int *qtdEmail)
{
    FILE *bin;
    bin = fopen("listaEmail","rb");
    if(!bin){
        wprintf(L"Não foi possível carregar as informações dos emails.\n");
        system("pause");
        return;
    }
    fread(qtdEmail, sizeof(int), 1, bin);
    if(qtdEmail!=0) fread(emails_funcionarios, sizeof(email_f), MAX_e, bin);

    fclose(bin);
}

void salvarEmail(email_f *emails_funcionarios, int qtdEmail)
{
    FILE *bin;
    bin = fopen("listaEmail","wb");
    if(!bin){
        wprintf(L"Não foi possível salvar as informações dos emails.\n");
        system("pause");
        exit(1);
    }
    fwrite(&qtdEmail, sizeof(int), 1, bin);
    fwrite(emails_funcionarios, sizeof(email_f), MAX_e, bin);

    fclose(bin);
}

///Outras funções
//Encontra um funcionário através de seu número funcional utilizando busca binária (1ª)
void busca_func_BB(func *vet, int *qtdFunc)
{
    system("cls");

    int i, num_func_chave;

    //Busca binária pelo funcionário
    wprintf(L"Digite o número funcional do(a) funcionário(a): ");
    fflush(stdin);
    scanf("%d",&num_func_chave);

    i = busca_binaria_func(vet, num_func_chave, *qtdFunc);

    system("cls");

    if(i==-1 || vet[i].deletado_func)
    {
        wprintf(L"Funcionário(a) não encontrado(a).\n");
        system("pause");
        system("cls");
        return;
    }

    //Aqui você pode confirmar as informações sobre ele
    wprintf(L"Informações do(a) funcionário(a) %d:\n",vet[i].num_func);
    wprintf(L"\tFuncionário(a): %S\n",vet[i].nome_func);
    wprintf(L"\tSalário: %.2f\n\n",vet[i].salario);
    system("pause");
    system("cls");
}

//Funcionários com salário acima de R$ 10.000 (2ª)
void coleta_func(func *vet, int *qtdFunc)
{
    system("cls");

    int i, j, k;
    func chave;
    func coletados[MAX_f];

    j=0;

    //Coleta de funcionarios com salários superiores a R$ 10.000,00 em um vetor
    for(i=0; i<*qtdFunc; i++)
    {
        if((vet[i].deletado_func!=1) && (vet[i].salario>10000)){
            coletados[j] = vet[i];
            j++; 
        }
    }

    if(j==0)
    {
        wprintf(L"Não há funcionários(as) com salário superior a R$ 10.000,00.\n\n");
        system("pause");
        return;
    }

    //Insertion Sort para ordenar o vetor coletado
    for(i=0; i<j; i++)
    {
        chave=coletados[i];
        k=i-1;
        while((k>=0) && (chave.salario>coletados[k].salario)) 
        {
            coletados[k+1] = coletados[k];
            k--;
        }
        coletados[k+1]=chave;
    }
    
    listar_func(coletados, &j);
    system("cls");
}

//Projetos com valor estimado acima de R$ 500.000 (3ª)
void coleta_proj(proj *vet, int *qtdProj)
{
    system("cls");

    int i, j;
    proj coletados[MAX_p];

    j=0;

    //Coleta de projetos com valor estimado superiores a R$ 500.000,00 em um vetor
    for(i=0; i<*qtdProj; i++)
    {
        if(!vet[i].deletado_proj && vet[i].tempo_estim && vet[i].valor_estim>500000)
        {
            coletados[j] = vet[i];
            j++; 
        }
    }

    if(j==0)
    {
        wprintf(L"Não há projetos com valor estimado superiores a R$ 500.000,00\n\n");
        system("pause");
        return;
    }

    quick_sort(coletados, 0, j-1);
    
    listar_proj(coletados, &j);
    system("cls");
}

//Dispor informações sobre os projetos atrasados (4ª)
void verificar_atrasados(proj *vet, int *qtdProj)
{
    system("cls");

    if(*qtdProj==0)
    {
        wprintf(L"Não há projetos cadastrados.\n\n");
        system("pause");
        system("cls");
        return;
    }

    int i, j, data_atual[3], num_data_atual, num_data_term, qtdAtrasados=0;
    proj *proj_atrasados;

    wprintf(L"Entre com a data atual:\n");
    wprintf(L"\tDia: ");
    scanf("%d",&data_atual[0]);
    wprintf(L"\tMês: ");
    scanf("%d",&data_atual[1]);
    wprintf(L"\tAno: ");
    scanf("%d",&data_atual[2]);

    system("cls");

    //Colocando as datas em um formato que permite comparação direta
    num_data_atual = 10000*data_atual[2] + 100*data_atual[1] + data_atual[0];

    //Contando o número de projetos atrasados
    for(i=0; i<*qtdProj; i++)
    {
        if(!vet[i].deletado_proj)
        {
            num_data_term = 10000*vet[i].data_term[2] + 100*vet[i].data_term[1] + vet[i].data_term[0];

            if(num_data_term < num_data_atual) qtdAtrasados++;
        }
    }

    //Criando um vetor para armazenar os atrasados
    proj_atrasados = (proj*) malloc(qtdAtrasados*sizeof(proj));

    //Preenchendo o vetor de atrasados
    for(i=0, j=0; j<qtdAtrasados && i<*qtdProj; i++)
    {
        num_data_term = 10000*vet[i].data_term[2] + 100*vet[i].data_term[1] + vet[i].data_term[0];

        if(!vet[i].deletado_proj && num_data_term < num_data_atual)
        {
            proj_atrasados[j] = vet[i];
            j++;
        }
    }

    //Ordenar proj_atrasados conforme o num_data_term em ordem crescente
    merge_sort(proj_atrasados, qtdAtrasados);

    //Printando os projetos atrasados
    listar_proj_atrasados(proj_atrasados, data_atual, &qtdAtrasados);
}

//Dispor informações sobre os funcionários responsáveis por projetos (inclusive o email) (5ª) 
void coleta_func_proj(func *vet, proj *array, email_f *tabela, int *qtdProj, int *qtdFunc)
{
    int i, j, k=0;
    int qtdColetado=0;
    int qtdIds=0;
    int id_coletados[MAX_p];
    func func_coletados[MAX_f];
    int index;
    func chave;

    //Coleta o id dos funcionarios responsaveis por projetos
    for(i=0; i<*qtdProj; i++)
    {
        if(array[i].deletado_proj!=1){
            id_coletados[qtdIds] = array[i].func_resp;
            qtdIds++; 
        }
    } 
    
    int ids_unicos[qtdIds];

    //Remove os numeros funcionais com valor duplicado
    for(i = 0; i<qtdIds; i++)
    {
        for(j=0; j<qtdColetado; j++)
        {
            if(id_coletados[i] == ids_unicos[j])
                break;
        }

        if(j==qtdColetado)
        {
            ids_unicos[qtdColetado] = id_coletados[i];
            qtdColetado++;
        }
    }

    //Busca binária pelos funcionarios responsaveis por projetos
    for(i=0; i<qtdColetado; i++)
    {
        index = busca_binaria_func(vet, ids_unicos[i], *qtdFunc);
        func_coletados[i] = vet[index];
    }

    //Insertion Sort para organizar os funcionarios em ordem alfabetica
    for(i=1; i<qtdColetado; i++)
    {
        chave = func_coletados[i];

        k=i;
        while((k>0) && (strcmp(chave.nome_func, func_coletados[k-1].nome_func)<0)) 
        {
            func_coletados[k] = func_coletados[k-1];
            k--;
        }
        func_coletados[k]=chave;
    }
    
    listar_func_resp_proj(func_coletados, tabela, &qtdColetado);
}

//Funções para lidar com os emails de gerentes de projetos utilizando o número funcional como chave (6ª)
void insercao_email(email_f *tabela, int num_func, char *email_func, int *qtdEmail)
{
    int i, index, rehash;

    //Rehash até encontra um 0
    for(i=0, rehash=1; i<MAX_e && rehash; i++)
    {
        index = (num_func + i) % MAX_e;

        if(tabela[index].num_func==0) rehash = 0;
        else rehash = 1;
    }

    tabela[index].num_func = num_func;
    strcpy(tabela[index].email, email_func);
    (*qtdEmail)++;
}

int encontrar_email(email_f *tabela, int num_func)
{
    int i, index, rehash;
    
    for(i=0, rehash=1; i<MAX_e && rehash; i++)
    {
        index = (num_func + i) % MAX_e;

        if(tabela[index].num_func==num_func) rehash = 0;
        else rehash = 1;
    }
    
    return index;
}

void remocao_email(email_f *tabela, int num_func, int *qtdEmail)
{
    int i;

    i = encontrar_email(tabela, num_func);

    tabela[i].num_func = 0;
    strcpy(tabela[i].email,"vazio");

    (*qtdEmail)--;
}

void inicializa_tabela(email_f *tabela)
{
    int i;

    for(i=0; i<MAX_e; i++)
    {
        //Essa é a cara de um elemento vazio
        tabela[i].num_func = 0;
        strcpy(tabela[i].email, "vazio");
    }
}

int main()
{
    setlocale(LC_ALL,"Portuguese");
    srand(time(NULL));

    func funcionarios[MAX_f];
    proj projetos[MAX_p];
    email_f emails_funcionarios[MAX_e];
    int qtdFunc = 0;
    int qtdProj = 0;
    int qtdEmail = 0;

    carregarFunc(funcionarios, &qtdFunc);
    carregarProj(projetos, &qtdProj);
    inicializa_tabela(emails_funcionarios);
    carregarEmail(emails_funcionarios, &qtdEmail);
    
    interface(funcionarios, projetos, emails_funcionarios, &qtdFunc, &qtdProj, &qtdEmail);

    salvarFunc(funcionarios, qtdFunc);
    salvarProj(projetos, qtdProj);
    salvarEmail(emails_funcionarios, qtdEmail);

    wprintf(L"Quantidade de projetos: %d\nQuantidade de funcionarios: %d\nQuantidade de emails: %d\n\n", qtdProj, qtdFunc, qtdEmail);

    system("pause");
    system("cls");

    return 0;
}

/* NOTAS

-TESTAR TESTAR EXCLUIR TESTAR INSERIR TESTAR EDITAR TESTAR *TODAS AS FUNÇÕES*

*/