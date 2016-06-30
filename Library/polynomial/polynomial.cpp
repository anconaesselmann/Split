// Polynomial implementation file    
// Created by Axel Esselmann on Oct 13th 2011
// Last edited: Oct 18th 2011

#include <iostream>
#include <cstdlib>
#include <math.h>
#include <string.h>
#include "myfunctions.h"
#include "polynomial.h"
#include "tokenlist.h"

using namespace mfAE;
 
namespace PolynomialAnconaEsselmann {
//\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\   
/// PUBLIC /////////////////////////////////////////////////////////////////
    
    //\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
    /// INITIALIZATION AND DESTRUCTION /////////////////////////////////////
    Polynomial::Polynomial(int coefficient) : LinkedList() {
        InsertPol(coefficient, 0);
    }
    Polynomial::Polynomial(int coefficient, int power) : LinkedList() {
        InsertPol(coefficient, power);
    }
    Polynomial::Polynomial(std::istream &ins) {
        using namespace TokenListAnconaEsselmann;
        TokenList tokenList(ins);
        std::cout << "\n****\n" << tokenList << "****\n";
        int sign, polTokenSize, co, po;
        Node<Token> *si = NULL, *coeff = NULL, *var = NULL, *op = NULL, *pow = NULL;
        Node<Token> *next = tokenList.getHead();
        while (next != NULL) {
            si = NULL; coeff = NULL; var = NULL; op = NULL; pow = NULL;
            if (next->item->type == 0) {
                sign = 1;
                var = next;
                //if token after var is ^ and token after ^ is # make it po
                if ( (tokenList.getNext(var) != NULL) && (*(tokenList.getNext(var)->item->token) == '^') ) {
                    if (tokenList.getNext(tokenList.getNext(var))->item->type == 1) {
                        pow = tokenList.getNext(tokenList.getNext(var));
                        op = tokenList.getNext(var);
                    }
                }
                //if token before var is # make it co and see if it is neg.
                if ( (tokenList.getPrev(var) != NULL) && (tokenList.getPrev(var)->item->type == 1)) {
                    coeff = tokenList.getPrev(var);
                    // what is the sign in front of the polinomial?
                    if (tokenList.getPrev(coeff) != NULL) {
                        Node<Token> *tempToken = tokenList.getPrev(coeff);
                        while (getSign(tempToken, sign)) {
                            tokenList.del(tokenList.getNext(tempToken));
                        }   
                    }
                } else {
                    // there is no coefficient before the variable. Is there 
                    // what is the sign in front of the polinomial?
                    if (tokenList.getPrev(var) != NULL) {
                        Node<Token> *tempToken = tokenList.getPrev(var);
                        while (getSign(tempToken, sign)) {
                            tokenList.del(tokenList.getNext(tempToken));
                        }   
                    }
                }
            
                //insert new poligon into list
                if (coeff != NULL) {
                    co = strToInt(coeff->item->token) * sign;
                } else co = 1 * sign;
                if (pow != NULL) {
                    po = strToInt(pow->item->token);
                } else po = 1;
                InsertPol(co, po);
                
                // replacing the tokens with a polinomial token
                char *newToken = new char[100]; // this needs to be streamlined
                newToken[0] = '\0';
                
                polTokenSize = 0;
                char *tempString = intToStr(co);
                strncat(newToken, tempString, 100);
                delete [] tempString;
                if (coeff != NULL) {  
                    tokenList.del(coeff);
                }
                if (var != NULL) {
                    strncat(newToken, var->item->token, 100);
                }
                if (op != NULL) {
                    strncat(newToken, op->item->token, 100);
                    if (op != NULL) {
                        tokenList.del(op);
                    }
                }        
                if (pow != NULL) {
                    strncat(newToken, pow->item->token, 100);
                    if (pow != NULL) {
                        tokenList.del(pow);
                    }
                }
                delete [] var->item->token;
                var->item->token =  newToken;
                var->item->type = 9;
            }
            next = next->next;
        }
        next = tokenList.getHead();
        while (next != NULL) {
            if (next->item->type == 1) {
                if ( (tokenList.getPrev(next) != NULL) && (tokenList.getPrev(next)->item->type == 4) ) {
                    if (*(tokenList.getPrev(next)->item->token) == '+') {
                        sign = 1;
                        tokenList.del(tokenList.getPrev(next));
                    } else
                    if (*(tokenList.getPrev(next)->item->token) == '-') {
                        sign = -1;
                        tokenList.del(tokenList.getPrev(next));
                    }
                }
                int tempToken = strToInt(next->item->token) * sign;
                delete [] next->item->token;
                next->item->token =  intToStr(tempToken);
                InsertPol(tempToken, 0);
            }
            next = next->next;
        }
        std::cout << "\n****\n" << tokenList << "****\n";
        reverse();
        simplyfy(); //out of order how it is, therefore this makes sense for now
    }
    //\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
    /// MUTATOR FUNKTIONS //////////////////////////////////////////////////
    void Polynomial::InsertPol(int coefficient, int power) {
        Node<Pol> *temp;
        temp = createNode();
        temp->item->coeff = coefficient;
        temp->item->pow = power;
        Insert(temp);
    }
    
    //\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
    /// ACCESSOR FUNKTIONS /////////////////////////////////////////////////
    
    //\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
    /// OVERLOADED OPERATORS ///////////////////////////////////////////////
    std::ostream &operator <<(std::ostream &outs, 
                                     const Polynomial &pol) {
        pol.printList(outs);
        return outs;
    }
    Polynomial operator +(const Polynomial &pol1, 
                          const Polynomial &pol2) {
        Polynomial returnPol = Polynomial(add(pol1.getHead(), pol2.getHead()));
        returnPol.simplyfy();
        return returnPol;
    }
    Polynomial operator -(const Polynomial &pol1, 
                          const Polynomial &pol2) {
        Polynomial temp = pol2;
        Node<Pol> *next = temp.getHead();
        while (next != NULL) {
            next->item->coeff = -(next->item->coeff); // overload unary -, if time
            next = next->next;
        }
        
        
        Polynomial returnPol = Polynomial(add(pol1.getHead(), temp.getHead()));
        returnPol.simplyfy();
        return returnPol;
    }
    Polynomial operator *(const Polynomial &pol1, 
                                 const Polynomial &pol2) {
        Polynomial product;
        Node<Pol> *next1 = pol1.getHead(), *next2 = pol2.getHead();
        while (next1 != NULL) {
            while (next2 != NULL) {
                product.InsertPol(next1->item->coeff * next2->item->coeff, next1->item->pow + next2->item->pow);
                next2 = next2->next;
            }
            next2 = pol2.getHead();
            next1 = next1->next;
        }
        product.simplyfy();
        return product;
    }
    
    //\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\    
    /// OTHER FUNKTIONS ////////////////////////////////////////////////////
    void Polynomial::printList(std::ostream &outs) const {
        Node<Pol> **NodePtrAr;
        int ls = listSize();
        NodePtrAr = new Node<Pol>*[ls];
        NodePtrAr[0] = getHead();
        bool firstPrint = true;
        for (int i = 1; i < ls; i++)
            NodePtrAr[i] = NodePtrAr[i-1]->next;
        for (int i = ls -1; i >= 0; i--) {
            if (NodePtrAr[i]->item->coeff != 0) {
                if (NodePtrAr[i]->item->coeff > 0) {
                    if (!firstPrint)
                        outs << "+ ";
                } else { 
                    if (!firstPrint)
                        outs << "- ";
                    else outs << "-";
                }
                if (abs(NodePtrAr[i]->item->coeff) != 1) { 
                    outs << abs(NodePtrAr[i]->item->coeff); 
                    firstPrint = false;
                } else if (NodePtrAr[i]->item->pow == 0 ) {
                    outs << abs(NodePtrAr[i]->item->coeff);
                    firstPrint = false;
                }
                if (NodePtrAr[i]->item->pow != 0) {
                    outs << "X";
                    firstPrint = false;
                    if (NodePtrAr[i]->item->pow != 1) {
                        outs << "^" << NodePtrAr[i]->item->pow; 
                    }
                }
                outs  << " ";
                
            }
        }
        bool allZero = true;
        for (int i = 0; i < ls; i++) {
            if (NodePtrAr[i]->item->coeff != 0 ) {
                allZero = false;
            }
        }
        if (allZero) {
            outs << "0";
        }
        delete [] NodePtrAr;
    }
    void Polynomial::simplyfy() {
        bool calculationMade = true;
        sort();
        Node<Pol> *thisNode;
        while (calculationMade) {
            calculationMade = false;
            thisNode = getHead();
            while (thisNode != NULL) {
                if (thisNode->next != NULL) {
                    if (thisNode->item->pow == (thisNode->next)->item->pow) {
                        thisNode->item->coeff = thisNode->item->coeff + (thisNode->next)->item->coeff;
                        calculationMade = true;
                        del(thisNode->next);
                    }
                }
                thisNode = thisNode->next;
            }
        } 
    }
    int Polynomial::evaluate(int valueForX) {
        Node<Pol> *temp = getHead();
        int result = 0;
        while (temp != NULL) {
            result = result + (temp->item->coeff * pow(valueForX, temp->item->pow));
            temp = temp->next;
        }
        return result;
    }
    void Polynomial::sort(int AscendDecend) {
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
                if ( (getItem(i + dec))->item->pow > (getItem(i + asc))->item->pow)  {
                    swapNodes((getItem(i + dec)), (getItem(i + asc)));
                    makeSwap = true;
                    lastSortMade = i;
                }
            }
            sorted = lastSortMade;
        }
    }
    void Polynomial::sort() {
        sort(1);
    }
    
//\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\   
/// PRIVATE ////////////////////////////////////////////////////////////////
    Node<Pol> *Polynomial::createNode() const {
        Node<Pol> *newNode = new Node<Pol>;
        Pol *newItem = new Pol;
        newItem->coeff = 0;
        newItem->pow = 0;
        newNode->item = newItem;
        newNode->next = NULL;
        
        return newNode;
    }
    bool Polynomial::getSign(Node<Token> *&node, int &sign) {
        if (node != NULL) {
            if (*(node->item->token) == '+') {
                node = node->next;
                return true;
            } else if (*(node->item->token) == '-') {
                sign = -sign;
                node = node->next;
                return true;
            } else return false;
        } else return false;

    } 
    
//\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
/// MANIPULATING MULTIPLE LINKEDLISTS //////////////////////////////////////
}