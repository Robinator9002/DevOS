// frontend/src/preload.js

import { contextBridge, ipcRenderer } from 'electron';

// Expose a limited API to the renderer
contextBridge.exposeInMainWorld('devos', {
    // Example: ping the main process
    ping: async () => {
        return await ipcRenderer.invoke('ping');
    },

    // Call Python backend (via FastAPI) or local C++ actions
    callApi: async (endpoint, data) => {
        const response = await fetch(`http://127.0.0.1:8000/${endpoint}`, {
            method: 'POST',
            headers: { 'Content-Type': 'application/json' },
            body: JSON.stringify(data),
        });
        return await response.json();
    },

    // Example: send a message to main process
    log: (msg) => ipcRenderer.send('log', msg),
});
