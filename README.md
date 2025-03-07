# Program-PIC16F722-Using-Arduino-Nano
How to Program the PIC16F722 Using Arduino Nano (CH340C)

<img align="right" width="35%" src="https://github.com/user-attachments/assets/b5362f43-7eec-449f-9652-5d813f59a7e1">

## **Step 1: Understanding the Limitations**
The **PIC16F722** is a PIC microcontroller and **cannot** be programmed directly using the Arduino IDE (which is designed for AVR and ARM-based microcontrollers like the ATmega328 on the Arduino Nano). However, you can use the Arduino Nano as a **PIC programmer** to upload the compiled HEX file to the PIC16F722.

### **Possible Approaches:**
1. **Using an Arduino Nano as a PIC Programmer** (Bit-Bang Method)
2. **Using a Dedicated PIC Programmer** (like a PICkit 3 or 4)
3. **Using MPLAB X IDE and XC8 Compiler to Write the Code**  
   (Instead of Arduino IDE)

---

## **Step 2: Circuit Connections**
To **program** the PIC16F722 using an **Arduino Nano**, you need to connect the **In-Circuit Serial Programming (ICSP)** pins.

### **PIC16F722 to Arduino Nano Wiring (ICSP Mode)**

| **PIC16F722 Pin** | **Function**  | **Arduino Nano Pin** |
|------------------|--------------|--------------------|
| Pin 1 (MCLR)     | VPP (Programming) | D8 (with 10K pull-up to 5V) |
| Pin 14 (VDD)     | Power (5V)        | 5V |
| Pin 5 (VSS)      | Ground            | GND |
| Pin 6 (PGC)      | Clock             | D9 |
| Pin 7 (PGD)      | Data              | D10 |
| Pin 21 (RB0)	   | LED 1 Output	     |	Cathode to GND, Anode via 330Ω resistor to RB0 |
| Pin 27 (ICSPDAT) | Data (Alternative) | D10 |
| Pin 28 (ICSPCLK) | Clock (Alternative) | D9 |

💡 **Note:** Some PIC microcontrollers require **12V on MCLR** for high-voltage programming. If this is the case, you might need an external 12V circuit.

---

<p float="center">
  <img src="https://github.com/user-attachments/assets/4d670c0d-3b12-4c24-a722-882d8daeb54f" width="45%" />
  <img src="https://github.com/user-attachments/assets/0bd14dbe-8c92-4514-bdd6-c3a15b973d3e" width="45%" />
</p>

## **Step 3: Writing the LED Blink Code**
Since the **Arduino IDE does not support PIC**, you need to write the code in **MPLAB X IDE** using the **XC8 Compiler**.

### **LED Blink Code (MPLAB X - XC8 Compiler)**
```c
#include <xc.h>

// Configuration Bits (Adjust for Your Setup)
#pragma config FOSC = INTRCIO  // Internal Oscillator
#pragma config WDTE = OFF      // Watchdog Timer Disable
#pragma config PWRTE = OFF     // Power-up Timer Disable
#pragma config MCLRE = ON      // MCLR Enable
#pragma config CP = OFF        // Code Protection Off
#pragma config BOREN = OFF     // Brown-out Reset Disable

#define _XTAL_FREQ 4000000  // 4MHz Internal Oscillator

void main() {
    TRISB0 = 0;  // Set RB0 as output (LED pin)
    
    while(1) {
        RB0 = 1;  // Turn LED ON
        __delay_ms(500);
        RB0 = 0;  // Turn LED OFF
        __delay_ms(500);
    }
}
```

### **Step 4: Compiling & Generating HEX File**

[![Screenshot (157)](https://github.com/user-attachments/assets/1fdc313c-4993-4ccc-b8ee-fdb113023f64)](https://www.microchip.com/en-us/tools-resources/develop/mplab-x-ide#tabs)
![Screenshot (159)](https://github.com/user-attachments/assets/ada24605-fda0-46f6-9d69-08b505551e7d)
![Screenshot (160)](https://github.com/user-attachments/assets/daa151a6-bacc-422e-80dc-c2df357bde0c)
![Screenshot (162)](https://github.com/user-attachments/assets/ef342cd8-faa4-4240-85d8-b867dfd36c2b)
![Screenshot (164)](https://github.com/user-attachments/assets/c37044c6-32d1-44cb-8536-e13afaafa004)
![Screenshot (166)](https://github.com/user-attachments/assets/3e4852a7-0366-430e-85a6-d22a0c5b2c6e)
![Screenshot (167)](https://github.com/user-attachments/assets/c8582962-7b54-446b-b6c5-1b1a7219a041)
![Screenshot (168)](https://github.com/user-attachments/assets/2a2b254b-8eec-4bfc-b182-ec7868d0e3dd)
![Screenshot (169)](https://github.com/user-attachments/assets/7e32caca-f677-4174-bfca-60ba6dcbfb6f)
![Screenshot (171)](https://github.com/user-attachments/assets/e6f2e0d0-4392-4fb3-a0b9-6af255cf0b01)
![Screenshot (172)](https://github.com/user-attachments/assets/6c414011-f499-496a-9ecc-3e642fee7b9e)
![Screenshot (174)](https://github.com/user-attachments/assets/32f19644-d1be-43a4-81bc-d6f23cee4e46)
![Screenshot (175)](https://github.com/user-attachments/assets/52c31189-c3ff-44e6-9190-10a51d2572d7)
![Screenshot (177)](https://github.com/user-attachments/assets/2804ac9b-e5dc-48a6-bd28-bd57bc17abd3)

1. Open **MPLAB X IDE** and create a new project for **PIC16F722**.
2. Select the **XC8 Compiler**.
3. Copy the **LED Blink Code** above into `main.c`.
4. Build the project (`Ctrl + Shift + B`).
5. Locate the generated `.hex` file in the `dist/default/production` folder.

---

## **Step 5: Uploading HEX File to PIC16F722 Using Arduino Nano**
Once you have the **HEX file**, you need to **upload it to the PIC16F722 using Arduino Nano**.

### **Methods to Upload HEX File**
1. **Use "Arduino as PIC Programmer" Sketch**  
   - Install `ArduinoPICProgrammer` firmware on Nano (Google "Arduino PIC Programmer GitHub").
   - Connect Nano to PC, upload the PIC programmer sketch.
   - Use `picprog` tool to upload the HEX file.

2. **Use a Dedicated PIC Programmer**  
   - If available, use a **PICkit 3/4** or an **USBASP PIC Programmer**.
   - Connect it to the ICSP pins and upload the HEX file via **MPLAB IPE**.

---

## **Conclusion**
- **The Arduino IDE does not support PIC16F722.**  
- **You must write code in MPLAB X with XC8 Compiler.**  
- **Use Arduino Nano as a PIC Programmer to upload the HEX file.**  
- **For an easier approach, use a dedicated PICkit programmer.**
