# Projeto de Controle Sequencial de LEDs com Raspberry Pi Pico

Este projeto demonstra o controle de três LEDs (vermelho, verde e azul) através de um botão. Ao pressionar o botão, todos os LEDs são acesos simultaneamente e, após um intervalo de tempo, eles se apagam em sequência:
- **LED Vermelho:** Desliga após 3 segundos.
- **LED Azul:** Desliga após 6 segundos.
- **LED Verde:** Desliga após 9 segundos (finalizando o ciclo).

## Funcionalidades

- **Debounce no Botão:** Implementação de debounce para evitar leituras incorretas.
- **Controle Sequencial:** Os LEDs se apagam em ordem com intervalos definidos.
- **Restrições de Estado:** Evita a reativação do ciclo enquanto o ciclo anterior não foi concluído.

## Requisitos

- **Hardware:**
  - [Raspberry Pi Pico](https://www.raspberrypi.com/documentation/microcontrollers/)
  - LEDs (vermelho, verde, azul)
  - Resistores compatíveis com LEDs
  - Botão push-button
  - Protoboard e jumpers

- **Software:**
  - [SDK do Pico](https://github.com/raspberrypi/pico-sdk)
  - Ambiente de desenvolvimento C/C++ configurado para o Pico
  - Ferramenta de compilação (CMake, Make ou similar)

## Configuração do Hardware

1. **Conexões dos LEDs:**
   - **LED Vermelho:** Conectado ao pino GPIO 13.
   - **LED Verde:** Conectado ao pino GPIO 11.
   - **LED Azul:** Conectado ao pino GPIO 12.
   
2. **Botão:**
   - Conecte o botão ao pino GPIO 5.
   - Configure o botão com pull-up (o programa já configura via `gpio_pull_up(BUTTON_A)`).

3. **Montagem:**
   - Conecte os LEDs através de resistores aos respectivos pinos e ao GND.
   - Monte o botão de forma que, ao ser pressionado, o pino GPIO 5 seja conectado ao GND.

## Compilação e Upload

1. **Clonar o Repositório e Configurar o SDK:**
   ```bash
   git clone https://seu-repositorio-exemplo.git
   cd seu-repositorio-exemplo
   mkdir build && cd build
   cmake ..
