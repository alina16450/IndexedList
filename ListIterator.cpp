#include "ListIterator.h"
#include "IndexedList.h"
#include <exception>

ListIterator::ListIterator(const IndexedList& list) : list(list) {
    current = list.first;
}

void ListIterator::first() {
    current = list.first;
}

void ListIterator::next() {
    if (!valid())
        throw "Invalid index";
    else {
        current = list.next[current];
    }
}

bool ListIterator::valid() const {
    return(current != -1);
}

TElem ListIterator::getCurrent() const {
    if (!valid())
        throw std::out_of_range("Position out of bounds");
    else {
        return list.elem[current];
    }
}
