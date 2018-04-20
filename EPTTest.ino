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
}

void loop() {

}

void testaAdicaoDeAtuadores(){
	Serial.print("<--------Testando adição de atuadores-------->\n\n");
	Serial.print("Adicionando AtuadorDigital1, Servo1, AtuadorDigital2 e Servo2\n");
	AtuadorDigital atuador1 ("AtuadorDigital", 1, false, 1000);
	bancada.adicionaAtuador(&atuador1);		
	Servo atuador2 ("Servo1", 2, false, 1000);
	bancada.adicionaAtuador(&atuador2);	
	AtuadorDigital atuador3 ("AtuadorDigital2", 3, false, 1000);
	bancada.adicionaAtuador(&atuador3);	
	Servo atuador4 ("Servo2", 4, false, 1000);
	bancada.adicionaAtuador(&atuador4);	

	bancada.listaAtuadores();
}

void testaRemocaoDeAtuadores(){
	Serial.print("<--------Testando remoção de atuadores-------->\n\n");
	Serial.print("Removendo Servo2 e AtuadorDigital2\n");

	bancada.removeAtuador("Servo2");		
	bancada.removeAtuador("AtuadorDigital2");	

	bancada.listaAtuadores();
}

void testaAtucaoDeAtuadores(){
	Serial.print("<--------Testando atuação de atuadores-------->\n\n");
	bancada.listaAtuadores();
	Serial.print("Atuando AtuadorDigital1 e Servo1\n");

	bancada.atuar("AtuadorDigital1", 1);	
	bancada.atuar("Servo1", 1);		
}




