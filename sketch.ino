#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>
#include "i2c.h"
#include "lcd.h"
#include "keypad.h"

// RGB LED pins
#define RED_LED_PIN    PB3  // OC0A (pin 11)
#define GREEN_LED_PIN  PB2  // OC1B (pin 10)
#define BLUE_LED_PIN   PB1  // OC2A (pin 9)

// Potentiometer pins
#define RED_POT_PIN    PC0  // A0
#define GREEN_POT_PIN  PC1  // A1
#define BLUE_POT_PIN   PC2  // A2

// Motion sensor pin
#define MOTION_SENSOR_LED_PIN  PB4  // Pin 12
#define MOTION_SENSOR_PIN      PB5  // Pin 13

// Function Prototypes
void init_pins(void);
void init_pwm(void);
uint16_t read_adc(uint8_t channel);
void set_led_color(uint8_t red, uint8_t green, uint8_t blue);
uint8_t read_motion_sensor(void);
void keypad_init(void);
char keypad_get_key(void);

volatile uint8_t red_value, green_value, blue_value;
volatile uint16_t light_duration = 0;
volatile uint32_t start_waiting_time = 0;
volatile uint8_t motion_detected = 0;

void setup() {
    // Serial communication initialization is removed as it's unused in this code
    init_pins();
    init_pwm();
    i2c_init();
    lcd_init();
    keypad_init();
    sei(); // Enable global interrupts

    lcd_print("Motion Light");
    _delay_ms(1000);
    lcd_clear();
    lcd_print("Waiting motion");
}

void loop() {
    // Read potentiometer values
    red_value = 256 - (read_adc(RED_POT_PIN) >> 2); // Map 0-1023 to 255-0
    green_value = read_adc(GREEN_POT_PIN) >> 2 ;
    blue_value = read_adc(BLUE_POT_PIN) >> 2;

    // Set the color according to potentiometers
    set_led_color(blue_value, green_value, red_value);

    // Check keypad for duration setting
    char key = keypad_get_key();
    if (key == 'S') {
        lcd_clear();
        lcd_print("Set duration: ");
        char duration_str[5] = "";
        uint8_t idx = 0;
        while (1) {
            key = keypad_get_key();
            if (key == 'E') {
                duration_str[idx] = '\0';
                light_duration = atoi(duration_str);
                lcd_clear();
                lcd_print("Duration set to: ");
                lcd_set_cursor(0, 1);
                char buffer[16];
                snprintf(buffer, sizeof(buffer), "%d sec", light_duration);
                lcd_print(buffer);
                _delay_ms(1500);
                lcd_clear();
                lcd_print("Waiting motion");
                break;
            } else if (key != '\0' && idx < 4) {
                duration_str[idx++] = key;
                lcd_set_cursor(idx, 1);
                lcd_data(key);
            }
        }
    }

    // Check motion sensor
    if (read_motion_sensor()) {
        if (!motion_detected) {
            motion_detected = 1;
            start_waiting_time = 0;
            lcd_clear();
            lcd_print("Motion Detected!");
            PORTB |= (1 << MOTION_SENSOR_LED_PIN);
            lcd_set_cursor(0, 1);
            lcd_print("Waiting!");
        } else {
            start_waiting_time = 0;  // Reset countdown if motion detected again
        }
    }

    // If motion was previously detected
    if (motion_detected) {
        if (start_waiting_time >= light_duration * 10) {
            PORTB &= ~(1 << MOTION_SENSOR_LED_PIN);
            lcd_clear();
            lcd_print("Waiting motion");
            motion_detected = 0;
        } else {
            if (start_waiting_time % 10 == 0) {
                uint32_t remaining_time = (light_duration * 10 - start_waiting_time) / 10;
                lcd_set_cursor(0, 1);
                char buffer[16];
                snprintf(buffer, sizeof(buffer), "Waiting... %lu sec", remaining_time);
                lcd_print(buffer);
            }
            start_waiting_time++;
        }
    }

    _delay_ms(100);
}

// Initialize pins
void init_pins(void) {
    DDRB |= (1 << RED_LED_PIN) | (1 << GREEN_LED_PIN) | (1 << BLUE_LED_PIN) | (1 << MOTION_SENSOR_LED_PIN);
    DDRB &= ~(1 << MOTION_SENSOR_PIN);
    PORTB |= (1 << MOTION_SENSOR_PIN);

    ADMUX |= (1 << REFS0);  // AVcc with external capacitor at AREF pin
    ADCSRA |= (1 << ADEN) | (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);  // Enable ADC and set prescaler to 128
}

// ADC
uint16_t read_adc(uint8_t channel) {
    ADMUX = (ADMUX & 0xF0) | (channel & 0x0F);
    ADCSRA |= (1 << ADSC);  // Start conversion
    while (ADCSRA & (1 << ADSC));  // Wait for conversion to complete
    return ADC;
}

void init_pwm(void) {
    // Timer0 for Red LED (OC0A)
   // Timer2 for Blue LED (OC2A)
    TCCR1A |= (1 << WGM10) | (1 << WGM11) | (1 << COM1A1); // Fast PWM, non-inverting mode
    TCCR1B |= (1 << CS11);

    // Timer1 for Green LED (OC1B)
    TCCR1A |= (1 << WGM10) | (1 << COM1B1);  // 8-bit Fast PWM, non-inverting mode
    TCCR1B |= (1 << CS11) | (1 << WGM12);  // Prescaler 8

    // Timer2 for Blue LED (OC2A)
    TCCR2A |= (1 << WGM20) | (1 << WGM21) | (1 << COM2A1); // Fast PWM, non-inverting mode
    TCCR2B |= (1 << CS21);

}

// Set LED color
void set_led_color(uint8_t red, uint8_t green, uint8_t blue) {
    OCR1A = red;    // Red LED on Timer0 OC0A
    OCR1B = green;  // Green LED on Timer1 OC1B
    OCR2A = blue;   // Blue LED on Timer2 OC2A
}

// Read motion sensor state
uint8_t read_motion_sensor(void) {
    return PINB & (1 << MOTION_SENSOR_PIN);
}
