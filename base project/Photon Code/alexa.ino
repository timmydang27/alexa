// This #include statement was automatically added by the Particle IDE.
#include "DHT.h"

// This #include statement was automatically added by the Particle IDE.
#include "DHT.h"

#define DHTPIN          D4
#define DHTTYPE         DHT22

#define DELAY           5000





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
    
    
    int pin = D2;
    int value = HIGH;
    
    if(strPin.equalsIgnoreCase("D2")){
        pin = D2;
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
    
    pinMode(D2, OUTPUT);
    pinMode(D6, OUTPUT);
    
    // Particle Functions
    Particle.function("gettmp", getTemperature);
    Particle.function("gethmd", getHumidity);
    Particle.function("ctrlled", controlled);
    


  
}

void loop() {
    // Get temperature and humidity
    temperature = (int)dht.readTemperature();
    humidity = (int)dht.readHumidity();



    
    delay(DELAY);
}
