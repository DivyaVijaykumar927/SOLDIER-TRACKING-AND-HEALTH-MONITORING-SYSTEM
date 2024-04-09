#include <Arduino_FreeRTOS.h> 
#include <SoftwareSerial.h> 
#include <TinyGPS++.h> 
 
// Pin configuration 
const int heartRateSensorPin = A1;    // Analog pin connected to heart 
rate sensor 
const int temperatureSensorPin = A0;  // Analog pin connected to the 
temperature sensor 
const int digitalPin = 5;             // Arduino's pin connected to digital 
pin of the MQ-2 sensor 
const int buzzerPin = 8;              // Pin connected to the buzzer 
const int RXPin = 4, TXPin = 3;       // Pins for SoftwareSerial 
communication 
const uint32_t GPSBaud = 9600;        // GPS baud rate 
 
// Task handles 
TaskHandle_t heartRateTaskHandle; 
TaskHandle_t locationTaskHandle; 
TaskHandle_t temperatureTaskHandle; 
TaskHandle_t gasSensorTaskHandle; 
 
// Threshold values 
const int heartRateThreshold = 200; 
2 
 
const float temperatureThreshold = 40; 
const int gasThreshold = 500; 
 
// Function prototypes 
void heartRateTask(void *pvParameters); 
void locationTask(void *pvParameters); 
void temperatureTask(void *pvParameters); 
void gasSensorTask(void *pvParameters); 
 
// GPS related objects 
TinyGPSPlus gps; 
SoftwareSerial GPS(RXPin, TXPin); 
 
void setup() { 
  Serial.begin(9600); 
  GPS.begin(GPSBaud); 
 
  pinMode(buzzerPin, OUTPUT); // Set buzzer pin as output 
 
  // Create tasks 
  xTaskCreate(heartRateTask, "HeartRateTask", 100, NULL, 4, 
&heartRateTaskHandle); // Highest priority 
  xTaskCreate(locationTask, "LocationTask", 100, NULL, 1, 
&locationTaskHandle);     // Lowest priority 
  xTaskCreate(temperatureTask, "TemperatureTask", 100, NULL, 3, 
&temperatureTaskHandle); 
3 
 
  xTaskCreate(gasSensorTask, "GasSensorTask", 100, NULL, 2, 
&gasSensorTaskHandle); 
} 
 
void loop() { 
  vTaskDelete(NULL); // Loop not used in FreeRTOS 
} 
 
// Task to read heart rate sensor 
void heartRateTask(void *pvParameters) { 
  (void) pvParameters; 
  for (;;) { 
    // Read the analog value from the heart rate sensor 
    int sensorValue = analogRead(heartRateSensorPin); 
    // Convert the analog value to heart rate value 
    int heartRateValue = map(sensorValue, 0, 1023, 60, 200); 
    // Print heart rate value 
    Serial.print("Heart Rate: "); 
    Serial.println(heartRateValue); 
 
    // Check if heart rate is abnormal 
    if (heartRateValue > heartRateThreshold) { 
      Serial.println("Abnormal Heart Rate"); 
      digitalWrite(buzzerPin, HIGH); // Turn on buzzer 
    } else { 
4 
 
      digitalWrite(buzzerPin, LOW); // Turn off buzzer 
    } 
    vTaskDelay(1000 / portTICK_PERIOD_MS); // Delay 1 second 
  } 
} 
 
// Task to read location from GPS 
void locationTask(void *pvParameters) { 
  (void) pvParameters; 
  for (;;) { 
    // GPS task implementation remains the same 
    vTaskDelay(1000 / portTICK_PERIOD_MS); // Delay 1 second 
  } 
} 
 
// Task to read temperature sensor 
void temperatureTask(void *pvParameters) { 
  (void) pvParameters; 
  for (;;) { 
    // Read the analog value from the temperature sensor 
    int sensorValue = analogRead(temperatureSensorPin); 
    // Convert the analog value to temperature in Celsius 
    float voltage = sensorValue * (5.0 / 1023.0); 
    float temperatureCelsius = voltage * 100.0; 
    // Print temperature value 
5 
 
    Serial.print("Temperature: "); 
    Serial.print(temperatureCelsius); 
    Serial.println(" °C"); 
 
    // Check if temperature is abnormal 
    if (temperatureCelsius > temperatureThreshold) { 
      Serial.println("Abnormal Temperature"); 
      vTaskPrioritySet(locationTaskHandle, 5); // Set GPS task to 
highest priority 
    } 
    vTaskDelay(1000 / portTICK_PERIOD_MS); // Delay 1 second 
  } 
} 
 
// Task to read gas sensor 
void gasSensorTask(void *pvParameters) { 
  (void) pvParameters; 
  for (;;) { 
    int analogValue = analogRead(digitalPin);       // Read analog pin 
value 
    Serial.print("Analog Pin Value: "); 
    Serial.println(analogValue); 
 
    // Check if gas is dangerous 
    if (analogValue > gasThreshold) { 
6 
 
      Serial.println("Dangerous Gas Detected!"); 
      vTaskPrioritySet(locationTaskHandle, 5); // Set GPS task to 
highest priority 
    } 
    vTaskDelay(1000 / portTICK_PERIOD_MS); // Delay 1 second 
  } 
}
