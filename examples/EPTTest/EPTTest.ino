#include <CommandParser.h>
#include <ElectroPneumaticsToolkit.h>

Bancada bancada;

void setup() {
	Serial.begin(9600);
	
	while(!Serial.available());
	Serial.println("Starting...");

	testaAdicaoDeAtuadores();
	testaRemocaoDeAtuadores();
	testaAtucaoDeAtuadores();
  	testaParseDeExpressions();
}

void loop() {

}

void testaAdicaoDeAtuadores(){
	Serial.print("<--------Testando adicao de atuadores-------->\n\n");
	Serial.print("Adicionando AtuadorDigital, Servo1, AtuadorDigital2 e Servo2\n");
	
	bancada.adicionaAtuador(new AtuadorDigital("AtuadorDigital", 1, false, 1000));		
	bancada.adicionaAtuador(new Servo("Servo1", 2, false, 1000));	
	bancada.adicionaAtuador(new AtuadorDigital("AtuadorDigital2", 3, false, 1000));	
	bancada.adicionaAtuador(new Servo("Servo2", 4, false, 1000));	

	bancada.listaAtuadores();
}

void testaRemocaoDeAtuadores(){
	Serial.print("<--------Testando remocao de atuadores-------->\n\n");
	Serial.println("Removendo Servo2 e AtuadorDigital2\n");

	bancada.removeAtuador("Servo2");		
	bancada.removeAtuador("AtuadorDigital2");	

	bancada.listaAtuadores();
}

void testaAtucaoDeAtuadores(){
	Serial.print("<--------Testando atuacao de atuadores-------->\n\n");
	bancada.listaAtuadores();
	Serial.println("Tentando atuar AtuadorDigital e Servo1\n");

	bancada.atuar("AtuadorDigital", 1);	
	bancada.atuar("Servo1", 0);
}

void testaParseDeExpressions(){
	Serial.print("<--------Testando parse de expressions-------->\n\n");
	Serial.println("Parseando AAAA+BBBB+AAAA-BBBB-\n");

	Expression expr;
	CommandParser::parseExpression("AAAA+BBBB+AAAA-BBBB-", &expr);

	expr.printTerms();
}


