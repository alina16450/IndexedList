#pragma once
#include "IndexedList.h"


class ListIterator {

    friend class IndexedList;

private:
    const IndexedList& list;
    int current;

    ListIterator(const IndexedList& list);
public:
    void first();
    void next();
    bool valid() const;
    TElem getCurrent() const;

};
