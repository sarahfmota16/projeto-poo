#ifndef HABILIDADE_H
#define HABILIDADE_H

#include <string>
#include <map>

using namespace std;

extern map<string, map<string, float>> TIPO_EFETIVIDADE;

class Habilidade {
public:
    string nome;
    string tipo;
    int danoBase;

    Habilidade(string n, string t, int d);

    float obterMultiplicador(string tipoAlvo);
};

#endif
