# SPOOKY  

[![Status](https://img.shields.io/badge/status-unstable-orange.svg)](../../releases/latest)
[![License](https://img.shields.io/github/license/darsto/spooky.svg)](LICENSE.md)
[![CircleCI](https://img.shields.io/circleci/project/darsto/spooky/master.svg)](https://circleci.com/gh/darsto/spooky)

#### Please note that this project is outdated. Modern embedded hardware no longer requires reuploading any GPU memory. 

Spooky is a C++14 **cross-platform** OpenGL 2.1/OpenGL ES 2.0 application runtime.  
It features a unified interface for writing application for different platforms,
also giving the developer as much maintainability as possible.

Simply saying, it is the simplest possible cross-platform OpenGL runtime.

### But... why?

APIs of OpenGL 2.1 and OpenGL ES 2.0 don't differ that much.
One could even write software for both of them without any #ifdefs, but there's a catch.

The basic difference between OpenGL on desktops (OpenGL 2.1) and OpenGL on
mobile/embedded devices (OpenGL ES 2.0) lies in **OpenGL context**.
On mobile devices, every time you minimize and maximize your application, it loses
it's context. This results in **all GPU memory being purged**. The CPU memory, however, remains 
untouched. **Spooky** is designed to e.g. reupload all GPU memory when necessary.
There are also some other minor runtime features, all listed below.

# FEATURES

 - **Cross-platform**  
    Official support for Linux/Windows/Android. There are still more platforms to come.
 - **Flexibility**  
    Can be adopted to work with any application/game structure.
 - **Internal window system**  
    One could compare it to Android's Activities, but in OpenGL.
    Spooky includes an easy mechanism to switch between such windows.
    As all rendering can be separated from the logic, it is possible to preserve render data,
    making the whole system **very efficient**.
 - **Unified input handling**  
    A single user-provided piece of code can handle keyboard, mouse and touchscreen.
 - **File access**  
    Simple abstraction for accessing assets.
 - **Logging**  
    Status, warning, debug, and error logging is available.

# STRUCTURE

![Structure](http://i.imgur.com/k6Su23K.png)

A few notes:
* This runtime should be slightly modified by the programmer to fulfill project needs. It is possible, but discouraged to use it without any changes.
* Contexts are used to store Window-independent (persistent) data.
* Window & Window Render are pure virtual classes, and their implementations are to be supplied by the *user*.

# INSTALLATION

See [INSTALL.md](INSTALL.md) for details.

# COPYRIGHT

Copyright 2015-2017 Dariusz Stojaczyk