// LikedList header file
// Created by Axel Esselmann on Oct 5th 2011
// Last edited: Oct 14th 2011

#ifndef LINKEDLIST_H
#define LINKEDLIST_H
//#include "item.h"

namespace LinkedListAnconaEsselmann {
    
    template<class T>
    class Node {
    public:
        Node();
        Node(const Node &toBeCoppied);
        void operator =(const Node &toBeCoppied);
        ~Node();
        Node *next;
        Node<T> *item;
    private:
        
    };
    
    //\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\    
    /// LinkedList class ///////////////////////////////////////////////////////
    //
    // Description: Basic class for a linked list that used the struct Node in
    // this same namespace. The head is the last item in this linked list, the 
    // front is the first item entered. All references to before, after, left, 
    // right, are based on this order. LinkedList is the parent class for
    // IntLinkedList, which makes use of "int item" in the struct Node.
    // LinkedList does not use item.
    class LinkedList {
        
    //\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
    /// PUBLIC /////////////////////////////////////////////////////////////////
    public:
        
        //\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
        /// INITIALIZATION AND DESTRUCTION /////////////////////////////////////
        LinkedList();
        // zero argument operator initializes the list by setting head to NULL
        template<class T>
        LinkedList(const LinkedList &list);
        // copy constructor: coppies each item of list to this instance of
        // LinkedList
        template<class T>
        LinkedList(Node<T> *Head);
        // constructor taking the head of a LinkedList as an argument.
        // coppies the list that Head is a part of
        ~LinkedList();
        // destructor deletes each Node of the linked list until head is NULL
        template<class T>
        void operator =(LinkedList rightSide);
        // overloaded assignment operator, coppies each node to the new list
        
        //\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
        /// MUTATOR FUNKTIONS //////////////////////////////////////////////////
        template<class T>
        void Insert(Node<T> *item);
        // adds an element to the end of the list (behind the item that was 
        // added last) changes head
        template<class T>
        void InsertFront(Node<T> *item);
        // adds an element to the front of the list
        template<class T>
        void insertBefore(Node<T> *X, Node<T> *item);
        // pass the adress of head (&head) to insertAfter()
        // inserts I after X
        // head has to be passed by reference
        template<class T>
        void insertAfter(Node<T> *X, Node<T> *item);
        // pass the adress of head (&head) to insertAfter()
        // inserts I after X
        // head has to be passed by reference
        template<class T>
        void moveLeft(Node<T> *item);
        // moves the Item towards the first item that was input
        template<class T>
        void moveRight(Node<T> *item);
        // moves the Item towards the first item that was input
        template<class T>
        void move(Node<T> *item, int moveBy);
        // moves the item to the left or rigth by however many steps moveBy demands.
        // moves left for negative moveBys and right for positive moveBys
        template<class T>
        void uncouple(Node<T> *X);
        //removes the item X from the list that head is pointing to but does not 
        // delete it. X will still point to the item but its ->next will be set 
        // to NULL
        template<class T>
        Node<T> *uncouple(int pos);
        // uncouples the item at position pos and returns a pointer to it.
        // if the item did not exist, NULL is returned.
        template<class T>
        void del(Node<T> *X);
        // deletes the item that X points to from the list
        // head has to be passed by reference
        template<class T>
        void del(int pos);
        // deletes the item at position pos from the list
        template<class T>
        void delAll();
        // deletes all Nodes and sets the head to NULL
        template<class T>
        Node<T> *setHead(Node<T> *newHead);
        // sets the head to newHead and returns the old head so it can be de-
        // leted, if so desired.
        
        //\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
        /// ACCESSOR FUNKTIONS /////////////////////////////////////////////////
        template<class T>
        int getPos(Node<T> *X) const;
        // returns the position the item *X has in the list. 0 is the beginning, 
        // listSize-1 is the most recent item
        //  returns -1 if not in the list
        template<class T>
        Node<T> *getNext(Node<T> *X) const;
        // returns the adress of the next item in the linked list in which X is 
        // included
        template<class T>
        Node<T> *getPrev(Node<T> *X) const;
        // returns the adress of the previous item in the linked list in which X 
        // is included
        template<class T>
        Node<T> *getItem(int pos) const;
        // head is pointing to the last item of a list
        // getItem returns the (pos)ths item, from the beginning of the list.
        // pos = 0 returns the first item, pos listSize()-1 returns the item 
        // head points to
        template<class T>
        Node<T> *getHead() const;
        // returns a pointer that points to the head of the list (the end)
        template<class T>
        int listSize() const;
        // returns the number of items in the list that has it's first item at 
        // adress head
        // a list with 5 entries will return int 5

        //\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\    
        /// OTHER FUNKTIONS ////////////////////////////////////////////////////
        template<class T>
        void swapNodes(Node<T> *X, Node<T> *Y);
        // Swaps the objects X and Y
        // head has to be passed by reference
        template<class T>
        Node<T> *copy() const;
        // copies the linked list that head points to and returns 
        // a pointer that points to the copied list
        template<class T>
        void reverse();
        // reverses the linked list of the class instance
        template<class T>
        void append(const LinkedList &list);
        // makes a copy of list and appends it to the the calling list
        // calls append(Node *append)
        template<class T>
        void join(LinkedList &list);
        // connects list to the instance of LinkedList and sets list to NULL
        // No nodes are coppied
        template<class T>
        T *add(Node<T> *head2);
        // makes a copy of both lists and joins them without making a further 
        // copy. Returns the pointer to the newly created list that holds both 
        // old lists
        template<class T>
        void randomize();
        // randomizes the order of head without making a copy individual items 
        // in the list

    //\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
    /// PRIVATE ////////////////////////////////////////////////////////////////    
    private:
        struct D_Pointer;
        D_Pointer *privateData;
    };
    
    //\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
    /// MANIPULATING MULTIPLE LINKEDLISTS //////////////////////////////////////
    template<class T>
    T *add( Node<T> *headList1,  Node<T> *headList2);
    // adds the seccond list to the first list
    template<class T>
    T *reverse(Node<T> *&head);
}
#endif
