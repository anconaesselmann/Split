// IntLinkedList implementation file
// Created by Axel Esselmann on Oct 5th 2011
// Last edited: Oct 13th 2011

#include <iostream>
#include "integer.h"
//#include "integerlinkedlist.h"
/*
namespace IntLinkedListAnconaEsselmann {
    using namespace LinkedListAnconaEsselmann;
    using namespace IntegerAnconaEsselmann;
    //\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
    /// ACCESSOR FUNKTIONS /////////////////////////////////////////////////
    Node<Integer>* IntLinkedList::getCursor() {
        return cursor;
    }
    
    //\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
    /// MUTATOR FUNKTIONS //////////////////////////////////////////////////
    void IntLinkedList::Insert(int i) {
        Node<Integer> *newNode;
        newNode = createNode();
        newNode->item->Int = i;
        LinkedList::Insert(newNode);
    }
    void IntLinkedList::InsertFront(int i) {
        Node<Integer> *newNode;
        newNode = createNode();
        newNode->item->Int = i;
        LinkedList::InsertFront(newNode);
    }
    void IntLinkedList::insertBefore(Node<Integer> *X, int i) {
        Node<Integer> *newNode;
        newNode = createNode();
        newNode->item->Int = i;
        LinkedList::insertBefore(X, newNode);
    }
    void IntLinkedList::insertAfter(Node<Integer> *X, int i) {
        Node<Integer> *newNode;
        newNode = createNode();
        newNode->item->Int = i;
        LinkedList::insertAfter(X, newNode);
    }
    void IntLinkedList::setCursor(Node<Integer> *Cursor) {
        cursor = Cursor;
    }
    void IntLinkedList::setCursor(int position) {
        cursor = getItem(position);
    }
    
    //\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
    /// OVERLOADED OPERATORS ///////////////////////////////////////////////
    std::ostream &operator <<(std::ostream &outs, const IntLinkedList &ll) {
        ll.printList(outs);
        return outs;
    }
    IntLinkedList& operator ++(IntLinkedList &list) {
        Node<Integer> *next;
        next = list.cursor;
        if (next != NULL) {
            next = list.getNext(list.cursor);
        }
        list.cursor = next;
        return list;
    }
    IntLinkedList& operator --(IntLinkedList &list) {
        Node<Integer> *next;
        next = list.cursor;
        if (next != NULL) {
            next = list.getPrev(list.cursor);
        }
        list.cursor = next;
        return list;
    }
    IntLinkedList operator +(const IntLinkedList &list1, const IntLinkedList &list2) {
        return add(list1.getHead(), list2.getHead());
    }
    void operator +=(IntLinkedList &list1, const IntLinkedList &list2) {
        list1.append(list2);
    }
    
    //\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\    
    /// OTHER FUNKTIONS ////////////////////////////////////////////////////
    void IntLinkedList::printList(std::ostream &outs) const {
        Node<Integer> **NodePtrAr;
        int ls = listSize();
        NodePtrAr = new Node<Integer>*[ls];
        NodePtrAr[0] = getHead();
        for (int i = 1; i < ls; i++) {
            NodePtrAr[i] = NodePtrAr[i-1]->next;
        }
        for (int i = ls -1; i >= 0; i--) {
            if (cursor == NodePtrAr[i]) {
                outs << "[";
            }
            outs << NodePtrAr[i]->item->Int;
            if (cursor == NodePtrAr[i]) {
                outs << "]";
            }
            outs  << " ";
        }
        delete [] NodePtrAr;
    }
    void IntLinkedList::printListBackToFront(std::ostream &outs) const {
        Node<Integer> *nextPtr = getHead();
        while (nextPtr != NULL) {
            outs << nextPtr->item->Int << ", ";
            nextPtr = nextPtr->next;
        }
    }
    void IntLinkedList::sort(int AscendDecend) {
        int asc = 1, dec = 0;
        if (AscendDecend < 0) {
            asc = 0;
            dec = 1;
        }
        bool makeSwap = true;
        int ls = listSize(),lastSortMade = ls - 1, sorted = lastSortMade;
        while (makeSwap) {
            makeSwap = false;
            for (int i = 0; i < sorted; i++) {
                if ( (getItem(i + dec))->item->Int > (getItem(i + asc))->item->Int)  {
                    swapNodes((getItem(i + dec)), (getItem(i + asc)));
                    makeSwap = true;
                    lastSortMade = i;
                }
            }
            sorted = lastSortMade;
        }
    }
    void IntLinkedList::sort() {
        sort(1);
    }
    Node<Integer> *IntLinkedList::search(int pos, int searchInt) const {
        Node<Integer> *returnItem = NULL;
        if (pos < 0) { // for negative positnions pos will be 0
            pos = 0;
        }
        if (pos < listSize() && (pos >= 0) ) {
            Node<Integer> *p = getItem(pos-1), *next = getHead();
            while ( (next != NULL) && (next != p) ) {
                if (next->item->Int == searchInt) {
                    returnItem = next;
                }
                next = next->next;
            }
        }
        return returnItem;
    }
    
    //\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
    /// PRIVATE ////////////////////////////////////////////////////////////////
    
    //\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
    /// MANIPULATING MULTIPLE LINKEDLISTS //////////////////////////////////////
    Node<Integer> *IntLinkedList::createNode() const {
        Node<Integer> *newNode = new Node<Integer>;
        Integer *newItem = new Integer;
        newItem->Int = 0;
        newNode->item = newItem;
        newNode->next = NULL;
        
        return newNode;
    }
    Node<Integer> *merge(IntLinkedList &list1, IntLinkedList &list2) {
        list1.sort();
        list2.sort();
        Node<Integer> *newHead = NULL, *next1 = list1.getHead(), *next2 = list2.getHead(), *temp;
        
        bool done = false;
        while (!done) {
            
            done = true;
            if (next1 != NULL) {
                if ( (next2 == NULL) || (next1->item->Int >= next2->item->Int) ) {
                    temp = next1->next;
                    next1->next = newHead;
                    newHead = next1;
                    next1 = temp;
                    done = false;
                }
            }
            if (next2 != NULL) {
                if ( (next1 == NULL) || (next2->item->Int >= next1->item->Int) ) {
                    temp = next2->next;
                    next2->next = newHead;
                    newHead = next2;
                    next2 = temp;
                    done = false;
                }
            }
        }
        list1.setHead(NULL);
        list2.setHead(NULL);
        return reverse(newHead);
    }
}*/