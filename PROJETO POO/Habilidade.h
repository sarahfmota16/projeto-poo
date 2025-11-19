#ifndef HABILIDADE_H
#define HABILIDADE_H

#include <string>
#include <map>

using namespace std;

// Mapa de efetividade simples para usar no jogo
static map<string, map<string, float>> TIPO_EFETIVIDADE = {
    {"Fogo",     {{"Gelo", 2.0f},  {"Terra", 2.0f},  {"Agua", 0.5f}}},
    {"Agua",     {{"Fogo", 2.0f},  {"Terra", 2.0f},  {"Eletrico", 0.5f}}},
    {"Eletrico", {{"Agua", 2.0f},  {"Terra", 0.5f}}},
    {"Gelo",     {{"Terra", 2.0f}, {"Fogo", 2.0f},   {"Agua", 0.5f}}},
    {"Terra",    {{"Eletrico", 2.0f}, {"Agua", 0.5f}, {"Gelo", 0.5f}}},
    {"Neutro",   {}}
};

class Habilidade {
public:
    string nome;
    string tipo;
    int danoBase;

    Habilidade(string n, string t, int d) : nome(n), tipo(t), danoBase(d) {}

    float obterMultiplicador(string tipoAlvo) {
        if (TIPO_EFETIVIDADE.count(tipo) && TIPO_EFETIVIDADE[tipo].count(tipoAlvo)) {
            return TIPO_EFETIVIDADE[tipo][tipoAlvo];
        }
        return 1.0f;
    }
};

#endif