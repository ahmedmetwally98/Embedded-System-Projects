# Door Lock Security System

- Developing a system to unlock a door using a password.


### Project overview:
1. Human machine unit, based on ATmega16, is used to process the input from user and displaying on LCD. 
2. Processing and storing unit, based on ATmega16, is used to store a given password and check the correctness of the input password from the user.
3. If incorrect password is entered then the system gives alarm sound.
### Mainly there are three layers, which are:
- Application Layer contains: Application.
- Hardware Abstraction Layer contains: External EEPROM (24C16), Keypad, LCD, Motor, and Bazzer modules.
- Micro-controller Abstraction Layer contains: GPIO, Timers, UART, I2C and Interrupt modules.

> - Project developed using Eclipse IDE and simulated on Proteus.
> - Micro-controller: ATmega16.