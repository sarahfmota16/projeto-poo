#include "Personagem.h"
#include <iostream>

using namespace std;

Arqueiro::Arqueiro(string n, int pv, int f, int d, int a)
    : Personagem(n, pv, f, d, "Eletrico"), agilidade(a) {
}

int Arqueiro::atacar(Personagem& alvo) {
    int danoBase = forca + agilidade;

    if (verificarCritico()) {
        danoBase = (int)(danoBase * 1.5);
        cout << "(HEADSHOT!) ";
    }

    int danoFinal = alvo.reduzirDanoPelaDefesa(danoBase);

    cout << nome << " dispara em " << alvo.getNome()
        << " causando " << danoFinal << " de dano!\n";

    alvo.receberDano(danoFinal);
    return danoFinal;
}