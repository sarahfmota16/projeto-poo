#include "Personagem.h"
#include <cstdlib> // Para rand()

Personagem::Personagem(string n, int pv, int f, int d, string el)
    : nome(n), pontosVida(pv), pontosVidaMax(pv), forca(f), defesa(d), elementoNato(el), nivel(1), xp(0), xpParaProximoNivel(100) {
}

bool Personagem::verificarCritico() {
    return (rand() % 100) < 20; // 20% de chance
}

void Personagem::receberDano(int dano) {
    pontosVida -= dano;
    if (pontosVida < 0) pontosVida = 0;
}

int Personagem::reduzirDanoPelaDefesa(int danoBase) {
    float multiplicador = 100.0f / (100.0f + defesa);
    int danoFinal = (int)(danoBase * multiplicador);
    return (danoFinal < 1) ? 1 : danoFinal;
}

void Personagem::ganharXP(int xpRecebido) {
    if (xpRecebido <= 0) return;
    xp += xpRecebido;
    cout << "   [XP] " << nome << " ganhou " << xpRecebido << " XP!\n";
    while (xp >= xpParaProximoNivel) {
        xp -= xpParaProximoNivel;
        nivel++;
        xpParaProximoNivel = (int)(xpParaProximoNivel * 1.5);
        subirNivel();
    }
}

void Personagem::subirNivel() {
    int ganhoPV = 10;
    pontosVidaMax += ganhoPV;
    pontosVida = pontosVidaMax;
    forca += 2;
    defesa += 1;
    cout << "   >>> LEVEL UP! " << nome << " alcançou o nivel " << nivel << "! <<<\n";
}

void Personagem::mostrarStatus() {
    cout << "STATUS: " << nome << " [" << elementoNato << "] | HP: " << pontosVida << "/" << pontosVidaMax
        << " | ATK: " << forca << " | DEF: " << defesa << " | LVL: " << nivel << "\n";
}

void Personagem::adicionarHabilidade(Habilidade h) {
    habilidades.push_back(h);
}