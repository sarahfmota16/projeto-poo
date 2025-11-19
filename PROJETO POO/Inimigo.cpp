#include "Personagem.h"
#include <iostream>

using namespace std;

Inimigo::Inimigo(string n, string t, string el, int pv, int f, int d, int xp)
    : Personagem(n, pv, f, d, el), tipoInimigo(t), recompensaXP(xp) {
}

int Inimigo::atacar(Personagem& alvo) {
    int danoBase = forca;

    if (verificarCritico()) {
        danoBase *= 2;
        cout << "(CRÍTICO!) Golpe atordoante!\n";
        alvo.adicionarEstado("Stun", 1);

        cout << ">> " << alvo.getNome()
            << " foi ATORDOADO e perderá o próximo turno!\n";

    }


    int danoFinal = alvo.reduzirDanoPelaDefesa(danoBase);

    cout << nome << " ataca " << alvo.getNome()
        << " causando " << danoFinal << " de dano!\n";

    alvo.receberDano(danoFinal);
    return danoFinal;
}
