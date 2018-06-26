#ifndef EPT_H
#define EPT_H
#define NRO_MAX_ATUADORES 13
#define NRO_MAX_EVENTOS 13
 
#include <Arduino.h>
#include <CommandParser.h>

class Atuador{
  public:
  	String nome;
  	int porta;
  	bool estadoAtual;
  	int tempoAtuacao;

  	Atuador(String _nome, int _porta, bool _estadoAtual, int _tempoAtuacao);

  	virtual void atuar() =0;
    virtual void atuar(boolean estado) =0;
};

class Servo: public Atuador{
  public:
  	Servo(String _nome, int _porta, bool _estadoAtual, int _tempoAtuacao);

  	void atuar();
    void atuar(boolean estado);
};

class AtuadorDigital: public Atuador{
  public:
  	AtuadorDigital(String _nome, int _porta, bool _estadoAtual, int _tempoAtuacao);

  	void atuar();
    void atuar(boolean estado);
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
  void executaExpression(Expression *expr, int repeticoes);
  void listaAtuadores();
};


#endif