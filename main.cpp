#include "largeInt.hpp"

/***************************************************************/
/* Programmer:Kalelo Dukuray                                   */
/* Date:  December 14, 2023                                    */
/* Purpose: LargeInt Calculator App in menu driven  program    */
/*                                                             */
/* Input: user’s choice of arithmetic Expression               */
/* Output: Result of user’s expresiion.                        */ 
/***************************************************************/

void printMenu();
int main(){
    //variables needed for menu-driven program
    int command;
    largeInt myInt1;
    largeInt myInt2;
    largeInt result;
    //event loop
    do{
        printMenu();
        std::cin >> command;

        while (command < 1 || command > 6){
            std::cout << "Please Enter a valid command!\n";
            std::cin >> command;
        }
        if (command != 6){
            std::cout << "Enter the first number: ";
            std::cin >> myInt1;
            std::cout << "Enter the second number: ";
            std::cin >> myInt2;
        }
    
        switch(command){
            case 1:
                result = myInt1 + myInt2;
                break;

            case 2:
                result = myInt1 - myInt2;
                break;

            case 3:
                result = myInt1 * myInt2;
                break;

            case 4:
                result = myInt1 / myInt2;
                break;
            case 5:
                result = myInt1 % myInt2;
                break;
        }

        if (command != 6){
            std::cout << "\nThe result of your arithmetic operation is: " << result << std::endl << std::endl;
            std::cout << "Press Enter to continue...";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cin.get();
        }
    }while(command != 6);

    std::cout << "\033cYou have quit the program!";
    return 0;
}

//prints the menu
void printMenu(){
    std::cout << "\033cThis is a menu driven Large Int Arithmetic Applcication where we can perform operation on integers";
    std::cout << "of unlimited size.\n";
    std::cout << "Pick an Operation:\n";
    std::cout << "1. For Addition\n";
    std::cout << "2. For Subtraction\n";
    std::cout << "3. For Multiplication\n";
    std::cout << "4. For Division (Division involving 0 is undefined behavior in C++, will crash progam as it does with normal integers)\n";
    std::cout << "5. For Modulos (Remainder after division)\n";
    std::cout << "6. To Quit\n";
}