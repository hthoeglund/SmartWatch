# Smartwatch
## Description
This project contains a rudimentary smart device with password protection and multiple apps. Smart devices are some of the most common, sought-after tools in the world, and they are used for everything from administrative tasks to playing games. As such, they can provide incredible insight into the hardware and software protocols used in modern global technology.

## Design and Implementation
### Hardware
A SparkFun Micro OLED Breakout (LCD-22495) was used to display vital information for the entirety of the system’s life cycle, including a password protection screen, home screen, and various app screens. Additionally, a SparkFun Qwiic Joystick (COM-15168) was selected for app navigation, a SparkFun Qwiic 12-Button Keypad (COM-15290), standard buttons, and a potentiometer were added for user input, and LEDs were added as another output option. All such components were connected to the AVR-BLE development board, which contains an ATmega3208 microcontroller. This resulted in the following hardware diagram:

![Smartwatch Hardware Diagram](https://github.com/hthoeglund/SmartWatch/blob/main/Smartwatch%20Hardware%20Diagram.png)

As depicted in the diagram, the OLED display, joystick, and keypad all utilized a system called QWIIC; QWIIC uses 4-pin wires to connect hardware components to breadboards, at which point the components connect to a microcontroller through I2C. As such, each component was connected to a QWIIC Breadboard Jumper Cable (PRT-179) which was then connected to ground (through the black wire), the microcontroller’s 3.3V power supply (through the red wire), SDA (through the blue wire), and SCL (through the yellow wire). For SDA and SCL, all components were connected to the same breadboard rail which was connected to pin A2 for SDA and A3 for SCL. Each LED was also connected to ground (through a 220 ohm resistor) and to a pin on the AVR-BLE board, with pin C0 being connected to the green LED, C1 being connected to the red LED, and D1 being connected to the yellow LED. Similarly, green, red, and yellow buttons were also connected to ground and to pins A4, A5, and A6 on the AVR-BLE board respectively. Finally, an additional blue button was connected to ground and to pin A7 to be used as a dedicated “home” button.

This hardware design was selected over alternatives (such as using a keyboard to type letters, using a second microcontroller for encryption, using buttons for navigation, or using an LCD) for a variety of reasons. Specifically, a potentiometer was used for letter selection rather than a full keyboard because keyboards are more expensive and would not fit with the condensed nature of a smart device. A joystick was also included (instead of using four buttons) specifically to give the project a more interactive, smooth user interface, and an OLED display was selected over an LCD to provide the complex, dynamic visuals fitting of a smart device.

### Software
#### Description
The project's software component is fairly complex; it consists of four primary applications that the user can seamlessly alternate between without losing any progress, since the device is meant to simulate a standard modern smart device experience. A general flow of device’s usage is as follows: the device first shows the user an “Enter PIN” screen (shown below), which prompts the user to enter a 4-digit password in order to proceed. The user is able to enter digits on the keypad, and they can press the red button to delete previously entered digits. They can then press the green button to enter their guess.

![Enter PIN Screen](https://github.com/hthoeglund/SmartWatch/blob/main/EnterPinScreen.png)

If the user enters an incorrect PIN, they are shown an animated “X” which indicates that the password was incorrect, and then they are given another chance to enter a PIN. If they enter the correct PIN, they proceed to the home screen shown below.

![Home Screen](https://github.com/hthoeglund/SmartWatch/blob/main/HomeScreen.png)

Once on the home screen, they can use the joystick, which moves the selection box left and right, to navigate between the four applications. There is also a real-time clock displayed in the bottom right corner, which updates in real time (starting at midnight upon first start up) and toggles the colon every 500 milliseconds.

The first application is a notes creator, which allows the user to store up to five strings consisting of up to 12 characters (letters, numbers, and punctuation). Specifically, the user can enter numbers on the keypad, and the ‘#’ key allows them to cycle through punctuation options including commas, apostrophes, colons, semicolons, periods, exclamation marks, question marks, and spaces. Additionally, they can press the ‘*’ button to select letters by turning a potentiometer, with any subsequent button presses saving their selected letter. They can also, once again, press the red button to delete previously typed characters. Upon pressing the green button, their note is saved and the cursor moves down to the next note, if another space is available. However, the user can also use the joystick to select specific notes, with the ability to edit (by pressing a valid key or button) and clear (by pressing the yellow button) individual notes. All notes are also stored in RAM, meaning that if the user presses the home button and then returns to the notes app later, their progress is saved. An example of the notes screen is shown below.

![Notes Screen](https://github.com/hthoeglund/SmartWatch/blob/main/NotesScreen.png)

The second application is a calculator, which allows the user to perform an infinite number of simple, two operand calculations. Similarly to the notes app, the user is able to type numbers on the keypad and use the ‘#’ button to cycle through special characters, with the characters being numerical operations (addition, subtraction, multiplication, and division) in this case. Given that the calculator only supports two operands, the user is not able to input more than one operator unless the operators can be validly interpreted as negation symbols, since the calculator does support negative numbers (and solutions). Once the equation is complete, the user can press the green button to calculate a solution, with equations automatically cycling off the screen as necessary. If the user chooses to enter an invalid equation (such as an equation that divides by zero or exceeds the size of long integers in C), the user is shown an X animation before being given the option to edit their equation. All calculator progress is also stored in RAM, meaning that if the user presses the home button and then returns to the calculator app later, their progress is saved. However, they may clear their calculation history by pressing the yellow button at any time. An example of the calculator screen is shown  below.

![Calculator Screen](https://github.com/hthoeglund/SmartWatch/blob/main/CalculatorScreen.png)

The third application is the game Simon, which flashes a sequence of colors on the LEDs and then prompts the user to repeat the sequence back through button presses. Upon opening the app, the display prompts the user with the text “ready?” and then starts the game when they press the green button. When the user is playing the game, the device incrementally increases the length of the provided sequence, disabling button inputs while flashing colors. It tracks their score (current highest input chain) on the display, updating (and flashing the next set of colors) whenever a chain is correctly inputted. If the user successfully reaches a score of 20, they are shown a win screen and the game is reset. Conversely, if they press an incorrect button, the game flashes an X animation before resetting to its “ready?” state. If the home button is pressed at any point, the game is concluded and reset. An example of the Simon screen is shown below.

![Simon Screen](https://github.com/hthoeglund/SmartWatch/blob/main/SimonScreen.png)

Finally, the fourth application is a reminders interface, which allows the user to store a reminder and receive a corresponding alert. First, the app prompts the user to type in a reminder of up to 13 characters using the same system that was used in the notes app. After typing their reminder and pressing the green button, they are then prompted with a choice of either “timer” or “clock” mode, which they can select using the joystick. In timer mode, the user is able to use the keypad to select a time in minutes and seconds, which will then count down to zero. In clock mode, the user is able to select a time of day in hours and minutes, which is then continuously compared to the time on the device’s real-time clock. After pressing the green button to start the reminder, the user is shown a check mark animation to indicate that the reminder was successfully set, and small text displaying “RUN” is displayed in the bottom right corner of the app screen. In timer mode, the display’s reminder clock also decreases in real time. When the timer reaches zero or the real-time clock reaches the specified time (depending on the mode), the user’s reminder is flashed on the bottom of the screen for five seconds, regardless of the user’s current app. If the user then returns to the reminder screen, they can see their reminder with the text “FIN” being displayed in the bottom right corner. They can then clear the reminder and restart the process by pressing the yellow button. An example of the reminders screen is shown below.

![Reminders Screen](https://github.com/hthoeglund/SmartWatch/blob/main/RemindersScreen.png)

#### Implementation
In order to implement this system, eight core files (aside from the six aforementioned feature files) were created, as listed below.
- Initialization: In the initialization file, SDA, SCL, and LED pins are set as output, I2C is initialized, and button pins are set as inputs with pull-up resistors enabled.
- OLED: The OLED file contains all of the display’s I2C and initialization processes alongside custom functions to write individual characters to the display.
- Joystick / Keypad: The joystick and keypad files contain all of the I2C and initialization processes for each respective hardware component, along with functions to resolve user inputs based on the current screen.
- Buttons: The buttons file contains an extensive interrupt service routine (ISR) which handles button presses at all points in the device’s life cycle. To do so, it determines which functions to call from the home, pin, notes, calculator, Simon, and reminder files.
- ADC: The ADC file has all of the ADC initialization code along with an ISR that determines which letter the user has selected on the potentiometer (when ADC is enabled).
- RTC: The RTC file has the initialization code for the RTC along with an extensive ISR that handles all of the timer functionality for the device’s built in RTC and simon and reminders apps.
- TCA: The TCA file has the initialization code for the TCA peripheral along with an ISR that checks for joystick and keypad inputs every 50 milliseconds.

As such, the entire project is interrupt-based and relies on user input through buttons (GPIO) and a potentiometer (ADC). It also relies heavily on timing peripherals (RTC and TCA) to synchronize app processes. 




