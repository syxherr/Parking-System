# Parking-System-Arduino

The project was developed as a major assignment for the Microcontroller Systems course, demonstrating the practical application of microcontroller programming in real-world scenarios. This project is an Arduino-Based Parking Barrier System that utilizes RFID technology for secure authentication. The system is designed to grant or deny access based on the RFID card's unique identification (UID). When an authorized RFID card is scanned, the system triggers a servo motor to unlock the door and displays a welcome message on an LCD screen. Unauthorized cards are met with a denial message, and the door remains locked.

## Components:
- Arduino Uno
- RFID Module (MFRC522)
- I2C LCD Display (16x2)
- Servo Motor
- Jumper Wires

## Technology & Libraries:
- C++ for Arduino: The core programming language used in this project.
- SPI Library: Facilitates communication between the Arduino and the RFID module.
- MFRC522 Library: Manages RFID communication, enabling the Arduino to read and process RFID card data.
- LiquidCrystal_I2C Library: Controls the I2C LCD display, allowing for efficient message display with minimal wiring.

## How It Works:
![demo](https://github.com/user-attachments/assets/13be026e-31dd-4600-9565-ff6d6a030ceb)
1. Initialization:
- The RFID module is initialized and prepared to scan for cards.
- The LCD screen displays the message "Please Scan Your Card!".
- The Servo motor is positioned at 0 degrees (locked position).

2. Card Scanning:
- The system continuously checks for the presence of a new RFID card.
- If a card is detected, the system reads its unique identifier (UID) and compares it with a pre-authorized UID stored in the program.

3. Access Control:
- Authorized Card: If the scanned card's UID matches the stored UID, the Servo motor rotates to 90 degrees, unlocking the door. The LCD displays "Access Granted" along with a personalized message. After a short delay, the Servo returns to the locked position.
- Unauthorized Card: If the UID does not match, the system displays "Access Denied" on the LCD, and the Servo remains in the locked position.

4. Return to Initial State:
- After each attempt, the system resets to its initial state, ready for the next scan.
