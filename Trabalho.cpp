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
    cout << "------------MENU------------\n" ;
    cout << "[0] - Encerrar programa\n" ;
    cout << "[1] - Ordenar arquivo\n" ;
    cout << "[2] - Remover universidade\n" ;
    cout << "[3] - Adicionar universidade\n" ;
    cout << "[4] - Buscar\n" ;
    cout << "[5] - Imprimir cadastros\n" ;
    cout << "Escolha uma opção > ";
}

int main()
{

    ifstream arqCSV("rankUniversidades.csv");
    ofstream newArqBi;
    newArqBi.open("rankToBi.bin", ios::binary | ios::out | ios::in | ios::trunc);
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

    cout << "Arquivo gerado com sucesso!" << endl;

    arqCSV.close();

    int opc;
    // MENU DE OPÇÕES COM CHAMADA DA FUNÇÃO printMenu ();
    do
    {
        printMenu();
        cin >> opc;
        cout << "----------------------------\n" ;

        switch (opc)
        {
            case 0:
                break;
            case 1:
                cout << "FIZ A FUNÇÃO!\n";
                break;
            case 2:
                cout << "FIZ A FUNÇÃO!\n";
                break;
            case 3:
                cout << "FIZ A FUNÇÃO!\n";
                break;
            case 4:
                cout << "FIZ A FUNÇÃO!\n";
                break;
            case 5:
                cout << "FIZ A FUNÇÃO\n!";
                break;
            default:
                cout << "DIGITE UMA OPÇÃO VÁLIDA !\n";
        }
    } while (opc != 0);

    
    
    
    newArqBi.close();

    return 0;
}



/*
void ordenarPorCidade(Dados *universidade, int tam)
{
    cout << "Digite o nome da cidade > ";
    string cidade;
    getline(cin, cidade);
    for (int i = 0; i < tam; i++)
    {
        if (universidade[i].cidade == cidade)
            cout << universidade[i].ano << " " << universidade[i].rank << " " << universidade[i].nome << " " << universidade[i].pontuacao << " " << universidade[i].cidade << universidade[i].pais << endl;
    }
    cout << endl;
}
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