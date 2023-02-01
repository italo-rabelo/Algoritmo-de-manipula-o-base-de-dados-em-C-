#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdlib>

using namespace std;

struct canais
{

    string nome;
    string inscritos;
    string views;
    string videos;
    string genero;
    string ano;
};

int main()
{
    canais vet[50];
    string tempString;

    ifstream leitura("top50youtube.csv");

    while (leitura.good())
    {
        for (int i = 0; i < 49; i++)
        {
            getline(leitura, vet[i].nome, ',');
            getline(leitura, vet[i].inscritos, ',');
            // vet[i].inscritos = atoi(tempString.c_str());
            getline(leitura, vet[i].views, ',');
            getline(leitura, vet[i].videos, ',');
            getline(leitura, vet[i].genero, ',');
            getline(leitura, vet[i].ano, ',');

            cout << vet[i].nome << endl
                 << vet[i].inscritos << endl
                 << vet[i].views << endl
                 << vet[i].videos << endl
                 << vet[i].genero << endl
                 << vet[i].ano << endl
                 << endl
                 << "<------------------->" << endl;
        }

        leitura.close();
    }
    cout << "ATUALIZAÇÃOOOOOOOOOO";

    cout << "Hello World";
    cout << "Oiiii";
    cout<< "Noooo"
    return 0;
}