#include <exception>
#pragma once
#include "IndexedList.h"
#include "ListIterator.h"

IndexedList::IndexedList() 
{//theta of cap
    cap = 10;
    elem = new TElem[cap];
    next = new int[cap];
    first = -1;
    for (int i = 0; i < cap; i++) {
        next[i] = i+1;
    }
    firstEmpty = 0;
    next[cap-1] = -1;
}

int IndexedList::size() const 
{//theta(n) where n is the number of elements in elem
    int s = 0;
    int current = first;
    while (current != -1) {
        current = next[current];
        s++;
    }
    return s;
}

bool IndexedList::isEmpty() const 
{//same as size
    return(size() == 0);
}

TElem IndexedList::getElement(int pos) const 
{//best case theta(1) if pos == 0; else theta(n)
    if (pos < 0 || pos >= size()) {
        throw std::out_of_range("Position out of bounds");
    }

    int current = first;
    int index = 0;

    while (current != -1 && index < pos) { //search for index, current traverses list of indexes from next[] until it gets to -1
        //if index equals pos, then the desired position is found.
        current = next[current];
        index++;
    }
    if (current == -1) //index not in list
        return NULL_TELEM;
    return elem[current];
}

TElem IndexedList::setElement(int pos, TElem e)
{//theta(n)
    if (pos < 0 || pos >= size()) {
        throw std::out_of_range("Position out of bounds");
    }
    int current = first;
    int empty = firstEmpty;
    int index = 0;
    int j = 0;
    int pre = -1;
    int emp = -1;

    while (current != -1 && index < pos) {
        pre = current;
        current = next[current];
        index++;
    }
    if (current == -1)
        throw std::out_of_range("Position not found"); 
    else if (index == pos){ // pos in list, already has elem. No changes to linking needed.
        TElem prev = elem[current];
        elem[current] = e;

        return prev;
    }
}

void IndexedList::addToEnd(TElem e) 
{//best case constant, when list is empty. theta(n) otherwise
    if (isEmpty()) { //list is empty, add to firstEmpty.
        first = firstEmpty;
        firstEmpty = next[firstEmpty];
        elem[first] = e;
        next[first] = -1;
        }
    else { //list not empty, iterate through list to find last occupied slot. Add elem right after, and update links for both lists.
        int current = first;
        int prev = -1;
        while (current != -1) {  //locates the end of the list.
            prev = current;
            current = next[current];
        }
        if (firstEmpty == -1) {
            int oldCap = cap;
            cap *= 2;
            TElem* newElems = new TElem[cap];
            int* newNext = new int[cap];
            for (int j = oldCap; j < cap - 1; j++) {
                newNext[j] = j + 1;
            }
            for (int i = 0; i < oldCap; i++) {
                newElems[i] = elem[i];
                newNext[i] = next[i];
            }
            newNext[cap - 1] = -1;
            delete[] elem;
            delete[] next;
            this->elem = newElems;
            this->next = newNext;
            this->firstEmpty = oldCap;
        }
        int index = firstEmpty;
        firstEmpty = next[firstEmpty];
        elem[index] = e;
        current = index;
        next[current] = -1;
        next[prev] = current;
        
    }
}

void IndexedList::addToPosition(int pos, TElem e) 
{//best case theta(1) when pos == 0; else O(n)
    if (pos < 0|| pos > size()-1) {
        throw std::out_of_range("Position out of bounds");
    }

    if (firstEmpty == -1) {
        int oldCap = cap;
        cap *= 2;
        TElem* newElems = new TElem[cap];
        int* newNext = new int[cap];
        for (int j = oldCap; j < cap - 1; j++) {
            newNext[j] = j + 1;
        }
        for (int i = 0; i < oldCap; i++) {
            newElems[i] = elem[i];
            newNext[i] = next[i];
        }
        newNext[cap - 1] = -1;
        delete[] elem;
        delete[] next;
        this->elem = newElems;
        this->next = newNext;
        this->firstEmpty = oldCap;
    }

    int current = first;
    int empty = firstEmpty;
    if (pos == 0) {
        elem[empty] = e;
        firstEmpty = next[firstEmpty];
        next[empty] = first;
        first = empty;
    }
    else {
        int index = 0;
        while (current != -1 && index < pos) {
            current = next[current];
            index++;

        }
        if (current != -1) {
            firstEmpty = next[firstEmpty];
            elem[empty] = e;
            next[empty] = next[current];
            next[current] = empty;
        }
        else {
            throw std::out_of_range("Invalid Index");
        }
    }

}

TElem IndexedList::remove(int pos) 
{ // O(n)
    if (isEmpty()) {
        throw std::out_of_range("Invalid position: List is empty");
    }
    if (pos < 0 || pos > size()-1) {
        throw std::out_of_range("Invalid position: Position out of range");
    }
    int current = first;
    int prev = -1;
    int currentPos = 0;
    int prevPos = -1;

    while (current != -1 && currentPos < pos) {
        prevPos = currentPos;
        prev = current;
        current = next[current];
        currentPos++;
    }
    if (current == -1) {
        throw std::out_of_range("Invalid position: Position not found");
    }
    TElem removedValue = elem[current];  // Save the value to be returned
    if (prev == -1) {
        first = next[current];
    }
    else {
        next[prev] = next[current];
    }
    next[current] = firstEmpty;
    firstEmpty = current;

    return removedValue;
}

int IndexedList::search(TElem e) const 
{//O(n)
    int current = first;
    int pos = 0;
    while (current != -1 && elem[current] != e) {
        current = next[current];
        pos++;
    }
    if (current != -1)
        return pos;
    else
        return -1;
}

ListIterator IndexedList::iterator() const 
{
    return ListIterator(*this);
}

IndexedList::~IndexedList() 
{
    delete[]elem;
    delete[]next;
}
