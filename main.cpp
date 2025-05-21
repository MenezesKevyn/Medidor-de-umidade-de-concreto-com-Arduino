#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// LCD I2C - endereço e tamanho
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Pino do sensor
const int pinoSensor = A0;

void setup() {
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Sensor Online!");
  delay(2000);

  Serial.begin(9600);
  Serial.println("Sensor de Umidade para Concreto - Projeto de Feira");
}

void loop() {
  lcd.clear();

  // Lê o valor do sensor
  int valorUmidade = analogRead(pinoSensor);
  int umidadePercentual = map(valorUmidade, 0, 1023, 0, 100);

  lcd.setCursor(0, 0);
  lcd.print("Umidade Concreto:");

  lcd.setCursor(0, 1);
  if (valorUmidade > 800) {
    lcd.print("Muito Seco");
    Serial.println("Alerta: Muito Seco");
  } else if (valorUmidade < 200) {
    lcd.print("Muito Úmido");
    Serial.println("Alerta: Muito Úmido");
  } else {
    lcd.print(umidadePercentual);
    lcd.print("%");
    Serial.print("Umidade ideal: ");
    Serial.print(umidadePercentual);
    Serial.println("%");
  }

  Serial.print("Valor bruto do sensor: ");
  Serial.println(valorUmidade);

  delay(2000);  // Aguarda 2 segundos antes da próxima leitura
}
