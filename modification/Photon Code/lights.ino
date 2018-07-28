// This #include statement was automatically added by the Particle IDE.
#include "neopixel.h"

// This #include statement was automatically added by the Particle IDE.
#include <neopixel.h>


// This #include statement was automatically added by the Particle IDE.
#include "DHT.h"

// This #include statement was automatically added by the Particle IDE.
#include "DHT.h"

// IMPORTANT: Set pixel PIN, COUNT, and TYPE
// Supported pixel types: WS2812, WS2812B, WS2812B2, WS2811, TM1803, TM1829, SK6812RGBW
#define PIXEL_PIN D2
#define PIXEL_COUNT 1
#define PIXEL_TYPE WS2812B2

#define BRIGHTNESS 50 // 0 - 255 


#define DHTPIN          D4
#define DHTTYPE         DHT22 

#define DELAY           5000

 Adafruit_NeoPixel ring = Adafruit_NeoPixel(PIXEL_COUNT, PIXEL_PIN, PIXEL_TYPE);


int setLightState(String state) {
  Serial.println("state: " + state);

  if(state == "on") {
    ring.setBrightness(BRIGHTNESS);
    changeColor(ring.Color(255, 255, 255)); // GRB+W
    ring.show();
  }
  else if(state == "off") {
    ring.setBrightness(0);
    ring.show();
  }
}

int setLightColor(String color) {
  Serial.println("color: " + color);

  if(color == "red") {
    changeColor(ring.Color(0, 255, 0)); // GRB
  }
  else if(color == "green") {
    changeColor(ring.Color(255, 0, 0)); // GRB
  }
  else if(color == "blue") {
    changeColor(ring.Color(0, 0, 255));
  }
  else if(color == "white") {
    //changeColor(ring.Color(0, 0, 0, 255)); // GRB+W
    changeColor(ring.Color(255,255,255));
  }
}

int setLightBrightness(String brightness) {
  int brightnessInt = brightness.toInt();

  if(brightnessInt >= 0 && brightnessInt <= 255) {
    Serial.println("brightness: " + brightness);

    ring.setBrightness(brightnessInt);
    ring.show();

    return brightnessInt;
  }
  else {
    Serial.println("Brightness level is invalid");

    return -1;
  }
}

void changeColor(uint32_t color) {
  for(uint16_t i=0; i < ring.numPixels(); i++) {
    ring.setPixelColor(i, color);
    ring.show();
  }
} 




DHT dht(DHTPIN, DHTTYPE);
int temperature = 0;
int humidity = 0;

// Returns temperature
int getTemperature(String args){
    return temperature;
}

// Returns humidity
int getHumidity(String args){
    return humidity;
}

// Turn on/off LEDs
int controlled(String args){
    int pos = args.indexOf(',');
    
    if(-1 == pos){
        return -1;
    }
    
    String strPin = args.substring(0, pos);
    String strValue = args.substring(pos + 1);
    
    
    int pin = D3;
    int value = HIGH;
    
    if(strPin.equalsIgnoreCase("D2")){
        pin = D3;
    }
    else if(strPin.equalsIgnoreCase("D6")){
        pin = D6;
    }
    else{
        return -2;
    }
    
    if(strValue.equalsIgnoreCase("HIGH")){
        value = HIGH;
    }
    else if(strValue.equalsIgnoreCase("LOW")){
        value = LOW;
    }
    else{
        return -3;
    }
    
    digitalWrite(pin, value);
 
    
    return 1;
}

void setup() {

    dht.begin();

   
    pinMode(D3, OUTPUT);
    pinMode(D6, OUTPUT);
  
    
    // Particle Functions
    Particle.function("gettmp", getTemperature);
    Particle.function("gethmd", getHumidity);
    Particle.function("ctrlled", controlled);
    
 

 ring.setBrightness(BRIGHTNESS);
 ring.begin();
 ring.show(); // Initialize all pixels to 'off'

  Particle.function("state", setLightState);
  Particle.function("color", setLightColor);
  Particle.function("brightness", setLightBrightness); 
    


  
}

void loop() {
    // Get temperature and humidity
    temperature = (int)dht.readTemperature();
    humidity = (int)dht.readHumidity();



    
    delay(DELAY);
}
