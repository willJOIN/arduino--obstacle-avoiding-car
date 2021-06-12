/*********************************************************************

          Competição de Robótica USJT 2021
          Professora Iara
          Professor Giocondo
          Professor Nuncio

          Equipe William

**********************************************************************/
const int botao = 8;
const int led_verde = 6;
const int led_vermelho = 7;
int sensor;
int motor_1A = 2;
int motor_1B = 3;
int motor_2A = 4;
int motor_2B = 5;
int tempo_inicial;
int tempo_parcial;
int tempo_final;
int resultado;
int vel = 128;                                //Velocidade de 0 à 255

void setup() {
  Serial.begin(115200);
  pinMode(botao, INPUT);
  pinMode(led_verde, OUTPUT);
  pinMode(led_vermelho, OUTPUT);
  pinMode(motor_1A, OUTPUT);
  pinMode(motor_1B, OUTPUT);
  pinMode(motor_2A, OUTPUT);
  pinMode(motor_2B, OUTPUT);
}

void loop() {
  sensor = digitalRead(botao);
  Serial.print("Estado do sensor = ");
  Serial.println(sensor);
  if (sensor == LOW) {                        //Se o sensor não captar obstáculos, acender LED verde e seguir em frente
    delay(10000); 		              //Tempo de partida de 10 segundos
    digitalWrite(led_verde, HIGH);
    digitalWrite(led_vermelho, LOW);
    Serial.println("Indo para frente");
    tempo_inicial = millis();
    analogWrite(motor_1A, 0);                 //Motor direito seguir em frente
    analogWrite(motor_1B, vel);
    analogWrite(motor_2A, 0);                 //Motor esquerdo seguir em frente
    analogWrite(motor_2B, vel);
  }
  else if (sensor == HIGH) {                  //Se o sensor captar obstáculos, acender LED vermelho e dar ré até dar o tempo de duração do percurso ocorrido
    tempo_parcial = tempo_inicial;
    tempo_final = millis();
    digitalWrite(led_verde, LOW);
    digitalWrite(led_vermelho, HIGH);
    Serial.println("Indo para trás");
    analogWrite(motor_1A, vel);               //Motor direito dar ré
    analogWrite(motor_1B, 0);
    analogWrite(motor_2A, vel);               //Motor esquerdo dar ré
    analogWrite(motor_2B, 0);
    if (tempo_final == tempo_parcial) {
      analogWrite(motor_1A, 0);               //Motor direito parar
      analogWrite(motor_1B, 0);
      analogWrite(motor_2A, 0);               //Motor esquerdo parar
      analogWrite(motor_2B, 0);
    }
  }
}
