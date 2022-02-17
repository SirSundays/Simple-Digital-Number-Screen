# Frontend & Server

This application uses Electron to setup a server and a frontend running in chromium at the same time. Works on nearly all platforms. (Of course also on the Raspberry Pi Zero 2)
The frontend and the server are communicating over Electrons internal process communication bus. The server also sets up 2 routes that can be accessed by other devices in the same network by calling the server over http. 

### Server
The Node-Server of Electron runs from the index.js. It includes all the windows configuration for the chromium browser and handles incoming http requests. These are the two available routes:
1. ` HTTP GET /` | Returns a JSON String. The currently displayed number can be found with the key `displayNumber`.
1.  `HTTP POST /:number` | Returns a JSON String. The currently displayed number can be found with the key `displayNumber`.  `:number` has to be replaced by the number that should be displayed. If it´s not a number, `0` will be displayed. If it is bigger then `10000` or smaller then `0`, also `0` will be displayed.

If the application crashes it will automatically restart. The Server is running on port `3000`.

### Frontend (browser folder)
The frontend shows the current number in a splitflap like display. For that it is using this library from Roosterfish called Fallblatt:
https://github.com/Roosterfish/fallblatt
The code can also be found in the `./browser/src` folder.
I removed all characters, excluding numbers and a colon.
In the index.js two options are present:
- `hideCursor` (default true)
- `activateTime` (default false)

`activateTime` is turned off by default because the used Raspberry Pi Zero 2 cannot keep track of the when it is turned of. This is because of the lack of a RTC. If you would connect it to a internet connected network it would get the actual time by calling an NTP Server. Because I´m using the Raspberry as a Hotspot I´m not able to utilize this.

### Getting Started

1.  Go into the `frontend+server`-folder
1.  Execute `npm i` to install all dependencies
1.  Execute `npm start` to get the application up and running

I decided to not build the actual application with Electron but rather just execute `npm start` on startup of the Raspberry. This makes the application much more platform independend. With a bigger application, building would make more sense.