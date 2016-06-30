// LinkedList implementation file
// Created by Axel Esselmann on Oct 5th 2011
// Last edited: Oct 14th 2011

#include <iostream>
#include "linkedlist.h"

namespace LinkedListAnconaEsselmann {
    
//\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
/// NODE ///////////////////////////////////////////////////////////////////
    template<class T>
    Node<T>::Node() {
        next = NULL;
        item = NULL;
    }
    template<class T>
    Node<T>::Node(const Node<T> &toBeCoppied) {
        next = toBeCoppied.next;
        item = toBeCoppied.item->copy();
    }
    template<class T>
    void Node<T>::operator =(const Node<T> &toBeCoppied) {
        next = toBeCoppied.next;
        item = toBeCoppied.item->copy();
    }
    template<class T>
    Node<T>::~Node() {
        delete item;
    }
    
    
//\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\   
/// D_POINTER //////////////////////////////////////////////////////////////
    struct LinkedList::D_Pointer {
        int createRandomNumber(int lower_bound, int upper_bound) const;
        // creates a random number between lower_bound and upper_bound
        template<class T>
        void append(Node<T> *append);
        // makes a copy of append and attaches it to head without copying head.
        template<class T>
        void reverse(Node<T> *(&head)) const;
        // reverses the linked list that head points to
        template<class T>
        Node<T> *copy(Node<T> *head) const;
        // copies the linked list that head points to and returns 
        // a pointer that points to the copied list
        template<class T>
        void Insert(Node<T> *&Head, Node<T> *item) const;
        // adds an element to the end of the list (behind the item that was 
        // addes last) changes head
        template<class T>
        Node<T> *createNode() const;
        // creates a node with all its variables initialized to zero or NULL
        template<class T>
        void join(Node<T> *(&head1), Node<T> *(&head2));
        // joins lists head1 and head2 without copying and returns list 1 after 
        // list 2 as head1. Head2 becomes NULL for security reasons, since for 
        // example sorting head1 would make head 2 useless, since it would point 
        // to some random object in the middle of the list;
        
        //\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
        /// VARIABLES AND CONSTANTS ////////////////////////////////////////////
        template<class T>
        T *head;
    };
    
//\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
/// PRIVATE ( D_POINTER FUNCTIONS ) ////////////////////////////////////////
    int LinkedList::D_Pointer::createRandomNumber(int lower_bound, int upper_bound) const {
        int temp, difference;
        
        if (upper_bound < lower_bound) {
            temp = lower_bound;
            lower_bound = upper_bound;
            upper_bound = temp;
        }
        difference = (upper_bound - lower_bound) + 1;
        return (rand() % difference + lower_bound);	
    }
    template<class T>
    void LinkedList::D_Pointer::append(Node<T> *append) {
        if (append != NULL) {
            Node<T> *temp = new Node<T>, *prev;
            temp = copy(append);
            Node<T> *next = temp; 
            
            while (next != NULL) {
                prev = next;
                next = next->next;
            }
            prev->next = head;
            
            head = temp;
        }
    }
    template<class T>
    void LinkedList::D_Pointer::reverse(Node<T> *(&head)) const {
        head = LinkedListAnconaEsselmann::reverse(head);
    }
    template<class T>
    Node<T> *LinkedList::D_Pointer::copy(Node<T> *Head) const {
        Node<T> *headCopy;
        Node<T> *next;
        
        headCopy = new Node<T>; // Noone needs to delete this, since we need this!
        headCopy = NULL;
        next = Head;
        while (next != NULL) {
            Node<T> *temp; // A copy of the node has to be made
            temp = createNode<T>();
            *temp = *next; /// test if this works!!!!
            
            Insert(headCopy, temp); // here each variable needs to be coppied, 
            // except the link to the next item
            next = next->next;
        }
        reverse(headCopy);
        return headCopy;
    }
    template<class T>
    void LinkedList::D_Pointer::Insert(Node<T> *&Head, Node<T> *item) const {
        item->next = Head;
        Head = item;
    }
    template<class T>
    Node<T> *LinkedList::D_Pointer::createNode() const {
        Node<T> *item;
        item = new Node<T>;
        item->next = NULL;
        item->item = 0;
        return item;
    }
    template<class T>
    void LinkedList::D_Pointer::join(Node<T> *(&head1), Node<T> *(&head2)) {
        Node<T> *prev;
        Node<T> *next = head2; 
        
        while (next != NULL) {
            prev = next;
            next = next->next;
        }
        prev->next = head1;
        
        head1 = head2;
        head2 = NULL;
    }
    
//\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
/// PUBLIC /////////////////////////////////////////////////////////////////

    //\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
    /// INITIALIZATION AND DESTRUCTION /////////////////////////////////////
    LinkedList::LinkedList() : privateData(new D_Pointer) {
        privateData->head = NULL;
    }
    template<class T>
    LinkedList::LinkedList(const LinkedList &list) : privateData(new D_Pointer( *(list.privateData)  )) { //copy constructor
        privateData->head = privateData->copy<T>(list.privateData->head);
    }
    template<class T>
    LinkedList::LinkedList(Node<T> *Head) : privateData(new D_Pointer){
        privateData->head = NULL;
        privateData->head = privateData->copy(Head);
    }
    LinkedList::~LinkedList() {
        //delAll();
        delete privateData;
    }
    template<class T>
    void LinkedList::operator =(LinkedList rightSide) {
        Node<T> *next, *insert;
        next = rightSide.getHead<T>();
        while (next != NULL) {
            insert = next;
            Insert(insert);
            next = next->next;
        }
        reverse<T>();
        std::swap(this->privateData, rightSide.privateData);
    }
    
    //\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
    /// MUTATOR FUNKTIONS //////////////////////////////////////////////////
    template<class T>
    void LinkedList::Insert(Node<T> *item) { 
        Node<T> *temp;
        temp = privateData->createNode<T>();
        *temp = *item;
        temp->next = privateData->head;
        privateData->head = temp;
    }
    template<class T>
    void LinkedList::InsertFront(Node<T> *item) {
        int ls = listSize<T>();
        if (ls != 0) {
            insertBefore(getItem<T>(0), item);
        } else Insert(item);
    }
    template<class T>
    void LinkedList::insertBefore(Node<T> *X, Node<T> *item) {
        if (listSize<T>() != 0) {
            Node<T> *temp;
            temp = privateData->createNode<T>();
            *temp = *item;
            temp->next = X->next;
            X->next = temp;
        } else Insert(item);
    }
    template<class T>
    void LinkedList::insertAfter(Node<T> *X, Node<T> *item) {
        Node<T> *temp;
        temp = privateData->createNode<T>();
        *temp = *item;
        int pos = getPos(X);
        int ls = listSize<T>();
        if (pos != ls-1) {
            Node<T> *prevPos = getItem<T>(pos +1);
            insertBefore(prevPos, temp);
        } else {
            Insert(temp);
        }
    }
    template<class T>
    void LinkedList::moveLeft(Node<T> *item) {
        if (getPos(item) > 0) {
            swapNodes(item, item->next);
        }
    }
    template<class T>
    void LinkedList::moveRight(Node<T> *item) {
        int ls = listSize<T>();
        if (getPos(item) < ls-1) {
            swapNodes(item, getNext(item));
        }
    }
    template<class T>
    void LinkedList::move(Node<T> *item, int moveBy) {
        if (moveBy < 0) {
            for (int i = 0; i < -moveBy; i++) {
                moveLeft(item);
            }
        }
        if (moveBy > 0) {
            for (int i = 0; i < moveBy; i++) {
                moveRight(item);
            }
        }
    }
    template<class T>
    void  LinkedList::uncouple(Node<T> *X) {
        int ls = listSize<T>();
        int pos = getPos(X);
        if (pos == 0) {
            if (ls > 1) {// without this, error when only one item is in the list
                (getNext(X))->next = NULL;
            } else privateData->head = NULL;
        } else if (pos == ls - 1) {
            privateData->head = (X)->next;
        } else {
            (getNext(X))->next = (X)->next;
        }
        X->next = NULL;
    }
    template<class T>
    Node<T> *LinkedList::uncouple(int pos) {
        int ls = listSize<T>();
        Node<T> *uncoupleItem = getItem<T>(pos);
        if (pos < ls) {
            uncouple(uncoupleItem);
        } else uncoupleItem = NULL;
        return uncoupleItem;
    }
    template<class T>
    void  LinkedList::del(Node<T> *X) {
        uncouple(X);
        delete X;
    }
    template<class T>
    void  LinkedList::del(int pos) {
        Node<T> *toDelete;
        toDelete = uncouple<T>(pos);
        if (toDelete != NULL) {
            delete toDelete;
        }
    }
    template<class T>
    void  LinkedList::delAll() {
        while (privateData->head != NULL) {
            del<T>(privateData->head);
        }
    }
    template<class T>
    Node<T> *LinkedList::setHead(Node<T> *newHead) {
        Node<T> *temp = privateData->head;
        privateData->head = newHead;
        return temp;
    }
    
    //\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
    /// ACCESSOR FUNKTIONS /////////////////////////////////////////////////
    template<class T>
    int   LinkedList::getPos(Node<T> *X) const {
        int ls = listSize<T>();
        int count = 0;
        bool inList = false;
        Node<T> *next;
        next = privateData->head;
        while ( (next != NULL) && (next != X) ) {
            next = next->next;
            if (next == X) {
                inList = true;
            }
            count++;
        }
        return ls - count - 1;
    }
    template<class T>
    Node<T> *LinkedList::getNext(Node<T> *X) const {
        // a prev variable would make this more efficient
        Node<T> *tempX = NULL, *next;
        next = privateData->head;
        while ( (next != NULL) && (next != X) ) {
            tempX = next;
            next = next->next; 
        }
        return tempX;
    }
    template<class T>
    Node<T> *LinkedList::getPrev(Node<T> *X) const {
        return X->next;
    }
    template<class T>
    Node<T> *LinkedList::getItem(int pos) const {
        Node<T> *get;
        int ls = listSize<T>();
        
        if (ls > pos) {
            get = privateData->head;
            for (int i = 1; i < (ls - pos); i++) {
                get = get->next;
            }
            return get;
        } else return NULL;
    }
    template<class T>
    Node<T> *LinkedList::getHead() const {
        return privateData->head;
    }
    template<class T>
    int  LinkedList::listSize() const {
        int count = 0;
        Node<T> *next;
        next = new Node<T>;
        next = privateData->head;
        while (next != NULL) {
            next = next->next;
            count++;
        }
        delete next;
        return count;
    }

    //\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\    
    /// OTHER FUNKTIONS ////////////////////////////////////////////////////
    template<class T>
    void LinkedList::swapNodes(Node<T> *X, Node<T> *Y) {
        // breaks when X is not in the list and Y is
        if (getPos(X) > getPos(Y)) {
            Node<T> *temp = X;
            X = Y;
            Y = temp;
        }
        if ( (X != Y ) && (Y != NULL) ) {
            Node<T> *tempY, *preX = getNext(X), *preY = getNext(Y);
            
            if (preX != NULL) { 
                preX->next = Y;
            } else privateData->head = Y; // X is at the end of the list (was added last, 
                             // head is pointing to it)
            tempY = Y->next;
            
            if (Y != X->next) {
                Y->next = X->next;
            } else Y-> next = X; // X and Y are right next to each other
            
            if (preY != X) { // X and Y are not right next to each other
                if (preY != NULL) {
                    preY -> next = X;
                } else privateData->head = X; // Y is at the end of the list (was added last, 
                                 // head is pointing to it)
            }
            
            X->next = tempY;
        }
    }
    template<class T>
    Node<T> *LinkedList::copy() const {
        return privateData->copy<T>(privateData->head);
    }
    template<class T>
    void LinkedList::reverse() {
        privateData->reverse<T>(privateData->head);
    }
    template<class T>
    void LinkedList::append(const LinkedList &list) {
        privateData->append<T>(list.privateData->head);
    }
    template<class T>
    void LinkedList::join(LinkedList &list) {
        privateData->join<T>(privateData->head, list.privateData->head);
    }
    template<class T>
    Node<T> *LinkedList::add(Node<T> *head2) {
        Node<T> *list1, *list2;
        
        list1 = new Node<T>;
        list1 = privateData->copy<T>(privateData->head);
        list2 = new Node<T>;
        list2 = privateData->copy(head2);
        
        privateData->join(list1, list2);
        delete list2;
        
        return list1;
    }
    template<class T>
    void LinkedList::randomize() {
        int ls = listSize<T>(), newSize = ls;
        Node<T> *newList, *temp;
        newList = new Node<T>;
        newList = NULL;
        for (int i = 0; i < ls; i++) {
            temp = uncouple<T>(privateData->createRandomNumber(0, --newSize));
            temp->next = newList;
            newList = temp;
        }
        delete privateData->head;
        privateData->head = newList;
    }


//\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
/// MANIPULATING MULTIPLE LINKEDLISTS //////////////////////////////////////
    template<class T>
    Node<T> *add( Node<T> *headList1,  Node<T> *headList2) {
        Node<T> *mergedHead;
        mergedHead = new Node<T>;
        
        LinkedList *list1 = new LinkedList;
        *list1 = LinkedList(headList1);
        LinkedList *list2 = new LinkedList;
        *list2 = LinkedList(headList2);
        list1->append<T>(*list2);
        mergedHead = list1->getHead<T>();
        list1->setHead<T>(NULL);
        list2->setHead<T>(NULL);
        delete list1;
        delete list2;
        
        return mergedHead;
    }
    template<class T>
    Node<T> *reverse(Node<T> *&head) {
        Node<T> *prevNode = NULL, *thisNode = head, *nextNode;
        while (thisNode != NULL) {
            nextNode = thisNode->next;
            thisNode->next = prevNode;
            prevNode = thisNode;
            thisNode = nextNode;
        }
        return prevNode;
    }
    
}








