// LikedList template header and comilation file
// Created by Axel Esselmann on Oct 5th 2011
// Last edited: Oct 18th 2011

#ifndef LINKEDLIST_H
#define LINKEDLIST_H

namespace LinkedListAnconaEsselmann {
    
    template<class T>
    class Node {
    public:
        Node(T _item) : item(_item) { }
        Node(const Node<T> &toBeCoppied);
        void operator =(const Node<T> &toBeCoppied);
        ~Node();
        Node<T> *next;
        T item;
    private:
        
    };
    
    //\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\    
    /// LinkedList class ///////////////////////////////////////////////////////
    //
    // Description: Basic class for a linked list that used the struct Node<T> in
    // this same namespace. The head is the last item in this linked list, the 
    // front is the first item entered. All references to before, after, left, 
    // right, are based on this order. LinkedList is the parent class for
    // IntLinkedList, which makes use of "int item" in the struct Node.
    // LinkedList does not use item.
    template<class T>
    class LinkedList {
        
    //\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
    /// PUBLIC /////////////////////////////////////////////////////////////////
    public:
        
        //\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
        /// INITIALIZATION AND DESTRUCTION /////////////////////////////////////
        LinkedList();
        // zero argument operator initializes the list by setting head to NULL
        LinkedList(const LinkedList &list);
        // copy constructor: coppies each item of list to this instance of
        // LinkedList
        LinkedList(Node<T> *Head);
        // constructor taking the head of a LinkedList as an argument.
        // coppies the list that Head is a part of
        ~LinkedList();
        // destructor deletes each Node<T> of the linked list until head is NULL
        void operator =(LinkedList rightSide);
        // overloaded assignment operator, coppies each Node<T> to the new list
        
        //\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
        /// MUTATOR FUNKTIONS //////////////////////////////////////////////////
        void Insert(Node<T> *item);
        // adds an element to the end of the list (behind the item that was 
        // added last) changes head
        void Insert(T item) {
            Node<T>* newNode = new Node<T>(item);
            Insert(newNode);
        }
        void InsertFront(Node<T> *item);
        // adds an element to the front of the list
        void insertBefore(Node<T> *X, Node<T> *item);
        // pass the adress of head (&head) to insertAfter()
        // inserts I after X
        // head has to be passed by reference
        void insertAfter(Node<T> *X, Node<T> *item);
        // pass the adress of head (&head) to insertAfter()
        // inserts I after X
        // head has to be passed by reference
        void moveLeft(Node<T> *item);
        // moves the Item towards the first item that was input
        void moveRight(Node<T> *item);
        // moves the Item towards the first item that was input
        void move(Node<T> *item, int moveBy);
        // moves the item to the left or rigth by however many steps moveBy demands.
        // moves left for negative moveBys and right for positive moveBys
        void uncouple(Node<T> *X);
        //removes the item X from the list that head is pointing to but does not 
        // delete it. X will still point to the item but its ->next will be set 
        // to NULL
        Node<T> *uncouple(int pos);
        // uncouples the item at position pos and returns a pointer to it.
        // if the item did not exist, NULL is returned.
        void del(Node<T> *X);
        // deletes the item that X points to from the list
        // head has to be passed by reference
        void del(int pos);
        // deletes the item at position pos from the list
        void delAll();
        // deletes all Nodes and sets the head to NULL
        Node<T> *setHead(Node<T> *newHead);
        // sets the head to newHead and returns the old head so it can be de-
        // leted, if so desired.
        
        //\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
        /// ACCESSOR FUNKTIONS /////////////////////////////////////////////////
        int getPos(Node<T> *X) const;
        // returns the position the item *X has in the list. 0 is the beginning, 
        // listSize-1 is the most recent item
        //  returns -1 if not in the list
        Node<T> *getNext(Node<T> *X) const;
        // returns the adress of the next item in the linked list in which X is 
        // included
        Node<T> *getPrev(Node<T> *X) const;
        // returns the adress of the previous item in the linked list in which X 
        // is included
        Node<T> *getItem(int pos) const;
        // head is pointing to the last item of a list
        // getItem returns the (pos)ths item, from the beginning of the list.
        // pos = 0 returns the first item, pos listSize()-1 returns the item 
        // head points to
        Node<T> *getHead() const;
        // returns a pointer that points to the head of the list (the end)
        int listSize() const;
        // returns the number of items in the list that has it's first item at 
        // adress head
        // a list with 5 entries will return int 5

        //\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\    
        /// OTHER FUNKTIONS ////////////////////////////////////////////////////
        void swapNodes(Node<T> *X, Node<T> *Y);
        // Swaps the objects X and Y
        // head has to be passed by reference
        Node<T> *copy() const;
        // copies the linked list that head points to and returns 
        // a pointer that points to the copied list
        void reverse();
        // reverses the linked list of the class instance
        void append(const LinkedList &list);
        // makes a copy of list and appends it to the the calling list
        // calls append(Node<T> *append)
        void join(LinkedList &list);
        // connects list to the instance of LinkedList and sets list to NULL
        // No nodes are coppied
        Node<T> *add(Node<T> *head2);
        // makes a copy of both lists and joins them without making a further 
        // copy. Returns the pointer to the newly created list that holds both 
        // old lists
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
    Node<T> *add( Node<T> *headList1,  Node<T> *headList2);
    // adds the seccond list to the first list
    template<class T>
    Node<T> *reverse(Node<T> *&head);
}



namespace LinkedListAnconaEsselmann {
    
    //\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
    /// Node ///////////////////////////////////////////////////////////////////
    

    template<class T>
    Node<T>::Node(const Node<T> &toBeCoppied) {
        next = toBeCoppied.next;
        item = toBeCoppied.item->copy();
    }
    template<class T>
    void Node<T>::operator =(const Node<T> &toBeCoppied) {
        next = toBeCoppied.next;
        item = toBeCoppied.item;
    }
    template<class T>
    Node<T>::~Node() {
        //delete item;
    }
    
    
    //\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\   
    /// D_POINTER //////////////////////////////////////////////////////////////
    template<class T>
    struct LinkedList<T>::D_Pointer {
        int createRandomNumber(int lower_bound, int upper_bound) const;
        // creates a random number between lower_bound and upper_bound
        void append(Node<T> *append);
        // makes a copy of append and attaches it to head without copying head.
        void reverse(Node<T> *(&head)) const;
        // reverses the linked list that head points to
        Node<T> *copy(Node<T> *head) const;
        // copies the linked list that head points to and returns 
        // a pointer that points to the copied list
        void Insert(Node<T> *&Head, Node<T> *item) const;
        // adds an element to the end of the list (behind the item that was 
        // addes last) changes head
        Node<T> *createNode(T _item) const;
        // creates a Node<T> with all its variables initialized to zero or NULL
        void join(Node<T> *(&head1), Node<T> *(&head2));
        // joins lists head1 and head2 without copying and returns list 1 after 
        // list 2 as head1. Head2 becomes NULL for security reasons, since for 
        // example sorting head1 would make head 2 useless, since it would point 
        // to some random object in the middle of the list;
        
        //\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
        /// VARIABLES AND CONSTANTS ////////////////////////////////////////////
        Node<T> *head;
    };
    
    //\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
    /// PRIVATE ( D_POINTER FUNCTIONS ) ////////////////////////////////////////
    template<class T>
    int LinkedList<T>::D_Pointer::createRandomNumber(int lower_bound, int upper_bound) const {
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
    void LinkedList<T>::D_Pointer::append(Node<T> *append) {
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
    void LinkedList<T>::D_Pointer::reverse(Node<T> *(&head)) const {
        head = LinkedListAnconaEsselmann::reverse(head);
    }
    template<class T>
    Node<T> *LinkedList<T>::D_Pointer::copy(Node<T> *Head) const {
        Node<T> *headCopy;
        Node<T> *next;
        
        headCopy = new Node<T>; // Noone needs to delete this, since we need this!
        headCopy = NULL;
        next = Head;
        while (next != NULL) {
            Node<T> *temp; // A copy of the Node<T> has to be made
            temp = createNode();
            *temp = *next; /// test if this works!!!!
            
            Insert(headCopy, temp); // here each variable needs to be coppied, 
            // except the link to the next item
            next = next->next;
        }
        reverse(headCopy);
        return headCopy;
    }
    template<class T>
    void LinkedList<T>::D_Pointer::Insert(Node<T> *&Head, Node<T> *item) const {
        item->next = Head;
        Head = item;
    }
    template<class T>
    Node<T> *LinkedList<T>::D_Pointer::createNode(T _item) const {
        Node<T> *item;
        item = new Node<T>(_item);
        item->next = NULL;
        return item;
    }
    template<class T>
    void LinkedList<T>::D_Pointer::join(Node<T> *(&head1), Node<T> *(&head2)) {
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
    template<class T>
    LinkedList<T>::LinkedList() : privateData(new D_Pointer) {
        privateData->head = NULL;
    }
    template<class T>
    LinkedList<T>::LinkedList(const LinkedList &list) : privateData(new D_Pointer( *(list.privateData)  )) { //copy constructor
        privateData->head = privateData->copy(list.privateData->head);
    }
    template<class T>
    LinkedList<T>::LinkedList(Node<T> *Head) : privateData(new D_Pointer){
        privateData->head = NULL;
        privateData->head = privateData->copy(Head);
    }
    template<class T>
    LinkedList<T>::~LinkedList() {
        delAll();
        delete privateData;
    }
    template<class T>
    void LinkedList<T>::operator =(LinkedList rightSide) {
        Node<T> *next, *insert;
        next = rightSide.getHead();
        while (next != NULL) {
            insert = next;
            Insert(insert);
            next = next->next;
        }
        reverse();
        std::swap(this->privateData, rightSide.privateData);
    }
    
    //\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
    /// MUTATOR FUNKTIONS //////////////////////////////////////////////////
    template<class T>
    void LinkedList<T>::Insert(Node<T> *item) { 
        Node<T> *temp;
        temp = privateData->createNode(item->item); // recently changed
        *temp = *item;
        temp->next = privateData->head;
        privateData->head = temp;
    }
    template<class T>
    void LinkedList<T>::InsertFront(Node<T> *item) {
        int ls = listSize();
        if (ls != 0) {
            insertBefore(getItem(0), item);
        } else Insert(item);
    }
    template<class T>
    void LinkedList<T>::insertBefore(Node<T> *X, Node<T> *item) {
        if (listSize() != 0) {
            Node<T> *temp;
            temp = privateData->createNode();
            *temp = *item;
            temp->next = X->next;
            X->next = temp;
        } else Insert(item);
    }
    template<class T>
    void LinkedList<T>::insertAfter(Node<T> *X, Node<T> *item) {
        Node<T> *temp;
        temp = privateData->createNode();
        *temp = *item;
        int pos = getPos(X);
        int ls = listSize();
        if (pos != ls-1) {
            Node<T> *prevPos = getItem(pos +1);
            insertBefore(prevPos, temp);
        } else {
            Insert(temp);
        }
    }
    template<class T>
    void LinkedList<T>::moveLeft(Node<T> *item) {
        if (getPos(item) > 0) {
            swapNodes(item, item->next);
        }
    }
    template<class T>
    void LinkedList<T>::moveRight(Node<T> *item) {
        int ls = listSize();
        if (getPos(item) < ls-1) {
            swapNodes(item, getNext(item));
        }
    }
    template<class T>
    void LinkedList<T>::move(Node<T> *item, int moveBy) {
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
    void  LinkedList<T>::uncouple(Node<T> *X) {
        int ls = listSize();
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
    Node<T> *LinkedList<T>::uncouple(int pos) {
        int ls = listSize();
        Node<T> *uncoupleItem = getItem(pos);
        if (pos < ls) {
            uncouple(uncoupleItem);
        } else uncoupleItem = NULL;
        if (ls == 0) {
            uncoupleItem = NULL;
        }
        return uncoupleItem;
    }
    template<class T>
    void  LinkedList<T>::del(Node<T> *X) {
        uncouple(X);
        delete X;
    }
    template<class T>
    void  LinkedList<T>::del(int pos) {
        Node<T> *toDelete;
        toDelete = uncouple(pos);
        if (toDelete != NULL) {
            delete toDelete;
        }
    }
    template<class T>
    void  LinkedList<T>::delAll() {
        while (privateData->head != NULL) {
            del(privateData->head);
        }
    }
    template<class T>
    Node<T> *LinkedList<T>::setHead(Node<T> *newHead) {
        Node<T> *temp = privateData->head;
        privateData->head = newHead;
        return temp;
    }
    
    //\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
    /// ACCESSOR FUNKTIONS /////////////////////////////////////////////////
    template<class T>
    int   LinkedList<T>::getPos(Node<T> *X) const {
        int ls = listSize();
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
    Node<T> *LinkedList<T>::getNext(Node<T> *X) const {
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
    Node<T> *LinkedList<T>::getPrev(Node<T> *X) const {
        return X->next;
    }
    template<class T>
    Node<T> *LinkedList<T>::getItem(int pos) const {
        Node<T> *get;
        int ls = listSize();
        
        if (ls > pos) {
            get = privateData->head;
            for (int i = 1; i < (ls - pos); i++) {
                get = get->next;
            }
            return get;
        } else return NULL;
    }
    template<class T>
    Node<T> *LinkedList<T>::getHead() const {
        return privateData->head;
    }
    template<class T>
    int  LinkedList<T>::listSize() const {
        int count = 0;
        Node<T> *next;
        
        if (privateData->head != NULL) {
            next = new Node<T>(privateData->head->item);
            next = privateData->head;
            while (next != NULL) {
                next = next->next;
                count++;
            }
            delete next;
            return count;
        } else return 0;
    }
    
    //\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\    
    /// OTHER FUNKTIONS ////////////////////////////////////////////////////
    template<class T>
    void LinkedList<T>::swapNodes(Node<T> *X, Node<T> *Y) {
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
    Node<T> *LinkedList<T>::copy() const {
        return privateData->copy(privateData->head);
    }
    template<class T>
    void LinkedList<T>::reverse() {
        privateData->reverse(privateData->head);
    }
    template<class T>
    void LinkedList<T>::append(const LinkedList &list) {
        privateData->append(list.privateData->head);
    }
    template<class T>
    void LinkedList<T>::join(LinkedList &list) {
        privateData->join(privateData->head, list.privateData->head);
    }
    template<class T>
    Node<T> *LinkedList<T>::add(Node<T> *head2) {
        Node<T> *list1, *list2;
        
        list1 = new Node<T>;
        list1 = privateData->copy(privateData->head);
        list2 = new Node<T>;
        list2 = privateData->copy(head2);
        
        privateData->join(list1, list2);
        delete list2;
        
        return list1;
    }
    template<class T>
    void LinkedList<T>::randomize() {
        int ls = listSize(), newSize = ls;
        Node<T> *newList, *temp;
        newList = new Node<T>;
        newList = NULL;
        for (int i = 0; i < ls; i++) {
            temp = uncouple(privateData->createRandomNumber(0, --newSize));
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
        
        LinkedList<T> *list1 = new LinkedList<T>;
        *list1 = LinkedList<T>(headList1);
        LinkedList<T> *list2 = new LinkedList<T>;
        *list2 = LinkedList<T>(headList2);
        list1->append(*list2);
        mergedHead = list1->getHead();
        list1->setHead(NULL);
        list2->setHead(NULL);
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
#endif
