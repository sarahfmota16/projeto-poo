#include "Personagem.h"

#include <iostream>

using namespace std;

Mago::Mago(string n, int pv, int f, int d, int mp)

    : Personagem(n, pv, f, d, "Fogo"), pontosMagia(mp) {
}


int Mago::atacar(Personagem& alvo) {

    // O mago usa sua força + um pequeno bônus mágico
    int danoBase = forca + (pontosMagia / 10);

    cout << nome << " ataca " << alvo.getNome()
        << " com um ataque basico reforçado por magia!\n";

    int danoFinal = alvo.reduzirDanoPelaDefesa(danoBase);

    alvo.receberDano(danoFinal);

    cout << "Dano causado: " << danoFinal << "\n";

    return danoFinal;
}
