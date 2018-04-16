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

#ifndef LISTTEST_H_
#define LISTTEST_H_

#include "Core/List.h"

using namespace Animately;

List<int, 5> list;

void resetList() {
    list.clear();
    
    list.add(0);
    list.add(1);
    list.add(2);
    list.add(3);
    list.add(4);
}


test(basicStorage)
{
    resetList();

    assertEqual(list.size(), 5);
    for (int i = 0; i < 5; i++) {
        assertEqual(list.get(i), i);
    }
}

test(removeAndInsert)
{
    resetList();
    
    list.remove(2);
    
    assertEqual(list.size(), 4);
    
    list.add(5);

    assertEqual(list.size(), 5);
    assertEqual(list.get(0), 0);
    assertEqual(list.get(1), 1);
    assertEqual(list.get(2), 3);
    assertEqual(list.get(3), 4);
    assertEqual(list.get(4), 5);
}

test(clearing)
{
    resetList();

    assertEqual(list.size(), 5);
    assertFalse(list.isEmpty());
    assertTrue(list.isNotEmpty());
    
    list.clear();
    
    assertEqual(list.size(), 0);
    assertTrue(list.isEmpty());
    assertFalse(list.isNotEmpty());
}



#endif /* LISTTEST_H_ */