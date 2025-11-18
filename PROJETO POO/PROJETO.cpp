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

	Personagem(string n, int pv, int f, int d) : nome(n), pontosVida(pv), forca(f), defesa(d){}

	virtual void atacar(Personagem&, alvo) = 0;

	void calcularDano() {

	}
};


class Guerreiro : public Personagem {
public:
	
	int resistenciaEscudo;
	
	void atacar() override {

	}
};

class Mago : public Personagem {
public:

	int pontosMagia;

	void atacar() override {

	}
};

class Arqueiro: public Personagem {
public:

	int destreza;

	void atacar() override {

	}
};

class Inimigo : public Personagem {
public: 

	std::string tipo;
	int recompensaXP;

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