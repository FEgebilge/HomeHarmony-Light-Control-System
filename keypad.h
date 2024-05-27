#include <avr/io.h>
#include <util/delay.h>

#define ROWS 4
#define COLS 3

// Array representing the keypad connections
char keys[ROWS][COLS] = {
    {'1','2','3'},
    {'4','5','6'},
    {'7','8','9'},
    {'S','0','E'}
};

void DigitalWrite(uint8_t pin, uint8_t value) {
    if (pin >= 0 && pin <= 7) { // Port D
        if (value == LOW) {
            PORTD &= ~(1 << pin); // Clear the corresponding bit in PORTD to set the pin LOW
        } else if (value == HIGH) {
            PORTD |= (1 << pin);  // Set the corresponding bit in PORTD to set the pin HIGH
        }
    } else if (pin >= 8 && pin <= 13) { // Port B
        pin -= 8; // Adjust pin number for Port B
        if (value == LOW) {
            PORTB &= ~(1 << pin); // Clear the corresponding bit in PORTB to set the pin LOW
        } else if (value == HIGH) {
            PORTB |= (1 << pin);  // Set the corresponding bit in PORTB to set the pin HIGH
        }
    } else if (pin >= 14 && pin <= 19) { // Port C (analog pins)
        pin -= 14; // Adjust pin number for Port C
        if (value == LOW) {
            PORTC &= ~(1 << pin); // Clear the corresponding bit in PORTC to set the pin LOW
        } else if (value == HIGH) {
            PORTC |= (1 << pin);  // Set the corresponding bit in PORTC to set the pin HIGH
        }
    }
}

uint8_t DigitalRead(uint8_t pin) {
    if (pin >= 0 && pin <= 7) { // Port D
        return (PIND & (1 << pin)) ? 1 : 0; // Read the corresponding bit in PIND
    } else if (pin >= 8 && pin <= 13) { // Port B
        pin -= 8; // Adjust pin number for Port B
        return (PINB & (1 << pin)) ? 1 : 0; // Read the corresponding bit in PINB
    } else if (pin >= 14 && pin <= 19) { // Port C (analog pins)
        pin -= 14; // Adjust pin number for Port C
        return (PINC & (1 << pin)) ? 1 : 0; // Read the corresponding bit in PINC
    }
    return 0; // Return 0 if pin number is out of range
}

void PinMode(uint8_t pin, uint8_t mode) {
    if (pin >= 0 && pin <= 7) { // Port D
        if (mode == INPUT) {
            DDRD &= ~(1 << pin); // Clear the corresponding bit in DDRD to set the pin as input
            PORTD &= ~(1 << pin); // Clear the corresponding bit in PORTD to disable pull-up
        } else if (mode == OUTPUT) {
            DDRD |= (1 << pin);  // Set the corresponding bit in DDRD to set the pin as output
        } else if (mode == INPUT_PULLUP) {
            DDRD &= ~(1 << pin); // Clear the corresponding bit in DDRD to set the pin as input
            PORTD |= (1 << pin);  // Set the corresponding bit in PORTD to enable pull-up
        }
    } else if (pin >= 8 && pin <= 13) { // Port B
        pin -= 8; // Adjust pin number for Port B
        if (mode == INPUT) {
            DDRB &= ~(1 << pin); // Clear the corresponding bit in DDRB to set the pin as input
            PORTB &= ~(1 << pin); // Clear the corresponding bit in PORTB to disable pull-up
        } else if (mode == OUTPUT) {
            DDRB |= (1 << pin);  // Set the corresponding bit in DDRB to set the pin as output
        } else if (mode == INPUT_PULLUP) {
            DDRB &= ~(1 << pin); // Clear the corresponding bit in DDRB to set the pin as input
            PORTB |= (1 << pin);  // Set the corresponding bit in PORTB to enable pull-up
        }
    } else if (pin >= 14 && pin <= 19) { // Port C (analog pins)
        pin -= 14; // Adjust pin number for Port C
        if (mode == INPUT) {
            DDRC &= ~(1 << pin); // Clear the corresponding bit in DDRC to set the pin as input
            PORTC &= ~(1 << pin); // Clear the corresponding bit in PORTC to disable pull-up
        } else if (mode == OUTPUT) {
            DDRC |= (1 << pin);  // Set the corresponding bit in DDRC to set the pin as output
        } else if (mode == INPUT_PULLUP) {
            DDRC &= ~(1 << pin); // Clear the corresponding bit in DDRC to set the pin as input
            PORTC |= (1 << pin);  // Set the corresponding bit in PORTC to enable pull-up
        }
    }
}

// Pins for rows
byte rowPins[ROWS] = { 8, 7, 6, 5 }; // Connected pins on the Arduino

// Pins for columns
byte colPins[COLS] = { 4, 3, 2 }; // Connected pins on the Arduino

// Initialize the keypad
void keypad_init(void) {
    // Set row pins as output
    for (int i = 0; i < ROWS; i++) {
        PinMode(rowPins[i], OUTPUT);
        DigitalWrite(rowPins[i], HIGH); // Enable pull-up resistors
    }

    // Set column pins as input and enable pull-up resistors
    for (int i = 0; i < COLS; i++) {
        PinMode(colPins[i], INPUT_PULLUP);
    }
}

// Read the pressed key
char keypad_get_key(void) {
    for (uint8_t row = 0; row < ROWS; row++) {
        // Set all rows high
        for (int i = 0; i < ROWS; i++) {
            DigitalWrite(rowPins[i], HIGH);
        }

        // Set the current row low
        DigitalWrite(rowPins[row], LOW);

        // Wait for the signal to settle
        _delay_us(1);

        for (uint8_t col = 0; col < COLS; col++) {
            // Check if the corresponding column is low
            if (!DigitalRead(colPins[col])) {
                // Debounce delay
                _delay_ms(50);
                // Wait for the key to be released
                while (!DigitalRead(colPins[col]));
                // Return the corresponding key value
                return keys[row][col];
            }
        }
    }

    // Return null character if no key is pressed
    return '\0';
}
