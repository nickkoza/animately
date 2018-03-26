#ifndef RINGBUFFER_H_
#define RINGBUFFER_H_


template <class T, int LENGTH> class RingBuffer
{
private:
    int headIndex;
    int count;
    T *contents[LENGTH];

public:
    RingBuffer() {
        headIndex = 0;
        count = 0;
        memset(contents, 0, sizeof(T *) * LENGTH);
    }

    void add(T *entry) {
        if (count >= LENGTH) {
            ERROR(INVALID_INDEX)
            return;
        }

        contents[(headIndex + count) % LENGTH] = entry;
        count++;
    }

    T *get(int index) {
        if (index > count + 1 || index < 0)
        {
            ERROR(INVALID_INDEX);
            return NULL;
        }
        
        return contents[(headIndex + index) % LENGTH];
    }

    T *remove() {
        if (count <= 0) {
            ERROR(INVALID_INDEX)
            return NULL;
        }
        
        T *returnVal = contents[headIndex];
        headIndex = (headIndex + 1) % LENGTH;
        count--;
        return returnVal;
    }

    int size() {
        return count;
    }

    boolean isEmpty() {
        return count == 0;
    }

    boolean isNotEmpty() {
        return !isEmpty();
    }
};

#endif /* RINGBUFFER_H_ */