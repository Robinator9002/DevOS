# api/main.py

import logging

from fastapi import FastAPI
from fastapi.middleware.cors import CORSMiddleware

# --- Logging Configuration ---
# Set up a consistent logging format for the entire application.
logging.basicConfig(
    level=logging.DEBUG,
    format="%(asctime)s - %(name)s - %(levelname)s - %(module)s.%(funcName)s:%(lineno)d - %(message)s",
)
logger = logging.getLogger(__name__)

# --- FastAPI Application Instance ---
# The main application object is created here.
app = FastAPI(
    title="DevOS - Development Oversight System API",
    description="DevOS — a programmable workspace for developers.",
    version="0.1.0-initial",  # Updated version to reflect changes
)
# --- Main Execution Block ---
# This block allows the application to be run directly for development.
if __name__ == "__main__":
    import uvicorn

    logger.info(f"Starting DevOS API server (v{app.version}) for development...")
    uvicorn.run("main:app", host="127.0.0.1", port=8000, reload=True, workers=1)
