#include "Personagem.h"

#include <iostream>

using namespace std;

Guerreiro::Guerreiro(string n, int pv, int f, int d, int re)

    : Personagem(n, pv, f, d, "Terra"), resistenciaEscudo(re) {
}

int Guerreiro::atacar(Personagem& alvo) {

    // Guerreiro recebe um pequeno bônus baseado no escudo
    int danoBase = forca + (resistenciaEscudo / 8);

    cout << nome << " ataca " << alvo.getNome()
        << " com um golpe poderoso!\n";

    // chance de crítico
    if (verificarCritico()) {
        danoBase = (int)(danoBase * 1.5);
        cout << "    (CRITICO!) Golpe devastador!\n";
    }

    int danoFinal = alvo.reduzirDanoPelaDefesa(danoBase);

    alvo.receberDano(danoFinal);

    cout << "Dano causado: " << danoFinal << "\n";

    return danoFinal;
}

