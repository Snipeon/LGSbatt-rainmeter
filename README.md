# G933-rainmeter

TUTORIAL STILL INCOMPLETE, PLEASE BEAR WITH ME.

This is a skin to monitor the battery level of your Logitech device through Logitech Gaming Software, however, you would have to use Cheat Engine to pull the base address and pointer offsets of the battery value. Refer to the tutorial below.

Many thanks to Wyse for his G930 rainmeter skin. I took his skin and modified it so that it can work with LGS. 

Wyse: https://github.com/Wyse-/G930BatteryReader

Downloads:
Cheat Engine http://www.cheatengine.org/

Supported devices:
1. G933  (Currently the only confirmed supported device as I only have this. Anyone who wants to test/modify the program with their device, feel free to do so)

How to use:
1. Download and unzip LGSbatt.rar to your rainmeter folder.
2. Download Cheat Engine (Your antivirus may detect it as a virus, don't worry, Cheat Engine is not a virus)
3. Install and run Cheat Engine.
4. Grab the required information of your device battery value off Cheat Engine. For the specific device, please consult the device guide below.
5. Run Offsets.exe and key in the information you got off Cheat Engine.
6. Add autostart in the G933 folder to your startup programs list.
7. Load the skin on rainmeter.
8. Restart your computer and enjoy!

Device Guide:
1. G933 Artemis Spectrum
For the G933, the battery value is stored on LGS as an integer value from 0 to 100. Basically, what percent battery you see, it is stored exactly as that value. Here's how to grab the addres for that value with Cheat Engine.
  1. When you run Cheat Engine, you would see a window like this.
