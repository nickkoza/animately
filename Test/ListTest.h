#ifndef LISTTEST_H_
#define LISTTEST_H_

#include "List.h"

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