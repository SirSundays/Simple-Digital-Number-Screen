const { contextBridge, ipcRenderer } = require("electron");

contextBridge.exposeInMainWorld(
    "api", {
    receive: (channel, func) => {
        let validChannels = ["new-number"];
        if (validChannels.includes(channel)) {
            ipcRenderer.on(channel, (event, ...args) => func(...args));
        }
    }
}
);