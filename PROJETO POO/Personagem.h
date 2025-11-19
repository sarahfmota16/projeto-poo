#ifndef PERSONAGEM_H
#define PERSONAGEM_H

#include <iostream>
#include <string>
#include <vector>
#include "Habilidade.h"

using namespace std;

class Personagem {
protected:
    string nome;
    int pontosVida;
    int pontosVidaMax;
    int forca;
    int defesa;
    string elementoNato;

    // Sistema de Nível
    int nivel;
    int xp;
    int xpParaProximoNivel;

public:
    vector<Habilidade> habilidades;

    Personagem(string n, int pv, int f, int d, string el = "Neutro");
    virtual ~Personagem() {}

    // Getters e Setters básicos
    string getNome() const { return nome; }
    string getElemento() const { return elementoNato; }
    int getPV() const { return pontosVida; }
    int getPVMax() const { return pontosVidaMax; }
    bool estaVivo() const { return pontosVida > 0; }

    // Métodos de Combate
    bool verificarCritico();
    virtual int atacar(Personagem& alvo) = 0; // Método puro
    void receberDano(int dano);
    int reduzirDanoPelaDefesa(int danoBase);

    // Métodos de Evolução
    void ganharXP(int xpRecebido);
    virtual void subirNivel();
    void mostrarStatus();
    void adicionarHabilidade(Habilidade h);
};

class Guerreiro : public Personagem {
public:
    int resistenciaEscudo;

    Guerreiro(string n, int pv, int f, int d, int re);

    int atacar(Personagem& alvo) override;
};

class Mago : public Personagem {
public:
    int pontosMagia;

    Mago(string n, int pv, int f, int d, int mp);

    int atacar(Personagem& alvo) override;
};

class Arqueiro : public Personagem {
public:
    int agilidade;

    Arqueiro(string n, int pv, int f, int d, int a);

    int atacar(Personagem& alvo) override;
};

class Inimigo : public Personagem {
public:
    string tipoInimigo;
    int recompensaXP;

    Inimigo(string n, string t, string el, int pv, int f, int d, int xp);

    int atacar(Personagem& alvo) override;
};

#endif