#include <iostream>
#include <string>
#include <vector>
#include <string>
#include <map>

using namespace std;

class Personagem {
public:
	std::string nome;
	int pontosVida;
	int forca;
	int defesa;
	std::vector<std::string> habilidades;

	//EXTRA A)Sistema de nível
	int nivel = 1;
	int xp = 0;
	int xpParaProximoNivel = 100;

	Personagem(string n, int pv, int f, int d) : nome(n), pontosVida(pv), forca(f), defesa(d) {}

	virtual int atacar(Personagem& alvo) = 0;

	virtual void calcularDano(int dano) {
		pontosVida -= dano;
		if (pontosVida < 0) pontosVida = 0;
	}

	// EXTRA B) Sistema de Defesa Aprimorado:
	// Implementa uma redução proporcional de dano baseada no atributo DEFESA.
	// Quanto maior a defesa do alvo, menor será o dano recebido, evitando resultados
	// extremos como dano zero constante ou defesa inútil. Torna o combate mais equilibrado.
	int reduzirDanoPelaDefesa(int danoBase) {
		float multiplicador = 100.0f / (100.0f + defesa);
		int danoFinal = danoBase * multiplicador;

		if (danoFinal < 0) danoFinal = 0;
		return danoFinal;
	}


	void ganharXP(int xpRecebido) {
		if (xpRecebido <= 0) return;
		xp += xpRecebido;
		cout << nome << " ganhou " << xpRecebido << " XP!\n";
		while (xp >= xpParaProximoNivel) {
			xp -= xpParaProximoNivel;
			nivel++;
			xpParaProximoNivel = nivel * 100; 
			subirNivel();
		}
		cout << nome << " agora tem " << xp << " XP (precisa de " << xpParaProximoNivel << " para o proximo nivel).\n";
	}

	virtual void subirNivel() {
		int ganhoPV = 10;
		int ganhoForca = 2;
		int ganhoDefesa = 1;

		pontosVida += ganhoPV; 
		forca += ganhoForca;
		defesa += ganhoDefesa;

		cout << nome << " subiu para o nivel " << nivel << "! (PV +" << ganhoPV << ", Foraa +" << ganhoForca << ", Defesa +" << ganhoDefesa << ")\n";
	}

	void mostrarStatus(Personagem& p) {
		cout << "=== Status de " << p.nome << " ===\n";
		cout << "Nivel: " << nivel << "  XP: " << xp << "/" << xpParaProximoNivel << "\n";
		cout << "Vida: " << p.pontosVida << "\n";
		cout << "Forca: " << p.forca << "\n";
		cout << "Defesa: " << p.defesa << "\n";
		cout << "-----------------------------\n";
	}

};



class Guerreiro : public Personagem {
public:

	int resistenciaEscudo;

	Guerreiro(string n, int pv, int f, int d, int re) : Personagem(n, pv, f, d), resistenciaEscudo(re) {}

	int atacar(Personagem& alvo) override {
		int danoBase = forca;
		int danoFinal = alvo.reduzirDanoPelaDefesa(danoBase);

		alvo.calcularDano(danoFinal);
		return danoFinal;
	}


	void calcularDano(int dano) override {
		int danoGuerreiro = dano - resistenciaEscudo;
		if (danoGuerreiro < 0) danoGuerreiro = 0;

		pontosVida -= danoGuerreiro;
		if (pontosVida < 0) pontosVida = 0;
	}

	void subirNivel() override {
		int ganhoPV = 12;
		int ganhoForca = 3;
		int ganhoDefesa = 1;
		pontosVida += ganhoPV;
		forca += ganhoForca;
		defesa += ganhoDefesa;
		cout << nome << " (Guerreiro) subiu para o nivel " << nivel << "! (PV +" << ganhoPV << ", Forca +" << ganhoForca << ")\n";
	}
};

class Mago : public Personagem {
public:
	int pontosMagia;

	Mago(string n, int pv, int f, int d, int mp)
		: Personagem(n, pv, f, d), pontosMagia(mp) {
	}

	int atacar(Personagem& alvo) override {
		int danoBase = forca + (pontosMagia / 2);
		int danoFinal = alvo.reduzirDanoPelaDefesa(danoBase);
		alvo.calcularDano(danoFinal);
		return danoFinal;
	}


	void subirNivel() override {
		int ganhoPV = 8;
		int ganhoForca = 1;
		int ganhoDefesa = 1;
		pontosVida += ganhoPV;
		forca += ganhoForca;
		defesa += ganhoDefesa;
		pontosMagia += 10;
		cout << nome << " (Mago) subiu para o nivel " << nivel << "! (PV +" << ganhoPV << ", PM +10)\n";
	}
};


class Arqueiro : public Personagem {
public:
	int agilidade;

	Arqueiro(string n, int pv, int f, int d, int a)
		: Personagem(n, pv, f, d), agilidade(a) {
	}

	int atacar(Personagem& alvo) override {
		int danoBase = forca + agilidade;
		int danoFinal = alvo.reduzirDanoPelaDefesa(danoBase);
		alvo.calcularDano(danoFinal);
		return danoFinal;
	}


	void calcularDano(int dano) override {
		int danoArqueiro = dano - (agilidade / 2);
		if (danoArqueiro < 0) danoArqueiro = 0;

		pontosVida -= danoArqueiro;
		if (pontosVida < 0) pontosVida = 0;
	}

	void subirNivel() override {
		int ganhoPV = 9;
		int ganhoForca = 2;
		int ganhoDefesa = 1;
		agilidade += 2;
		pontosVida += ganhoPV;
		forca += ganhoForca;
		defesa += ganhoDefesa;
		cout << nome << " (Arqueiro) subiu para o nivel " << nivel << "! (PV +" << ganhoPV << ", Agilidade +2)\n";
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
		int danoBase = forca;
		int danoFinal = alvo.reduzirDanoPelaDefesa(danoBase);
		alvo.calcularDano(danoFinal);
		return danoFinal;
	}

};



class Batalha {
public:

	void ordenarEvento() {

	}
};















extern const std::map<std::string, std::map<std::string, float>> TIPO_EFETIVIDADE;

class Habilidade {
public:
	std::string Nome;
	std::string Tipo;
	int DanoBase;

	Habilidade(std::string n, std::string t, int d);
	float obterMultiplicador(const std::string& tipoAlvo) const;
};

const std::map<std::string, std::map<std::string, float>> TIPO_EFETIVIDADE = {
	{"Fogo",     {{"Gelo", 2.0f},  {"Terra", 2.0f},  {"Água", 0.5f}}},
	{"Água",     {{"Fogo", 2.0f},  {"Terra", 2.0f},  {"Elétrico", 0.5f}, {"Gelo", 0.5f}}},
	{"Elétrico", {{"Água", 2.0f},  {"Terra", 0.5f}}},
	{"Gelo",     {{"Terra", 2.0f}, {"Fogo", 2.0f},   {"Água", 0.5f}}},
	{"Terra",    {{"Elétrico", 2.0f}, {"Água", 0.5f}, {"Gelo", 0.5f}}},
	{"Neutro",   {}}
};

Habilidade::Habilidade(std::string n, std::string t, int d)
	: Nome(n), Tipo(t), DanoBase(d) {
}

float Habilidade::obterMultiplicador(const std::string& tipoAlvo) const {
	auto it_ataque = TIPO_EFETIVIDADE.find(Tipo);
	if (it_ataque != TIPO_EFETIVIDADE.end()) {
		auto it_alvo = it_ataque->second.find(tipoAlvo);
		if (it_alvo != it_ataque->second.end()) {
			return it_alvo->second;
		}
	}
	return 1.0f;
}






















class Jogo {
public:
	void iniciar() {
		cout << "Bem-vindo ao RPG!\n";

	}
};


int main() {
	Guerreiro g("Arthur", 100, 20, 10, 5);

	g.mostrarStatus(g);

	cout << "---- Ganho de XP ----\n";
	g.ganharXP(50);
	g.ganharXP(80);  
	g.ganharXP(150);

	g.mostrarStatus(g);

	return 0;
}
