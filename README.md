# framework2d
A small but usable 2D game framework for the desktop.

## Features:

### OpenGL:
Contains wrappers around basic OpenGL objects (vertex buffers, index buffers, 2D textures).
### Shaders:
Also has a shader class that supports loading vertex and fragment shaders from a string or a file.
### Platform Abstraction:
Furthermore, it contains platform-specific abstractions such as a combined window+openGLcontext object and an simple input system that handles keyboard and mouse. This is handled by SDL2 in the background.
### 2D Renderer:
Finally, the framework includes a small renderer that can handle individual files of sprites and spritesheets (loaded with stb_image). It also allows 3D rotations unlike other 2D renderers in libraries such as SDL or Allegro.
### GUI:
Framework is integrated with IMGUI. An object abstraction around IMGUI context creation is also included.
### Requirements:
- SDL2
- GLEW
## For the future:
### Todo:
- Add the game Camera (represents view matrix)
- Add functionality for rendering quads filled with just colors (quite simple)
- Revamp the trash project structure
- Add support for mouse input
- Unspaghetti the source code
### Possible features (if I ever needed them):
- Wrappers for OpenGL framebuffers and graphical use in the renderer (for cool postprocessing and such)
- Support for geometry shaders and batch rendering (unlikely as 2D games don't usually require such optimisation)
- Better integration with GLM (e.g. use glm::vec3 instead of three floats as parameter)
- Other forms of input (controller support is likely, touch support isn't since who likes mobile games)
- Evolve the project for 3D???
