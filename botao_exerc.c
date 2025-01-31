#include <stdio.h>
#include "pico/stdlib.h"
#include "pico/time.h"

// Definição dos Botões e LEDs
#define BUTTON_A 5       // Pino do botão A
#define LED_VERMELHO 13  // Pino do LED Vermelho
#define LED_VERDE 11     // Pino do LED Verde
#define LED_AZUL 12      // Pino do LED Azul

// Variáveis globais
bool leds_active = false;  // Indica se os LEDs estão em execução
bool debounce_active = false; // Controle para debounce do botão
bool leds_all_off = true;  // Indica se todos os LEDs estão apagados

// Funções de callback para desligar os LEDs
int64_t turn_off_callback1(alarm_id_t id, void *user_data) {
    gpio_put(LED_VERMELHO, false); // Desliga apenas o LED vermelho
    return 0;
}

int64_t turn_off_callback2(alarm_id_t id, void *user_data) {
    gpio_put(LED_AZUL, false); // Desliga apenas o LED azul
    return 0;
}

int64_t turn_off_callback3(alarm_id_t id, void *user_data) {
    gpio_put(LED_VERDE, false); // Desliga o LED verde
    leds_active = false; // Permite novos ciclos após o último LED apagar
    leds_all_off = true; // Todos os LEDs foram apagados
    return 0;
}

// Função para inicializar os pinos GPIO
void gpio_init_all() {
    // Configuração dos LEDs como saída
    gpio_init(LED_VERMELHO);
    gpio_set_dir(LED_VERMELHO, GPIO_OUT);
    gpio_put(LED_VERMELHO, false);

    gpio_init(LED_AZUL);
    gpio_set_dir(LED_AZUL, GPIO_OUT);
    gpio_put(LED_AZUL, false);

    gpio_init(LED_VERDE);
    gpio_set_dir(LED_VERDE, GPIO_OUT);
    gpio_put(LED_VERDE, false);

    // Configuração do botão como entrada com pull-up
    gpio_init(BUTTON_A);
    gpio_set_dir(BUTTON_A, GPIO_IN);
    gpio_pull_up(BUTTON_A);
}

// Função para verificar o estado do botão com debounce
bool button_pressed() {
    if (!debounce_active && gpio_get(BUTTON_A) == 0) {
        debounce_active = true;
        sleep_ms(50); // Debounce simples
        if (gpio_get(BUTTON_A) == 0) {
            return true;
        }
        debounce_active = false; // Libera o debounce se não for pressão válida
    }
    return false;
}

int main() {
    stdio_init_all();
    gpio_init_all();

    while (true) {
        // Verifica se o botão foi pressionado e se os LEDs não estão ativos
        if (button_pressed() && !leds_active && leds_all_off) {
            leds_active = true; // Bloqueia novos ciclos enquanto os LEDs estão ativos
            leds_all_off = false; // Inicia o ciclo de LEDs
            debounce_active = false; // Libera o debounce para futuras pressões

            // Liga todos os LEDs
            gpio_put(LED_VERMELHO, true);
            gpio_put(LED_VERDE, true);
            gpio_put(LED_AZUL, true);

            // Configura os alarmes para desligar os LEDs em sequência
            add_alarm_in_ms(3000, turn_off_callback1, NULL, false);
            add_alarm_in_ms(6000, turn_off_callback2, NULL, false);
            add_alarm_in_ms(9000, turn_off_callback3, NULL, false);
        }

        sleep_ms(10); // Reduz o consumo de CPU
    }

    return 0;
}
