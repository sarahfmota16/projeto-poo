#include "Personagem.h"

#include <iostream>

using namespace std;

Guerreiro::Guerreiro(string n, int pv, int f, int d, int re)

    : Personagem(n, pv, f, d, "Terra"), resistenciaEscudo(re) {
}

int Guerreiro::atacar(Personagem& alvo) {

    int danoBase = forca;

    if (verificarCritico()) {

        danoBase = (int)(danoBase * 1.5);

        cout << "(CRITICO!) ";

    }

    int danoFinal = alvo.reduzirDanoPelaDefesa(danoBase);

    cout << nome << " golpeia " << alvo.getNome()
        << " causando " << danoFinal << " de dano!\n";

    alvo.receberDano(danoFinal);

    return danoFinal;

}

