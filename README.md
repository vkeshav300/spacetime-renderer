# Spacetime Renderer

A physics-based rendering software built on metal. \
[![CMake on a single platform](https://github.com/vkeshav300/spacetime-renderer/actions/workflows/cmake-single-platform.yml/badge.svg)](https://github.com/vkeshav300/spacetime-renderer/actions/workflows/cmake-single-platform.yml)
> [!IMPORTANT]\
> This project is built on Apple's Metal framework.
> That means to run this, you must have macOS, and your `xcode-select` path must be set to your XCode app developer directory (run `sudo xcode-select --switch /Applications/Xcode.app/Contents/Developer`).

## Tech stack

* Graphics engine: [Metal](https://developer.apple.com/metal/)
* Window management: [GLFW](https://www.glfw.org/)
* Image handling: [stb](https://github.com/nothings/stb)
