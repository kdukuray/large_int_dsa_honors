#include "dLList.cpp"

void printMenu();
void confirmListAreSame(dLList<int> l1, dLList<int> l2);

int main(){

    dLList<int> myList;
    int toInsert;
    int toPrint;
    dLList<int> list2copy;


    char command;
   

    do {
        printMenu();
        std::cin >> command;
        switch(command){
            case '1':
                myList.printList();
                break;
            
            case '2':
                std::cout << "Enter a number to Insert at beginning \n";
                std::cin >> toInsert;
                myList.insertAtBegin(toInsert);
                break;
            
            case '3':
                std::cout << "enter a number to Insert at the End \n";
                std::cin >> toInsert;
                myList.insertAtEnd(toInsert);
                break;

            case '4':
                std::cout << "Printing using Forward Iterator\n";
                myList.setForwardIterator();
                if (myList.forwardIteratorActive()){
                    while(myList.getForwardIterator(toPrint)){
                        std::cout << toPrint << ", ";
                        myList.moveForwardIterator();
                    }
                }
                std::cout << "Forward Iterator Print Done!\n";
                break;

             case '5':
                std::cout << "Printing using Backward Iterator\n";
                myList.setBackwardIterator();
                if (myList.backwardIteratorActive()){
                    while(myList.getBackwardIterator(toPrint)){
                        std::cout << toPrint << ", ";
                        myList.moveBackwardIterator();
                    }
                }
                std::cout << "Backward Iterator Print Done!\n";
                break;


            case '6':
                list2copy = myList;
                confirmListAreSame(myList, list2copy);
                break;
            
            case '7':
                list2copy = myList;
                list2copy.insertAtBegin(9);
                confirmListAreSame(myList, list2copy);
                break;
            

        }
        



    }while (command != 'q');






    return 0;
}



void printMenu(){
    std::cout << "Enter a command to perform operations on your Doubly Linked List\n";
    std::cout << "1. To print the the list\n";
    std::cout << "2. To insert an element at the beginning.\n";
    std::cout << "3.To insert an element at the end.\n";
    std::cout << "4. To print using forward iterator\n";
    std::cout << "5. To print using backward iterator\n";
    std::cout << "6. To test if it is equal with another list (should be)\n";
    std::cout << "7. To test if it is equal with another list (shouldn't be)\n";
    std::cout << "q. to quit\n\n";
}


void confirmListAreSame(dLList<int> l1, dLList<int> l2){
    if (l1 == l2){
        std::cout << "Both lists are the same\n";
    }
    else{
        std::cout << "the two lists are not the same\n";
    }
}