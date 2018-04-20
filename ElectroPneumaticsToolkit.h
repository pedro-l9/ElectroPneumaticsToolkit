#ifndef EPT_H
#define EPT_H
#define NRO_MAX_ATUADORES 13
#define NRO_MAX_EVENTOS 13
 
#include <Arduino.h>

class Atuador{
  public:
  	String nome;
  	int porta;
  	bool estadoAtual;
  	bool estadoDesejado;
  	int tempoAtuacao;

  	Atuador();

  	Atuador(String _nome, int _porta, bool _estadoAtual, int _tempoAtuacao);

  	virtual void atuar();
};

class Servo: public Atuador{
  public:
  	Servo();
  	Servo(String _nome, int _porta, bool _estadoAtual, int _tempoAtuacao);

  	void atuar();
};

class AtuadorDigital: public Atuador{
  public:
  	AtuadorDigital();
  	AtuadorDigital(String _nome, int _porta, bool _estadoAtual, int _tempoAtuacao);

  	void atuar();
};

class Evento{
  public:
    String nome;
	Atuador* atuador;
	int porta;
	bool estadoDesejadoDaPorta;
};

class Bancada{
    Atuador atuadores[NRO_MAX_ATUADORES];
    Evento eventos[NRO_MAX_EVENTOS];

    int qtdAtuadores;
    int qtdEventos; 

  public:
	Bancada();

	void adicionaAtuador(Atuador* atuador);
	void adicionaEvento(Atuador* atuador, int porta, bool estadoDesejadoDaPorta);
	int getAtuadorIdByName(String nome);
	int getEventoIdByPorta(int porta);
    int getEventoIdByName(String nome);
	void removeAtuador(String nome);
	void removeEvento(int porta);
    void atuar(String nomeAtuador, int estadoDesejado);
    void atuar(String nomeEvento);
    void listaAtuadores();
};


#endif