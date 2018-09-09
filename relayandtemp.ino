// This #include statement was automatically added by the Particle IDE.
#include <spark-dallas-temperature.h>

// This #include statement was automatically added by the Particle IDE.
#include <spark-dallas-temperature.h>

// This #include statement was automatically added by the Particle IDE.
#include <OneWire.h>





double tempC = 0.0;

int tempSensorPin = D2;
int RELAY1 = D3;
int RELAY2 = D4;
int RELAY3 = D5;
int RELAY4 = D6;

OneWire oneWire(tempSensorPin);
DallasTemperature sensors(&oneWire);


void setup()
{
   //Initilize the relay control pins as output
   pinMode(RELAY1, OUTPUT);
   pinMode(RELAY2, OUTPUT);
   pinMode(RELAY3, OUTPUT);
   pinMode(RELAY4, OUTPUT);
   // Initialize all relays to an OFF state
   digitalWrite(RELAY1, LOW);
   digitalWrite(RELAY2, LOW);
   digitalWrite(RELAY3, LOW);
   digitalWrite(RELAY4, LOW);
   
   sensors.begin();
   Spark.variable("tempc", &tempC, DOUBLE);

   //register the Particle function
   Particle.function("relay", relayControl);
}

void loop()
{
   // This loops for ever
   sensors.requestTemperatures();
   tempC = sensors.getTempCByIndex(0);
}

// command format r1
int relayControl(String command)
{
  int relayOff = 0;
  int relayON = 1;
  // parse the relay number
  int relayNumber = command.charAt(1) - '0';
  // do a sanity check
  if (relayNumber < 1 || relayNumber > 4) return -1;

  // find out the state of the relay
  //if (command.substring(3,7) == "HIGH") relayState = 1;
  //else if (command.substring(3,6) == "LOW") relayState = 0;
  //else return -1;

  // write to the appropriate relay
  digitalWrite(relayNumber+2, 1);
  delay(500);
  digitalWrite(relayNumber+2, 0);


  return 1;
}