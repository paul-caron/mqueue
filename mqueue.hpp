/*
Copyright: Paul Caron
Date: May 22, 2021
*/
#ifndef _MQUEUE_HPP_
#define _MQUEUE_HPP_

#include <semaphore.h>
#include <iostream>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>
#include <array>
#include <string>

template<class T, int N>
class MQueue{
    private:
    struct store{
        int size;
        int front;
        int back;
        sem_t * mutex;
        std::array <T, N> container; 
    };
    store * state;
    public:
    MQueue(const char * pathname);
    ~MQueue();
    void push(T element);
    T pop();
    bool empty();
};

#include "mqueue.tpp"
#endif

