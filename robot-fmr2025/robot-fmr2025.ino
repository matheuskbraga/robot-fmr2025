#include <AFMotor.h>

// Motores
AF_DCMotor motorEsquerdo(2); // M2 - com encoder
AF_DCMotor motorDireito(4);  // M4 - sem encoder

// Pinos do encoder (motor esquerdo)
const int encoderA = 2;  // Com interrupção
const int encoderB = 9;  // Sem interrupção

volatile long encoderTicks = 0;  // Ticks acumulados

// Conversão
const int TICKS_POR_ROTACAO = 600;
const float CM_POR_ROTACAO = 15.7;
const float TICKS_POR_CM = TICKS_POR_ROTACAO / CM_POR_ROTACAO;  // ≈ 38.2

// Número de ticks para 90 graus
const long TICKS_POR_90GRAUS = 416;  // 90 graus é 1/4 de uma rotação completa

void setup() {
  Serial.begin(115200);

  pinMode(encoderA, INPUT);
  pinMode(encoderB, INPUT);

  // Interrupção simples usando lógica A == B
  attachInterrupt(digitalPinToInterrupt(encoderA), handleEncoder, CHANGE);

  Serial.println("Sistema pronto.");
}

void loop() {
  delay(5000);
  mover_cm(80, 255); 
  delay(500);
  girar(15, 255);
  delay(500);
  mover_cm(15, 255); 
  delay(500);
    girar(-5, 255);
    delay(500);
    mover_cm(65, 255);
    delay(500);
    girar(68, 255);
    delay(500);
    mover_cm(55, 255); 
  delay(500);
  girar(-30, 255);
  delay(500);
    mover_cm(23, 255); 
    delay(500);
      girar(-130, 140);
    delay(500);
  mover_cm(160, 255); 
while(true);
}
void resetEncoder() {
  encoderTicks = 0;
}

void mover_cm(float cm, int velocidade) {
  resetEncoder();
  long alvoTicks = abs(cm) * TICKS_POR_CM;

  Serial.print("Alvo de ticks (cm): ");
  Serial.println(alvoTicks);

  // Define direção
  if (cm > 0) {
    motorEsquerdo.setSpeed(velocidade);
    motorDireito.setSpeed(velocidade);
    motorEsquerdo.run(BACKWARD);  // Inverter para BACKWARD se o motor esquerdo estiver errado
    motorDireito.run(BACKWARD);   // Inverter para BACKWARD se o motor direito estiver errado
  } else {
    motorEsquerdo.setSpeed(velocidade);
    motorDireito.setSpeed(velocidade);
    motorEsquerdo.run(FORWARD);   // Inverter para FORWARD se o motor esquerdo estiver errado
    motorDireito.run(FORWARD);    // Inverter para FORWARD se o motor direito estiver errado
  }

  // Aguarda até atingir o alvo
  while (abs(encoderTicks) < alvoTicks) {
    Serial.print("Ticks: ");
    Serial.println(encoderTicks);
    delay(50); // Pequena pausa para não travar o loop
  }

  // Para os motores
  motorEsquerdo.run(RELEASE);
  motorDireito.run(RELEASE);

  Serial.println("Movimento concluído.");
}

// Função de interrupção para contar os ticks (lógica simples)
void handleEncoder() {
  int A = digitalRead(encoderA);
  int B = digitalRead(encoderB);

  if (A == B) {
    encoderTicks++;   // Sentido horário
  } else {
    encoderTicks--;   // Sentido anti-horário
  }
}

// Função para girar o robô para esquerda ou direita
void girar(int graus, int velocidade) {
  resetEncoder();
  long alvoTicks = abs(graus) * TICKS_POR_90GRAUS / 90; // Calcular ticks para a rotação

  Serial.print("Alvo de ticks (graus): ");
  Serial.println(alvoTicks);

  // Girar para a direita (sentido horário)
  if (graus < 0) {
    motorEsquerdo.setSpeed(velocidade);
    motorDireito.setSpeed(velocidade);
    motorEsquerdo.run(BACKWARD);  // Motor esquerdo para trás
    motorDireito.run(FORWARD);    // Motor direito para frente
  }
  // Girar para a esquerda (sentido anti-horário)
  else {
    motorEsquerdo.setSpeed(velocidade);
    motorDireito.setSpeed(velocidade);
    motorEsquerdo.run(FORWARD);   // Motor esquerdo para frente
    motorDireito.run(BACKWARD);   // Motor direito para trás
  }

  // Aguarda até atingir o número de ticks
  while (abs(encoderTicks) < alvoTicks) {
    Serial.print("Ticks: ");
    Serial.println(encoderTicks);
    delay(50); // Pequena pausa para não travar o loop
  }

  // Para os motores
  motorEsquerdo.run(RELEASE);
  motorDireito.run(RELEASE);

  Serial.println("Rotação concluída.");
}
