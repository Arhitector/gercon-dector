#include <avr/io.h>
#include <util/delay.h>

#define REED_PIN PB2
#define BUTTON_PIN PB1

void setup() {
    DDRB &= ~(1 << REED_PIN);
    PORTB |= (1 << REED_PIN);

    DDRB |= (1 << BUTTON_PIN);
    PORTB &= ~(1 << BUTTON_PIN);
}

void pressButton() {
    PORTB |= (1 << BUTTON_PIN);
    _delay_ms(50);
    PORTB &= ~(1 << BUTTON_PIN);
}

int main(void) {
    setup();

    uint8_t lastState = 1;

    while (1) {
        uint8_t currentState = PINB & (1 << REED_PIN);

        if (currentState == 0 && lastState != 0) {
            pressButton();
        }

        lastState = currentState;
        _delay_ms(500);
    }

    return 0;
}
