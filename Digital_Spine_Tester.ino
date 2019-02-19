/*
  Credits:
  OLED library for Oled
    Universal 8bit Graphics Library (https://github.com/olikraus/u8g2/)
  HX711 library for load cell amplifier
    Bogde HX711 lib (https://github.com/bogde/HX711)
  Button library 
    Mathertel OneButtonlib (https://github.com/mathertel/OneButton)
*/
#include <Arduino.h>
#include <U8g2lib.h>
#include <SPI.h>
#include <OneButton.h>
#include "HX711.h"

#define DOUT  2                                   //Pin 2 and 3 to connect HX711 load cell amplifier
#define CLK  3                                    //

HX711 scale(DOUT, CLK);

OneButton buttonTare(4, true);                    //Digital pin 3 for Tare button
OneButton buttonWeight(5, true);                  //Digital pin 4 for Weight button
OneButton buttonSpine(6, true);                   //Digital pin 5 for Spine button

float calibration_factor = 456;                   //Value calculated from calibration of digital scale. Standard values in grams
float baseWeight = 0.0;                           //To store shaft weight
float spineWeight = 0.0;                          //To store weight for spine measurement

U8G2_SSD1306_128X32_UNIVISION_F_HW_I2C u8g2(U8G2_R0); //Initialize the proper oled. See library sample for the correct one.

void setup(void) {
  u8g2.begin();                                   //Initialize display
  buttonTare.attachClick(click1);                 //-----------------------------------------------
  buttonTare.attachLongPressStop(pressStop1);     //Attach different..
  buttonWeight.attachClick(click2);               //..buttons actions
  buttonSpine.attachClick(click3);                //-----------------------------------------------
}

void loop(void) {
  scale.set_scale(calibration_factor);            //Adjust to the calibration factor (here 456)
  buttonTare.tick();                              //-----------------------------------------------
  buttonWeight.tick();                            //Read button state
  buttonSpine.tick();                             //-----------------------------------------------
}

void click1() {                                   //Event simple click for TARE before spine (button 3)
  scale.tare();                                   //Tare
  u8g2.clearBuffer();                             //Clear the internal buffer
  u8g2.setFont(u8g2_font_logisoso28_tr);          //Choose a font before position cursor and print
  u8g2.setCursor(0, 32);                          //Set cursor position
  u8g2.print(0.0, 2);                             //Print 0.00 with two decimals
  u8g2.setFont(u8g2_font_t0_16_tr);               //Change font
  u8g2.setCursor(85, 24);                         //Change cursor position
  u8g2.print("But3>");                            //Print But3 to indicate to click the third button
  u8g2.sendBuffer();                              //Transfer internal memory to the display
}

void pressStop1() {                               //Event end of long press to tare before weight shaft
  scale.tare();                                   
  u8g2.clearBuffer();                             
  u8g2.setFont(u8g2_font_logisoso28_tr);          
  u8g2.setCursor(0, 32);                          
  u8g2.print(0.0, 2);                             
  u8g2.setFont(u8g2_font_t0_16_tr);               
  u8g2.setCursor(85, 24);                         
  u8g2.print("But2>");                            //Print But2 to indicate to click the second button
  u8g2.sendBuffer();                              
}

void click2() {                                   //Event click for Weight
  baseWeight=scale.get_units(10);                 //Average of ten readings 
  u8g2.clearBuffer();                             
  u8g2.setFont(u8g2_font_logisoso28_tr);   
  u8g2.setCursor(0, 32);                   
  u8g2.print(baseWeight, 2);                      //Print shaft weight with two decimals
  u8g2.setFont(u8g2_font_t0_16_tr);
  u8g2.setCursor(85, 16);
  u8g2.print(baseWeight, 2);                      //Print resume of the shaft weight
  u8g2.sendBuffer();                       
}
void click3() {                                   //Event click for Spine
  float localWeight=0.0;                          //Variable to store the weight for spine calc
  localWeight=scale.get_units(10);                
  spineWeight=(((localWeight/1000.00)-0.521980143)*60/1.565940428)+20;      //Formula to calculate the spine. It depends from maximum bending
  u8g2.clearBuffer();                      
  u8g2.setFont(u8g2_font_logisoso28_tr);   
  u8g2.setCursor(0, 32);                   
  u8g2.print(spineWeight, 2);                     //Print shaft spine with two decimals
  u8g2.setFont(u8g2_font_t0_16_tr);
  u8g2.setCursor(85, 16);
  u8g2.print(baseWeight, 2);                      //Print resume of the shaft weight
  u8g2.setFont(u8g2_font_t0_16_tr);
  u8g2.setCursor(85, 32);
  u8g2.print(spineWeight, 2);                     //Print resume of the shaft spine
  u8g2.sendBuffer();                       
}
