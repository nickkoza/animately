// MIT License
// 
// Copyright (c) 2018 Nicholas Koza
// 
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
// 
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#ifndef LIST_H_
#define LIST_H_

namespace Animately {
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