GRAVITY ENGINE DEMO by Alexandre Bressane

Originally written in C++ using VS (windows)

Port made for Linux x64

Requires SDL2 Libs imported on Visual Studio (Windows)

Or installig SDL2 and SDL2-Image libs headers on your Linux distro (Eg: apt-get install libsdl2-dev libsdl2-image-dev)

To compile it and run on Linux you can use g++ linking either the package modules and SDL libraries like this:

" g++ Body.cpp GameManager.cpp GameObject.cpp Main.cpp MMath.cpp Scene.cpp Texture.cpp VMath.cpp Window.cpp World.cpp -o ge_demo -lSDL2 -lSDL2_image -fpermissive"

Then, check the binary permissions to execute (chmod) and run by "./ge_demo"

For Windows OS, just download the VS Project from "Windows" folder and install the SDL librarys in your project as described on "http://wiki.libsdl.org/Installation"

Feel free to use on your project.

Alexandre Bressane
