# IgModelConverter

<!--![$(Game Title)](screenshots/screenshot000.png "$(Game Title)")-->

## Description

Converts Igz Model Files from the VV Alchemy Engine to gltf. 
Currently supports Crash Bandicoot™ N. Sane Trilogy.

## Generate Projects
For windows users, there are two batch files you can use depending on what compiler you are using. For linux users you can simply use a terminal.
Only do ONE of these options depending on your compiler and platform.
### Windows Users
Visual Studio users should run

    premake-VisualStudio.bat
	
This will generate a Visual Studio project.
	
### MinGW-w64 Users
Please make sure you have a recent version of MinGW-W64. The older versons from mingw.org will not work.
We recomend the W64Devkit. It has everything needed to build raylib. It can be downloaded from here https://github.com/skeeto/w64devkit/releases
Once you have MinGW-W64
Run the batch file.

    premake-mingw.bat
This will generate a makefile for you.
	
### Linux users
cd to the root folder and run

    ./premake5 gmake2
This will generate a makefile for you.
# macOS users
cd to the root folder and run

    ./premake5.osx gmake2
	
This will generate a makefile for you.
## Build
Only do ONE of these options depending on your compiler and platform.
### Windows Users
Double click the .sln file that was generated in the folder. From here you can use the project as normal.
	
### MinGW-w64 Users
Open your compiler terminal (w64devkit if you are using it), change to the root folder and type 

    make
	
### Linux/macOS users
Open your terminal, change to the root folder and type

    make
	
### Building for other OpenGL targets
If you need to build for a different OpenGL version than the default (OpenGL 3.3) you can specify an openGL version in your premake command line. Just modify the bat file or add the following to your command line
#### For OpenGL 1.1
    --graphics=opengl11
#### For OpenGL 2.1
    --graphics=opengl21
#### For OpenGL 4.3
    --graphics=opengl43

## License

This game sources are licensed under an unmodified zlib/libpng license, which is an OSI-certified, BSD-like license that allows static linking with closed source software. Check [LICENSE](LICENSE) for further details.

*Copyright (c) 2024 AdventureT (@AdventureT)*
