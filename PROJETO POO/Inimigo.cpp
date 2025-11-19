#include "Personagem.h"
#include <iostream>

using namespace std;

Inimigo::Inimigo(string n, string t, string el, int pv, int f, int d, int xp)
    : Personagem(n, pv, f, d, el), tipoInimigo(t), recompensaXP(xp) {
}

int Inimigo::atacar(Personagem& alvo) {
    int danoFinal = alvo.reduzirDanoPelaDefesa(forca);

    cout << ">> " << nome << " ataca voce causando "
        << danoFinal << " de dano!\n";

    alvo.receberDano(danoFinal);
    return danoFinal;
}