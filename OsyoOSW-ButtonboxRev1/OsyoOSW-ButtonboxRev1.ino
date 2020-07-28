#include <BleGamepad.h>
#define PUSH_SHORT 50
#include "driver/pcnt.h"
#define PULSE_INPUT_PIN_A 4 //1st encoder's pulse input pin 
#define PULSE_CTRL_PIN_A 5 //1st encoder's pulse ctrl pin
#define PCNT_H_LIM_VAL 100 //not for use
#define PCNT_L_LIM_VAL -100 //not for use
#define PULSE_INPUT_PIN_B 12 //2nd encoder;s pulse input pin
#define PULSE_CTRL_PIN_B 13 //2nd encoder;s pulse ctrl pin


BleGamepad bleGamepad;
byte pins[] ={18, 19, 23, 22, 25, 26, 32, 33}; // GPIO Pin number of Key matrix
int buttonState[16]; //16 button state available but in this case it use only 12
int16_t pcount_A = 0; //1st encoder pulse counter value
int16_t pcount_B = 0; //2nd encoder pulse counter value

void setup() {
  bleGamepad.begin();
  Serial.begin( 9600 );
  for (int i=0; i<4; i++) {
    pinMode(pins[i], OUTPUT);          // Output pins setup
    digitalWrite(pins[i], HIGH);       // initial pin state setup
    pinMode(pins[i+4], INPUT_PULLUP);  // Pull-up setup for input pins
  }

  pcnt_config_t pcnt_config_A; //Declaration of 1st pulse counter configuration structures
    pcnt_config_A.pulse_gpio_num = PULSE_INPUT_PIN_A;
    pcnt_config_A.ctrl_gpio_num = PULSE_CTRL_PIN_A;
    pcnt_config_A.lctrl_mode = PCNT_MODE_REVERSE;
    pcnt_config_A.hctrl_mode = PCNT_MODE_KEEP;
    pcnt_config_A.channel = PCNT_CHANNEL_0;
    pcnt_config_A.unit = PCNT_UNIT_0;
    pcnt_config_A.pos_mode = PCNT_COUNT_INC;
    pcnt_config_A.neg_mode = PCNT_COUNT_DEC;
    pcnt_config_A.counter_h_lim = PCNT_H_LIM_VAL;
    pcnt_config_A.counter_l_lim = PCNT_L_LIM_VAL;

  pcnt_config_t pcnt_config_B;  //Declaration of 2nd pulse counter configuration structures
    pcnt_config_B.pulse_gpio_num = PULSE_INPUT_PIN_B;
    pcnt_config_B.ctrl_gpio_num = PULSE_CTRL_PIN_B;
    pcnt_config_B.lctrl_mode = PCNT_MODE_REVERSE;
    pcnt_config_B.hctrl_mode = PCNT_MODE_KEEP;
    pcnt_config_B.channel = PCNT_CHANNEL_1;
    pcnt_config_B.unit = PCNT_UNIT_1;
    pcnt_config_B.pos_mode = PCNT_COUNT_INC;
    pcnt_config_B.neg_mode = PCNT_COUNT_DEC;
    pcnt_config_B.counter_h_lim = PCNT_H_LIM_VAL;
    pcnt_config_B.counter_l_lim = PCNT_L_LIM_VAL;

                  
    // Initialize pulse counter parameters
    pcnt_unit_config(&pcnt_config_A); 
    pcnt_unit_config(&pcnt_config_B);
    pcnt_counter_pause(PCNT_UNIT_0);
    pcnt_counter_clear(PCNT_UNIT_0);
    pcnt_counter_pause(PCNT_UNIT_1);
    pcnt_counter_clear(PCNT_UNIT_1);
    pcnt_counter_resume(PCNT_UNIT_0);
    pcnt_counter_resume(PCNT_UNIT_1);

 
}


char keyStatus(void) {
  int count;
  for (int i=0; i<16; i++) { 
    buttonState[i] = LOW; //Initialize buttons of KeyMatrix
  }

  for (int i=0; i<4; i++) {
    digitalWrite(pins[i], LOW);
    for (int j=0; j<4; j++) {
        count = 0;  
        for (int k=0; k<30; k++) {              // Measures against button chattering
          if (!digitalRead(pins[j+4])) count++;
        }    
        if (count > 20) {                        // The section recognize the key push state after 20times count
        buttonState[i*4+j] = HIGH;
        //Debug          Serial.print("ButtonState HIGH: ");
        //Debug          Serial.println(i*4+j);
      }
    }
    digitalWrite(pins[i], HIGH);
  }
}

void loop() {
 //  Serial.write( keyStatus() );
    if (bleGamepad.isConnected()) {
      keyStatus(); //Get button pusing state and push it to currentButtonStete array

       if(buttonState[0] == HIGH){
          bleGamepad.press(BUTTON_1);
       }else{
          bleGamepad.release(BUTTON_1);     
       }
       if(buttonState[1] == HIGH){
          bleGamepad.press(BUTTON_2);
       }else{
          bleGamepad.release(BUTTON_2);     
       }

       if(buttonState[2] == HIGH){
          bleGamepad.press(BUTTON_3);
       }else{
          bleGamepad.release(BUTTON_3);     
       }

       if(buttonState[3] == HIGH){
          bleGamepad.press(BUTTON_4);
       }else{
          bleGamepad.release(BUTTON_4);     
       }

       if(buttonState[4] == HIGH){
          bleGamepad.press(BUTTON_5);
       }else{
          bleGamepad.release(BUTTON_5);     
       }

       if(buttonState[5] == HIGH){
          bleGamepad.press(BUTTON_6);
       }else{
          bleGamepad.release(BUTTON_6);     
       }

       if(buttonState[6] == HIGH){
          bleGamepad.press(BUTTON_7);
       }else{
          bleGamepad.release(BUTTON_7);     
       }
       if(buttonState[7] == HIGH){
          bleGamepad.press(BUTTON_8);
       }else{
          bleGamepad.release(BUTTON_8);     
       }
       if(buttonState[8] == HIGH){
          bleGamepad.press(BUTTON_9);
       }else{
          bleGamepad.release(BUTTON_9);     
       }
       if(buttonState[9] == HIGH){
          bleGamepad.press(BUTTON_10);
       }else{
          bleGamepad.release(BUTTON_10);     
       }
       if(buttonState[10] == HIGH){
          bleGamepad.press(BUTTON_11);
       }else{
          bleGamepad.release(BUTTON_11);     
       }
       if(buttonState[11] == HIGH){
          bleGamepad.press(BUTTON_12);
       }else{
          bleGamepad.release(BUTTON_12);     
       }
       if(buttonState[12] == HIGH){
          bleGamepad.press(BUTTON_13);
       }else{
          bleGamepad.release(BUTTON_13);     
       }
       if(buttonState[13] == HIGH){
          bleGamepad.press(BUTTON_14);
       }else{
          bleGamepad.release(BUTTON_14);     
       }
       if(buttonState[14] == HIGH){
          bleGamepad.press(BUTTON_15);
       }else{
          bleGamepad.release(BUTTON_15);     
       }
       if(buttonState[15] == HIGH){
          bleGamepad.press(BUTTON_16);
       }else{
          bleGamepad.release(BUTTON_16);     
       }


    


        // Pulse counter, rotary encoder section
        pcnt_get_counter_value(PCNT_UNIT_0, &pcount_A);
//Debug        if(pcount_A > 1000) pcnt_counter_clear(PCNT_UNIT_0);
//Debug        if(pcount_A < -1000) pcnt_counter_clear(PCNT_UNIT_0);
        if(pcount_A < 0){
          bleGamepad.press(BUTTON_17);
          delay(50);
          bleGamepad.release(BUTTON_17);
          pcnt_counter_clear(PCNT_UNIT_0);
          }
        if(pcount_A > 0){
          bleGamepad.press(BUTTON_18);
          delay(50);
          bleGamepad.release(BUTTON_18);
          pcnt_counter_clear(PCNT_UNIT_0);
          }
            

        pcnt_get_counter_value(PCNT_UNIT_1, &pcount_B);
//Debug        if(pcount_B > 1000) pcnt_counter_clear(PCNT_UNIT_0);
//Debug        if(pcount_B < -1000) pcnt_counter_clear(PCNT_UNIT_0);
        if(pcount_B < 0){
          bleGamepad.press(BUTTON_19);
          delay(50);
          bleGamepad.release(BUTTON_19);
          pcnt_counter_clear(PCNT_UNIT_1);
          }
        if(pcount_B > 0){
          bleGamepad.press(BUTTON_20);
          delay(50);
          bleGamepad.release(BUTTON_20);
          pcnt_counter_clear(PCNT_UNIT_1);
          }




//          ===== Pulse counter debug section =====
//          Serial.print("Counter value-A: ");
//          Serial.println(pcount_A);
//          Serial.print("Counter value-B: ");
//          Serial.println(pcount_B);

          
    }

}
