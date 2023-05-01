# Digital clock and Stopwatch

- Developing digital clock and stopwatch system, where user can choose which program, whether digital clock or the stopwatch, to dispaly on the multiplexed seven segment with single press on the push button.
- For digital clock program user has the choice to change the clock using keypad, if user press `=` then the clock remains as it is without any change. 
- For stopwatch program user has three options:
> 1. pause the stopwatch.
> 2. resume the stopwatch.
> 3. reset the stopwatch.


Mainly there are three layers, which are:
- Application Layer contains: Application.
- Hardware Abstraction Layer contains: Keypad, Multiplexed Seven-Segement.
- Micro-controller Abstraction Layer contains: GPIO, Timers, and Interrupt modules.

> - Project developed using MPLAP X IDE and simulated on Proteus.
> - Micro-controller: PIC18F4620.