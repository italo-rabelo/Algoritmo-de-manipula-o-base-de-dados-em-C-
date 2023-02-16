#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <sstream>
//#include <windows.h>
// Participantes > Bernardo Bertante Martins, Esther Silva Magalhaes, Ítalo Alves Rabelo

// Ano,Nome,Pontuacao,Cidade,País

// Ordenação por Cidade e por País

using namespace std;

struct Dados // Struct na qual os dados do arquivo seguirão com o seu padrão (int, char, float, char, char, int);
{
    int ano;
    char nome[200]; // 1 ponto
    float pontuacao;
    char cidade[200]; //
    char pais[200];   //
    int valido = 1;
};

Dados convertVetor(string vetor[]) // Subprograma no qual trabalha em conjunto com as primeiras linhas da função main(); Converte as Strings provenientes do arquivo .csv para int, char e float;
{
    Dados dados; //
    dados.ano = stoi(vetor[0]);
    strcpy(dados.nome, vetor[1].c_str());
    dados.pontuacao = stof(vetor[2]);
    strcpy(dados.cidade, vetor[3].c_str());
    strcpy(dados.pais, vetor[4].c_str());

    return dados;
}

void printMenu() // Subprograma no qual sempre orientrá o usuário em relação as suas opções de escolha na manipulação dos arquivos;
{
    cout << "\n|--------------MENU--------------|\n"
         << endl;
    cout << "[0] - Encerrar programa\n";
    cout << "[1] - Ordenar arquivo\n";
    cout << "[2] - Remover universidade\n";
    cout << "[3] - Adicionar universidade\n";
    cout << "[4] - Buscar\n";
    cout << "[5] - Imprimir cadastros\n";
    cout << "[6] - Converter binario para CSV\n";
    cout << "[7] - Ver Universidades cadastradas\n"
         << endl;
    cout << "\nEscolha uma opcao > ";
}

void intercala(Dados *a, int inicio, int meio, int fim, int aux_opcao) {
	int i = inicio, j = meio + 1;
	int tamanho = fim - inicio + 1;
	Dados *aux = new Dados[tamanho]; // vetor auxiliar
	if(aux_opcao == 1){
		for (int k=0; k < tamanho; k++) {//ano
			if ((i <= meio) and (j <= fim)){ 
				if (a[i].ano >= a[j].ano){ 
					aux[k] = a[i]; // copia trecho1 em aux[]
					i++; 			// avança em trecho1
				} else { // 
					aux[k] = a[j]; // copia trecho2 em aux[]
					j++;	 		// avanca em trecho2
				}	
			} 
			else if (i > meio) { // terminou o trecho1	
				aux[k] = a[j];
				j++;
			} else { 				 // terminou o trecho2
				aux[k] = a[i];
				i++;
			}		
		}	
		// terminando: copiar de aux[] em a[inicio:fim]
		for (int k=0; k < tamanho; k++){ 
			a[inicio + k] = aux[k];
		}
	}
	else if(aux_opcao == 2){//pontuacao
		for (int k=0; k < tamanho; k++) {
			if ((i <= meio) and (j <= fim)){ 
				if (a[i].pontuacao >= a[j].pontuacao){ 
					aux[k] = a[i]; // copia trecho1 em aux[]
					i++; 			// avança em trecho1
				} else { // 
					aux[k] = a[j]; // copia trecho2 em aux[]
					j++;	 		// avanca em trecho2
				}	
			} 
			else if (i > meio) { // terminou o trecho1	
				aux[k] = a[j];
				j++;
			} else { 				 // terminou o trecho2
				aux[k] = a[i];
				i++;
			}		
		}	
		// terminando: copiar de aux[] em a[inicio:fim]
		for (int k=0; k < tamanho; k++){ 
			a[inicio + k] = aux[k];
		}
	}
}


void mergesort(Dados *a, int inicio, int fim, int escolha){
	int meio;
	if (inicio < fim) {
		meio = (inicio + fim)/2; 
		mergesort(a, inicio, meio,escolha);
		mergesort(a, meio+1, fim,escolha);
		intercala(a, inicio, meio, fim, escolha);
	}
}

void ordenacao(fstream &newArqBi,int aux_opcao) // Subprograma no qual permite a ordenação dos dados contidos no arquivo binário, isso por meio de um vetor auxiliar no qual reescreve os dados já ordenados novamente no arquivo binário;
{
    // OPERAÇÕES PARA CALCULAR A QUANTIDADE DE REGISTROS PRESENTES NO ARQUIVO BINÁRIO
    long int tamArq = newArqBi.tellg();
    int quantUni = int(tamArq / sizeof(Dados));
    Dados *vet = new Dados[quantUni];
    //cout << "\nQUANTI UNI = " << quantUni << endl;

    // LOOP PARA REALIZAR A LEITURA DO VETOR DE STRUCT A PARTIR DO ARQUIVO BINÁRIO
    for (int i = 0; i < quantUni; i++)
    {
        newArqBi.seekg(0, newArqBi.beg);
        newArqBi.seekg(i * sizeof(Dados));
        newArqBi.read((char *)&vet[i], sizeof(Dados));
        // cout << vet[i].ano << " " << vet[i].nome << " " << vet[i].pontuacao << " " << vet[i].cidade << " "  << vet[i].pais << endl;
    }

    newArqBi.close();

    // ORDENAÇÃO POR ANO(1) E POR PONTUAÇÃO(2)
    switch (aux_opcao)
    {
		case 1:
			mergesort(vet, 0, quantUni - 1, aux_opcao);
			// ordena por ano
			break;
		case 2:
			mergesort(vet, 0, quantUni - 1, aux_opcao);
			// ordena por pontuação
			break;
		default:
			cout << "OPÇÃO INVALIDA!\n";
			break;
    }
    //mostrar na tela a ordenação
    /*for(int i=0; i < quantUni; ++i){
		cout << vet[i].ano << " " << vet[i].nome << " " <<vet[i].pontuacao << " " << vet[i].cidade << " " << vet[i].pais << endl;
	}
	*/
	newArqBi.open("rankToBi.bin", ios::trunc | ios::out);
	
	for(int i=0; i < quantUni; ++i){
		newArqBi.seekg(i * sizeof(Dados));
		newArqBi.write(reinterpret_cast<char*>(&vet[i]), sizeof(vet[i]));
	}
	
	cout << "\nOrdenacao concluida!" << endl;
	
	/*
	if(opcaoOrd != 1 and opcaoOrd != 2){
		cout << "Opção de ordenação inválida" << endl;
	} 
	*/
}

void cadastrarUniv(Dados dados) // Subprograma no qual permite o usuário adicionar 1 ou Mais Universidades ao arquivo binário quando chamado;

{
    int opc;
    cout << "Quantas Universidades deseja cadastrar?" << endl
         << endl;
    cout << "[1] Cadastrar apenas 1." << endl
         << "[2] Mais de uma." << endl;
    cin >> opc;
    cout << endl;

    ofstream novoCadastro;
    novoCadastro.open("rankToBi.bin", ios::binary | ios::out | ios::app);

    switch (opc)
    {
    case 1: // AO SER EXECUTADO, SOMENTE UMA FACULDADE NOVA SERÁ ADICIONADA AO ARQUIVO
        cout << "Ano: ";
        cin >> dados.ano;
        cin.ignore();
        cout << "Nome: ";
        cin.getline(dados.nome, 200);
        cout << "Pontuacao: ";
        cin >> dados.pontuacao;
        cin.ignore();
        cout << "Cidade: ";
        cin.getline(dados.cidade, 200);
        cout << "País: ";
        cin.getline(dados.pais, 200);

        novoCadastro.write((char *)&dados, sizeof(Dados));
        break;

    case 2: // AO SER EXECUTADO, MAIS DE UMA FACULDADE NOVA SERÁ ADICIONADA AO ARQUIVO (ENTRARÁ EM UM LOOP [FOR()]);
        cout << "Quantas ao todo você deseja cadastrar? ";
        int segOpc;
        cin >> segOpc;
        cout << endl;

        for (int i = 0; i < segOpc; i++)
        {
            cout << "Nova Faculdade: " << i + 1 << endl;

            cout << "Ano: ";
            cin >> dados.ano;
            cin.ignore();
            cout << "Nome: ";
            cin.getline(dados.nome, 200);
            cout << "Pontuacao: ";
            cin >> dados.pontuacao;
            cin.ignore();
            cout << "Cidade: ";
            cin.getline(dados.cidade, 200);
            cout << "País: ";
            cin.getline(dados.pais, 200);

            novoCadastro.write((char *)&dados, sizeof(Dados));

            cout << endl;
        }
        break;

    default:
        cout << "Opacao Invalida";
        break;
    }

    novoCadastro.close();
}

void buscarPorCidade(fstream &newArqBi) // Subprograma que tem a função de fazer a busca de determinada cidade expecificada pelo usuário dentro do arquivo binário;
{
    // OPERAÇÕES PARA CALCULAR A QUANTIDADE DE REGISTROS PRESENTES NO ARQUIVO BINÁRIO
    long int tamArq = newArqBi.tellg();
    int quantUni = int(tamArq / sizeof(Dados));
    Dados vet[quantUni];

    cout << "\nDigite o nome da cidade > ";
    cin.clear();
    cin.ignore();
    char cidade[25];
    cin.getline(cidade, 25);
    cout << endl;

    int cont = 0;
    int aux = 0; // CONTADOR DE UNIVERSIDADES COM A MESMA CIDADE DA BUSCA
    Dados universidade;
    newArqBi.seekg(0, newArqBi.beg);


    // REALIZA A BUSCA NO ARQUIVO BINÁRIO
    while (cont < quantUni)
    {
        newArqBi.seekg (cont * sizeof (Dados));
        newArqBi.read ((char*) &universidade, sizeof (Dados));
        if (strcmp (cidade, universidade.cidade) == 0)
        {
            cout << universidade.ano << "  " << universidade.nome << "  " << universidade.pontuacao << "  " << universidade.cidade << "  " << universidade.pais << endl;
            aux++;
        }
        cont++;
    }

    if (aux == 0)
        cout << "Não ha universidades cadastradas nesta cidade !\n";

    newArqBi.close();
}

void buscarPorPais(fstream &newArqBi) // Subprograma que tem a função de fazer a busca de determinado país expecificado pelo usuário dentro do arquivo binário;
{
    // OPERAÇÕES PARA CALCULAR A QUANTIDADE DE REGISTROS PRESENTES NO ARQUIVO BINÁRIO
    long int tamArq = newArqBi.tellg();
    int quantUni = int(tamArq / sizeof(Dados));

    cout << "\nDigite o nome do país > ";
    cin.clear();
    cin.ignore();
    char pais[25];
    cin.getline(pais, 25);
    cout << endl;

    int cont = 0;
    int aux = 0; // CONTADOR DE UNIVERSIDADES COM A MESMA CIDADE DA BUSCA
    Dados universidade;
    newArqBi.seekg(0, newArqBi.beg);


    // REALIZA A BUSCA NO ARQUIVO BINÁRIO
    while (cont < quantUni)
    {
        newArqBi.seekg (cont * sizeof (Dados));
        newArqBi.read ((char*) &universidade, sizeof (Dados));
        if (strcmp (pais, universidade.pais) == 0)
        {
            cout << universidade.ano << "  " << universidade.nome << "  " << universidade.pontuacao << "  " << universidade.cidade << "  " << universidade.pais << endl;
            aux++;
        }
        cont++;
    }
    
    if (aux == 0)
        cout << "Não ha universidades cadastradas neste pais !\n";

    newArqBi.close();
}

int retornaEscolha() //
{
    int n;
    cin >> n;
    return n;
}

void printUniversidades(Dados dados) // Subprograma que exibe/printa no terminal o atual estado(informações) do arquivo binário, porém em decimal;
{
    ifstream arqBi;
    arqBi.open("rankToBi.bin", ios::binary | ios::in);
    while (arqBi.read((char *)&dados, sizeof(Dados)))
    {
        cout << dados.ano << " " << dados.nome << " " << dados.pontuacao << " " << dados.cidade << " " << dados.pais << endl;
    }
    arqBi.close();
}

void exportarCSV(fstream &arqBi) // Subprograma na qual sua função é de converter o atual arquivo binário para um arquivo novo .csv;
{
    ofstream arqCSV("binToCSV.csv");

    long int tamArq = arqBi.tellg();
    int quantUniv = int(tamArq / sizeof(Dados));
    int cont = 0;
    Dados universidade;

    while (cont < quantUniv)
    {
        arqBi.seekg(cont * sizeof(Dados));
        arqBi.read((char *)&universidade, sizeof(Dados));

        // if (universidade.valido != 0)
        {
            arqCSV << universidade.ano << ";" << universidade.nome << ";" << universidade.pontuacao << ";" << universidade.cidade << ";" << universidade.pais << endl;
        }

        cont++;
    }
}

int main()
{

    // Aqui começa a conversão dos dados do arquivo .csv para o arquivo binário;

	//SetConsoleOutputCP(CP_UTF8); 
    ifstream arqCSV("rankUniversidades.csv");
    fstream newArqBi;
    newArqBi.open("rankToBi.bin", ios::binary | ios::out | ios::in);
    string vetor[5];
    string coluna;
    string aux;
    Dados dados;

    while (getline(arqCSV, aux))
    {
        stringstream linha(aux);
        for (int i = 0; i < 5; i++)
        {
            getline(linha, coluna, ',');
            vetor[i] = coluna;
        }

        dados = convertVetor(vetor); // Até então todos os dados se encontram como string, porém a partir de agora são convertidos para seus devidos tipos por meio desse subprograma;
        newArqBi.write(reinterpret_cast<char *>(&dados), sizeof(Dados));
    }
    newArqBi.close();

    cout << "Arquivo gerado com sucesso!" << endl;

    arqCSV.close();

    printUniversidades(dados); // Os dados iniciais na abetura atual do programa são mostrados logo de cara para o usuáio, para que o mesmo tenha noção do estado corrente do arquivo binário;

    int opc; // varável do switch

    // MENU DE OPÇÕES COM CHAMADA DA FUNÇÃO printMenu ();
    do
    {
        printMenu();
        /*[0] - Encerrar programa
          [1] - Ordenar arquivo
          [2] - Remover universidade
          [3] - Adicionar universidade
          [4] - Buscar
          [5] - Imprimir cadastros
          [6] - Converter Binário para CSV
          [7] - Ver Universidades
          */
        cin >> opc;
        cout << "----------------------------\n";

        int opt = 0; //  variável que receberá o retorno da função retornaEscolha();

        switch (opc) // Dentro desse switch principal, dependendo de qual número o usuário digitar, diferentes funções são acionadas! Cada um com seus respctivos objetivos.
        {
        case 0:
            break;
        case 1:
            int opcao;
            newArqBi.open ("rankToBi.bin", ios::in | ios::binary | ios::ate);
            cout << "Escolha como o arquivo será ordenado:\n";
			cout << "[1] - Por Ano\n"
                 << "[2] - Por Pontuação\n";
            cin >> opcao;
            ordenacao(newArqBi,opcao);
            newArqBi.close();
            break;

        case 2:
            cout << "FIZ A FUNÇÃO\n!" << endl;
            break;

        case 3:
            cout << "Cadastrar nova(s) Universidades:\n"
                 << endl;
            cadastrarUniv(dados);
            break;

        case 4:
            newArqBi.open("rankToBi.bin", ios::in | ios::binary | ios::ate);
            cout << "[1] - Buscar por cidade\n[2] - Busca por país\nOu pressione qualquer número para voltar ao menu anterior\n> ";
            opt = retornaEscolha();
            if (opt == 1)
            {
                buscarPorCidade(newArqBi);
                break;
            }
            else if (opt == 2)
            {
                buscarPorPais(newArqBi);
                break;
            }
            else
                break;

        case 5:
            cout << "FIZ A FUNÇÃO\n!";
            break;

        case 6:
            cout << "Arquivo CSV exportado.";
            newArqBi.open("rankToBi.bin", ios::binary | ios::in | ios::out);
            exportarCSV(newArqBi);
            newArqBi.close();
            break;
        case 7:
            cout << "Universidades Cadastradas e Ativas:" << endl
                 << endl;
            printUniversidades(dados);
            break;
        default:
            cout << "DIGITE UMA OPÇÃO VÁLIDA !\n";
        }
    } while (opc != 0);

    return 0;
}
