Sensor de incêndio para torres de comunicação com ESP32 NodeMCU
---
Projeto composto por 5 estudantes de Sistemas da Informação e Engenharia de Software da Faculdade da Indústria em São José dos Pinhais, onde 3 participaram ativamente na criação deste código. Visa criar um dispositivo que informe a empresa via Telegram que foi detectado fumaça em um local remoto (onde as torres de comunicação se encontram) e assim possam agilizar o combate ao fogo.

Students of the Information Systems and Software Engineering courses at the Faculty of Industry in the city of São José dos Pinhais, composed of 5 students. 3 students actively participated in the creation of this code. This code is used to create a device that informs the company through the Telegram application that smoke has been detected in a remote location (where the communication towers are located). With this device, the company can speed up fire fighting.

*Dispositivos usados no projeto:* 
*Devices used in the project:*

      ESP 32 NodeMCU
      MQ-135
      LED ou Buzzer
      Protoboard
      Jumpers
      Painel solar para Arduino (Solar panel for Arduino)
      Módulo de baterias de Li-on (Li-on battery module)
      Stepdown
      CN-3065 Mini Carregador Solar (Mini Solar Charger)

*Bibliotecas e IDE:* 
*Libraries and IDE:*

      IDE Arduino
      WiFi.h
      WiFiClientSecure.h
      UniversalTelegramBot.h

*Inicialmente, para que o dispositivo fosse mais independente, utilizaríamos o SIM800L pra conexão 3G, mas devido a restrição da ANATEL sobre IMEI's, decidimos concluir com WI-FI. Nossa sugestão é utilizar o roteador industrial HF-8104.*

*Initially, for the device to be more independent, we would use SIM800L for 3G connection, but due to ANATEL's restriction on IMEI's, we decided to conclude with WI-FI. Our suggestion is to use the industrial router HF-8104.*
