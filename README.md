
# Razor - Game Engine




![App Logo](https://i.ibb.co/kgV6v2B/R.png)

Razor is an early-stage interactive application and rendering engine designed primarily for Windows. While the project is still in its infancy, nearly every aspect of the repository is being developed as a hands-on learning experience and out of personal interest. The repository can be found at GitHub.
## Recommended Development Environment

It is suggested to use Visual Studio 2022 for building Razor, as it is officially optimized for this setup. Note that Razor has not been extensively tested on other development environments, so focusing on a Windows build is recommended.

- ### Getting Started with Razor
1. Clone the Repository
To start, clone the repository by executing the following command: https://github.com/manishtomarleo21/Razor.

2. Updating Submodules
If you previously cloned the repository without the --recursive option, you can ensure the necessary submodules are included by running: git submodule update --init

- ### Configuring Dependencies
1. Running the GenerateProjects Script
After downloading and extracting the files, the GenerateProjects.bat script will automatically run. This script will generate a Visual Studio solution file, setting up the necessary configurations for the Razor project to be used in Visual Studio. 

## Overview

**Razor** is an early-stage 2D game engine to understand the fundamentals of game development and rendering techniques. Currently, it supports basic rendering of **quads, circles**, and **2D physics using Box2D**. It also includes a **view projection system** for camera control. While Razor is still in its early stages of development, it aims to provide an accessible and extensible platform for creating 2D games and interactive applications.

The engine is built with several modern C++ libraries and tools, offering a robust foundation for expanding into more complex features in the future.

## Features

- **2D Rendering**  
  Razor can render **quads**, **circles**, and basic shapes to form the visual foundation of your game world.

- **Box2D Physics**  
  The engine integrates **Box2D**, a popular physics library, to simulate realistic 2D physics behaviors such as collisions, gravity, and forces.

- **View Projection System**  
  Razor includes a camera system with a **view projection matrix**, allowing you to create dynamic scenes that can be zoomed in or out and panned across different coordinates.

- **Particle System**  
  A simple particle system is implemented to manage visual effects like explosions, fire, and more, as a small side feature.

## Technologies & Libraries Used

Razor is built using a combination of open-source libraries and tools that facilitate rendering, physics simulation, and game development. Below is a list of the key technologies and libraries currently used in the engine:

- **GLFW**  
  A cross-platform library for creating windows with OpenGL contexts and handling user input.

- **OpenGL**  
  A powerful graphics API used for rendering 2D and 3D objects.

- **Glad**  
  OpenGL loader to manage extensions and core functions required by the engine.

- **ImGui**  
  A bloat-free graphical user interface library for creating in-game tools, editors, and debugging interfaces.

- **GLM**  
  A math library for OpenGL, useful for managing transformations, matrices, and vectors.

- **STB Image**  
  A simple, single-header library for loading image files (e.g., textures) into the engine.

- **Box2D**  
  A physics library for simulating 2D rigid body dynamics, including collisions and forces.

- **Entt (Optional)**  
  A fast and lightweight entity-component-system (ECS) framework for handling game objects and their interactions.

- **YAML**  
  A human-readable data serialization format used for configuration files, settings, and scene data.

- **ImGuizmo**  
  A small tool for manipulating transformations in 3D or 2D, useful for creating in-game scene editors.

- **spdlog**  
  A fast and powerful logging library used to log debug messages, errors, and other information for development purposes.

- **Premake**  
  A build configuration tool that simplifies generating project files for different environments (e.g., Visual Studio).

