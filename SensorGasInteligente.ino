//importação das bibliotecas para comunicação via MQTT
#include <ESP8266WiFi.h>
#include <PubSubClient.h>
//definição dos tópicos de publish e do id MQTT
#define TOPICO_PUBLISH_GAS "leitura_gas"
#define ID_MQTT "sensorgas_mqtt"
#define TOPICO_ALERT_GAS "alert_gas"
//declaração das variáveis que irão armazenar o usuário e a senha WiFi da rede
const char* ssid = "Caetano 2G";
const char* password = "***************";
//declaração da variável que irá armazenar o MQTT Broker Service utilizado
const char* mqtt_server = "test.mosquitto.org";

WiFiClient espClient;
PubSubClient client(espClient);

//função para tentar se reconectar ao Broker caso a tentativa falhe
void reconectMQTT(void) {
  if (!client.connected()){
    while (!client.connected()) {
      Serial.print("* Tentando se conectar ao Broker MQTT: ");
      Serial.println(mqtt_server);
      if (client.connect(ID_MQTT)) {
        Serial.println("Conectado ao MQTT");
      } else {
        Serial1.println("Falha ao tentar se reconectar com o broker");
        Serial.println("Havera nova tentativa de conexao em 2s");
        //nova tentativa de reconexão em 2 segundos
        delay(2000);
      }
    }
  }
}

//função para tentar se reconectar ao WiFi caso a tentativa falhe
void reconnectWiFi(void) {
  
  if (WiFi.status() == WL_CONNECTED)
    return;
    
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(100);
    Serial.print(".");
  }

  Serial.println();
  Serial.print("Conectado com sucesso na rede ");
  Serial.print(ssid);
  Serial.println("IP obtido: ");
  Serial.println(WiFi.localIP());
}

//função que irá verificar a situação atual das conexões WiFi e MQTT
//irá chamar as duas funções no caso de ser a primeira tentativa, obtendo assim, a primeira conexão
void verifyConnection(void) {
  reconnectWiFi(); 
  reconectMQTT(); 
}

//função callback para obtenção e processamento de um tópico e seu payload
void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Topic arrived[");
  Serial.print(topic);
  Serial.print("]");
  for (int i=0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();
}


void setup() {
  //definição do serial, server MQTT utilizado e a porta de comunicação
  Serial.begin(115200);
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
  //definição dos pinos do circuito que irão receber ou enviar informações
  pinMode(A0, INPUT);
  pinMode(D2, OUTPUT);
  pinMode(D8, OUTPUT);
}

void loop(){
  //declaração das variáveis de resposta padrão que serão utilizadas como payloads em chamadas de funções publish
  char ppm_str[10] = {0};
  char alert_str[20] = {"GÁS VAZANDO"};
  char empty[30] = {"NÍVEL DE GÁS NORMAL"};
  //chamada da função verifyConnection() para se conectar ao WiFi e ao MQTT Broker
  verifyConnection();
  //obtenção e leitura dos dados do sensor de gás MQ-2
  int sensor = analogRead(A0);
  sprintf(ppm_str,"%i", sensor);
  Serial.println(sensor);
  //publish da leitura do gás através do protocolo MQTT
  client.publish(TOPICO_PUBLISH_GAS, ppm_str);

  if(sensor >= 150){
    //alteração do estado do LED alertando o usuário sobre o vazamento de gás
    digitalWrite(D2, HIGH);
    //publish no tópico alertando o usuário sobre o vazamento de gás
    client.publish(TOPICO_ALERT_GAS, alert_str);
    Serial.println(alert_str);
    //acionamento do estado do LED alertando o usuário do vazamento de gás
    tone(D8, 1000, 500);
  }
  else{
    //alteração do estado do LED alertando o usuário sobre a normalização do nível de gás no ambiente
    digitalWrite(D2, LOW);
    //publish no tópico de alerta informando o usuário sobre a normalização do nível de gás no ambiente
    client.publish(TOPICO_ALERT_GAS, empty);
    Serial.println(empty);
  }
  //delay de 1 segundo para retomada do processo de leitura e publish dos dados nos tópicos
  delay(1000);
}
