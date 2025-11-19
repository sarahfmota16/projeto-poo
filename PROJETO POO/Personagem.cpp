#include "Personagem.h"
#include <cstdlib> // Para rand()

Personagem::Personagem(string n, int pv, int f, int d, string el)
    : nome(n), pontosVida(pv), pontosVidaMax(pv), forca(f), defesa(d), elementoNato(el), nivel(1), xp(0), xpParaProximoNivel(50) {

    estaDefendendo = false;
}

bool Personagem::verificarCritico() {
    return (rand() % 100) < 20; // 20% de chance
}

//CalcularDano
void Personagem::receberDano(int dano) {

    if (estaDefendendo) {
        dano /= 2;
        cout << "   [DEFESA] O dano foi reduzido para " << dano << "!\n";
        estaDefendendo = false; // defesa só vale 1 ataque
    }

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
    cout << "   [XP] " << nome << " ganhou " << xpRecebido << " XP! (Agora: " << xp << "/" << xpParaProximoNivel << ")\n";
    while (xp >= xpParaProximoNivel) {
        xp -= xpParaProximoNivel;
        nivel++;
        xpParaProximoNivel = (int)(xpParaProximoNivel * 1.5);
        subirNivel();
        cout << "   [INFO] XP restante: " << xp << " | Proximo nivel em: " << xpParaProximoNivel << "\n";
    }
}


void Personagem::subirNivel() {
    int ganhoPV = 10;
    pontosVidaMax += ganhoPV;
    pontosVida = pontosVidaMax;
    forca += 2;
    defesa += 1;
    cout << "   >>> LEVEL UP! " << nome << " alcancou o nivel " << nivel << "! <<<\n";
}

void Personagem::mostrarStatus() {
    // no Personagem::mostrarStatus()
    cout << "STATUS: " << nome << " [" << elementoNato << "] | HP: " << pontosVida << "/" << pontosVidaMax
        << " | ATK: " << forca << " | DEF: " << defesa << " | LVL: " << nivel
        << " | XP: " << xp << "/" << xpParaProximoNivel << "\n";

}

void Personagem::adicionarHabilidade(Habilidade h) {
    habilidades.push_back(h);
}

void Personagem::defender() {
    estaDefendendo = true;
    cout << nome << " esta em posicao de defesa! (Dano recebido reduzido pela metade)\n";
}

void Personagem::limparDefesa() {
    estaDefendendo = false;
}


int Personagem::usarHabilidade(Habilidade& hab, Personagem& alvo) {

    int dano = calcularDanoHabilidade(hab, alvo);

    cout << "\n" << nome << " usa a habilidade **" << hab.nome
        << "** do tipo [" << hab.tipo << "]!\n";
    cout << "Dano base: " << hab.danoBase << "\n";

    alvo.receberDano(dano);

    cout << "Dano final causado: " << dano << "!\n";

    return dano;
}

int Personagem::calcularDanoHabilidade(Habilidade& hab, Personagem& alvo) {

    float multiplicador = hab.obterMultiplicador(alvo.getElemento());
    int dano = hab.danoBase * multiplicador;

    // Redução pela defesa do alvo
    dano = alvo.reduzirDanoPelaDefesa(dano);

    if (multiplicador > 1.0f) {
        cout << "   E SUPER EFETIVO! (x" << multiplicador << ")\n";
    }
    else if (multiplicador < 1.0f) {
        cout << "   Pouco efetivo... (x" << multiplicador << ")\n";
    }

    return dano;
}






// Adiciona um novo estado ao personagem
void Personagem::adicionarEstado(const string& nome, int turnos) {
    estados.push_back({ nome, turnos });
    cout << nome << " aplicado por " << turnos << " turnos!\n";
}

// Verifica se o personagem está atordoado (Stun)
bool Personagem::estaStunado() const {
    for (const auto& e : estados) {
        if (e.nome == "Stun" && e.turnosRestantes > 0)
            return true;
    }
    return false;
}

// Atualiza efeitos dos estados a cada turno
void Personagem::atualizarEstados() {
    for (auto& e : estados) {

        if (e.turnosRestantes <= 0)
            continue;

        // ----- EFEITOS DOS ESTADOS -----

        if (e.nome == "Poison") {
            cout << ">> " << nome
                << " está ENVENENADO e sofre 5 de dano!\n";
            pontosVida -= 5;
        }
        else if (e.nome == "Burn") {
            cout << ">> " << nome
                << " está QUEIMANDO e sofre 3 de dano!\n";
            pontosVida -= 3;
        }
        else if (e.nome == "Shield") {
            cout << ">> Um ESCUDO PROTETOR envolve " << nome
                << ". (Defesa aumentada temporariamente)\n";
            // futuramente coloque aqui o buff
        }
        else if (e.nome == "Stun") {
            // Não aplicar nada aqui — o stun só impede de agir
            cout << ">> " << nome
                << " segue ATORDOADO e não consegue reagir!\n";
        }

        // Reduz duração
        e.turnosRestantes--;
    }

    // Remove estados expirados
    estados.erase(
        remove_if(estados.begin(), estados.end(),
            [](const Estado& e) { return e.turnosRestantes <= 0; }),
        estados.end()
    );
}
