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

# How To Use
The message queue needs a pathname for initialization, which will become a named shared memory space. This shared memory space will be persistent after a program is finished, but not persistent across reboot. If the shared memory space needs be unlink, this will need to be done manually on your end.

## Initialization
```
MQueue<T,N> mq{"/mqshmem"};
```

