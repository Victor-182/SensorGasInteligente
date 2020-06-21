# Sensor de Gás Inteligente

  Projeto destinado a implementação de um sensor de gás inteligente, utilizando o microcontrolador NodeMcu ESP8266 e a comunicação com a internet com o protocolo MQTT.
	
  O equipamento visa ser um facilitador para a segurança e bem-estar do indivíduo, seja em seu cotidiano ou no meio de trabalho. Ele é composto por um sensor de gás e fumaça MQ-2, o qual pode detectar diversos tipos de gases e fumaça no ar, tendo capacidade de detecção que vai de 200 a 10.000ppm (partes por milhão), onde, é atribuído um valor máximo para representação do nível normal de gás no ambiente, e caso esse valor seja excedido, o Buzzer (atuador) será ativado, e um LED irá acender, informando, de forma audiovisual, para quem estiver no ambiente, que está havendo um vazamento de gás, todo esse processo é controlado por intermédio do microcontroladro Node Mcu ESP8266.
  
# Montagem e lógica por trás do funcionamento

  A leitura dos dados é feita através do sensor, sendo este conectado a uma porta analógica, onde essas informações, são armazenadas em uma variável, a qual é processada para ser concatenada a um payload que irá ser utilizado e enviado junto a um tópico, e que através do método publish será enviada utilizando o protocolo MQTT, esta também será lida por uma estrutura condicional, e de forma constante, será verificado se esse número que foi armazenado ultrapassa ou não o valor imposto no cógido, caso ultrapasse, o atuador Buzzer será acionado, o qual está conectado a uma porta digital, emitindo uma frequência parecida com a de um alarme, um LED vermelho, que também está conectado a uma porta digital, irá se acender e por último realizado um publish, enviando um payload contendo a mensagem de alerta sobre o vazamento de gás para o usuário, caso o nível de gás do ambiente diminua, o LED irá se apagar, o Buzzer irá parar de tocar, e será realizado outro publish com o payload contendo uma mensagem sobre a normalização do nível de gás no ambiente, com isso temos o LED, que servirá como um indicador visual e o Buzzer que servirá como um indicador sonoro, além da comunicação com o usuário via internet utilizando o protocolo MQTT.
  Para comunicação utilizando MQTT e a transmissão de informações pela rede através do WiFi foram utilizadas as bibliotecas ESP8266WiFi e PubSubClient, as quais possuem os métodos e classes para estabelecer a conexão com a internet e a conexão com o protocolo MQTT e uso de seus métodos de publish e subscribe, respectivamente

#Relação do Hardware utilizado

 Toda relação do Hardware utilizado pode ser acessada através da página WiKi, ou também através do documento em PDF disponível no repostiório
	  
