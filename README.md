# gl-sandbox
A repo to experiment with GPU tech and openGL functionalities

## Cloning

Make sure to clone the submodules with the project

```
git clone --recurse-submodules https://github.com/logandarby/gl-sandbox
```

## Running

Cmake is used to build and run the project. Make sure all commands are run in git bash.

### Ninja

If you have ninja installed, you can use the default cmake preset.

```bash
cmake --preset default
cd build
ninja
./CMakeTest.exe
```

### Makefiles

If you wish to use make instead, then run the following:

If you have ninja installed, you can use the default cmake preset.

```bash
cmake --preset makefile_debug
cd build
make
./CMakeTest.exe
```

## References

- [Learn OpenGL](https://learnopengl.com/Introduction)
- [The Cherno Game Engine Series](https://www.youtube.com/playlist?list=PLlrATfBNZ98dC-V-N3m0Go4deliWHPFwT)
- [The Cherno OpenGL Series](https://www.youtube.com/playlist?list=PLlrATfBNZ98foTJPJ_Ev03o2oq3-GGOS2)
  
