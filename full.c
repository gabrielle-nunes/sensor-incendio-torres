#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>

// Initialize Wifi connection to the router
char ssid[] = " ";     // your network SSID (name)
char password[] = " "; // your network key

// Use @myidbot to find out the chat ID of an individual or a group
// Also note that you need to click "start" on a bot before it can
// message you
#define CHAT_ID1 " "

// Initialize Telegram BOT
#define Esp32token " "  // your Bot Token (Get from Botfather)

WiFiClientSecure client;
UniversalTelegramBot Esp32bot(Esp32token, client);

int Pinled = 17; //Pin LED ESP32
int MQ_analog = 34; //Pin MQ-135 ESP32

int tempo_medio = 900; //verification messages time
long ultima_verificacao; // last check of messages
int ledStatus = 0;
bool teste_atv = false;

//messages received by esp32
void gerencia_nova_message(int nova_message) {
  Serial.println("Gerenciador de novas mensagens:");
  Serial.println(String(nova_message));

  for (int i=0; i< nova_message; i++) {
    String chat_id = String(Esp32bot.messages[i].chat_id);
    String texto = Esp32bot.messages[i].text;

    String esp32bot_name = " "; //bot name
    
    //bot commands
    if (texto == "ON") {
      digitalWrite(Pinled, HIGH);
      ledStatus = 1;
      teste_atv = true;
      Esp32bot.sendMessage(chat_id, "Alarme acionado!", "");
    }

    if (texto == "OFF") {
      ledStatus = 0;
      teste_atv = false;
      digitalWrite(Pinled, LOW);
      Esp32bot.sendMessage(chat_id, "Alarme desligado", "");
    }

    if (texto == "Status") {
      if(ledStatus){
        Esp32bot.sendMessage(chat_id, "Alarme de Incendio Acionado", "");
      } else {
        Esp32bot.sendMessage(chat_id, "Alarme de Incendio desligado", "");
      }
    }

    //bot keyboard
    if (texto == "Teclado") {
      String teclado_Json = "[[\"ON\", \"OFF\"], [\"Status\"]]";
      Esp32bot.sendMessageWithReplyKeyboard(chat_id, "Escolha uma das opções a seguir", "", teclado_Json, true);
    }

    if (texto == "Iniciar") {
      Esp32bot.sendMessage(chat_id,"Bem vindo! Instruções para usar Teclado Telegram :\n"
      "ON : Para ligar Buzzer de Teste onboard\n"
      "OFF : Para desligar Buzzer de Teste onboard\n"
      "Status : Retorna status do Buzzer do Alarme\n"
      "Teclado : Retorna opções no teclado\n","");  
    }
    
  }
}

void setup() {
  Serial.begin(115200);
  
  //pin ESP32
  pinMode(Pinled, OUTPUT);
  pinMode(MQ_analog, INPUT);

  // Attempt to connect to Wifi network:
  Serial.print("Connecting Wifi: ");
  Serial.println(ssid);

  // Set WiFi to station mode and disconnect from an AP if it was Previously
  // connected
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  Serial.println("");
  Serial.println("WiFi conectado");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  delay(10);
  digitalWrite(Pinled, LOW);
  
  Esp32bot.sendMessage(CHAT_ID1, "Bot acionado!", "");
  
}

void loop()
{
  if (millis() > ultima_verificacao + tempo_medio) {
    int nova_message = Esp32bot.getUpdates(Esp32bot.last_message_received + 1);

    while(nova_message) {
      Serial.println("Obteve Resposta");
      gerencia_nova_message ( nova_message );
      nova_message = Esp32bot.getUpdates(Esp32bot.last_message_received + 1); 
    }

    ultima_verificacao = millis();
  }
  //MQ-135 analog calibration
  if ((analogRead(MQ_analog) > 2500) & (analogRead(MQ_analog) != 0)) {
    digitalWrite(Pinled, HIGH);
    Serial.println(analogRead(MQ_analog));
    ledStatus = 1;
    Esp32bot.sendMessage(CHAT_ID1, "ATENÇÃO! foi detectado fumaça no local da torre!", "");

  }
  else if ((analogRead(MQ_analog) < 2500) & (analogRead(MQ_analog) != 0) & (teste_atv = false)) {
    digitalWrite(Pinled, LOW);
    Serial.println(analogRead(MQ_analog));
    ledStatus = 0;
  }
  delay(1000);
}
