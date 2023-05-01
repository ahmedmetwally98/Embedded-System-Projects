# Simple Calculator

- Developing a simple calculator that calculate basic operations:
> 1. Addition.
> 2. Subtraction (large number - small number).
> 3. Multiplication.
> 4. Division.

- each number entered by user is displayed on LCD screen. 
when user enter `=` then the result of the entered operation will occur on the screen.
- The program handles some errors like (dividing by zero, entering invalid operation..).
- Push button is provided for preparing the screen to enter a new operation.


### Mainly there are three layers, which are:
- Application Layer contains: Application.
- Hardware Abstraction Layer contains: Keypad, LCD modules.
- Micro-controller Abstraction Layer contains: GPIO, and Interrupt modules.

> - Project developed using Eclipse IDE and simulated on Proteus.
> - Micro-controller: ATmega16.