# SPOOKY

[![Status](https://img.shields.io/badge/status-stable-blue.svg)](../../releases/latest) [![License](https://img.shields.io/github/license/darsto/spooky.svg)](LICENSE.md)

Spooky is a C++14 **cross-platform** OpenGL 2.1/OpenGL ES 2.0 application/game engine.  
It features a common interface for writing application for different platforms while trying to give the developer as much maintainability as possible. Simply saying, it provides simple cross-platform support and a **low-level access** to the engine at the same time.

Linux build    | Windows build        | Android build
-------------- | -------------------- | -------------
[![CircleCI](https://img.shields.io/circleci/project/darsto/spooky/master.svg)](https://circleci.com/gh/darsto/spooky)  | - | -

# FEATURES

 - **Cross-platform**  
    Official support for Linux/Windows/Android. There are still more platforms to come.
 - **Highly separated logic & rendering**  
    Logic classes contain pure logic. Spooky features separate render classes and a mechanism to bind (one or more) logic class to a render instance. It is also possible to run just a *simulation* of the game.
 - **Internal window system**  
    One could compare it to Android's Activities, but in OpenGL. Spooky includes an easy mechanism to switch between such windows. As all rendering is separated from the logic, it is possible to preserve render context, making the whole system **very efficient**.
 - **Scalable graphics**  
    Since Spooky runs on both PCs and mobile devices, a special effort has been put into graphics scalability. Bleeding-free texture atlases with mipmapping are available.

# STRUCTURE

![License](http://i.imgur.com/k6Su23K.png)

Notes:
* Contexts are used to expose only a part of their parent's interface. They contain no logic, just data and setters.
* Window Render uses Window only to **get** and render the actual content.
* Window & Window Render are pure virtual classes, and their implementations are to be supplied by the *user*.

# INSTALLATION

See [INSTALL.md](INSTALL.md) for details.

Please note that this project is still under construction. For updates, follow my blog: https://darsto.github.io

# COPYRIGHT

Copyright 2015-2016 Dariusz Stojaczyk