
#include <Wire.h>
/*
 ic2 is at pc4,pc5
 sig_a_EN  pd3
 sig_b_EN  pd4
 r_enable_44
 r_enable_27
 r_enable_0
*/
#define SIG_INIT        DDRD = 0
#define A_EN        	PORTD |=   (1<<3)
#define A_DIS			PORTD &=  ~(1<<3)
#define B_EN        	PORTD |=   (1<<4)
#define B_DIS			PORTD &=  ~(1<<4)

#define RESISTOR_44_on   DDRD  |=  (1<<7)
#define RESISTOR_44_off  DDRD  &= ~(1<<7)
#define RESISTOR_27_on   DDRB  |=  (1<<0)
#define RESISTOR_27_off  DDRB  &= ~(1<<0)
#define RESISTOR_0_on    DDRB  |=  (1<<1)
#define RESISTOR_0_off   DDRB  &= ~(1<<1)

#define LED_INIT        DDRB  |=    (1<<5)
#define LED1			PORTB |=    (1<<5)
#define LED0			PORTB &=   ~(1<<5)


char c;
int i=0;

void disable_ab(){
    A_DIS;
    B_DIS;
}
void disable_all(){
    RESISTOR_0_off;
    RESISTOR_27_off;
    RESISTOR_44_off;
    disable_ab();
    LED0;
}

void receiveEvent(int how_many){
    i=0;
    while ( Wire.available() > 0 ){
        LED1;
        c = Wire.read();
        if (c==0){
            return;
        }
        else if (c==1){
            return;
        }
        else if (c==2){
            A_EN;
            RESISTOR_0_on;
        }
        else if (c==3){
            B_EN;
            RESISTOR_0_on;
        }
        else if (c==4){
            A_EN;
            RESISTOR_27_on;
        }
        else if (c==5){
            B_EN;
            RESISTOR_27_on;
        }
        else if (c==6){
            A_EN;
            RESISTOR_44_on;
        }
        else if (c==7){
            B_EN;
            RESISTOR_44_on;
        }
    }
}


void setup() {
    MCUCR &= ~(1<<PUD); // enable pullups
    LED_INIT;
    SIG_INIT;
    Wire.begin(8);
    Wire.onReceive(receiveEvent);
}

void loop() {
    delay(100);
    i++;
    if (i>1){
        disable_all();
        i=0;
    }
}
