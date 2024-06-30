# LargeInt
### Summary
This is a C++ implementation of a LargeInt class written by myself as part of my honors project for Data Structures and Algorithms. It is used to handle very large integers that cannot be represented by the standard integer types (like int, long, or even long long) due to their limited size. This class is especially useful in applications where arithmetic operations on extremely large numbers are required, such as in cryptography, scientific computing, and certain types of simulations or numerical methods. 

### Implementaion
The LargeInt class is imlplemented as Doubly Linked List. Each node in the linked list contains a digit in the LargeInt.  Because it uses linked lists, the only liitations on how large your LargeInt can be is physical limitation of your computer’s memory.

### Usage
You can test implemenation using the Menu Driven program in main.cpp. To compile and run the code (on Mac and UNIX systems), follow the steps below:
1. #### Clone this Repository to your machine using the command:
```
git clone <repositiry_url>
```

2. #### Copile the source code into object files using the commands:
```
g++ -c main.cpp DLlist.cpp LargeInt.cpp
//OR
clang -c main.cpp DLlist.cpp LargeInt.cpp
```
This will generate 3 object files: main.o, DLlist.o LargeInt.o

3. Link the object files into an executable:
```
g++ -o <name_of_executable> main.o DLlist.o LargeInt.o
```
This will give you an executable with the name you specified

4. Run the program:
```
./<name_of_exececutable>
```
