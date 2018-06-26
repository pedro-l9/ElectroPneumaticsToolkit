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

class Bancada{
    Atuador *atuadores[NRO_MAX_ATUADORES];

    int qtdAtuadores;

  public:
	Bancada();

  void adicionaAtuador(Atuador* atuador);;
  int getAtuadorIdByName(String nome);
  void removeAtuador(String nome);
  void atuar(String nomeAtuador, int estadoDesejado);
  void listaAtuadores();
};


#endif