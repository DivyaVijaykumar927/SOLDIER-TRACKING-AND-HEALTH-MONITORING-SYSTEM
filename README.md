# Soldier Tracking and Health Monitoring System  

## Introduction  
The **Soldier Tracking and Health Monitoring System** is an advanced solution that integrates **GPS tracking** and **biomedical sensors** with **RTOS (Real-Time Operating System)** for real-time monitoring of soldiers' health and location. The system ensures continuous tracking and provides immediate alerts when abnormal conditions, such as high heart rate, elevated temperature, or hazardous gas exposure, are detected.  

## Features  
- **Real-time health monitoring** (Heart Rate, Temperature, and Gas Levels)  
- **GPS-based location tracking** for real-time soldier positioning  
- **RTOS-based task scheduling** for efficient sensor data processing  
- **Automatic alerts and notifications** for critical conditions  
- **Simulation validation** using Proteus for performance testing  

## System Architecture  
### 1. **Heart Rate Monitoring**  
- Uses a **Pulse Sensor** connected to **Analog Pin A1**.  
- Continuously tracks heart rate in **beats per minute (BPM)**.  
- If BPM exceeds **200**, a buzzer is triggered and an alert is sent.  

### 2. **Location Tracking (GPS)**  
- Utilizes the **Neo 6M GPS Module** for real-time positioning.  
- Provides **latitude, longitude, and altitude** for soldier tracking.  
- Ensures navigation assistance for military operations.  

### 3. **Body Temperature Monitoring**  
- Uses the **LM35 Temperature Sensor** connected to **Analog Pin A0**.  
- Measures temperature in **degrees Celsius (°C)**.  
- If the temperature exceeds **40°C**, GPS tracking is prioritized for rapid response.  

### 4. **Gas Sensor Monitoring**  
- Uses the **MQ-5 Gas Sensor** connected to **Digital Pin 5**.  
- Detects **harmful gas concentration levels** in the environment.  
- If unsafe gas levels are detected, the **GPS task priority is elevated** for evacuation assistance.  
