#include "ElectroPneumaticsToolkit.h"
  	
Atuador::Atuador(){
	nome = "";
	porta = -1;
	estadoAtual = 0;
	estadoDesejado = 0;
	tempoAtuacao = 0;
}

Atuador::Atuador(String _nome, int _porta, bool _estadoAtual, int _tempoAtuacao){
	nome = _nome;
	porta = _porta;
	estadoAtual = _estadoAtual;
	estadoDesejado = _estadoAtual;
	tempoAtuacao = _tempoAtuacao;
}

void Atuador::atuar(){
	Serial.println("Método virtual");
}

Servo::Servo() 
: Atuador(){
	
}

Servo::Servo(String _nome, int _porta, bool _estadoAtual, int _tempoAtuacao) 
: Atuador(_nome, _porta, _estadoAtual, _tempoAtuacao){
  		
}

void Servo::atuar(){
	Serial.println("Atuando Servo");
}

AtuadorDigital::AtuadorDigital() 
: Atuador(){

}

AtuadorDigital::AtuadorDigital(String _nome, int _porta, bool _estadoAtual, int _tempoAtuacao) 
: Atuador(_nome, _porta, _estadoAtual, _tempoAtuacao){
  		nome = _nome;
  		porta = _porta;
  		estadoAtual = _estadoAtual;
  		tempoAtuacao = _tempoAtuacao;

  		digitalWrite(porta, estadoAtual);
}

void AtuadorDigital::atuar(){
	digitalWrite(porta, estadoAtual);
}

Bancada::Bancada(){
	qtdAtuadores = 0;
}

void Bancada::adicionaAtuador(Atuador* atuador){
	atuadores[qtdAtuadores] = atuador;
	Serial.println("Adicionando " + atuador->nome);
	qtdAtuadores++;
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
	if((estadoDesejado != 0) != atuador->estadoAtual){

		atuador->estadoAtual = !atuador->estadoAtual;
		atuador->atuar();
		delay(atuador->tempoAtuacao);

		Serial.println(nomeAtuador + " Atuado");
	}
}

void Bancada::listaAtuadores(){
	Serial.print("Lista de Atuadores: ");
	for(int i = 0; i < qtdAtuadores; i++){
		Serial.print(atuadores[i]->nome + (i < qtdAtuadores -1 ? "," : ";\n\n"));
	}
}