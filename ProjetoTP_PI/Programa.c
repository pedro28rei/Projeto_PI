// Trabalho Pr�tico de Programa��o Imperativa
// Realizado por: Pedro Rei(26013) ; Gon�alo Gon�alves(26019) ; M�rio Macedo(25664)

#pragma region Bibliotecas 

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Permite o uso de acentos e carateres especiais
#include <locale.h>

#pragma endregion Bibliotecas usadas no trabalho

#pragma region Structs

// Define o n�mero m�ximo de participantes que o programa suporta,neste caso 100
#define MAX_PARTICIPANTES 100
// Define o n�mero m�ximo de atividades que o programa suporta,neste caso 100
#define MAX_ATIVIDADES 100


// Cria uma struct global chamada DadosParticipante que vai guardar informa��o do Ficheiro1
typedef struct {
	int numeroparticipante, telefone, idade;
	char nome[50];
} DadosParticipante;

// Cria uma v�riavel do tipo DadosParticipante em que cada participante fica com uma posi��o do array,o Participante 0001 com a posi�ao 0 e assim sucessivamente 
DadosParticipante Participante[MAX_PARTICIPANTES];

// Cria uma struct global chamada InformacaoAtividade que vai guardar informa��o do Ficheiro2
typedef struct {
	int numeroparticipante, distancia, duracao;
	char data[11], horainicio[6], atividade[20], unidademedida[3];
} InformacaoAtividade;

// Cria uma v�riavel do tipo InformacaoAtividade em que cada informa��o da atividade de um participante fica com uma posi��o do array, a primeira com a posi�ao 0 e assim sucessivamente 
InformacaoAtividade Atividade[MAX_ATIVIDADES];

// Cria uma struct global chamada PlanoAtividade que vai guardar informa��o do Ficheiro3
typedef struct {
	int numeroparticipante, distancia;
	char datainicio[11], datafim[11], horainicio[6], horafim[6], atividade[20], unidademedida[3];
} PlanoAtividade;

// Cria uma v�riavel do tipo PlanoAtividade em que cada informa��o do plano da atividade para participante fica com uma posi��o do array, a primeira com a posi�ao 0 e assim sucessivamente
PlanoAtividade Plano[MAX_ATIVIDADES];

#pragma endregion Structs utilizadas para armazenar os dados dos ficheiros

#pragma region Ficheiros

// Fun��o que faz o carregamento do Ficheiro1 e que vai guardar a informa��o do Ficheiro1 na struct DadosParticipante
void ler_ficheiro1() {

	// Abre o ficheiro em modo leitura
	FILE* fp;
	fp = fopen("Ficheiro1.txt", "r");

	// Come�a na linha 0
	int linha = 0;

	// Verifica se se o arquivo foi aberto com sucesso, logo se n�o � NULL
	if (fp != NULL) {

		// Faz o processo enquanto n�o � o fim do ficheiro
		while (!feof(fp)) {

			// Guarda as vari�veis da linha que est� a ser lida do ficheiro
			fscanf(fp, "%d;%[^;];%d;%d", &Participante[linha].numeroparticipante, Participante[linha].nome, &Participante[linha].telefone, &Participante[linha].idade);

			// Passa para a linha seguinte(posi��o seguinte do array da struct)
			linha++;
		}
	}
	// Caso o ficheiro n�o exista ou aconte�a algum erro aparece esta mensagem ao utilizador
	else printf("\tErro ao abrir o Ficheiro1!\n");

	// Fecha o ficheiro
	fclose(fp);
}

// Fun��o que faz o carregamento do Ficheiro2 e que vai guardar a informa��o do Ficheiro2 na struct InformacaoAtividade
void ler_ficheiro2() {

	// Abre o ficheiro em modo leitura
	FILE* fp;
	fp = fopen("Ficheiro2.txt", "r");

	// Come�a na linha 0
	int linha = 0;

	// Verifica se se o arquivo foi aberto com sucesso, logo se n�o � NULL
	if (fp != NULL) {

		// Faz o processo enquanto n�o � o fim do ficheiro
		while (!feof(fp)) {

			// Guarda as vari�veis da linha que est� a ser lida do ficheiro
			fscanf(fp, "%d;%[^;];%[^;];%[^;];%d;%d;%[^\n]", &Atividade[linha].numeroparticipante, Atividade[linha].data, Atividade[linha].horainicio, Atividade[linha].atividade,
				&Atividade[linha].duracao, &Atividade[linha].distancia, Atividade[linha].unidademedida);

			// Passa para a linha seguinte(posi��o seguinte do array da struct)
			linha++;
		}
	}
	// Caso o ficheiro n�o exista ou aconte�a algum erro aparece esta mensagem ao utilizador
	else printf("\tErro ao abrir o Ficheiro2!\n");

	// Fecha o ficheiro
	fclose(fp);
}

// Fun��o que faz o carregamento do Ficheiro3 e que vai guardar a informa��o do Ficheiro3 na struct PlanoAtividade
void ler_ficheiro3() {

	// Abre o ficheiro em modo leitura
	FILE* fp;
	fp = fopen("Ficheiro3.txt", "r");

	// Contador come�a na linha 0
	int linha = 0;

	//Verifica se se o arquivo foi aberto com sucesso, logo se n�o � NULL
	if (fp != NULL) {

		// Faz o processo enquanto n�o � o fim do ficheiro
		while (!feof(fp)) {

			// Guarda as vari�veis da linha que est� a ser lida do ficheiro
			fscanf(fp, "%d;%[^;];%[^;];%[^;];%[^;];%[^;];%d;%s", &Plano[linha].numeroparticipante, Plano[linha].datainicio, Plano[linha].horainicio, Plano[linha].datafim, Plano[linha].horafim,
				Plano[linha].atividade, &Plano[linha].distancia, Plano[linha].unidademedida);

			// Passa para a linha seguinte(posi��o seguinte do array da struct)
			linha++;
		}
	}
	// Caso o ficheiro n�o exista ou aconte�a algum erro aparece esta mensagem ao utilizador
	else printf("\tErro ao abrir o Ficheiro3!\n");

	// Fecha o ficheiro
	fclose(fp);
}

#pragma endregion Func�es utilizadas para ler os ficheiros

#pragma region Resolu��o

// Fun��o que transforma a data,que foi armazenada numa string, em um valor time_t  e permite fazer a compara��o depois 
time_t str2time(char* string) {


	int dia, mes, ano;

	// Parte a string em tr�s inteiros
	sscanf(string, "%d-%d-%d", &dia, &mes, &ano);

	// Cria uma struct com os valores extra�dos
	struct tm tm = { 0 };
	tm.tm_mday = dia;
	tm.tm_mon = mes - 1;
	tm.tm_year = ano - 1900;

	// Converte a struct tm num valor time_t 
	return mktime(&tm);
}

// Fun��o que atrav�s de o nome de uma atividade e um per�odo de tempo introduzido pelo utilizador, identifica o n�mero de participantes que realizou a atividade
void nrparticipantesatividade() {

	char atividade[20], datainicio[11], datafim[11];

	printf("|| Numero de partipantes que realizaram uma atividade desportiva num determinado periodo de tempo ||\n");
	printf("\n\t-Insira o nome da atividade: ");
	scanf("%s", atividade);
	printf("\n\t-Insira a data inicial (use o formato dd-mm-aaaa): ");
	scanf("%s", datainicio);
	printf("\n\t-Insira a data final (use o formato dd-mm-aaaa): ");
	scanf("%s", datafim);


	// Inicializa o contador de n�mero participantes
	int numeroParticipantes = 0;

	// Cria um array para armazenar os participantes que realizaram a atividade de modo a evitar que se repita o mesmo participante 
	int participantescontados[MAX_PARTICIPANTES] = { 0 };

	// Loop pela array da struct Atividade
	for (int i = 0; i < MAX_ATIVIDADES; i++) {

		// Converte a data da Atividade em um valor time_t
		time_t atividadeData = str2time(Atividade[i].data);

		// Converte a datainicio e datafim fornecidas pelo utilizador para valores time_t
		time_t inicio = str2time(datainicio);
		time_t fim = str2time(datafim);

		// Verifica se a data da atividade do ficheiro est� entre as datas dadas pelo utilizador, e se � a atividade indicada pelo utilizador
		if (atividadeData >= inicio && atividadeData <= fim && strncmp(Atividade[i].atividade, atividade, 20) == 0) {

			// Verifica se o participante j� foi ou n�o contado, logo se a posi��o do array nao tiver l� 0, mas sim 1 � porque j� foi
			if (participantescontados[Atividade[i].numeroparticipante] == 0) {

				// Se o participante ainda n�o tiver sido contado, incrementa o contador e adiciona o participante ao Array
				numeroParticipantes++;
				participantescontados[Atividade[i].numeroparticipante] = 1;
			}
		}
	}
	printf("\nA atividade %s foi feita por %d participantes.\n", atividade, numeroParticipantes);
}

/* Fun��o que compara o n�mero dos participantes que est�o em cada posi��o do array e retorna um negativo se o n�mero do participante do segundo elemento � maior que o do primeiro, zero
se os elementos s�o iguais, e um valor positivo se o n�mero de participante do segundo elemento � menor que o do primeiro */
int comparar_participantes(const void* a, const void* b) {
	const InformacaoAtividade* ia = (const InformacaoAtividade*)a;
	const InformacaoAtividade* ib = (const InformacaoAtividade*)b;
	return ib->numeroparticipante - ia->numeroparticipante;;
}

// Fun��o que faz a listagem dos praticantes, por ordem decrescente do n�mero de praticante, que realizaram alguma atividade desportiva num determinado per�odo introduzido pelo utilizador
void ListagemPraticantes() {

	char datainicio[11], datafim[11];

	printf("\n|| Listagem dos praticantes que realizaram alguma atividade desportiva num determinado periodo de tempo ||\n");
	printf("\n\t-Insira a data inicial (use o formato dd-mm-aaaa): ");
	scanf("%s", datainicio);
	printf("\n\t-Insira a data final (use o formato dd-mm-aaaa): ");
	scanf("%s", datafim);

	// Vai ordenar o array por ordem descrecente de n�mero de participante,
	qsort(Atividade, MAX_ATIVIDADES, sizeof(InformacaoAtividade), comparar_participantes);

	printf("\nNeste periodo do tempo foram realizadas atividades pelos seguintes participantes:\n");

	// Cria um array para armazenar os participantes que realizaram uma atividade no espa�o de tempo indicado pelo utilizador de modo a evitar que se repita o mesmo participante 
	int participantescontados[MAX_PARTICIPANTES] = { 0 };

	// Loop pela array da struct Atividade
	for (int i = 0; i < MAX_ATIVIDADES; i++) {

		// Converte a data da Atividade em um valor time_t
		time_t atividadeData = str2time(Atividade[i].data);

		// Converte a datainicio e datafim fornecidas pelo utilizador para valores time_t
		time_t inicio = str2time(datainicio);
		time_t fim = str2time(datafim);

		// Verifica se a data da atividade do ficheiro est� entre as datas dadas pelo utilizador
		if (atividadeData >= inicio && atividadeData <= fim) {

			// Percorre o array da Struct dos Participantes
			for (int j = 0; j < MAX_PARTICIPANTES; j++)
			{
				//Verifica se o Numero do Participante � igual na struct Atividade e na struct Participante
				if (Participante[j].numeroparticipante == Atividade[i].numeroparticipante) {
					// Verifica se o participante j� foi ou n�o contado, logo se a posi��o do array nao tiver l� 0, mas sim 1 � porque j� foi
					if (participantescontados[Atividade[i].numeroparticipante] == 0) {

						printf("| Participante: %d | Nome: %s | Idade: %d | Telefone: %d | \n", Participante[j].numeroparticipante, Participante[j].nome,
							Participante[j].idade, Participante[j].telefone);

						participantescontados[Atividade[i].numeroparticipante] = 1;
					}
				}
			}

		}

	}

}

// Fun��o utilizada para apresentar o plano de atividades de determinado tipo, para um determinado per�odo e praticante introduzidos pelo utilizador
void apresentacao_plano() {

	char atividade[20], datainicio[11], datafim[11];
	int numeroParticipante;

	printf("||  Plano de atividades de determinado tipo, para um determinado periodo e praticante ||\n");
	printf("\n\t-Insira o nome da atividade: ");
	scanf("%s", atividade);
	printf("\n\t-Insira a data inicial (use o formato dd-mm-aaaa): ");
	scanf("%s", datainicio);
	printf("\n\t-Insira a data final (use o formato dd-mm-aaaa): ");
	scanf("%s", datafim);
	printf("\n\t-Insira o numero do participante: ");
	scanf("%d", &numeroParticipante);


	printf("\nNeste periodo do tempo estes sao os planos da atividade %s do participante %d:\n", atividade, numeroParticipante);

	// Loop pela array da struct Plano
	for (int i = 0; i < MAX_ATIVIDADES; i++) {

		// Converte a datainicio e datafim do Plano em um valor time_t
		time_t dataInicioFicheiro = str2time(Plano[i].datainicio);
		time_t dataFimFicheiro = str2time(Plano[i].datafim);

		// Converte a datainicio e datafim fornecidas pelo utilizador para valores time_t
		time_t inicio = str2time(datainicio);
		time_t fim = str2time(datafim);

		// Verifica se a data da atividade do ficheiro est� entre as datas dadas pelo utilizador, e se � a atividade e o utilizador indicados pelo utilizador
		if (dataInicioFicheiro >= inicio && dataFimFicheiro <= fim && strncmp(Plano[i].atividade, atividade, 20) == 0 && Plano[i].numeroparticipante == numeroParticipante) {

			printf("| Data Inicio : %s | Hora Inicio: %s | Data Fim: %s | Hora Fim: %s | Distancia: %d%s |\n", Plano[i].datainicio,
				Plano[i].horainicio, Plano[i].datafim, Plano[i].horafim, Plano[i].distancia, Plano[i].unidademedida);
		}
	}
}


// Fun��o que faz o c�lculo dos tempos totais e m�dias dos tempos por atividade em que cada praticante esteve envolvido num determinado per�odo introduzido pelo utilizador
void temposemedias() {

	char datainicio[11], datafim[11];

	printf("|| Tempos medios e total de cada participante ||\n");
	printf("\n\t-Insira a data inicial (use o formato dd-mm-aaaa): ");
	scanf("%s", datainicio);
	printf("\n\t-Insira a data final (use o formato dd-mm-aaaa): ");
	scanf("%s", datafim);

	// Converte a datainicio e datafim fornecidas pelo utilizador para valores time_t
	time_t inicio = str2time(datainicio);
	time_t fim = str2time(datafim);

	printf("\nNeste periodo do tempo estes sao os tempos totais e medios de cada participante nas respetivas atividades:\n");

	// Loop pela array da struct Plano
	for (int i = 0; i < MAX_ATIVIDADES; i++) {
		
		// Vari�vel que ir� armazenar a duracao total da atividade do participante, sempre que se avan�ar no loop da struct Plano (ficheiro3), voltar� a 0
		int duracao = 0;
		// Vari�vel que ir� armazenar as vezes que um participante fez a mesma atividade, sempre que se avan�ar no loop da struct Plano (ficheiro3), voltar� a 0
		int contador = 0;

		// Loop pela array da struct Atividade
		for (int j = 0; j < MAX_ATIVIDADES; j++) {

			// Converte a data da struct Atividade em um valor time_t
			time_t dataFicheiro = str2time(Atividade[j].data);

			// Verifica se a data da atividade do ficheiro est� entre as datas dadas pelo utilizador, e se � a atividade e o utilizador s�o iguais
			if (dataFicheiro >= inicio && dataFicheiro <= fim && Plano[i].numeroparticipante == Atividade[j].numeroparticipante && strncmp(Plano[i].atividade, Atividade[j].atividade, 20) == 0) {

				duracao += Atividade[j].duracao;
				contador++;
			}

		}

		// Se o contador for diferente de 0, significa que pelo menos uma vez o praticante fez a Atividade
		if (contador != 0 && Plano[i].numeroparticipante != 0) {
			printf("| Participante: %d | Atividade: %s | Duracao: %d | Tempo medio: %d minutos |\n", Plano[i].numeroparticipante, Plano[i].atividade, duracao, duracao / contador);
		}
	}
}

// Fun��o que gera a tabela
void tabela() {

	printf("|| Tabela de atividades planeadas e realizadas para todos os praticantes ||\n");

	// Imprime o cabe�alho da tabela
	printf("\t___________________________________________________________________________________________________________________________________________________________________________________________");
	printf("\n\t| Numero Participante |                  Nome                     |      Atividade    |       Data Planeada       |      Data Realizada      | Valor Planeado | Valor Realizado | Medida  |\n");
	
	// Percorre a struct Participantes
	for (int i = 0; i < MAX_PARTICIPANTES; i++)
	{
		printf("\t|---------------------|-------------------------------------------|-------------------|---------------------------|--------------------------|----------------|-----------------|---------|\n");
		
		// Quando encontra a primeira a c�lula vazia (valor 0) acaba o ciclo pois n�o existem mais participantes
		if (Participante[i].numeroparticipante == 0)
		{
			break;
		}

		// Percorre a struct Plano
		for (int j = 0; j < MAX_ATIVIDADES; j++)
		{
			// Vari�vel que ir� guardar a soma das dist�ncias de cada atividade do Participante
			int distancia = 0, contador = 0;
			// Vari�vel que ir� armazenar as datas que o Participante realizou as atividades
			char data[25] , unidademedida[3];

			// Caso encontre um n�mero do participante na Struct Plano igual ao n�mero do Participante atual da struct Participante
			// Iniciar� o loop pela struct Atividade
			// Caso n�o encontre ir� continuar a percorrer a Struct Plano
			if (Participante[i].numeroparticipante == Plano[j].numeroparticipante) {
				
				// Percorre a sturct Atividade
				for (int k = 0; k < MAX_ATIVIDADES; k++)
				{
					// Verifica se o n�mero do participante � igual em ambas as structs e se a atividade � a mesma
					if (Atividade[k].numeroparticipante == Plano[j].numeroparticipante && strncmp(Plano[j].atividade, Atividade[k].atividade, 20) == 0) {
						
						// Na primeira entrada ir� armazenar a data da struct numa vari�vel
						if (contador == 0) {

							// Copia a string da struct Atividade para a vari�vel data
							strcpy(data, Atividade[k].data);
							contador++;
						}
						// Caso o Praticante tenha realizado mais de uma vez a mesma Atividade juntamos as datas em que realizou essa atividade
						else {
							char string[3] = ", ";
							
							//Concatena��o de strings, junta as strings "string" e a string da struct Atividade na string "data"
							strcat(data, string);
							strcat(data, Atividade[k].data);
						}
						distancia += Atividade[k].distancia;
						strcpy(unidademedida, Atividade[k].unidademedida);
					}
				}
				// Print realizado fora do loop da struct Atividade para n�o imprimir dados desnecess�rios 
				printf("\t| %-19d | %-41s | %-17s | %-12sa  %s | %-24s | %-14.2d | %-15.2d | %-7s |\n", Participante[i].numeroparticipante,
					Participante[i].nome, Plano[j].atividade, Plano[j].datainicio, Plano[j].datafim, data, Plano[j].distancia, distancia,
					unidademedida);
			}
		}
	}

}

#pragma endregion Fun��es utilizadas para os exerc�cios 4, 5, 6, 7, 8

#pragma region Seguidores

// Matriz criada para armazenar o n�mero de partcipante e os seus seguidores
int seguidores[MAX_PARTICIPANTES][MAX_PARTICIPANTES] = { 0 };

// Fun��o utilizada para registar os seguidores na matriz
void registarSeguidores() {

	printf("|| Funcionalidade que regista que um praticante segue o outro e apresenta uma listagem de todos os praticantes e seus seguidores ||\n");

	int numeroParticipante, numeroSeguidor;
	printf("\n\tInsira o numero do Participante que deseja adicionar um seguidor: ");
	scanf("%d", &numeroParticipante);
	printf("\n\tInsira o numero do Partcipante que deseja adicionar como seguidor do participante %d: ", numeroParticipante);
	scanf("%d", &numeroSeguidor);

	// O n�mero inserido pelo utilizador corresponde � coluna desse mesmo partcipante
	seguidores[0][numeroParticipante] = numeroParticipante;
	
	// Loop para percorrer a coluna do n�mero do Participante inserido pelo utilizador
	for (int i = 1; i < MAX_PARTICIPANTES; i++)
	{
		// Assim que encontrar a primeira linha com valor 0 ir� guardar nessa linha o n�mero do seguidor
		if (seguidores[i][numeroParticipante] == 0)
		{
			seguidores[i][numeroParticipante] = numeroSeguidor;
			break;
		}
	}
	// Loop que percorre as colunas
	for (int i = 0; i < MAX_PARTICIPANTES; i++)
	{
		if (seguidores[0][i] != 0)
		{
			printf("\n\tParticipante %d:\n\tSeguidores:\n", seguidores[0][i]);
		}

		// Loop que percorre as linhas
		for (int j = 1; j < MAX_PARTICIPANTES; j++)
		{
			// Vai imprimrir se o valor da linha for diferente de 0
			if (seguidores[j][i]) {
				printf("\t| %d |\n", seguidores[j][i]);
			}
		}
	}
}

// Fun��o utilizada para imprimir as atividades com mais tempo dos seguidores de um determinado participante
void seguidorMelhorTempo() {
	
	printf("|| Listagem por atividade com o praticante com o maior tempo de pratica dessa atividade, e o respetivo tempo, dos seus seguidores||\n");

	int praticante, melhortempo = 0, contador = 0, tempototal = 0;
	// N�mero Praticante [0] | Tempo [1]
	int atividadeTempo[MAX_PARTICIPANTES][2] = { 0 };
	// Atividade
	char atividade[MAX_ATIVIDADES][20];

	printf("\n\tInsira o numero do praticante:");
	scanf("%d", &praticante);

	// Percorre as linhas da coluna do praticante inserido pelo utilizador na matriz Seguidores
	for (int i = 1; i < MAX_PARTICIPANTES; i++)
	{
		// Percorre a struct Plano
		for (int j = 0; j < MAX_PARTICIPANTES; j++)
		{
			// Vari�vel que armazena o tempo total
			tempototal = 0;

			// Caso o numero do participante na Struct Plano seja igual ao numero do participante do seguidor atual da matriz Seguidores
			// Ir� percorrer a matriz Atividade de forma a somar os tempos praticados pelo participante na atividade
			// Caso o numero seja diferente ir� avan�ar no loop da Struct Plano
			if (Plano[j].numeroparticipante == seguidores[i][praticante]){
				
				// Loop pela struct Atividade
				for (int k = 0; k < MAX_ATIVIDADES; k++)
				{
					// Caso a atividade da Struct Atividade (Ficheiro2) seja igual � atividade da linha atual da struct Plano e, o n�mero do participante for o mesmo incrementa o tempo ao tempototal
					// Repete o processo at� acabar o loop
					if (Atividade[k].numeroparticipante == seguidores[i][praticante] && strncmp(Atividade[k].atividade, Plano[j].atividade, 20) == 0) {
						tempototal = tempototal + Atividade[k].duracao;
						contador++;
					}
				}

				// Loop pelas matrizes criadas para armazenar os dados dos seguidores com mais tempo em cada atividade
				for (int l = 0; l < MAX_PARTICIPANTES; l++)
				{
					// Caso a atividade atual da struct Plano seja igual � Atividade armazenada na matriz atividade
					if (strcmp(atividade[l], Plano[j].atividade) == 0) {

						// Ir� verificar se o tempototal � maior do valor anteriormente guardado de outro participante
						// Se for maior ir� substituir os dados j� guardados pelos dados do novo participante
						if (tempototal > atividadeTempo[l][1])
						{
							atividadeTempo[l][0] = seguidores[i][praticante];
							atividadeTempo[l][1] = tempototal;
							strcpy(atividade[l], Plano[j].atividade);
							break;
						}
						// Se n�o for maior d� break do loop pois n�o precisamos de guardar os dados sendo que j� temos o participante com mais tempo
						else {
							
							break;
						}
						
					}
					// Caso a linha da matriz ativididadeTempo esteja vazia (valor 0) significa que ainda n�o foram guardados dados daquela atividade pelo que ser�o armazenados
					else if (atividadeTempo[l][0] == 0 && tempototal != 0) {
						atividadeTempo[l][0] = seguidores[i][praticante];
						atividadeTempo[l][1] = tempototal;
						strcpy(atividade[l], Plano[j].atividade);
						break;
					}
				}
			}
		}
	}

	printf("\nAtividades com mais tempo dos seguidores do praticante %d: \n\n", praticante);
	for (int i = 0; i < MAX_PARTICIPANTES; i++)
	{
		if (atividadeTempo[i][0] == 0) {
			break;
		}
		printf("\tParticipante: %d | Tempo Total: %d | Atividade: %s\n", atividadeTempo[i][0], atividadeTempo[i][1], atividade[i]);
	}

}

// Fun��o utilizada para imprimir as atividades com mais tempo dos participantes seguidos por um determinado participante
void seguidoMelhorTempo() {

	int participante;

	printf("Insira o numero do participante que deseja ver os tempos dos seguidos: ");
	scanf("%d", &participante);

	int seguidos[MAX_PARTICIPANTES] = { 0 };

	// Loop pelas linhas da matriz onde est�o armazenados os participantes e os seus seguidores
	for (int i = 1; i < MAX_PARTICIPANTES; i++)
	{
		// Loop pelas colunas da matriz onde est�o armazenados os participantes e os seus seguidores
		for (int j = 0; j < MAX_PARTICIPANTES;  j++) {
			
			// Caso o n�mero do seguidor seja igual ao n�mero do praticante inserido pelo utilizador guardamos o cabe�alho dessa coluna
			// Na matriz dos seguidores a linha 0 corresponde ao participante e as seguintes correspondem aos seguidores desse praticante
			if (seguidores[i][j] == participante)
			{
				seguidos[seguidores[0][j]] = seguidores[0][j];
			}
		}
	}

	int tempototal;
	int atividadeTempo[MAX_PARTICIPANTES][2] = { 0 };
	char atividade[MAX_ATIVIDADES][20];

	for (int i = 1; i < MAX_PARTICIPANTES; i++)
	{
		for (int j = 0; j < MAX_PARTICIPANTES; j++)
		{
			tempototal = 0;
			if (Plano[j].numeroparticipante == seguidos[i]) {
				for (int k = 0; k < MAX_ATIVIDADES; k++)
				{
					if (Atividade[k].numeroparticipante == seguidos[i] && strncmp(Atividade[k].atividade, Plano[j].atividade, 20) == 0) {
						tempototal = tempototal + Atividade[k].duracao;
					}
				}
				for (int l = 0; l < MAX_PARTICIPANTES; l++)
				{
					if (strcmp(atividade[l], Plano[j].atividade) == 0) {
						if (tempototal > atividadeTempo[l][1])
						{
							atividadeTempo[l][0] = seguidos[i];
							atividadeTempo[l][1] = tempototal;
							strcpy(atividade[l], Plano[j].atividade);
							break;
						}
						else {

							break;
						}

					}
					else if (atividadeTempo[l][0] == 0 && tempototal != 0) {
						atividadeTempo[l][0] = seguidos[i];
						atividadeTempo[l][1] = tempototal;
						strcpy(atividade[l], Plano[j].atividade);
						break;
					}
				}
			}
		}
	}


	printf("\nAtividades com mais tempo dos seguidores do praticante %d: \n\n", participante);
	for (int i = 0; i < MAX_PARTICIPANTES; i++)
	{
		if (atividadeTempo[i][0] == 0) {
			break;
		}
		printf("\tParticipante: %d | Tempo Total: %d | Atividade: %s\n", atividadeTempo[i][0], atividadeTempo[i][1], atividade[i]);
	}
}

#pragma endregion Fun��es utilizadas para os exerc�cios 9, 10, 11

#pragma region Ficheiro

// Fun��o usada para criar um ficheiro com o nome "FicheiroDados.txt" e escrever nela a informa��o das structs e dos seguidores
void ficheiroComInformacoes() {
	
	FILE* fp;
	fp = fopen("FicheiroDados.txt", "w+");

	if (fp != NULL) {

		// Loop pela struct Participante e escreve os dados no ficheiro
		for (int i = 0; i < MAX_PARTICIPANTES; i++)
		{
			// Caso encontre um espa�o com valor significa que n�o existem mais dados na struct e ent�o d� break no loop
			if (Participante[i].numeroparticipante == 0)
			{
				break;
			}
			fprintf(fp, "%d;%s;%d%d\n", Participante[i].numeroparticipante, Participante[i].nome, Participante[i].telefone, Participante[i].idade);
		}
		// Loop pela struct Atividade e escreve os dados no ficheiro
		for (int l = 0; l < MAX_ATIVIDADES; l++)
		{
			// Caso encontre um espa�o com valor significa que n�o existem mais dados na struct e ent�o d� break no loop
			if (Atividade[l].numeroparticipante == 0)
			{
				break;
			}
			fprintf(fp, "%d;%s;%s;%s;%d;%d;%s\n", Atividade[l].numeroparticipante, Atividade[l].data, Atividade[l].horainicio, Atividade[l].atividade,
				Atividade[l].duracao, Atividade[l].distancia, Atividade[l].unidademedida);
		}
		// Loop pela struct Plano e escreve os dados no ficheiro
		for (int k = 0; k < MAX_ATIVIDADES; k++)
		{
			// Caso encontre um espa�o com valor significa que n�o existem mais dados na struct e ent�o d� break no loop
			if (Plano[k].numeroparticipante == 0)
			{
				break;
			}
			fprintf(fp, "%d;%s;%s;%s;%s;%s;%d;%s\n", Plano[k].numeroparticipante, Plano[k].datainicio, Plano[k].horainicio, Plano[k].datafim, 
				Plano[k].datafim, Plano[k].atividade, Plano[k].distancia, Plano[k].unidademedida);
		}
		// Loop pelas colunas da matriz dos seguidores
		for (int i = 0; i < MAX_PARTICIPANTES; i++)
		{
			// Caso encontre algum valor vai imprimir para o ficheiro
			if (seguidores[0][i] != 0) {
				fprintf(fp, "%d", seguidores[0][i]);

				// Ap�s encontrar um valor vai percorrer as linhas da coluna desse valor at� encontrar um campo vazio (valor 0) e assim dar break no loop
				for (int l = 1; l < MAX_PARTICIPANTES; l++)
				{
					if (seguidores[l][i] == 0)
					{
						fprintf(fp, "\n");
						break;
					}
					fprintf(fp, ";%d", seguidores[l][i]);
				}
			}
		}
		printf("Ficheiro criado com o nome FicheiroDados!\n");
	}
	else
	{
		printf("Erro ao criar ou a escrever no ficheiro!");
	}

	fclose(fp);
}

#pragma endregion Fun��o para criar um ficheiro com os dados do programa

#pragma region Menu

void menuSecundario() {

	printf("\nPressione qualquer tecla para regressar ao menu...");
	getch();
	system("cls");
	menu();
}

int menu(){
	int escolha;
	printf("\t\t ___________________________________________\n");
	printf("\t\t|\033[4m                   Menu:                   \033[0m|\n");
	printf("\t\t| Escolha: \t\t\t\t    |\n");
	printf("\t\t|                 1. Ponto 4                |\n");
	printf("\t\t|                 2. Ponto 5                |\n");
	printf("\t\t|                 3. Ponto 6                |\n");
	printf("\t\t|                 4. Ponto 7                |\n");
	printf("\t\t|                 5. Ponto 8                |\n");
	printf("\t\t|                 6. Ponto 9                |\n");
	printf("\t\t|                 7. Ponto 10               |\n");
	printf("\t\t|                 8. Ponto 11               |\n");
	printf("\t\t|                 9. Ponto 12               |\n");
	printf("\t\t|\033[4m                10. Sair!                  \033[0m|\n");
	printf("\n\t\t| Insira a sua escolha: ");
	scanf("%d", &escolha);

	switch (escolha)
	{
	case 1:
		system("cls");
		nrparticipantesatividade();
		menuSecundario();
		break;
	case 2:
		system("cls");
		ListagemPraticantes();
		menuSecundario();
		break;
	case 3:
		system("cls");
		apresentacao_plano();
		menuSecundario();
		break;
	case 4:
		system("cls");
		temposemedias();
		menuSecundario();
		break;
	case 5:
		system("cls");
		tabela();
		menuSecundario();
		break;
	case 6:
		system("cls");
		registarSeguidores();
		menuSecundario();
		break;
	case 7:
		system("cls");
		seguidorMelhorTempo();
		menuSecundario();
		break;
	case 8:
		system("cls");
		seguidoMelhorTempo();
		menuSecundario();
		break;
	case 9:
		system("cls");
		ficheiroComInformacoes();
		menuSecundario();
		break;
	case 10:
		exit(0);
		break;
	default:
		printf("\nEscolha Invalida!\n");
		menuSecundario();
		break;
	}

	return 0;
}

#pragma endregion Fun��es usadas para criar o menu

#pragma region Main

// Fun��o main
void main() {
	
	setlocale(LC_ALL, "pt_PT.utf8");

	ler_ficheiro1(); // Ex1
	ler_ficheiro2(); // Ex2
	ler_ficheiro3(); // Ex3
	menu();
}

#pragma endregion Fun��o Main