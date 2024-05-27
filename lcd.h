#define LCD_ADDR 0x27

void lcd_send_nibble(uint8_t data) {
    data |= 0x08; // Set the highest bit to keep the backlight on
    i2c_start();
    i2c_write(LCD_ADDR << 1); // Send the I2C address of the LCD with the R/W bit cleared (write)
    i2c_write(data | 0x04); // Send high nibble with E high
    i2c_write(data & ~0x04); // Send high nibble with E low
    i2c_stop();
    _delay_us(50); // Short delay to let the LCD process the nibble
}

void lcd_send_byte(uint8_t data, uint8_t rs) {
    uint8_t high_nibble = (data & 0xF0) | rs;
    uint8_t low_nibble = ((data << 4) & 0xF0) | rs;
    lcd_send_nibble(high_nibble);
    lcd_send_nibble(low_nibble);
}

void lcd_send_command(uint8_t command) {
    lcd_send_byte(command, 0x00);
    _delay_ms(2); // Most commands take 40 us, but clear and home commands require more time
}

void lcd_data(uint8_t data) {
    lcd_send_byte(data, 0x01);
}

void lcd_init(void) {
    _delay_ms(50); // Wait for LCD to power up
    lcd_send_command(0x03);
    _delay_ms(5);
    lcd_send_command(0x03);
    _delay_us(150);
    lcd_send_command(0x03);
    lcd_send_command(0x02); // Switch to 4-bit mode
    lcd_send_command(0x28); // Function set: 4-bit mode, 2 line, 5x8 dots
    lcd_send_command(0x0C); // Display on, Cursor off, Blink off
    lcd_send_command(0x01); // Clear display
    _delay_ms(2); // Clear command needs more time
    lcd_send_command(0x06); // Entry mode set: Increment automatically, No display shift
}

void lcd_set_cursor(uint8_t col, uint8_t row) {
    uint8_t address = (row == 0) ? col : (col + 0x40);
    lcd_send_command(0x80 | address);
}

void lcd_clear(void) {
    lcd_send_command(0x01); // Clear display command
    _delay_ms(2); // Clear command needs more time
}

void lcd_print(char *str) {
    while (*str) {
        lcd_data(*str++);
    }
}
