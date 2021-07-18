#include <SoftwareSerial.h>
#include <IRremote.h> // saída pino 3

#include <Wire.h>
#include <DS3231.h>
#include "DHT.h"

#define DHTPIN A1 // pino do DHT conectado
#define DHTTYPE DHT11 // DHT 11

DS3231 rtc;              //Criação do objeto do tipo DS3231
RTCDateTime dataehora;   //Criação do objeto do tipo RTCDateTime

#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// If using software SPI (the default case):
#define OLED_MOSI   11
#define OLED_CLK   12
#define OLED_DC    9
#define OLED_CS    8
#define OLED_RESET 10
Adafruit_SSD1306 display(OLED_MOSI, OLED_CLK, OLED_DC, OLED_RESET, OLED_CS);

DHT dht(DHTPIN, DHTTYPE);

IRsend irsend;

SoftwareSerial bluetooth(4, 5); // RX = 4      TX = 5

String sinalbluetooth;
char caractere;
int estadolampada;
char elampada;
char canalTV;

void setup() {

  Serial.begin(9600);
  bluetooth.begin(9600);
  dht.begin();
  rtc.begin();

  display.begin(SSD1306_SWITCHCAPVCC);
  display.display();
  delay(2000);
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);

  //rtc.setDateTime(__DATE__, __TIME__); // seta a hora atual no arduino

  pinMode(13, OUTPUT);
}



String leStringSerial() {
  String conteudo = "";
  char caractere;

  // Enquanto receber algo pela serial
  while (bluetooth.available() > 0) {
    
    // Lê byte da serial
    caractere = bluetooth.read();
    
    // Ignora caractere de quebra de linha
    if (caractere != "\n") {
      
      // Concatena valores
      conteudo.concat(caractere);
    }
    // Aguarda buffer serial ler próximo caractere
    delay(10);
  }
  Serial.print("Recebi: ");
  Serial.println(conteudo);

  return conteudo;
}


void loop() {

  estadolampada = digitalRead(13);


  if (bluetooth.available()) {

    sinalbluetooth = leStringSerial();
    //Serial.println(sinalbluetooth);

    if (sinalbluetooth == "LUZDASALA" && estadolampada == 0) { //LIGA LÂMPADA
      digitalWrite(13, 1);
      bluetooth.write("L");
      delay(250);
    }

    if (sinalbluetooth == "LUZDASALA" && estadolampada == 1) { //DESLIGA LÂMPADA
      digitalWrite(13, 0);
      bluetooth.write("D");
      delay(250);
    }

    if (sinalbluetooth == "LIGATV") { //LIGA TV
      LIGATV();
      delay(250);
    }

    if (sinalbluetooth == "MENUSMART") { //LIGA TV
      MENUSMART();
    }

    if (sinalbluetooth == "SAIR") { //LIGA TV
      SAIR();
    }

    if (sinalbluetooth == "ENTRADAS") { //LIGA TV
      ENTRADAS();
    }

    if (sinalbluetooth == "PLAY") { //LIGA TV
      PLAY();
    }

    if (sinalbluetooth == "PAUSE") { //LIGA TV
      PAUSE();
    }

    if (sinalbluetooth == "STOP") { //LIGA TV
      STOP();
    }

    if (sinalbluetooth == "BACKWARD") { //LIGA TV
      BACKWARD();
    }

    if (sinalbluetooth == "FORWARD") { //LIGA TV
      FORWARD();
    }


    if (sinalbluetooth == "VOLUP") { //AUMENTA VOLUME
      RV1();
    }

    if (sinalbluetooth == "VOLDOWN") { //ABAIXA VOLUME
      RV0();
    }


    if (sinalbluetooth == "MUDO") { //MUDO
      RV();
    }

    if (sinalbluetooth == "CANALUP") { //AUMENTA CANAL
      RC1();
    }

    if (sinalbluetooth == "CANALDOWN") { //ABAIXA CANAL
      RC0();
    }

    if (sinalbluetooth == "VOLTAR") { //VOLTAR
      RVOLTAR();
    }

    if (sinalbluetooth == "OK") { //OK
      ROK();
    }

    if (sinalbluetooth == "QVIEW") { //Q.VIEW - INFO
      RQVIEW();
    }

    if (sinalbluetooth == "CIMAREC") { //CIMA
      RCIMA();
    }

    if (sinalbluetooth == "BAIXOREC") { //BAIXO
      RBAIXO();
    }

    if (sinalbluetooth == "DIREITAREC") { //DIREITA
      RDIREITA();
    }

    if (sinalbluetooth == "ESQUERDAREC") { //ESQUERDA
      RESQUERDA();
    }

    if (sinalbluetooth == "GUIDE") { //GUIDE
      RGUIDE();
    }

    if (sinalbluetooth == "1") { //BOTAO 1
      R1();
    }

    if (sinalbluetooth == "2") { //BOTAO
      R2();
    }

    if (sinalbluetooth == "3") { //BOTAO 3
      R3();
    }

    if (sinalbluetooth == "4") { //BOTAO 4
      R4();
    }

    if (sinalbluetooth == "5") { //BOTAO 5
      R5();
    }

    if (sinalbluetooth == "6") { //BOTAO 6
      R6();
    }

    if (sinalbluetooth == "7") { //BOTAO 7
      R7();
    }

    if (sinalbluetooth == "8") { //BOTAO 8
      R8();
    }

    if (sinalbluetooth == "9") { //BOTAO 9
      R9();
    }

    if (sinalbluetooth == "0") { //BOTAO 0
      R0();
    }
    sinalbluetooth = "";
  }

  ////////////////RTC e DHT/////////////////////////
  unsigned long previousMillis = 0;
  //Intervalo de medicao temperatura
  const long interval = 5000;

  unsigned long currentMillis = millis();
  
  static unsigned long thisMicros = 0;
  static unsigned long lastMicros = 0;

  // testa se retorno é valido, caso contrário algo está errado.

  //  if (isnan(t) || isnan(h)) {
  //    Serial.println("Failed to read from DHT");
  //  }
  //  else
  //  {
  //  Serial.print("UR: ");
  //  Serial.print(h);
  //  Serial.println(" %");
  //  Serial.print("T: ");
  //  Serial.print(s);
  //  Serial.println(" °C");
  //  }

  dataehora = rtc.getDateTime();
  Serial.print(dataehora.day);      //Imprimindo o Dia
  Serial.print("/");
  Serial.print(dataehora.month);    //Imprimindo o Mês
  Serial.print("/");
  Serial.print(dataehora.year);     //Imprimindo o Ano
  Serial.print(" ");
  Serial.print(dataehora.hour);     //Imprimindo a Hora
  Serial.print(":");
  Serial.print(dataehora.minute);   //Imprimindo o Minuto
  Serial.print(":");
  Serial.print(dataehora.second);   //Imprimindo o Segundo
  Serial.println("");
  delay(500);



  //Timer para ler o valor da temperatura
  if (currentMillis - previousMillis >= interval)
  {
    float h = dht.readHumidity();
    float t = dht.readTemperature();
    float s = dht.computeHeatIndex(t, h, false); // Real Fell
    display.setTextSize(1);
    display.clearDisplay();
    display.setCursor(0,0);
    display.print("T: ");
    display.print(s);
    display.print(" C ");
    display.print("UR: ");
    display.println(h);
    display.print(dataehora.day);
    display.print("/");    
    display.print(dataehora.month);
    display.print("/");
    display.println(dataehora.year);
    display.setCursor(38,19);
    display.setTextSize(2);
    display.print(dataehora.hour);
    display.print(":");
    display.print(dataehora.minute);
    
    display.display();
    lastMicros = thisMicros;
    thisMicros = micros();
    
    Serial.print("UR: ");
    Serial.print(h);
    Serial.println(" %");
    Serial.print("T: ");
    Serial.print(t);
    Serial.println(" °C");
  }

  ////////////////FIM RTC e DHT/////////////////////////
}



// Controles TV
void LIGATV() {
  //for (int i = 0; i < 3; i++) {
  irsend.sendNEC(0x20DF10EF , 32);
  //Serial.println("Liga");
  delay(40);//}
}


void R0() {
  // for (int i = 0; i < 3; i++) {
  irsend.sendNEC(0x20DF08F7, 32);
  //Serial.println("0");
  delay(40);//}
}

void R1() {
  //   for (int i = 0; i < 3; i++) {
  irsend.sendNEC(0x20DF8877, 32);
  //Serial.println("1");
  delay(40);//}
}

void R2() {
  // for (int i = 0; i < 3; i++) {
  irsend.sendNEC(0x20DF48B7, 32);
  //Serial.println("2");
  delay(40);//}
}

void R3() {
  //    for (int i = 0; i < 3; i++) {
  irsend.sendNEC(0x20DFC837, 32);
  //Serial.println("3");
  delay(40);//}
}

void R4() {
  //  for (int i = 0; i < 3; i++) {
  irsend.sendNEC(0x20DF28D7, 32);
  //Serial.println("4");
  delay(40);//}
}

void R5() {
  //for (int i = 0; i < 3; i++) {
  irsend.sendNEC(0x20DFA857, 32);
  //Serial.println("5");
  delay(40);//}
}

void R6() {
  // for (int i = 0; i < 3; i++) {
  irsend.sendNEC(0x20DF6897, 32);
  //Serial.println("6");
  delay(40);//}
}

void R7() {
  //   for (int i = 0; i < 3; i++) {
  irsend.sendNEC(0x20DFE817, 32);
  //Serial.println("7");
  delay(40);//}
}

void R8() {
  //for (int i = 0; i < 3; i++) {
  irsend.sendNEC(0x20DF18E7, 32);
  //Serial.println("8");
  delay(40);//}
}

void R9() {
  // for (int i = 0; i < 3; i++) {
  irsend.sendNEC(0x20DF9867, 32);
  //Serial.println("9");
  delay(40);//}
}

void RV1() {
  //for (int i = 0; i < 3; i++) {
  irsend.sendNEC(0x20DF40BF, 32);
  //Serial.println("V+");
  delay(40);//}
}

void RV0() {
  //for (int i = 0; i < 3; i++) {
  irsend.sendNEC(0x20DFC03F, 32);
  //Serial.println("V-");
  delay(40);//}
}

void RV() {
  // for (int i = 0; i < 3; i++) {
  irsend.sendNEC(0x20DF906F, 32);
  //Serial.println("V");
  delay(40);//}
}

void RC1() {
  //   for (int i = 0; i < 3; i++) {
  irsend.sendNEC(0x20DF00FF, 32);
  //Serial.println("C+");
  delay(40);//}
}

void RC0() {
  //for (int i = 0; i < 3; i++) {
  irsend.sendNEC(0x20DF807F, 32);
  //Serial.println("C-");
  delay(40);//}
}

void RVOLTAR() {
  //   for (int i = 0; i < 3; i++) {
  irsend.sendNEC(0x20DF14EB, 32);
  //Serial.println("VOLTAR");
  delay(40);//}
}

void ROK() {
  //for (int i = 0; i < 3; i++) {
  irsend.sendNEC(0x20DF22DD, 32);
  //Serial.println("OK");
  delay(40);//}
}

void RQVIEW() { //q.view
  //for (int i = 0; i < 3; i++) {
  irsend.sendNEC(0x20DF58A7, 32);
  //Serial.println("Q.VIEW");
  delay(40);//}
}

void RGUIDE() { //guide
  //for (int i = 0; i < 3; i++) {
  irsend.sendNEC(0x20DFD52A, 32);
  //Serial.println("GUIDE");
  delay(40);//}
}

void RCIMA() {
  // for (int i = 0; i < 3; i++) {
  irsend.sendNEC(0x20DF02FD, 32);
  //Serial.println("CIMA");
  delay(40);//}
}

void RESQUERDA() {
  //for (int i = 0; i < 3; i++) {
  irsend.sendNEC(0x20DFE01F, 32);
  //Serial.println("ESQUERDA");
  delay(40);//}
}

void RBAIXO() {
  //for (int i = 0; i < 3; i++) {
  irsend.sendNEC(0x20DF827D, 32);
  //Serial.println("BAIXO");
  delay(40);//}
}

void RDIREITA() {
  //for (int i = 0; i < 3; i++) {
  irsend.sendNEC(0x20DF609F, 32);
  //Serial.println("DIREITA");
  delay(40);//}
}

void MENUSMART() {
  // for (int i = 0; i < 3; i++) {
  irsend.sendNEC(0x20DF3EC1, 32);
  //Serial.println("MENUSMART");
  delay(40);//}
}

void SAIR() {
  //for (int i = 0; i < 3; i++) {
  irsend.sendNEC(0x20DFDA25, 32);
  //Serial.println("SAIR");
  delay(40);//}
}

void ENTRADAS() {
  //for (int i = 0; i < 3; i++) {
  irsend.sendNEC(0x20DFD02F, 32);
  //Serial.println("ENTRADAS");
  delay(40);//}
}

void PLAY() {
  //for (int i = 0; i < 3; i++) {
  irsend.sendNEC(0x20DF0DF2, 32);
  //Serial.println("PLAY");
  delay(40);//}
}

void PAUSE() {
  //for (int i = 0; i < 3; i++) {
  irsend.sendNEC(0x20DF5DA2, 32);
  //Serial.println("PAUSE");
  delay(40);//}
}

void STOP() {
  // for (int i = 0; i < 3; i++) {
  irsend.sendNEC(0x20DF8D72, 32);
  //Serial.println("STOP");
  delay(40);//}
}

void BACKWARD() {
  //for (int i = 0; i < 3; i++) {
  irsend.sendNEC(0x20DFF10E, 32);
  //Serial.println("BACKWARD");
  delay(40);//}
}

void FORWARD() {
  //for (int i = 0; i < 3; i++) {
  irsend.sendNEC(0x20DF718E, 32);
  //Serial.println("FORWARD");
  delay(40);//}
}






