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

	virtual void atacar() {

	}

	void calcularDano() {

	}
};

class Guerreiro : public Personagem {
public:

	void atacar() override {

	}
};

class Mago : public Personagem {
public:

	void atacar() override {

	}
};

class Arqueiro: public Personagem {
public:

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

	void determinarordem() {

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