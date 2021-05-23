# MQueue
Named message queue in C++ for Linux/Unix/Mac

# How To Include Into A Project
Simply include these two files into your project folder and in your C++ code you write

```
#include "mqueue.hpp"
```
and then compilation with linkage to pthread

```
g++ example.cpp -pthread
```
