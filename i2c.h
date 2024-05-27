#define F_CPU 16000000UL
#define SCL_CLOCK  100000L

void i2c_init(void) {
    TWSR = 0x00; // Prescaler value to 1
    TWBR = ((F_CPU/SCL_CLOCK) - 16) / 2; // SCL frequency
    TWCR = (1<<TWEN); // Enable TWI
}

void i2c_start(void) {
    TWCR = (1<<TWSTA) | (1<<TWEN) | (1<<TWINT); // Send START condition
    while (!(TWCR & (1<<TWINT))); // Wait for TWINT Flag set. This indicates that the START condition has been transmitted
}

void i2c_stop(void) {
    TWCR = (1<<TWSTO) | (1<<TWINT) | (1<<TWEN); // Send STOP condition
}

void i2c_write(uint8_t data) {
    TWDR = data;
    TWCR = (1<<TWINT) | (1<<TWEN); // Clear TWINT bit in TWCR to start transmission of data
    while (!(TWCR & (1<<TWINT))); // Wait for TWINT Flag set. This indicates that the data has been transmitted
}