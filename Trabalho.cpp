#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <sstream>

// Participantes > Bernardo Bertante Martins, Esther Silva Magalhaes, Ítalo Alves Rabelo

// Ano,Nome,Pontuacao,Cidade,País

// Ordenação por Cidade e por País

using namespace std;

struct Dados
{
    int ano;
    char nome[200]; // 1 ponto
    float pontuacao;
    char cidade[200]; //
    char pais[200];   //
};

Dados convertVetor(string vetor[])
{
    Dados dados; //
    dados.ano = stoi(vetor[0]);
    strcpy(dados.nome, vetor[1].c_str());
    dados.pontuacao = stof(vetor[2]);
    strcpy(dados.cidade, vetor[3].c_str());
    strcpy(dados.pais, vetor[4].c_str());

    return dados;
}

void printMenu()
{
    cout << "\n------------MENU------------\n" ;
    cout << "[0] - Encerrar programa\n" ;
    cout << "[1] - Ordenar arquivo\n" ;
    cout << "[2] - Remover universidade\n" ;
    cout << "[3] - Adicionar universidade\n" ;
    cout << "[4] - Buscar\n" ;
    cout << "[5] - Imprimir cadastros\n" ;
    cout << "[6] - Converter binário para csv\n" ;
    cout << "\nEscolha uma opção > ";
}

void ordenacao(fstream &newArqBi)
{
    // OPERAÇÕES PARA CALCULAR A QUANTIDADE DE REGISTROS PRESENTES NO ARQUIVO BINÁRIO
    long int tamArq = newArqBi.tellg();
    int quantUni = int(tamArq / sizeof (Dados));
    Dados vet[quantUni];
    cout << "\nQUANTI UNI = " << quantUni << endl;

    // LOOP PARA REALIZAR A LEITURA DO VETOR DE STRUCT A PARTIR DO ARQUIVO BINÁRIO
    for (int i = 0; i < quantUni; i++)
    {
        newArqBi.seekg (0, newArqBi.beg);
        newArqBi.seekg (i * sizeof(Dados));
        newArqBi.read ((char*)&vet[i], sizeof (Dados));
        //cout << vet[i].ano << " " << vet[i].nome << " " << vet[i].pontuacao << " " << vet[i].cidade << " "  << vet[i].pais << endl;
    }
    
    newArqBi.close();
}

void buscarPorCidade(fstream &newArqBi)
{
    // OPERAÇÕES PARA CALCULAR A QUANTIDADE DE REGISTROS PRESENTES NO ARQUIVO BINÁRIO
    long int tamArq = newArqBi.tellg();
    int quantUni = int(tamArq / sizeof (Dados));
    Dados vet[quantUni];

    // LOOP PARA REALIZAR A LEITURA DO VETOR DE STRUCT A PARTIR DO ARQUIVO BINÁRIO
    for (int i = 0; i < quantUni; i++)
    {
        newArqBi.seekg (0, newArqBi.beg);
        newArqBi.seekg (i * sizeof(Dados));
        newArqBi.read ((char*)&vet[i], sizeof (Dados));
        //cout << vet[i].ano << " " << vet[i].nome << " " << vet[i].pontuacao << " " << vet[i].cidade << " "  << vet[i].pais << endl;
    }

    cout << "Digite o nome da cidade > ";
    cin.clear();
    cin.ignore();
    string cidade;
    getline (cin, cidade);
    cout << endl;
    for (int i = 0; i < quantUni; i++)
    {
        if (vet[i].cidade == cidade)
            cout << vet[i].ano << " " << vet[i].nome << " " << vet[i].pontuacao << " " << vet[i].cidade << " "  << vet[i].pais << endl;
    }
    cout << endl;
    newArqBi.close();
}

void buscarPorPais(fstream &newArqBi)
{
    // OPERAÇÕES PARA CALCULAR A QUANTIDADE DE REGISTROS PRESENTES NO ARQUIVO BINÁRIO
    long int tamArq = newArqBi.tellg();
    int quantUni = int(tamArq / sizeof (Dados));
    Dados vet[quantUni];

    // LOOP PARA REALIZAR A LEITURA DO VETOR DE STRUCT A PARTIR DO ARQUIVO BINÁRIO
    for (int i = 0; i < quantUni; i++)
    {
        newArqBi.seekg (0, newArqBi.beg);
        newArqBi.seekg (i * sizeof(Dados));
        newArqBi.read ((char*)&vet[i], sizeof (Dados));
        //cout << vet[i].ano << " " << vet[i].nome << " " << vet[i].pontuacao << " " << vet[i].cidade << " "  << vet[i].pais << endl;
    }

    cout << "Digite o nome do país > ";
    cin.clear();
    cin.ignore();
    string pais;
    getline (cin, pais);
    //cin.ignore();
    cout << endl;
    for (int i = 0; i < quantUni; i++)
    {
        if (vet[i].pais == pais)
            cout << vet[i].ano << " " << vet[i].nome << " " << vet[i].pontuacao << " " << vet[i].cidade << " "  << vet[i].pais << endl;
    }
    cout << endl;
    newArqBi.close();
}

int retornaEscolha ()
{
    int n;
    cin >> n;
    return n;
}

int main()
{

    ifstream arqCSV("rankUniversidades.csv");
    fstream newArqBi;
    newArqBi.open("rankToBi.bin", ios::binary | ios::out | ios::in);
    string vetor[5];
    string coluna;
    string aux;

    while (getline(arqCSV, aux))
    {
        stringstream linha(aux);
        for (int i = 0; i < 5; i++)
        {
            getline(linha, coluna, ',');
            vetor[i] = coluna;
        }

        Dados dados = convertVetor(vetor);
        newArqBi.write(reinterpret_cast<char *>(&dados), sizeof(Dados));
    }
    newArqBi.close();

    cout << "Arquivo gerado com sucesso!" << endl;

    arqCSV.close();

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
            [6] - Converter binário para csv*/
        cin >> opc;
        cout << "----------------------------\n" ;

        int opt = 0; //  variável que receberá o retorno da função  retornaEscolha();

        switch (opc)
        {
            case 0:
                break;
            case 1:
                
                newArqBi.open ("rankToBi.bin", ios::in | ios::binary | ios::ate);
                ordenacao(newArqBi);
                break;

            case 2:
                cout << "FIZ A FUNÇÃO!\n";
                break;

            case 3:
                cout << "FIZ A FUNÇÃO!\n";
                break;

            case 4:
                newArqBi.open ("rankToBi.bin", ios::in | ios::binary | ios::ate);
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
                //função converte binario para csv
                break;
            default:
                cout << "DIGITE UMA OPÇÃO VÁLIDA !\n";
        }
    } while (opc != 0);

    
    
    
    

    return 0;
}



/*

void ordenarPorPais(Dados *universidade, int tam)
{
    cout << "Digite o nome do país > ";
    string pais;
    getline(cin, pais);
    for (int i = 0; i < tam; i++)
    {
        if (universidade[i].pais == pais)
            cout << universidade[i].ano << " " << universidade[i].rank << " " << universidade[i].nome << " " << universidade[i].pontuacao << " " << universidade[i].cidade << universidade[i].pais << endl;
    }
    cout << endl;
}
*/