
#ifndef OUTPUT
// for IDE LSP to keep silent
#define digitalWrite(...) (0)
#define digitalRead(...) (0)
#define delay(...) (0)
#define  pinMode(...) (0)
#define OUTPUT 1 
#define INPUT 1
#define HIGH 1
#define LOW 0
#define BIN 1
#define HEX 1


// https://docs.arduino.cc/retired/hacking/software/PortManipulation/
// 8-13
int DDRB =  0b11111111;
int PORTB;
int PINB;

// 0-7
int DDRD =  0b11111111; 
int PORTD;
int PIND;

typedef struct{
    void(*write)();
    void(*begin)();
    void(*print)();
}_Serial;

_Serial Serial;

#endif

int ranks_map[33]={0};
int rank_record[6]={};


int rank_index=0;
int rank_show_index=0;

void reset_rank_status(){
    rank_index=0;
    rank_show_index=0;
    ranks_map[0b000001]=-1;
    ranks_map[0b000010]=-1;
    ranks_map[0b000100]=-1;
    ranks_map[0b001000]=-1;
    ranks_map[0b010000]=-1;
    ranks_map[0b100000]=-1;
    for(int i=0;i<6;i++) rank_record[i]=0;
}



void output_setup(){
    DDRD = 0b11111100;
}

void input_setup(){
    DDRB = 0b00000000;
}

void setup(){
    Serial.begin(9600);
    output_setup();
    input_setup();
    reset_rank_status();
}

#define ITERATE_MODE 0b00
#define RESET_MODE   0b10

void loop(){
    int intrupt = PINB&0b00111111; 
    
    if(intrupt && ranks_map[intrupt] < 0 && rank_index<6){
        ranks_map[intrupt] = rank_index;
        rank_record[rank_index] = intrupt;
    }
    int light_to_toggle = rank_show_index<6?rank_record[rank_show_index]:0b00111111; 
    int pin1Toggle = PIND&0b01;
    int pin1Mode   = PIND&0b10;
    Serial.print(PIND,BIN);
    Serial.print("\n");
    PORTD ^= (light_to_toggle<<2);


    switch (pin1Mode) {
        case ITERATE_MODE:{
            if(pin1Toggle){
                rank_show_index= (rank_show_index+1)%7;
            }
            break;
        }
        case RESET_MODE:{
            if(pin1Toggle){
                PORTD=0;
                reset_rank_status();
    
            }
            break;
        }
    }
    delay(10);
}
