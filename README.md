# Morse decoder

Hello world. As my journey of learning C++ continues, I deceided to play around a bit with hardware programming.

The project's idea is very simple, I wrote a small Arduino program to upload the light dependent voltage to the USB port. Since the signal/noise ratio is very good for transporting information, I came to the idea to use the sensor for decoding Morse code (https://de.wikipedia.org/wiki/Morsecode). The idea worked out quite well and here is the result :)
 
![](data/output.gif)

### Setup

The light dependent transistor (https://en.wikipedia.org/wiki/Photoresistor) is a passive component that decreases resistance with respect to receiving luminosity (light) on the component's sensitive surface. Arduino gave me a really nice tool to start with this component, the bread board setup is really easy, too.

![](data/setup.jpeg)

With some standard component and a bit tutorial of https://create.arduino.cc/projecthub/sumanbargavr/working-with-light-dependent-resistor-ldr-1ded4f and we are ready to go. 

### References

- [Huge thanks to https://github.com/gbmhunter for the amazing serial port reader. My implementation could interact with the port but yours is way superior](https://github.com/gbmhunter/CppLinuxSerial)
