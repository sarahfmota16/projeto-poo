#include "Personagem.h"
#include <iostream>

using namespace std;

Arqueiro::Arqueiro(string n, int pv, int f, int d, int a)
    : Personagem(n, pv, f, d, "Eletrico"), agilidade(a) {
}

int Arqueiro::atacar(Personagem& alvo) {

    // bônus baseado na agilidade (tiro rápido e preciso)
    int danoBase = forca + (agilidade / 4);

    cout << nome << " dispara uma flecha rapida contra "
        << alvo.getNome() << "!\n";

    if (verificarCritico()) {
        danoBase = (int)(danoBase * 1.8); // arqueiros critam mais forte
        cout << "    (HEADSHOT!) Critico mortal!\n";
    }

    int danoFinal = alvo.reduzirDanoPelaDefesa(danoBase);

    alvo.receberDano(danoFinal);

    cout << "Dano causado: " << danoFinal << "\n";

    return danoFinal;
}
