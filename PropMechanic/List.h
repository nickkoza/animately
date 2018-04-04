#ifndef LIST_H_
#define LIST_H_

namespace PropMechanic {
    template <class T, unsigned int LENGTH> class List
    {
    private:
        unsigned int count;
        T contents[LENGTH];

    public:
        void clear() {
            count = 0;
            memset(contents, 0, sizeof(T) * LENGTH);
        }

        List() {
            clear();
        }

        void add(T entry) {
            if (count >= LENGTH) {
                ERROR(INVALID_INDEX)
                return;
            }

            contents[count] = entry;
            count++;
        }

        T get(unsigned int index) {
            if (index > count)
            {
                ERROR(INVALID_INDEX);
                return NULL;
            }
        
            return contents[index];
        }

        void remove(unsigned int index) {
            if (count <= 0) {
                ERROR(INVALID_INDEX)
                return;
            }

            if (index == count - 1) {
                // This is the end that we're removing -- simply trunc the list
                count--;
                return;
            }

            memmove(&contents[index], &contents[index + 1], sizeof(T) * (count - index - 1));
            count--;
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
}
#endif /* LIST_H_ */