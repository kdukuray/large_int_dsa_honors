#ifndef DLLIST_H
#define DLLIST_H
#include <iostream>

template <class T>
struct node{
    node<T> *next;
    node<T> *back;
    T info;

};

template <class T>
class dLList{
    private:
        node<T> *first;
        node<T> * last;
        node<T> *forwardIterator;
        node<T> *backwardIterator;
        int length;

    public:
    //default constructor
        dLList();
    //copy constructor
        dLList(const dLList<T> &other);
    //destructor
        ~dLList();
    //overloaded operator equal
        const dLList<T>& operator=(const dLList<T>& other);
    //insertion at beginning function
        void insertAtBegin(T item);
    //insertion at end function
        void insertAtEnd(T item);
    //destroy function
        void destroy();
    //sets the iterator to the beginnig of the list
        void setForwardIterator() ;
    //stores the value at the Forward iterator in a given variable, returns bool based on success status
        bool getForwardIterator(T &item);
    //returns true only if the forward iterator is not null;
        bool forwardIteratorActive();
    //this function moves the forward iterator up a node
        void moveForwardIterator();
    //sets the literator to the end of the list
        void setBackwardIterator() ;
    //stores the value at the Backward iterator in a given variable, returns bool based on success status
        bool getBackwardIterator(T &item);
    //returns true only if the backward Iterator is not null
        bool backwardIteratorActive();
    //this function moves the backward iterator up a node
        void moveBackwardIterator();
    //returns the length of the linked list
        int getLength() const;
    //overloaded equal-equal opertor
        bool operator==(const dLList<T>& other);
    //prints list (for development purposes)
        void printList();
    //this is the copy function
        void copy(const dLList<T>& other);
    //deletes the last node in the Doubly Linked list
        void deleteLast();

};

#endif