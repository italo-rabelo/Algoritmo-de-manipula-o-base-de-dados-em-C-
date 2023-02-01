#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdlib>
//Participantes > Bernardo Bertante Martins, Esther Silva Magalhaes, Ítalo Alves Rabelo

//Ano,Rank,Nome,Pontuacao,Cidade,País

//Ordenação por Cidade e por País

using namespace std;

struct Dados
{

    string ano;
    string rank;
    string nome;
    string pontuacao;
    string cidade;
    string pais;
};

void ordenarPorCidade (Dados *universidade, int tam)
{
    cout << "Digite o nome da cidade > ";
    string cidade;
    getline (cin, cidade);
    for (int i = 0; i < tam; i++)
    {
        if (universidade[i].cidade == cidade)
            cout << universidade[i].ano << " " << universidade[i].rank << " " << universidade[i].nome << " " << universidade[i].pontuacao << " " << universidade[i].cidade << universidade[i].pais << endl;
    }
    cout << endl;
}

void ordenarPorPais (Dados *universidade, int tam)
{
    cout << "Digite o nome do país > ";
    string pais;
    getline (cin, pais);
    for (int i = 0; i < tam; i++)
    {
        if (universidade[i].pais == pais)
            cout << universidade[i].ano << " " << universidade[i].rank << " " << universidade[i].nome << " " << universidade[i].pontuacao << " " << universidade[i].cidade << universidade[i].pais << endl;
    }
    cout << endl;
}

int main ()
{
    int tam = 50;
    Dados *universidade = new Dados [tam];
    ifstream read ("rankUniversidades.csv");
    if (read)
    {
        int i = 0;
        while (!read.eof ())
        {
            getline (read, universidade[i].ano, ',');
            getline (read, universidade[i].rank, ',');
            getline (read, universidade[i].nome, ',');
            getline (read, universidade[i].pontuacao, ',');
            getline (read, universidade[i].cidade, ',');
            getline (read, universidade[i].pais, '\n');
            i++;
        }

    }
    else
        cout << "\nFATAL ERROR : FILE DOESN'T EXISTS !\n";
    read.close ();
    ordenarPorCidade (universidade, tam);
    return 0;
}