  const int EchoPin = A5;
  const int TriggerPin = A4;
  long duration, distanceCm;
  
  #include <LiquidCrystal.h>
  LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  lcd.begin(16,2);
  lcd.setCursor(0,0);
  pinMode(TriggerPin, OUTPUT);
  pinMode(EchoPin, INPUT);  
}

void loop() {

  int cm = ping(TriggerPin, EchoPin);//pasamos los datos de la variable al metodo "ping" como enteros a la variable cm

  if (cm == NULL){

    lcd.print("Sensor no funciona");
    lcd.setCursor(0,1);
    lcd.print("Sensor failure");
    lcd.setCursor(0,0);
    Serial.println("El sensor ultrasónico no funciona...");  

  } else if (cm < 5)  {

    lcd.print("Tanque lleno :)");
    lcd.setCursor(0,1);
    lcd.print("Full tank :) ");
    lcd.setCursor(0,0);
    Serial.println("Tanque lleno :)");

  } else if (cm < 10) {

    lcd.print("Hay menos de 90% de agua ");
    lcd.setCursor(0,1);
    lcd.print("Less than 90% ");
    lcd.setCursor(0,0);
    Serial.println("Hay menos de 90% de agua");

  } else if (cm < 20) {

    lcd.print("Hay menos de 50% de agua ");
    lcd.setCursor(0,1);
    lcd.print("Less than 50% ");
    lcd.setCursor(0,0);
    Serial.println("Hay menos de 50% de agua");

  } else {
    lcd.print("Vacio: 0%  :(   ");
    lcd.setCursor(0,1);
    lcd.print("Empty: 0% :(  ");
    lcd.setCursor(0,0);
    Serial.println("Hay 0% de agua...");
  }
  
  Serial.print("Distancia del sensor al agua: ");
  Serial.println(cm);
  delay(1000);
}
// Metodo que retorna la distancia calculada de acuerdo a los valores recibidos
  int ping(int TriggerPin, int EchoPin) {
    
  digitalWrite(TriggerPin, LOW);  //para generar un pulso limpio ponemos a LOW 4us
  delayMicroseconds(4);
  digitalWrite(TriggerPin, HIGH);  //generamos Trigger (disparo) de 10us
  delayMicroseconds(10);
  digitalWrite(TriggerPin, LOW);

  duration = pulseIn(EchoPin, HIGH);  //medimos el tiempo entre pulsos, en microsegundos
  distanceCm = duration * 10 / 292 / 2;  //convertimos a distancia, en cm
  return distanceCm;
  }
