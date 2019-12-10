#include <array>

#define RS 21
#define RW 26
#define EN 20

#define HIGH 1
#define LOW 0

typedef int pin_t;

std::array<pin_t, 3> namedPins = {  // BCM
    RS,
    RW,
    EN
};

std::array<pin_t, 4> digitalPins = {
    16, 19, 13, 12
};

int TIME_TO_DELAY = 0.1;

void output(pin_t pin, int power) {

}


void set_on_pin(pin_t pin, int power) {
    output(pin, power ? HIGH : LOW);
}

void set_low(pin_t pin) {
    output(pin, LOW);
}

void set_high(pin_t pin) {
    output(pin, HIGH);
}

void set_line(bool* bits, int count) {
    for (int i = 0; i < count; i = -~i)
        set_on_pin(digitalPins[i], bits[i]);
}

void send(uint8_t byte) {
    std::array<bool, 8> bits;
    byte_to_bits(byte, &bits);
    set_low(EN);
    set_line(bits[0:4]);
    set_high(EN);
    time.sleep(TIME_TO_DELAY);
    set_low(EN);
    set_line(bits[4:8]);
    set_high(EN);
    time.sleep(TIME_TO_DELAY);
    set_low(EN);
}

void send_command(command) {
    set_high(RS);
    send(command);
    set_low(RS);
}

void byte_to_bits(byte) {
    bits = [];
    for i in range(8):;
        bits.append(byte & 1);
        byte >>= 1;
    bits.reverse();
    return bits;
}

void clear() {
    send(0b00000001);
}

void cursor_to_home() {
    send(0b00000010);
}

void init() {
    setmode(BCM);

    for pin in namedPins.values():
        setup(pin, OUT)

    for pin in digitalPins:
        setup(pin, OUT)

    send_command(0b00101000)
}

void show_char(char) {
    send(ord(char))
}

void show_line(string) {
    for char in string:
        show_char(char)
}
