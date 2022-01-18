const { app, BrowserWindow } = require('electron');
const path = require('path');
const express = require("express");

const server = express();
const PORT = 3000;

var displayNumber = 0;

const createWindow = () => {
    const mainWindow = new BrowserWindow({
        width: 1920,
        height: 1080,
        frame: false,
        center: true,
        resizable: false,
        alwaysOnTop: true,
        webPreferences: {
            nodeIntegration: false,
            contextIsolation: true,
            enableRemoteModule: false,
            preload: path.join(__dirname, "preload.js")
        }
    });

    mainWindow.loadFile('./browser/index.html');

    const printNumber = () => {
        mainWindow.webContents.send(
            "new-number",
            { displayNumber: displayNumber }
        );
    }

    mainWindow.webContents.once('did-finish-load', function () {
        mainWindow.webContents.send(
            "new-number",
            { displayNumber: displayNumber }
        );

        server.get("/", (req, res) => {
            res.send({ displayNumber: displayNumber });
        });

        server.post("/:number", (req, res) => {
            let newNumber = parseInt(req.params.number);
            if (!isNaN(newNumber) && newNumber < 10000 && newNumber >= 0) {
                displayNumber = newNumber;
                printNumber();
                res.send({ displayNumber: displayNumber });
            } else {
                displayNumber = 0;
                printNumber();
                res.send({ displayNumber: displayNumber });
            }
        });

        server.listen(PORT, () => {
            console.log(`Server is running on PORT: ${PORT}`);
        });
    });
};

app.whenReady().then(() => {
    createWindow();
});