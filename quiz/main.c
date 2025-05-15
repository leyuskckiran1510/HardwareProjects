
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

#define DEBUG

#ifdef DEBUG 
#define log Serial.print
#else 
#define log(...) 
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

void print_ranks(){
    log("Ranks\n========\n");
    for(int i=0;i<6;i++){
        log(i);
        log("\t: ");
        switch (rank_record[i]){
            case 0b000001: {log("port8"); break;}
            case 0b000010: {log("port9"); break;}
            case 0b000100: {log("port10"); break;}
            case 0b001000: {log("port11"); break;}
            case 0b010000: {log("port12"); break;}
            case 0b100000: {log("port13"); break;}
            default:  log("unknown");  
        }
        if(i==rank_show_index) log("\t(active)");
        log("\n");
    }
    log("========\n");
}

#define ITERATE_MODE 0b00
#define RESET_MODE   0b10

void loop(){
    int intrupt = PINB&0b00111111; 
    
    if(intrupt && ranks_map[intrupt] < 0 && rank_index<6){
        ranks_map[intrupt] = rank_index;
        rank_record[rank_index++] = intrupt;
    }
    int light_to_toggle = rank_show_index < (rank_index) ?rank_record[rank_show_index]:0b00111111; 
    int pin1Toggle = PIND&0b01;
    int pin1Mode   = PIND&0b10;
    PORTD = (light_to_toggle<<2);


    switch (pin1Mode) {
        case ITERATE_MODE:{
            if(pin1Toggle){
                rank_show_index= (rank_show_index+1)%(rank_index+1);
            }
            break;
        }
        case RESET_MODE:{
            Serial.write("Reset Mode on \n");
            if(pin1Toggle){
                PORTD=0;
                reset_rank_status();
    
            }
            break;
        }
    }
    print_ranks();
    delay(10);
}
