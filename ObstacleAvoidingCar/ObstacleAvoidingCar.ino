/*********************************************************************

          Competição de Robótica USJT 2021
          Professora Iara
          Professor Giocondo
          Professor Nuncio

          Equipe William

**********************************************************************/
#define botao  8
#define led_verde 6
#define led_vermelho 7
#define motor1control 3
#define motor1A 2
#define motor1B 4
#define motor2control 5
#define motor2A 12
#define motor2B 13

int sensor;
int tempo_inicial;
int tempo_parcial;
int tempo_final;
int vel = 128;                            //Velocidade de 0 à 255

void setup() {
  Serial.begin(115200);
  pinMode(botao, INPUT);
  pinMode(led_verde, OUTPUT);
  pinMode(led_vermelho, OUTPUT);
  pinMode(motor1control, OUTPUT);
  pinMode(motor1A, OUTPUT);
  pinMode(motor1B, OUTPUT);
  pinMode(motor2control, OUTPUT);
  pinMode(motor2A, OUTPUT);
  pinMode(motor2B, OUTPUT);
}

void loop() {
  sensor = digitalRead(botao);
  Serial.print("Estado do sensor = ");
  Serial.println(sensor);
  if (sensor == LOW) {                    //Se o sensor não captar obstáculos, acender LED verde e seguir em frente
    delay(10000);                         //Tempo de partida de 10 segundos
    digitalWrite(led_verde, HIGH);
    digitalWrite(led_vermelho, LOW);
    Serial.println("Indo para frente");
    tempo_inicial = millis();
    analogWrite(motor1control, vel);      //Motor esquerdo seguir em frente
    digitalWrite(motor1A, HIGH);
    digitalWrite(motor1B, LOW);
    analogWrite(motor2control, vel);      //Motor direito seguir em frente
    digitalWrite(motor2A, HIGH);
    digitalWrite(motor2B, LOW);
  }
  else if (sensor == HIGH) {              //Se o sensor captar obstáculos, acender LED vermelho e dar ré até dar o tempo de duração do percurso ocorrido
    tempo_parcial = tempo_inicial;
    tempo_final = millis();
    digitalWrite(led_verde, LOW);
    digitalWrite(led_vermelho, HIGH);
    Serial.println("Indo para trás");
    analogWrite(motor1control, vel);      //Motor esquerdo dar ré
    digitalWrite(motor1A, LOW);
    digitalWrite(motor1B, HIGH);
    analogWrite(motor2control, vel);      //Motor direito dar ré
    digitalWrite(motor2A, LOW);
    digitalWrite(motor2B, HIGH);
    if (tempo_final == tempo_parcial) {
      analogWrite(motor1control, 0);      //Motor esquerdo parar
      digitalWrite(motor1A, LOW);
      digitalWrite(motor1B, LOW);
      analogWrite(motor2control, 0);      //Motor direito parar
      digitalWrite(motor2A, LOW);
      digitalWrite(motor2B, LOW);
    }
  }
}
