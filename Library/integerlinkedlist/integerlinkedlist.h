// IntLinkedList headder file
// Created by Axel Esselmann on Oct 5th 2011
// Last edited: Oct 18th 2011

#ifndef IntLinkedList_H
#define IntLinkedList_H

#include "linkedlist.h"
using namespace LinkedListAnconaEsselmann;

namespace IntLinkedListAnconaEsselmann {
    
    struct Integer {
        int Int;
        
        Integer *copy() {
            Integer *newItem = new Integer;
            newItem->Int = Int;
            return newItem;
        }
        
    };    
    
    //\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\    
    /// IntLinkedList class ////////////////////////////////////////////////
    //
    // Description: 
    class IntLinkedList: public LinkedList<Integer> {
        
    //\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
    /// PUBLIC /////////////////////////////////////////////////////////////////
    public:
        
        //\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
        /// INITIALIZATION AND DESTRUCTION /////////////////////////////////////
        IntLinkedList() : LinkedList<Integer>() {
            // empty
        }
        IntLinkedList(Node<Integer> *Head) : LinkedList(Head) {
            // empty
        }
        IntLinkedList(IntLinkedList const &list) : LinkedList<Integer>(list) {
            // empty copy constructor
        }
        //~IntLinkedList() : ~LinkedList() {}
        
        //\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
        /// ACCESSOR FUNKTIONS /////////////////////////////////////////////////
        Node<Integer>* getCursor();
        // returns the Node<Integer> that cursor is pointing to
        
        //\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
        /// OVERLOADED OPERATORS ///////////////////////////////////////////////
        friend std::ostream &operator <<(std::ostream &outs, 
                                         const IntLinkedList &ll);
        friend IntLinkedList& operator ++(IntLinkedList &list);
        // moves the cursor to the right
        friend IntLinkedList& operator --(IntLinkedList &list);
        // moves the cursor to the left
        friend IntLinkedList operator +(const IntLinkedList &list1, 
                                        const IntLinkedList &list2);
        // merges list1 and list2
        friend void operator +=(IntLinkedList &list1, 
                                const IntLinkedList &list2);
        // appends list 1 with list 2;
        
        //\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
        /// MUTATOR FUNKTIONS //////////////////////////////////////////////////
        void Insert(int i);
        // creates a Node<Integer> element with its item variable set to i and adds the 
        // element to the end of the list (behind the item that was addes last)
        void InsertFront(int i);
        // adds an element to the front of the list
        void insertBefore(Node<Integer> *X, int i);
        // pass the adress of head (&head) to insertAfter()
        // inserts I after X
        // head has to be passed by reference
        void insertAfter(Node<Integer> *X, int i);
        // pass the adress of head (&head) to insertAfter()
        // inserts I after X
        // head has to be passed by reference
        void setCursor(Node<Integer> *Cursor);
        // sets the cursor to Cursor
        void setCursor(int position);
        // sets the cursor to Cursor
        
        //\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\    
        /// OTHER FUNKTIONS ////////////////////////////////////////////////////
        void printListBackToFront(std::ostream &outs) const;
        // prints the list in the reverse order each item was added
        void printList(std::ostream &outs) const;
        // prints the list in the order each item was added
        void sort(int AscendDecend);
        // sorts the linked list that head points to either ascending or 
        // descending, depending on AscendDecend:
        // AscendDecend >= 0 sorts the list in an ascending order
        // AscendDecend < 0  sorts the list in a decending order
        // head has to be passed by reference
        // the cursor stays on whatever Node<Integer> it was, the position gets
        // shifted with it.
        void sort();
        // sorts the linked list that head points to in an ascending order
        // head has to be passed by reference
        Node<Integer> *search(int pos, int searchInt) const;
        // starting at pos, retrieves the first instance of searchInt as a Node
        // !!!!!!!!!overload with only pos at 0
      
    //\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
    /// PRIVATE ////////////////////////////////////////////////////////////////    
    private:
        Node<Integer> *createNode() const;
        // creates a Node<Integer> with all its variables initialized to zero or NULL
        Node<Integer> *cursor; 
        // only uses are in <<, ++,--, getCursor, setCursor and in 
        // the main function
    };
    
    //\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
    /// MANIPULATING MULTIPLE LINKEDLISTS //////////////////////////////////////
    Node<Integer> *merge(IntLinkedList &list1, IntLinkedList &list2);
    // sorts both lists alphabetically and merges the two lists so that both are
    // combined in one list that is returned alphabetically
}

#endif
