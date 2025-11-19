#include "Personagem.h"

#include <iostream>

using namespace std;

Mago::Mago(string n, int pv, int f, int d, int mp)

    : Personagem(n, pv, f, d, "Fogo"), pontosMagia(mp) {
}

int Mago::atacar(Personagem& alvo) {

    int danoCalculado = forca;

    string nomeAtaque = "Ataque Basico";

    if (!habilidades.empty()) {

        Habilidade h = habilidades[0];

        float mult = h.obterMultiplicador(alvo.getElemento());

        danoCalculado = (int)((forca + h.danoBase + (pontosMagia / 5)) * mult);

        nomeAtaque = h.nome;

        if (mult > 1.0f) cout << "(SUPER EFETIVO!) ";

    }

    int danoFinal = alvo.reduzirDanoPelaDefesa(danoCalculado);

    cout << nome << " lança " << nomeAtaque << " em "
        << alvo.getNome() << " causando " << danoFinal << " de dano!\n";

    alvo.receberDano(danoFinal);

    return danoFinal;

}

