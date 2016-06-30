// Polynomial headder file
// Created by Axel Esselmann on Oct 13th 2011
// Last edited: Oct 18th 2011

#ifndef POLINOMIAL_H

#define POLINOMIAL_H
#include "linkedlist.h"
#include "tokenlist.h"

using namespace LinkedListAnconaEsselmann;
using namespace TokenListAnconaEsselmann;

namespace PolynomialAnconaEsselmann {
    struct Pol {
        int pow;
        int coeff;
        Pol *copy() { //change so that Node does not do this but a copy constr.
            Pol *newItem = new Pol;
            newItem->pow = pow;
            newItem->coeff = coeff;
            return newItem;
        }
    };
    
    //\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\    
    /// Polynomial class ////////////////////////////////////////////////
    //
    // Description: 
    class Polynomial : public LinkedList<Pol> {
        
    //\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
    /// PUBLIC /////////////////////////////////////////////////////////////////
    public:
        
        //\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
        /// INITIALIZATION AND DESTRUCTION /////////////////////////////////////
        Polynomial() : LinkedList<Pol>() {
        // zero argument constructor
        } 
        Polynomial(Node<Pol> *Head) : LinkedList<Pol>(Head) {
        // empty
        }
        Polynomial(int coefficient, int power);
        //
        Polynomial(std::istream &ins);
        //
        Polynomial(int coefficient);
        //
        Polynomial(Polynomial const &pol) : LinkedList<Pol>(pol.getHead()) {
        // copy constructor
        }
        //~Polynomial() {} ????????????????????????????????
        
        //\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
        /// MUTATOR FUNKTIONS //////////////////////////////////////////////////
        void InsertPol(int coefficient, int power);
        // 
        
        //\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
        /// ACCESSOR FUNKTIONS /////////////////////////////////////////////////
        
        //\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
        /// OVERLOADED OPERATORS ///////////////////////////////////////////////
        friend std::ostream &operator <<(std::ostream &outs, 
                                         const Polynomial &pol);
        //        

        friend Polynomial operator +(const Polynomial &pol1, 
                                        const Polynomial &pol2);
        // 
        friend Polynomial operator -(const Polynomial &pol1, 
                                     const Polynomial &pol2);
        // 
        friend Polynomial operator *(const Polynomial &pol1, 
                                     const Polynomial &pol2);
        //
        
        
        //\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\    
        /// OTHER FUNKTIONS ////////////////////////////////////////////////////
        void printList(std::ostream &outs) const;
        //
        void simplyfy();
        //
        int evaluate(int valueForX);
        //
        void sort(int AscendDecend);
        //
        void sort();
        //
        
    //\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
    /// PRIVATE ////////////////////////////////////////////////////////////////
    private:
        Node<Pol> *createNode() const;
        // creates a node with all its variables initialized to zero or NULL
        bool getSign(Node<Token> *&node, int &sign);
        // 
    //\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
    /// MANIPULATING MULTIPLE LINKEDLISTS //////////////////////////////////////
        
    };
}
#endif
