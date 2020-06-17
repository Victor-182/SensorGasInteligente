# Sensor de Gás Inteligente

  Projeto destinado a implementação de um sensor de gás inteligente, utilizando o microcontrolador Arduino UNO R3 e a comunicação com a internet via o protocolo MQTT.
	
  O equipamento visa ser um facilitador para a segurança e bem-estar do indivíduo, seja em seu cotidiano ou no meio de trabalho. Ele é composto por um sensor de gás e fumaça MQ-2, o qual pode detectar diversos tipos de gases e fumaça no ar, tendo capacidade de detecção que vai de 300 a 10.000ppm (partes por milhão), onde, é atribuído um valor máximo para representação do nível normal de gás no ambiente, e caso esse valor seja excedido, o Buzzer (atuador) será ativado, e um LED irá piscar, informando, de forma audiovisual, para quem estiver no ambiente, que está havendo um vazamento de gás, todo esse processo é controlado por intermédio do microcontroladro Arduino UNO R3.
  
  A leitura dos dados é feita através do sensor, onde essas informações, são armazenadas em uma variável, que será lida por uma estrutura condicional, onde será verificado se esse número que está sendo armazenado na variável ultrapassa ou não o valor imposto pelo usuário, caso ultrapasse, o atuador Buzzer será acionado, emitindo uma frequência que também poderá determinada pelo usuário e um LED vermelho irá começar a piscar, e caso o nível de gás do ambiente diminua, o LED irá parar de piscar e o Buzzer irá parar de tocar, logo, temos o LED, que servirá como um indicador visual e o Buzzer que servirá como um indicador sonoro.

Modelo do projeto construído na plataforma tinkercad contendo:

 - Arduino UNO R3 (Microcontrolador) 
 - Sensor de gás MQ-2
 - Buzzer (Atuador)

![Projeto TinkerCad](https://github.com/Victor-182/SensorGasInteligente/blob/master/ProjetoArduinoTinkercad.jpg?raw=true)
