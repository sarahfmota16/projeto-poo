#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Personagem {
public:
	std::string nome;
	int pontosVida;
	int forca;
	int defesa;
	std::vector<std::string> habilidades;

	Personagem(string n, int pv, int f, int d) : nome(n), pontosVida(pv), forca(f), defesa(d) {}

	virtual int atacar(Personagem& alvo) = 0;

	virtual void calcularDano(int dano){
		pontosVida -= dano;
		if (pontosVida < 0) pontosVida = 0;
	}
};



class Guerreiro : public Personagem {
public:
	
	int resistenciaEscudo;

	Guerreiro(string n, int pv, int f, int d, int re) : Personagem(n, pv, f, d), resistenciaEscudo(re) {}
	
	int atacar(Personagem& alvo) override {
		int dano = forca - alvo.defesa;
		if (dano < 0) dano = 0;

		alvo.calcularDano(dano);
		return dano;
	}

	void calcularDano(int dano) override {
		int danoGuerreiro = dano - resistenciaEscudo;
		if (danoGuerreiro < 0) danoGuerreiro = 0;

		pontosVida -= danoGuerreiro;
		if (pontosVida < 0) pontosVida = 0;
	}
};

class Mago : public Personagem {
public:
	int pontosMagia;

	Mago(string n, int pv, int f, int d, int mp)
		: Personagem(n, pv, f, d), pontosMagia(mp) {
	}

	int atacar(Personagem& alvo) override {
		int dano = (forca + (pontosMagia / 2)) - alvo.defesa;
		if (dano < 0) dano = 0;

		alvo.calcularDano(dano);
		return dano;
	}
};


class Arqueiro : public Personagem {
public:
	int agilidade;

	Arqueiro(string n, int pv, int f, int d, int a)
		: Personagem(n, pv, f, d), agilidade(a) {
	}

	int atacar(Personagem& alvo) override {
		int dano = (forca + agilidade) - alvo.defesa;
		if (dano < 0) dano = 0;

		alvo.calcularDano(dano);
		return dano;
	}

	void calcularDano(int dano) override {
		int danoArqueiro = dano - (agilidade / 2);
		if (danoArqueiro < 0) danoArqueiro = 0;

		pontosVida -= danoArqueiro;
		if (pontosVida < 0) pontosVida = 0;
	}
};


class Inimigo : public Personagem {
public:
	string tipo;
	int recompensaXP;

	Inimigo(string n, string t, int pv, int f, int d, int xp)
		: Personagem(n, pv, f, d), tipo(t), recompensaXP(xp) {
	}

	int atacar(Personagem& alvo) override {
		int dano = forca - alvo.defesa;
		if (dano < 0) dano = 0;

		alvo.calcularDano(dano);
		return dano;
	}
};



class Batalha {
public:

	void ordenarEvento() {

	}
};

class Habilidade {
public:

	std::string nome;
	std::string tipo;
	int danoBase;

};

class Jogo {
public:

};