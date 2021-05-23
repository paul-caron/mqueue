/*
Copyright: Paul Caron
Date: May 22, 2021
*/

template <class T, int N>
MQueue<T,N>::MQueue(const char * pathname){
    auto fd = shm_open(pathname, O_CREAT|O_EXCL|O_RDWR, 0644);
    if(fd < 0){
        if(errno == EEXIST){
            perror("queue file exists: ");
            fd = shm_open(pathname, O_RDWR, 0644);
        }else{
            perror("shm_open error: ");
            exit(-1);
        }
    }
    else {
        ftruncate(fd, 4096);
        state->size=0;
        state->front=0;
        state->back=0;
    }
    state = (store*)mmap(0,sizeof(store),PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);
    close(fd);
    std::string semName = pathname;
    semName = std::string("/sem.")+semName;
    state->mutex = sem_open(semName.c_str(), O_CREAT|O_EXCL|O_RDWR, 0644, 1);
    if(state->mutex == SEM_FAILED){
        if(errno == EEXIST){
            perror("mutex file already exists: ");
            state->mutex = sem_open(semName.c_str(), O_CREAT);
        }else{
            perror("sem_open error: ");
            exit(-1);
        }
    }
}

template <class T, int N>
MQueue<T,N>::~MQueue(){
    sem_close(state->mutex);
    munmap(state, sizeof(store));
}

template <class T, int N>
void MQueue<T,N>::push(T element){
    sem_wait(state->mutex);
    (state->container.at(state->back++)) = element;
    state->size++;
    state->back%=N;
    sem_post(state->mutex);
}

template <class T, int N>
T MQueue<T,N>::pop(){
    sem_wait(state->mutex);
    T value{}
    if(state->size<=0) return value; //simply returns a default value for message type if queue is empty.
    value = (state->container.at(state->front++));
    state->size--;
    state->front%=N;
    sem_post(state->mutex);
    return value;
}

template <class T, int N>
bool MQueue<T,N>::empty(){
    return state->size == 0;
}
