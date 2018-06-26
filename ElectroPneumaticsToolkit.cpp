#include "ElectroPneumaticsToolkit.h"

Atuador::Atuador(String _nome, int _porta, bool _estadoAtual, int _tempoAtuacao){
	nome = _nome;
	porta = _porta;
	estadoAtual = _estadoAtual;
	tempoAtuacao = _tempoAtuacao;
}

Servo::Servo(String _nome, int _porta, bool _estadoAtual, int _tempoAtuacao) 
: Atuador(_nome, _porta, _estadoAtual, _tempoAtuacao){
  		
}

void Servo::atuar(){
	Serial.println("Atuando Servo");
}

void Servo::atuar(boolean estado){ 
	Serial.print("Atuando Servo para ");
	Serial.println(estado ? "+" : "-");
}

AtuadorDigital::AtuadorDigital(String _nome, int _porta, bool _estadoAtual, int _tempoAtuacao) 
: Atuador(_nome, _porta, _estadoAtual, _tempoAtuacao){
  		nome = _nome;
  		porta = _porta;
  		estadoAtual = _estadoAtual;
  		tempoAtuacao = _tempoAtuacao;

  		if(porta >= 0 && porta <= 13) {
  			pinMode(porta, OUTPUT);
  			atuar(estadoAtual);
  		}else{
  			Serial.println("Erro ao alocar porta do atuador " + nome);
  			porta = -1;
  		}
}

void AtuadorDigital::atuar(){
	atuar(!estadoAtual);
}

void AtuadorDigital::atuar(boolean estado){
	estadoAtual = estado;
	digitalWrite(porta, estadoAtual);
	delay(tempoAtuacao);
}

Bancada::Bancada(){
	qtdAtuadores = 0;
}

void Bancada::adicionaAtuador(Atuador* atuador){
	if(atuador->porta >=0){
		atuadores[qtdAtuadores] = atuador;
		Serial.println("Adicionado " + atuador->nome);
		qtdAtuadores++;	
	}
}

int Bancada::getAtuadorIdByName(String nome){
	for(int i = 0; i < qtdAtuadores; i++){
		if(atuadores[i]->nome == nome) return i;
	}
	return -1;
}

void Bancada::removeAtuador(String nome){
	int idAtuadorRemovido = getAtuadorIdByName(nome);

	if(idAtuadorRemovido != -1){
		delete atuadores[idAtuadorRemovido];
		atuadores[idAtuadorRemovido] = atuadores[qtdAtuadores-1];
		qtdAtuadores--;
	}
}

void Bancada::atuar(String nomeAtuador, int estadoDesejado){
	Atuador* atuador = atuadores[getAtuadorIdByName(nomeAtuador)];

	Serial.println("Atuando " + atuador->nome);	

	atuador->atuar(estadoDesejado == 1);

	Serial.println(nomeAtuador + " Atuado");
}

void Bancada::executaExpression(Expression *expr, int repeticoes){
	do{
    	for(int i = 0; i < expr->termCount; i++){
    		Term term = expr->terms[i];
    		atuar(term.name, term.state);
    	}
		repeticoes--;
	}while(repeticoes > 0);
}

void Bancada::listaAtuadores(){
	Serial.print("Lista de Atuadores: ");
	for(int i = 0; i < qtdAtuadores; i++){
		Serial.print(atuadores[i]->nome + (i < qtdAtuadores -1 ? "," : ";\n\n"));
	}
}