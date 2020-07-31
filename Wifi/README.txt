Programming ESP and see Serial monitor
 board mode = esp
OFF OFF OFF OFF ON ON ON NoUSE   to upload
press MCU reset                to be able to receive
upload sketch
OFF OFF OFF OFF ON ON OFF NoUSE  to see ESP serial monitor
!!!!! Important - disconnect any rx & tx connection


Programming Arduino and see Serial monitor
 board mode = arduino
OFF OFF ON ON OFF OFF OFF NoUSE   to upload
press MCU reset                to be able to receive
upload sketch





For serial communication between UNO and ESP 
1.) connect RXesp to TXuno and TXesp to RXuno
2.) SoftwareSerial mySerial(3, 2);   RX, TX 
    mySerial.begin(9600);
3.) set jumpers from 1 to 8 to  OFF OFF ON ON OFF OFF OFF OFF


Robodyn uno wifi datasheet  httpsrobotdyn.compubmedia0G-00005215==UNO+WiFi-R3-AT328-ESP8266-CH340GDOCSPINOUT==0G-00005215==UNO+WiFi-R3-AT328-ESP8266-CH340G.pdf
