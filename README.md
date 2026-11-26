!\[Powered By: ](materials/PoweredByCore.png)
# CoreEngine

![C++20](https://img.shields.io/badge/Language-C%2B%2B20-blue.svg)
![OpenGL](https://img.shields.io/badge/API-OpenGL%203.3%20Core-green.svg)
![Platform](https://img.shields.io/badge/Platform-Windows%20x64-orange.svg)
![License](https://img.shields.io/badge/License-MIT-lightgrey.svg)

**CoreEngine** is a lightweight, custom 2D/3D game engine built from scratch in modern **C++20** and **OpenGL 3.3 Core Profile**. Designed from first principles, the engine focuses on clean architectural boundaries, zero-overhead abstractions, and direct hardware interaction.

---

[Demo Preview](docs/pong_demo.gif)

## Key Architecture & Features

- **Decoupled Engine-Game Architecture:**
  - `CoreEngine` compiles as an independent Static Library (`.lib`).
  - Game client projects (such as `Pong.exe`) interact strictly via the public `api/` layer.
- **Application Lifecycle & Event Hooks:**
  - Centralized `Application` orchestrator managing window creation, runtime state, and clean shutdown.
  - Frame-rate independent physics powered by high-precision Delta Time calculation (`dt`).
  - Decoupled game loop execution via functional callbacks (`std::function`).
- **Low-Level Graphics Pipeline:**
  - Modern OpenGL 3.3 Core Profile implementation.
  - Dedicated dynamic quad rendering pipeline utilizing hardware Vertex Buffer Objects (VBO) and static Element Buffer Objects (EBO).
  - Custom **GPU State Caching** mechanism eliminating redundant driver state transitions (`glBindTexture`, `glUseProgram`, `glBindVertexArray`).
- **Hardware-Agnostic Input System:**
  - Strongly typed keyboard abstraction (`InputKeys.h` / `enum class Key`).
  - Clean query interface (`Input::isPressed`) shielding gameplay code from underlying windowing and GLFW dependencies.
- **Thread-Safe Logging Subsystem:**
  - Multithreaded logger with categorized severity levels (`INFO`, `WARN`, `ERROR`, `FATAL`).

---

## Vertical Slice: Pong Demo

Included in the solution is a proof-of-concept **Pong** game powered entirely by `CoreEngine`.
- Smooth paddle interpolation via decoupled input polling and `deltaTime`.
- Axis-Aligned Bounding Box (AABB) collision checks and velocity reflection.
- (coming soon) Isolated game state management completely free of low-level graphics API calls.
---

## Tech Stack & Dependencies

All dependencies are strictly vetted for performance and permissive commercial licensing:
- **Language Standard:** C++20 (MSVC / Ninja x64)
- **Graphics API:** OpenGL 3.3 Core Profile
- **Windowing & Context:** [GLFW](https://www.glfw.org/) (Custom built from source via Ninja for x64) *(zlib/libpng License)*
- **OpenGL Loader:** [GLAD](https://glad.dav1d.de/) *(Public Domain / MIT)*
- **Image Loading:** [stb_image](https://github.com/nothings/stb) *(Public Domain / MIT)*

---

## Building from Source

### Prerequisites
- Windows 10 / 11 (64-bit)
- Visual Studio 2022 (with "Desktop development with C++" workload)
- MSVC compiler supporting `/std:c++20`

### Steps
1. Clone the repository:
   ```bash
   git clone https://github.com/<YourUsername>/CoreEngine.git
   cd CoreEngine
