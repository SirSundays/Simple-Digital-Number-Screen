const { app, BrowserWindow } = require('electron');
const path = require('path');

const createWindow = () => {
    const mainWindow = new BrowserWindow({
        width: 1920,
        height: 1080,
        frame: false,
        center: true,
        resizable: false,
        alwaysOnTop: true,
        webPreferences: {
            contextIsolation: true,
            preload: path.join(__dirname, 'preload.js'),
        }
    });

    mainWindow.loadFile('./browser/index.html');

    var displayNumber = 0;

    BrowserWindow.getFocusedWindow().webContents.send(
        "new-number",
        { displayNumber: displayNumber }
    );
}

app.whenReady().then(() => {
    createWindow();
});