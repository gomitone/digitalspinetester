# digitalspinetester
Arrow digital spine tester powered by Arduino Nano compatible board.

The digital spine tester allows to weigh and calculate shaft spine.
It uses cheap components and it is made of few lines of code.
It uses well known libraries that are referenced in the code itself.
Also listed below.

The schema is in the dwg/dxf file but can be improved as also the overall design could be.

All the logic to obtain the main spine formula is reported in the excel file.
There is no comments but easy to understand.
The principle is to work on the opposite of the classic spine tester.
Usually (classic approach), we apply a weight of two pounds reading the shaft bending.
So the constant is the weight while the variable is the bending.
In the digital spine tester, the constant is the bending and the variable is the applied weight.

That's all...

The code and all the information are shared and freely usable for personal use and amusement.

Some commercial versions of the digital spine tester are available on the market.
If you need something more professional, I suggest to give to them a chance.
Even if this DIY version is cheap and precise. :-)

Please share your hints and, if possible, your version and improvements.

Credits:
Libraries referenced in the code:

OLED library for Oled
    Universal 8bit Graphics Library (https://github.com/olikraus/u8g2/)
HX711 library for load cell amplifier
    Bogde HX711 lib (https://github.com/bogde/HX711)
Button library 
    Mathertel OneButtonlib (https://github.com/mathertel/OneButton)