Morse Code Interface for VBand
==============================

Introduction
---------------

This interface used the same hardware as the USB/HID Interface (The Gadget) and the cw_lcwo_pcw_interface.
  
Related Websites
---------------

- [For STL files and SeeeduinoXIAO](https://hackaday.io/project/184702-morse-code-usbhid-interface-the-gadet)
- [VBand](https://hamradio.solutions/vband/)
- [Seeeduino](https://wiki.seeedstudio.com/Seeed_Arduino_Boards/)

Initial Setup and Key Detection
-------------------------------

During the initial setup, the program waits for an input signal. It then determines whether to operate as a straight key or paddle based on your input:

    For straight key mode: Press and hold down the single key.
    For paddle mode: Press the right paddle.

The interface will automatically configure itself based on which input it detects first.
  
Building Interface and STL file
-------------------------------

![image](https://github.com/user-attachments/assets/cddb993a-dabf-4d2f-94d4-71d31f3f7a09)

The STL files for the 3d printed Seeeduino case, you will found on morse-code-usbhid-interface-the-gadet

![image](https://github.com/user-attachments/assets/9772ca79-4dc4-4013-a776-0f0fd51553f1)


For this project pin 6, 7  and ground is used, so building this project you can use also the next software

- [morse-code-usbhid-interface-the-gadet](https://hackaday.io/project/184702-morse-code-usbhid-interface-the-gadet)
- [cw_lcwo_pcw_interface](https://github.com/pe1hvh/cw_lcwo_pcw_interface)


Notes and Warning
-----------------

When you use the Keyboard.print() or Keyboard.press() command, the Arduino board takes over your keyboard! Make sure you have control before you use the command.

73 [PE1HVH ](https://www.pe1hvh.nl)

