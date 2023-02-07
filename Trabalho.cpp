#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <sstream>

// Participantes > Bernardo Bertante Martins, Esther Silva Magalhaes, Ítalo Alves Rabelo

// Ano,Rank,Nome,Pontuacao,Cidade,País

// Ordenação por Cidade e por País

using namespace std;

struct Dados
{
    int ano;
    int rank;
    char nome[50]; // 1 ponto
    float pontuacao;
    char cidade[50]; //
    char pais[50];   //
};

Dados convertVetor(string vetor[])
{
    Dados dados; //
    dados.ano = stoi(vetor[0]);
    dados.rank = stoi(vetor[1]);
    strcpy(dados.nome, vetor[2].c_str());
    dados.pontuacao = stof(vetor[3]);
    strcpy(dados.cidade, vetor[4].c_str());
    strcpy(dados.pais, vetor[5].c_str());

    return dados;
}

int main()
{

    ifstream arqCSV("rankUniversidades.csv");
    ofstream newArqBi;
    newArqBi.open("rankToBi.bin", ios::binary | ios::out | ios::in | ios::trunc);
    string vetor[6];
    string coluna;
    string aux;

    while (getline(arqCSV, aux))
    {
        stringstream linha(aux);
        for (int i = 0; i < 6; i++)
        {
            getline(linha, coluna, ',');
            vetor[i] = coluna;
        }

        Dados dados = convertVetor(vetor);
        newArqBi.write(reinterpret_cast<char *>(&dados), sizeof(Dados));
    }

    cout << "Arquivo gerado com sucesso!" << endl;

    arqCSV.close();
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
