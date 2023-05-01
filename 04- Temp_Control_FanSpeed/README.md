# Temperature Control Fan 

- Developing a system where temperature sensor read the temperature in celsius degree, based on the temperature degree the micro-controller turn-off or turn-on the fan (motor) with led indicator. speed of the fan is determined based on the temperature degree.


### Mainly there are three layers, which are:
- Application Layer contains: Application.
- Hardware Abstraction Layer contains: Led, LCD, Motor, and LM35 modules.
- Micro-controller Abstraction Layer contains: GPIO, ADC, PWM and Interrupt modules.

> - Project developed using Eclipse IDE and simulated on Proteus.
> - Micro-controller: ATmega16.