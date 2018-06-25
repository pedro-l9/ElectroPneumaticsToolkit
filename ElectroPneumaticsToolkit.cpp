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
	//Virtual method
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
  		
}

void AtuadorDigital::atuar(){
	Serial.println("Atuando Atuador Digital");
}

Bancada::Bancada(){
	qtdAtuadores = 0;
	/*qtdEventos = 0;	*/
}

void Bancada::adicionaAtuador(Atuador* atuador){
	atuadores[qtdAtuadores] = atuador;
	qtdAtuadores++;
}

/*void Bancada::adicionaEvento(Atuador* atuador, int porta, bool estadoDesejadoDaPorta){
	eventos[qtdEventos].atuador = atuador;
	eventos[qtdEventos].porta = porta;
	eventos[qtdEventos].estadoDesejadoDaPorta = estadoDesejadoDaPorta;
	qtdAtuadores++;
}*/

int Bancada::getAtuadorIdByName(String nome){
	for(int i = 0; i < qtdAtuadores; i++){
		if(atuadores[i]->nome == nome) return i;
	}
	return -1;
}

/*int Bancada::getEventoIdByPorta(int porta){
	for(int i = 0; i < qtdAtuadores; i++){
		if(eventos[i].porta == porta) return i;
	}
	return -1;
}*/

/*int Bancada::getEventoIdByName(String nome){
	for(int i = 0; i < qtdAtuadores; i++){
		if(eventos[i].nome == nome) return i;
	}
	return -1;
}*/

void Bancada::removeAtuador(String nome){
	int idAtuadorRemovido = getAtuadorIdByName(nome);

	if(idAtuadorRemovido != -1){
		delete atuadores[idAtuadorRemovido];
		atuadores[idAtuadorRemovido] = atuadores[qtdAtuadores-1];
		qtdAtuadores--;
	}
}

/*void Bancada::removeEvento(int porta){
	int idEventoRemovido = getEventoIdByPorta(porta);

	if(idEventoRemovido != -1){
		eventos[idEventoRemovido].atuador = eventos[qtdEventos-1].atuador;
		eventos[idEventoRemovido].porta = eventos[qtdEventos-1].porta;
		eventos[idEventoRemovido].estadoDesejadoDaPorta = eventos[qtdEventos-1].estadoDesejadoDaPorta;
		qtdEventos--;
	}
}*/

void Bancada::atuar(String nomeAtuador, int estadoDesejado){
	Atuador* atuador = atuadores[getAtuadorIdByName(nomeAtuador)];
	

	Serial.println("Atuando " + atuador->nome);	
	if((estadoDesejado != 0) != atuador->estadoAtual){

		atuador->atuar();
		delay(atuador->tempoAtuacao);
		atuador->estadoAtual = !atuador->estadoAtual;

		Serial.println(nomeAtuador + " Atuado");
	}

	
}

/*void Bancada::atuar(String nomeEvento){
	Evento* evento = &eventos[getEventoIdByName(nomeEvento)];
	
	if((evento->estadoDesejadoDaPorta != 0) != evento->atuador->estadoAtual){
		evento->atuador->atuar();
		while(digitalRead(evento->porta) != evento->estadoDesejadoDaPorta);
		evento->atuador->estadoAtual = !evento->atuador->estadoAtual;
	}
}*/

void Bancada::listaAtuadores(){
	Serial.print("Lista de Atuadores: ");
	for(int i = 0; i < qtdAtuadores; i++){
		Serial.print(atuadores[i]->nome + (i < qtdAtuadores -1 ? "," : ";\n\n"));
	}
}