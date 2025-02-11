/******************************************************/
/* 
       Title:   VBand Interface with a SeeeduinoXIAO.
      Author:   JA van Hernen, www.pe1hvh.nl
        Date:   5 Jan 2025
     Version:   1.0   
    Hardware:   Seeeduino XIAO samd
         IDE:   Arduino IDE 1.8.19
       Legal:   Copyright (c) 2025  JA van Hernen.
                Open Source under the terms of the MIT License. 

  Description

  Simple program to generate a key keystroke with your favorite morse key for using VBand 
  
  After adding the interface to a computer USB port, the program wait for a initial key press
  The first pressed by the morse key
   - if straight key or left paddle => Interface used for straight key
   - if right paddle => Interface used for paddle
   
  Used hardware as describe at  https://hackaday.io/project/184702-morse-code-usbhid-interface-the-gadget  
  
  Add Seeeduino to your Arduino IDE
        Click on File > Preference, and fill Additional Boards Manager URLs with the url below:
        https://files.seeedstudio.com/arduino/package_seeeduino_boards_index.json
        and use your library managers to install the keyboard library.
    

   Notes and Warnings

   When you use the Keyboard.print() command, the Arduino takes over your keyboard! 
   Make sure you have control before you use the command. 
   VBand: https://hamradio.solutions/vband/

*/  

#include <Keyboard.h>
#define inPin6 6 // Straight Key or left paddle
#define inPin7 7 // Right Paddle

/*****************************************************/
/* @brief The BaseHandler                            */
/*****************************************************/

class BaseHandler {

  public:

    virtual void handleMorseKey(int pinDot ,int pinDash) = 0;
    virtual void initHandler() = 0;


};

/*****************************************************/
/* @brief The Straight Key Handler                   */
/*****************************************************/
class StraightKeyHandler : public BaseHandler {
  
  public:
  
    void initHandler() override {
            Keyboard.begin();
        }


    void handleMorseKey(int pinKey ,int pinDummy) override {
             if(pinKey == LOW || pinDummy == LOW )  { //pin==LOW  => is closed (activated )
                 Keyboard.press(KEY_LEFT_CTRL);       // print a space on the monitor window    
              } else {                                //pin==HIGH => is open ( deactived )
                 Keyboard.releaseAll();
              }  
           }
    

};
/*****************************************************/
/* @brief The PaddleHandler                          */
/*****************************************************/
class PaddleHandler : public BaseHandler {
  
  public:
  
    void initHandler() override {
            Keyboard.begin();
        }


    void handleMorseKey(int pinDot ,int pinDash) override {
             if(pinDot == LOW)                      { //pin==LOW  => is closed (activated )
                 Keyboard.press(KEY_LEFT_CTRL);       // print a space on the monitor window    
              }else if(pinDash == LOW)              { //pin==LOW  => is closed (activated )  
                 Keyboard.press(KEY_RIGHT_CTRL);      // print a space on the monitor window    
              }  else {                               //pin==HIGH => is open ( deactived )
                 Keyboard.releaseAll();
              }  
           }
    
};

/*********************************************/
/* @brief Calculation of key pressed         */
/*********************************************/ 
class InputType {
  
  private:
    
    int type = 0; // 0 => single key  1 => paddle   

  public:
  
    /******************************************/
    /* @brief setType                         */   
    /******************************************/
    void setType() {
         while (digitalRead(inPin6) == HIGH && digitalRead(inPin7)==HIGH) {
            //key is not Pressed
            delay(25);                // simple method against bouncing
         }
         
         if(digitalRead(inPin6) == LOW ) {
            delay(25);                // simple method against bouncing
            type = 0; 
         } else {
            delay(25);                // simple method against bouncing
            type = 1; 
         }        
    }

    /******************************************/
    /* @brief The getter for type             */   
    /******************************************/
    int getType(){
         return type;
    }
          
};

BaseHandler* myObjectHandler = nullptr;  // Declare the pointer to the BaseHandler class and initialize it to nullptr
                                         // myObjectHandler is the pointer that hold the address of a BaseHandler object.
                                         // it is initiazed to nullptr, meaning it currently do not point (now) to any object


void setup() {
  pinMode(inPin6, INPUT_PULLUP);
  pinMode(inPin7, INPUT_PULLUP);
 
  InputType myInputType; 
  myInputType.setType();
  
  if(myInputType.getType()==0) {
    myObjectHandler = new StraightKeyHandler();
  } else {
    myObjectHandler = new PaddleHandler();
  }
  myObjectHandler->initHandler();
  
}
/****************************************************/
/* @brief loop 
   1. Determine the status of pin6 and pin 7
   2. Use Straight Key or Paddle  
*/
/****************************************************/
void loop(){
 
     myObjectHandler->handleMorseKey(digitalRead(inPin6),digitalRead(inPin7));
 
}
