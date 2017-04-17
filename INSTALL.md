# Installation

This document describes how to build & run Spooky examples.

Note that building has been only tested on a linux machine.

##### Table of Contents
[Linux builds](#linux-builds)  
[Windows builds](#windows-builds)  
[Android builds](#android-builds)  

## Linux builds
Linux builds depend on SDL2, GLEW and OpenGL 2.1. Provided examples also require [glm][1] and [SOIL2][2] libraries, SOIL2 is, however, added to Spooky as a git submodule.

On debian:
```
sudo apt-get install cmake libsdl2-dev libglew-dev libglm-dev
```

```
git clone https://github.com/darsto/spooky.git
cd spooky
git submodule init && git submodule update --remote --recursive
mkdir -p build/linux && cd build/linux
cmake ../.. && make
```
If everything goes well, executable files should appear in spooky/examples/**/bin directories.

## Windows builds
Library dependencies are the same as in linux builds. Spooky is known to compile Windows builds via [MXE][3].  
Follow the installation instructions on the [mxe website][4], then install the following mxe packages:
```
make gcc sdl2 glew cmake glm
```

The rest of the installation looks just like the linux one, but instead standard *cmake* we use *i686-w64-mingw32.static-cmake*.
```
git clone https://github.com/darsto/spooky.git
cd spooky
git submodule init && git submodule update --remote --recursive
mkdir -p build/win32 && cd build/win32
i686-w64-mingw32.static-cmake ../.. && make
```
.exe files should appear in spooky/examples/**/bin directories.

## Android builds
Android builds consist of 2 parts: C++ cores (shared libraries) and a Java wrapper. C++ core will need to be compiled multiple times for different CPU architectures.

First of all, install Android [NDK][5] & [SDK][6].  
C++ cores are known to build with a CMake [standalone toolchain][7].

The following four ABIs should cover most of the CPU architectures used by Android devices:
* armeabi (ARMv5, ARMv6)
* armeabi-v7a (ARMv7)
* x86
* mips (Ingenic CPUs, R2000+)

In the following instructions armeabi ABI will be used as an example.

After downloading all the development kits and the toolchain, download and install the following libraries inside Android environment:
* [glm][10] (it's header-only library, just copy files to the include dir)

These should be placed inside toolchain's *CMAKE_FIND_ROOT_PATH* (you might have to explicitly set this variable inside the previously downloaded toolchain)

Then begin with the Spooky compilation:
```
git clone https://github.com/darsto/spooky.git
cd spooky
git submodule init && git submodule update --remote --recursive
mkdir -p build/android && cd build/android
cmake -DCMAKE_TOOLCHAIN_FILE=/path/to/toolchain-android.cmake -DANDROID_ABI="armeabi" -DANDROID_NATIVE_API_LEVEL="android-9" -DCMAKE_BUILD_TYPE=Debug ../..
make
```
Shared library files should appear in *spooky/build/android/examples/*** directories.

Now get the Java wrapper:
```
cd /any/project/path
git clone -b android-wrapper --single-branch https://github.com/darsto/spooky.git spooky-android
```
Copy (or symlink) the just compiled c++ shared library into *spooky-android/app/src/main/jniLibs/armeabi/* (create any missing folders). If you've compiled multiple c++ cores for different CPU architectures, you should copy (or symlink) all of them.

Lastly, build the apk:
```
cd spooky-android
./gradlew assembleDev
```
It should appear in *spooky-android/app/build/outputs/apk/* directory

[1]: https://github.com/g-truc/glm/
[2]: https://github.com/darsto/SOIL2
[3]: http://mxe.cc/
[4]: http://mxe.cc/#tutorial
[5]: https://developer.android.com/ndk/downloads/index.html
[6]: https://developer.android.com/studio/index.html
[7]: https://github.com/taka-no-me/android-cmake
[8]: https://www.lua.org/download.html
[9]: http://luadist.org/
[10]: http://glm.g-truc.net/