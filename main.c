#include <avr/io.h>
#include <util/delay.h>

#define REED_PIN PB2   // Reed switch input pin (P2)
#define BUTTON_PIN PB1 // Pin to simulate button press (P1)

void setup() {
    // Configure REED_PIN as input with internal pull-up
    DDRB &= ~(1 << REED_PIN);  // Set REED_PIN as input
    PORTB |= (1 << REED_PIN);  // Enable internal pull-up resistor

    // Configure BUTTON_PIN as output
    DDRB |= (1 << BUTTON_PIN); // Set PB1 as output
    PORTB &= ~(1 << BUTTON_PIN); // Default PB1 LOW
}

void pressButton() {
    PORTB |= (1 << BUTTON_PIN);  // Set PB1 HIGH (simulate button press)
    _delay_ms(50);               // Short press duration
    PORTB &= ~(1 << BUTTON_PIN); // Return PB1 to LOW
}

int main(void) {
    setup();

    uint8_t lastState = 1; // Start with reed switch default state (HIGH)

    while (1) {
        uint8_t currentState = PINB & (1 << REED_PIN); // Read REED_PIN state

        if (currentState == 0 && lastState != 0) { // Detect transition from HIGH to LOW
            pressButton(); // Simulate button press
        }

        lastState = currentState; // Update last state
        _delay_ms(20000);         // Check every 20 seconds
    }

    return 0;
}
