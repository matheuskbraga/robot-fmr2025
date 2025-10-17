# Controle de Robô com Encoder usando Arduino

Este projeto implementa o controle de movimentação de um robô com dois motores DC, sendo um deles equipado com encoder. O sistema permite deslocamentos precisos em centímetros e rotações angulares em graus, utilizando a biblioteca [AFMotor](https://learn.adafruit.com/adafruit-motor-shield/library-install) para controle dos motores.

---

## Visão Geral:

O robô possui:

- **Motor esquerdo (M2)** com encoder para medição de deslocamento
- **Motor direito (M4)** sem encoder
- **Encoder óptico** conectado aos pinos digitais 2 (interrupção) e 9

A movimentação é baseada na contagem de "ticks" do encoder, convertidos em centímetros ou graus de rotação.

---

## Funcionalidades:

- ✅ Movimentação linear com precisão em centímetros
- 🔄 Rotação angular em graus (esquerda/direita)
- 📊 Contagem de ticks via interrupção
- 🔁 Conversão de unidades:
  - 600 ticks por rotação completa
  - 15,7 cm por rotação
  - ~38,2 ticks por centímetro
  - 416 ticks para uma rotação de 90°

---

## Requisitos:

- Arduino Uno (ou compatível)
- Shield de motores compatível com a biblioteca AFMotor
- Motor DC com encoder (mínimo um)
- Fonte de alimentação adequada

---

## Estrutura do Código:

- `setup()`: inicializa comunicação serial, configura pinos e interrupções
- `loop()`: executa uma sequência de movimentos e rotações
- `mover_cm(cm, velocidade)`: movimenta o robô em linha reta
- `girar(graus, velocidade)`: realiza rotação angular
- `handleEncoder()`: função de interrupção que atualiza os ticks do encoder
- `resetEncoder()`: zera a contagem de ticks

---

## Exemplo de Trajetória:

O `loop()` realiza a seguinte sequência:

1. Move 80 cm para frente
2. Gira 15° à esquerda
3. Move 15 cm
4. Gira 5° à direita
5. Move 65 cm
6. Gira 68° à esquerda
7. Move 55 cm
8. Gira 30° à direita
9. Move 23 cm
10. Gira 130° à direita
11. Move 160 cm

---

## Observações:

- A direção dos motores pode variar conforme a montagem. Ajuste `FORWARD` e `BACKWARD` conforme necessário
- O encoder deve estar corretamente calibrado para garantir precisão
- O sistema usa lógica simples de quadratura: `A == B` para sentido horário, `A != B` para anti-horário

---

## Referências:

- [AFMotor Library - Adafruit](https://learn.adafruit.com/adafruit-motor-shield/library-install)
- [Arduino - attachInterrupt()](https://www.arduino.cc/reference/en/language/functions/external-interrupts/attachinterrupt/)
