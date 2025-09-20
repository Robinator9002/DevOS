// frontend/src/global.d.ts

export {}; // Ensures this file is a module

declare global {
    interface Window {
        devos: {
            ping: () => Promise<string>;
            callApi: (endpoint: string, data: any) => Promise<any>;
            log: (msg: string) => void;
        };
    }
}
