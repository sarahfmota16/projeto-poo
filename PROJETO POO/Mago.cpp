#include "Personagem.h"

#include <iostream>

using namespace std;

Mago::Mago(string n, int pv, int f, int d, int mp)

    : Personagem(n, pv, f, d, "Fogo"), pontosMagia(mp) {
}


int Mago::atacar(Personagem& alvo) {
    int danoBase = forca + (pontosMagia * 0.7);

    if (verificarCritico()) {
        danoBase = (int)(danoBase * 1.8);
        cout << "(CRÍTICO ARCANO!) ";
    }

    cout << nome << " lança uma magia em " << alvo.getNome() << "!\n";

    int danoFinal = alvo.reduzirDanoPelaDefesa(danoBase);
    alvo.receberDano(danoFinal);

    cout << "Dano causado: " << danoFinal << "\n";

    // Mago gasta magia
    pontosMagia = max(0, pontosMagia - 5);

    return danoFinal;
}

