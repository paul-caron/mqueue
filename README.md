# MQueue
Named message queue in C++ for Linux/Unix/Mac for inter process communication (IPC).

# How To Include Into A Project
Simply include these two files into your project folder and in your C++ code you write

```
#include "mqueue.hpp"
```
and then compile with linkage to pthread (because of semaphore.h)

```
g++ example.cpp -pthread
```

# How To Use
The message queue needs a pathname for initialization, which will become a named shared memory space. This shared memory space will be persistent after a program is finished, but not persistent across reboot. If the shared memory space needs be unlinked, this will need to be done manually on your end.
Initialization must also include the type of messages (T) and the maximum number of messages that the queue can hold (N).

Besides that, the queue is simple and easy to operate. Push things in, pop things out, check if empty prior poping things out. Pushing and poping will lock and unlock a named semaphore (POSIX, semaphore.h) to enable only one process at a time for modifications on the queue.

The type of messages (T) can be integers, chars, or structs of a fixed size and containing no pointers to a process local memory (like dont point something that wont be seen from other processes).

A struct type for messages can be like

```
struct msg{
    char data[20];
}
```

## Initialization
```
MQueue<T,N> mq{"/mqshmem"};
```

## Push
```
mq.push(message);
```

## Pop
```
auto message = mq.pop();
```

## Empty
```
bool is_empty = mq.empty();
```


