#include "dLList.hpp"

//--default constructor
template <class T>
dLList<T>::dLList(){
    this->first = nullptr;
    this->last = nullptr;
    length = 0;
}

//--copy constructor
template <class T>
dLList<T>::dLList(const dLList<T> &other){
    copy(other);
}

//--destructor
template <class T>
dLList<T>::~dLList(){
    destroy();
}

//--overloaded operator equal
template <class T>
const dLList<T>& dLList<T>::operator=(const dLList<T>& other){
    if (this != &other){
        destroy();
        copy(other);
    }
    return *this;

}

//--insertion at beginning function
template <class T>
void dLList<T>::insertAtBegin(T item){
    node<T> *localptr = new node<T>;
    localptr->info = item;
    localptr->back = nullptr;
    localptr->next = first;
    if (first != nullptr){
        first->back = localptr;
    }
    first = localptr;
    
    if (last == nullptr){
        last = localptr;
    }
    length++;
}

//--insertion at end function
template <class T>
void dLList<T>::insertAtEnd(T item){
    node<T> *localptr = new node<T>;
    localptr->info = item;
    localptr->next = nullptr;
    localptr->back = last;

    if (last != nullptr){
        last->next = localptr;
    }

    last = localptr;

    if (first == nullptr){
        first = localptr;

    }
    length++;
    
}

//--destroy function
template <class T>
void dLList<T>::destroy(){
    if (first != nullptr){
        node<T> *localptr;

        while (first != nullptr){
            localptr = first;
            first = first->next;
            delete localptr;
        }
        last = nullptr;
        length = 0;
    }

}

//--stores the value at the Forward iterator in a given variable, returns bool based on success status
template <class T>
void dLList<T>::setForwardIterator() {
    forwardIterator = first;

}

//--returns the value in the forward iterator
template <class T>
bool dLList<T>::getForwardIterator(T &item){
    if (forwardIterator != nullptr){
        item = forwardIterator->info;
        return true;
    }
    return false;
    

}

//--returns true only if the forward iterator is not null;
template <class T>
bool dLList<T>::forwardIteratorActive(){
    return forwardIterator != nullptr;

}

 //--returns true only if the backward iterator is not null;
template <class T>
bool dLList<T>::backwardIteratorActive(){
    return backwardIterator != nullptr;

}

//--this function moves the forward iterator up a node
template <class T>
void dLList<T>::moveForwardIterator(){
    if (forwardIterator != nullptr){
        forwardIterator = forwardIterator->next;
    }

}

//--this function moves the backward iterator down a node
template <class T>
void dLList<T>::moveBackwardIterator(){
     if (backwardIterator != nullptr){
        backwardIterator = backwardIterator->back;
    }

}

//--sets the iterator to the end of the list
template <class T>
void dLList<T>::setBackwardIterator() {
    backwardIterator = last;
}
//--stores the value at the Backward iterator in a given variable, returns bool based on success status
template <class T>
bool dLList<T>::getBackwardIterator(T &item){
    if (backwardIterator != nullptr){
        item = backwardIterator->info;
        return true;
    }
    return false;

}

//--returns the length of the linked list
template <class T>
int dLList<T>::getLength() const{
    return length;
}

//--overloaded equal-equal opertor
template <class T>
bool dLList<T>::operator==(const dLList<T>& other){
    bool both_are_equal = true;

//if they have a different lengths, they are not equal
    if (this->length != other.length){
        both_are_equal = false;
    }
//else, they have the same length.
//loop through both and ee if you can find any inconsistency with their contents
    else{
        node<T> *localptr = this->first;
        node<T> *other_localptr = other.first;

//this loop will termiante for only two reasons, both lists have been exahusted
//they become exhausted at the same time because we've verfifed that they're eqal in lenghth
//or if there is an inconsistency int  heir number content
        while(localptr != nullptr && other_localptr != nullptr && both_are_equal){
            if (localptr->info != other_localptr->info){
                both_are_equal = false;
            }
            localptr = localptr->next;
            other_localptr = other_localptr->next;
        }

    }

    return both_are_equal;

}

//--this is the copy function
template <class T>
void dLList<T>::copy(const dLList<T>& other){
    this->length = other.length;

    if (other.first == nullptr){
        this->first = nullptr;
        this->last = nullptr;
    }
    else{
        first =  new node<T>;
        first->info = other.first->info;
        node<T> *localptr = first;
        node<T> *localptr_trail;
        node<T> *other_localptr = other.first->next;

        while (other_localptr != nullptr){
            localptr_trail = localptr;
            localptr->next = new node<T>;
            localptr = localptr->next;
            localptr->info = other_localptr->info;
            localptr->back = localptr_trail;
            other_localptr = other_localptr->next;
        }
        last = localptr;
        localptr->next = nullptr;
    }
}

//--deletes the last node in the Doubly Linked list
template <class T>
void dLList<T>::deleteLast(){
   node<T> *localptr = last;
   if (!(localptr == nullptr)){
        if (localptr == first){
            first = nullptr;
            last = nullptr;
            delete localptr;
        }
        else{
            last = last->back;
            last->next = nullptr;
            delete localptr;   
        }
        length--;
   }
}

//--prints list (for development purposes)
template <class T>
void dLList<T>::printList(){
    if (first ==  nullptr){
        std::cout << "<- [  ] ->\n";
    }
    else {
        node<T> *localptr = first;
        std::cout << "\n|nullptr|";
        
        while (localptr != nullptr){
            std::cout << "<--[ " << localptr->info << "  ]-->";
            localptr = localptr->next;
        }
        std::cout << "|nullptr|\n\n";
    }
}