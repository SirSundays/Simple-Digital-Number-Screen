# Simple digital number screen

This project is ment to give a base for further development of a simple screen that just shows a number. This can be used to show customers which one is next. It does not rely on any other third-party services. 

## Idea

A screen hangs somewhere prominent in a room. It has some sort of small computer attached running software to drive the display. A worker has a small controller that connects to the display (or rather the computer). With the controller he can control the number displayed.

## Solution

### Screen

I choose a 27 inch 1080p monitor that was under 200€. The only things really from interest where the size and good viewing angles.

### Computer

As a computer I choose the (now new) Raspberry Pi Zero 2. It definitly has enough horse power to run a little application to display numbers. 
It also runs the [RaspAP](https://raspap.com/ "RaspAP") software. Which makes the Raspberry Pi a small router. It is a bit overkill but works flawlessly. It just creates a WiFi Hotspot for the controller to connect to. So it is independend from other hardware.

### Number display software

I choose to write my own little software for that. More information can be found here:
[Link to the Readme](http://github.com "Link to the Readme")
The software is autostarted by the Raspberry. This article by Lucas Vogel helped with some best practices:
https://lucas-vogel.de/blog/perfect-electron/

### Controller

The controller consist of a ESP8266 with battery, a rotary encoder and a small display. All together in a 3d-printed housing. More information can be found here:
[Link to the Readme](http://github.com "Link to the Readme")

## Background

This project was a short 2 day project for me. My professor got some money for this a couple of years ago but no one every started this small project. I had some flexible time now and then so I just started working on it.  I liked to use skills of every tech area, this is really a Full Stack Project:
- Frontend Programming (JavaScript / HTML)
- Server Programming (Node.js)
- Server Administration (Autostart + RaspAP)
- Embedded Programming (ESP8266 / C++)
- Electronic Design (Yeah just attach some components directly to the Feather)
- CAD (Maybe just a little Box but hey atleast something)
