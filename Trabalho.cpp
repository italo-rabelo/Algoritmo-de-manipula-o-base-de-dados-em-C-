#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdlib>
//Ano,Rank,Nome,Pontuacao,Cidade,País

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
int main ()
{
    Dados *universidade = new Dados [50];
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
    /*for (int i = 45; i < 50; i++)
    {
        cout << universidade[i].ano << " " << universidade[i].rank << " " << universidade[i].nome << " " << universidade[i].pontuacao << " " << universidade[i].cidade << universidade[i].pais << endl;
    }*/
    return 0;
}