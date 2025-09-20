# DevOS - Development Oversight System

[![Build Status](https://img.shields.io/github/actions/workflow/status/<your-username>/DevOS/build.yml?branch=main)](https://github.com/<your-username>/DevOS/actions)
[![License](https://img.shields.io/github/license/<your-username>/DevOS)](LICENSE)
[![Python](https://img.shields.io/badge/Python-3.12-blue)](https://www.python.org/)
[![C++](https://img.shields.io/badge/C%2B%2B-20-lightgrey)](https://isocpp.org/)
[![Electron](https://img.shields.io/badge/Electron-36-blueviolet)](https://www.electronjs.org/)
[![React](https://img.shields.io/badge/React-18-blue)](https://reactjs.org/)

---

## 🚀 Overview

**DevOS** (Development Oversight System) is a **cross-platform, modular workspace for developers**.  
It integrates:

-   **High-performance C++ backend** for compute-intensive tasks
-   **Python layer (FastAPI)** for API and orchestration
-   **Electron + React frontend** for a sleek, native-feeling desktop app

DevOS is designed to **track, visualize, and optimize developer workflows**, acting as your personal development cockpit.

---

## 🎯 Features

-   [x] Real-time activity and productivity tracking
-   [x] Hybrid Efficiency Index (HEI) metric calculation
-   [x] Cross-platform support (Windows, Linux, macOS)
-   [x] Full modular architecture (C++ → Python → Electron/React)
-   [x] Secure Electron preload bridge for safe renderer communication
-   [ ] Future: GitHub integration for commits and repo metrics
-   [ ] Future: Plugin system for custom workflows

---

## 🗂️ Project Structure

```text
DevOS/
├─ core/                # C++ high-performance backend
├─ python_bindings/     # pybind11 bridge to Python
├─ api/                 # Python FastAPI layer
├─ frontend/            # Electron + React GUI
├─ demo/                # Quick demos / experiments
├─ build/               # Out-of-source build directory (ignored in git)
├─ tools/               # Utility scripts
├─ CMakeLists.txt       # Root CMake build config
├─ pyproject.toml       # Python project config
├─ package.json         # Node/Electron project config
└─ README.md            # This file
```
