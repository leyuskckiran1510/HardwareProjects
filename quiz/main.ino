#ifndef OUTPUT
// for IDE LSP to keep silent
#define digitalWrite(...) (0)
#define digitalRead(...) (0)
#define delay(...) (0)
#define pinMode(...) (0)
#define OUTPUT 1
#define INPUT 1
#define HIGH 1
#define LOW 0
#define BIN 1
#define HEX 1

// https://docs.arduino.cc/retired/hacking/software/PortManipulation/
// 8-13
int DDRB = 0b11111111;
int PORTB;
int PINB;

// 0-7
int DDRD = 0b11111111;
int PORTD;
int PIND;

typedef struct {
  void (*write)();
  void (*begin)();
  void (*print)();
} _Serial;

_Serial Serial;

#endif

#define DEBUGA

#ifdef DEBUG
#define log Serial.print
#else
#define log(...)
#endif

#define ITERATE_MODE 0
#define RESET_MODE 1

int intrupt = 0;
int light_to_toggle = 0;
int reset_button = 0;
int toggle_button = 0;
int reset_seq = 0;

int ranks_map[33] = {0};
int rank_record[6] = {};
int reset_flicker_pattren[16] =
    { 
        // all_on   all_off     even_on     odd_on      1st on       2nd on
        0b11111100, 0b00000000, 0b10101000, 0b01010100, 0b10000000, 0b01000000,
        // 3rd on   4th on      5th on       6th on     1-2 on      3-4 on  
        0b00100000, 0b00010000, 0b00001000, 0b00000100, 0b11000000, 0b00110000,
        // 5-6 on   1-4 on      5-6on       all on
        0b00001100, 0b11110000, 0b00001111, 0b11111100,
};

int rank_index = 0;
int rank_show_index = 0;

void reset_rank_status() {
  rank_index = 0;
  rank_show_index = 0;
  ranks_map[0b000001] = -1;
  ranks_map[0b000010] = -1;
  ranks_map[0b000100] = -1;
  ranks_map[0b001000] = -1;
  ranks_map[0b010000] = -1;
  ranks_map[0b100000] = -1;
  for (int i = 0; i < 6; i++) rank_record[i] = 0;
}

void output_setup() { DDRD = 0b11111100; }

void input_setup() { DDRB = 0b00000000; }

void setup() {
  // Serial.begin(9600);
  output_setup();
  input_setup();
  reset_rank_status();
}

// this is for debug purpose
// remeber using Serial will interfer
// with tx pins, so don't use this in  produtcion
// when tx pin is being used to control something
void print_ranks() {
  log("Ranks\n========\n");
  for (int i = 0; i < 6; i++) {
    log(i);
    log("\t: ");
    switch (rank_record[i]) {
      case 0b000001: {
        log("port8");
        break;
      }
      case 0b000010: {
        log("port9");
        break;
      }
      case 0b000100: {
        log("port10");
        break;
      }
      case 0b001000: {
        log("port11");
        break;
      }
      case 0b010000: {
        log("port12");
        break;
      }
      case 0b100000: {
        log("port13");
        break;
      }
      default:
        log("unknown");
    }
    if (i == rank_show_index) log("\t(active)");
    log("\n");
  }
  log("========\n");
}

void reset_shower() {
  PORTD = reset_flicker_pattren[reset_seq--];
  delay(300);
}

void loop() {
  if (reset_seq > 0) {
    reset_shower();
    return;
  }
  // capture the inrupt
  intrupt = PINB & 0b00111111;
  if (intrupt && ranks_map[intrupt] < 0 && rank_index < 6) {
    ranks_map[intrupt] = rank_index;
    rank_record[rank_index++] = intrupt;
  }
  // choose the light to be toggled
  light_to_toggle = (rank_show_index < (rank_index)? rank_record[rank_show_index]: 0b00111111);
  
  // check for toggle button 
  toggle_button = (PIND & 0b10) >> 1;
  
  // check for reset button
  reset_button = PIND & 0b01;
  
  // enable the light
  PORTD = (light_to_toggle << 2);
  
  if (toggle_button) {
    rank_show_index = (rank_show_index + 1) % (rank_index + 1);
    delay(200);
  }
  
  if (reset_button) {
    PORTD = 0;
    reset_seq = 16;
    reset_rank_status();
  }
  delay(100);
}
