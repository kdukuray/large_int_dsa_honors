#include "largeInt.hpp"

//default constructor
largeInt::largeInt(){
    sign = true;
}
//constructor with string
largeInt::largeInt(std::string toConsume){
    stringToLargeInt(toConsume);
}

//returns true if number is poisitive
bool largeInt::isPositive() const{
    return sign;
}

// copy constructor
largeInt::largeInt(const largeInt& other){
    copy(other);
    removeleadingZeros();

}

//overloaded equal operator
const largeInt& largeInt::operator=(const largeInt& other){
    if (this != &other){
        destroy();
        copy(other);
        removeleadingZeros();
    }
    return *this;
}

// overloaded equal operator for string 
largeInt& largeInt::operator=(std::string toConsume){
    destroy();
    stringToLargeInt(toConsume);
    return *this;
}

//takes in a numeric string and stores in largeint
void largeInt::stringToLargeInt(std::string toConsume){
     std::string numeric_value;
    int i = 0;
    //if the first charcter in the string is a '-', the number is negative
    if (toConsume[i] == '-'){
        sign = false;
        i++;
    }
    //if it is not a '-', the number is positive.
    else{
        sign = true;
    }
    for (; i < toConsume.length(); i++){
        numeric_value = toConsume[i];
        num_content.insertAtBegin(stoi(numeric_value));
    }
    removeleadingZeros();
}

//overloaded plus operator
largeInt largeInt::operator+(largeInt& other){
    largeInt result;
    if (this->sign == other.sign){
        result = this->plus(other);
        result.sign = this->sign;
    }
    else if (this->absGreaterThanOrEqual(other)){
        result = this->minus(other);
        if (this->absequal(other)){
            result.sign = true;
        }
        else{
            result.sign = this->sign;
        }
    }
    else{
        result = other.minus(*this);
        result.sign = other.sign;
    }
    return result;

}

//overloaded minus operator
//addition and subtract are the same operation
//subtraction is merely adding the negative
//this case has already been taken care of in the addition function so no need to re-invent the wheel
largeInt largeInt::operator-( largeInt& other){
    //if either numbers has a negative sign, additon will cover the case
    //only case in which they differ is when both largeInts are positive, separate this into a special case
    largeInt result;
    //if  other is negative (or they both are negative), the subtration turns to addition, keep sign of greater value
    if (!other.sign){
        largeInt *tempLargeint = new largeInt();
        tempLargeint->operator=(other);
        tempLargeint->sign = true;
        result = this->operator+(*tempLargeint);
        delete tempLargeint;
    }
    //else if this is negative and other is positive, add and keep sign of the greater integer
    else if (!this->sign){
        result = this->operator+(other);
    }
    //if both signs are positive,
    else{
        //if this is larger, subtract and the result is positive, this holds even for when they are eqaul because i want 0 to be positive
        if (this->operator>=(other)){
            result = this->minus(other);
            result.sign = true;
        }
        //else, other is larger, therefore the reslt should be negative 
        else{
            result = other.minus(*this);
            result.sign = false;
        }
    }
    return result;
}

//overloaded mulptiplication operator
largeInt largeInt::operator*(largeInt& other){
    largeInt result;
    result = this->multiply(other);
    if (this->sign == other.sign){
        result.sign = true;
    }
    else{
        result.sign = false;
    }
    return result;
}
//overloaded division operator
largeInt largeInt::operator/(largeInt& other){
    largeInt result = this->divide(other);
    //if this's absolute value is less than others, the return is zero and zero is always positive
    if (this->absLessThan(other)){
        result.sign = true;
    }
    //else if the return value is not zero and both largeInts have the same size
    else if (this->sign == other.sign){
        result.sign = true;
    }
    //if they have different sings and the result isnt 0, then the result is negative
    else{
        result.sign = false;
    }
    return result;
} 

//Ths function is repsonsible for the division of absolute values of numbers
largeInt largeInt::divide(largeInt& other){
    largeInt result("0");
    if (this->absLessThan(other)){
        return result;
    }
    while ((other.multiply(result)).absLessThanOrEqual(*this)){
        result.operator++();
    }
    result.operator--();
    return result;
}

//adds one to the large int
largeInt& largeInt::operator++(){
    largeInt toAdd("1");
    this->operator= (this->operator+(toAdd));
    return *this;
}

//subtracts one to the large int
largeInt& largeInt::operator--(){
   largeInt toSubtract("1");
    this->operator= (this->operator-(toSubtract));
    return *this;
}

//Ths function is repsonsible for the addition of absolute values of Integers
largeInt largeInt::plus(largeInt& other){
    largeInt result;
    int carry = 0;
    int arithmetic_result;
    int operand1;
    int operand2;

    this->num_content.setForwardIterator();
    other.num_content.setForwardIterator();

    //While both large numbers being added still have digits
    while(num_content.forwardIteratorActive() && other.num_content.forwardIteratorActive()){
    //extract a digit from each
        num_content.getForwardIterator(operand1);
        other.num_content.getForwardIterator(operand2);

    //add the digits together to get the arithmetic result, also add number that carried over
        arithmetic_result = operand1 + operand2 + carry;
        carry = 0;

    //if the resulting number is equal to or greater than 10, it should carry over as well and be subtracted from arithmetic result
        if (arithmetic_result >= 10){
            carry = 1;
            arithmetic_result %= 10;
        }

    // the final arithmetic result is to be added at the end result.
        result.num_content.insertAtEnd(arithmetic_result);

        num_content.moveForwardIterator();
        other.num_content.moveForwardIterator();
    }

    //if any number is not exhausted in the process, bring it all down into the result
    while (num_content.forwardIteratorActive()){
        num_content.getForwardIterator(operand1);
        operand1 += carry;
        carry = 0;
        if (operand1 >= 10){
            carry = 1;
            operand1 %= 10;
        }
        result.num_content.insertAtEnd(operand1);
        num_content.moveForwardIterator();
    }

    while (other.num_content.forwardIteratorActive()){
        other.num_content.getForwardIterator(operand2);
        operand2 += carry;
        carry = 0;
        if (operand2 >= 10){
            carry = 1;
            operand2 %= 10;
        }
        result.num_content.insertAtEnd(operand2);
        other.num_content.moveForwardIterator();
    }

    if (carry == 1){
        result.num_content.insertAtEnd(1);
    }
    return result;
}

//Ths function is repsonsible for the minus of absolute values of numbers
largeInt largeInt::minus(largeInt& other){
    largeInt result;

    int negative_carry = 0;
    int operand1;
    int operand2;
    int arithmetic_result;

    num_content.setForwardIterator();
    other.num_content.setForwardIterator();

    while (num_content.forwardIteratorActive() && other.num_content.forwardIteratorActive()){
        num_content.getForwardIterator(operand1);
        other.num_content.getForwardIterator(operand2);

        operand1 -= negative_carry;
        negative_carry = 0;

        if (operand1 < operand2){
            operand1 += 10;
            negative_carry = 1;
        }

        arithmetic_result = operand1 - operand2;
        result.num_content.insertAtEnd(arithmetic_result);

        num_content.moveForwardIterator();
        other.num_content.moveForwardIterator();
    }


    while (num_content.forwardIteratorActive()){
        num_content.getForwardIterator(operand1);
        if (operand1 == 0 && negative_carry > 0){
            operand1 += 10;
            operand1 -= negative_carry;
        }
        else{
            operand1 -= negative_carry;
            negative_carry = 0;
        }
        result.num_content.insertAtEnd(operand1);
        
        num_content.moveForwardIterator();
    }
    return result;
}

//Ths function is repsonsible for the multiplication of absolute values of numbers
largeInt largeInt::multiply(largeInt& other){
    largeInt result;
    result.num_content.insertAtEnd(0);

    largeInt intermediate_result;

    int carry = 0;
    int decimal_places = 0;
    int operand1;
    int operand2;
    int arithmetic_result;

    num_content.setForwardIterator();
    other.num_content.setForwardIterator();


    while (other.num_content.forwardIteratorActive()){
        other.num_content.getForwardIterator(operand1);
        for (int i = 0; i < decimal_places; i++){
                intermediate_result.num_content.insertAtEnd(0);
            }
        num_content.setForwardIterator();
        while(num_content.forwardIteratorActive()){
            num_content.getForwardIterator(operand2);
            arithmetic_result = operand1 * operand2;
            arithmetic_result += carry;
            carry = 0;
            if (arithmetic_result >= 10){
                carry = arithmetic_result / 10;
                arithmetic_result %= 10;
            }
            intermediate_result.num_content.insertAtEnd(arithmetic_result);
            num_content.moveForwardIterator();
        }

        if (carry > 0){
            intermediate_result.num_content.insertAtEnd(carry);
            carry = 0; 
        }
        decimal_places++;
        result = result.plus(intermediate_result);
        intermediate_result.num_content.destroy();
        other.num_content.moveForwardIterator();
    }
    return result;
}

//prints the largeInt (use for development)
void largeInt::printNum(){
    int digit;
    if (!sign){
        std::cout << "-";
    }
    num_content.setBackwardIterator();
    if(num_content.backwardIteratorActive()){
        while(num_content.getBackwardIterator(digit)){
            std::cout << digit;
            num_content.moveBackwardIterator();
        }
    }
    std::cout << std::endl;
}

//copy function
void largeInt::copy(const largeInt& other){
    this->num_content = other.num_content;
    this->sign = other.sign;
}

//destroy function
void largeInt::destroy(){
    this->num_content.destroy();
}

//overloaded operator== function
bool largeInt::operator==(largeInt& other){
    return this->num_content == other.num_content && this->sign == other.sign;

}
//returns true if the absolute values of the largeInt's are equal
bool largeInt::absequal(largeInt& other){
    return this->num_content == other.num_content;
}

//overloaded greater than operator
bool largeInt::operator>(largeInt& other){
//if this is positive 
    if (this->sign){
        //if other is negative or if this is just greater than other (even if other is positive too), return true
        if (!(other.sign) || this->absGreaterThan(other)){
            return true;
        }
        //if other is positive and this isn't greater then other,return false; they are either equal or other is greater
        else{
            return false;
        }
    }
    //else if this is negative
    else{
        //if other is negative too AND this's absolute value is less than other's (making it greater because they are negative), return true
        if (!(other.sign) && this->absLessThan(other)){
            return true;
        }
        //else, other is positive, or other is negative but has absolute value equal to or less than this (making it greater because they are negative)
        else{
            return false;
        }
    }
}

//overloaded greater than or equal to operator
bool largeInt::operator>=(largeInt& other){
    if (this->operator==(other)){
        return true;
    }
    else{
        return this->operator>(other);
    }

}

//overloaded less than operator
bool largeInt::operator<(largeInt& other){
    //if this largeInt is positive
    if (this->sign){
        //if other is also positive and the absolute value of this is less than the absolute value of other, return true
        if (other.sign && this->absLessThan(other)){
            return true;
        }
        //this else only executes if other is negative, making it less than this, or 
        //if both of them are positive BUT this isn't less than other, meaning, they are either equal 
        //or other is outright less than this
        else{
            return false;
        }
    }
    //else, this is negative
    else{
        //if other is positive, this is automatucally less than it.
        if (other.sign){
            return true;
        }
        //else if other is also negative
        else{
            //if this has a greater absolute value and they're both negative, then this is smaller
            if (this->absGreaterThan(other)){
                return true;
            }
            //else if this doesnt have a greater absolute value, then they're either equal or other is smaller (because it has a greater absolute value)
            else{
                return false;
            }
        }
    }

}

//overloaded less than or equal to operator
bool largeInt::operator<=(largeInt& other){
    if (this->operator==(other)){
        return true;
    }
    else{
        return this->operator<(other);
    }

}

//greater than function for absolute values of the largeInts
bool largeInt::absGreaterThan(largeInt& other){
    if (this->getlength() > other.getlength()){
        return true;
    }
    //if the largeInt calling the function has less digigts, it is smaller 
    else if (this->getlength() < other.getlength()){
        return false;
    }
    //if they have the same amount of digits, you must loop through to see which number is larger
    //starting from the leftmost digit, the first largeint with a greater digit is greater
    else {

        num_content.setBackwardIterator();
        other.num_content.setBackwardIterator();

        int current_int_digit;
        int other_int_digit;

        //while we can still extract digits from both largeInts and the digits from each are the same, keep going
        while ((num_content.getBackwardIterator(current_int_digit) && other.num_content.getBackwardIterator(other_int_digit)) &&
        (current_int_digit == other_int_digit)){

            num_content.moveBackwardIterator();
            other.num_content.moveBackwardIterator();

        }


        //the above loop will only break for two reasons, either the numbers are the same so the largeInts were exhuasted
        //or because we encounter a larger digit in one of the two largeInts

        //if the iterator for either largeInt is still active, it means that it wasn't exahusted
        //therefore one largeInt must be larger
        if (num_content.backwardIteratorActive() || other.num_content.backwardIteratorActive()){
            if (current_int_digit > other_int_digit){
                return true;
            }
            else{
                return false;
                }
        }
        //if both went until they were both exhausted, it means, the numbers are the same.
        else{
            return false;
        }
    }
}





//less than function for absolute values of the largeInts
//instead of re-inventing the wheel, the absolute less than function relies on pre-defined functions 
//first we check if the number are equal, if they are, return false
//if not, we've established that the numbers aren't equal, so simply return the inverse of absolute greater than.
bool largeInt::absLessThan(largeInt& other){
    if (num_content == other.num_content){
        return false;
    }
    else{
        return !(this->absGreaterThan(other));
    }
}

//greater than or equal function for absolute values of the largeInts
//instead of re-inventing the wheel, the absolute greater than or equal to function relies on pre-defined functions
//first we check if the number are equal, if they are, return true
//if the're not equal, return the value of absolute greater than
//the reason we can rely on absolute greater than is because it checks and return false if too numbers are
//equal in the last case. This is the only case in which absolute greater than and absolute greater or equal then differ
//by checking the eqaulity first in this function, we make sure the equality case is never checked in absolute greater than function
bool largeInt::absGreaterThanOrEqual(largeInt& other){
    if (num_content == other.num_content){
        return true;
    }
    else{
        return this->absGreaterThan(other);
    }


}

//less than or equal function for absolute values of the largeInt
//same annotation/explanation as the greater than or equal to function
bool largeInt::absLessThanOrEqual(largeInt& other){    
    if (num_content == other.num_content){
        return true;
    }
    else{
        return this->absLessThan(other);
    }
}

//get length of the largeInt (number of digits in it)
int largeInt::getlength() const{
    return this->num_content.getLength();
}

//overloading the stream insertion operator
std::ostream& operator<<(std::ostream& os, largeInt& myInt) {
    if (!myInt.isPositive()){
        os << "-"; 
    }
    int digit;
    myInt.num_content.setBackwardIterator();
    if(myInt.num_content.backwardIteratorActive()){
        while(myInt.num_content.getBackwardIterator(digit)){
            os << digit;
            myInt.num_content.moveBackwardIterator();
        }
    }
    return os;
}

//overloading the stream extraction operator
std::istream& operator>>(std::istream& is, largeInt& myInt){
    std::string toConsume;
    is >> toConsume;
    myInt = toConsume;
    return is;
}

//removes leading zeros from a number
void largeInt::removeleadingZeros(){
    int num;
    this->num_content.setBackwardIterator();
    if (this->num_content.backwardIteratorActive()){
        do{
            this->num_content.getBackwardIterator(num);
            if (num == 0 && this->getlength() > 1){
                this->num_content.moveBackwardIterator();
                this->num_content.deleteLast();
            }   
        }while(this->getlength() > 1 && num == 0);
    }
}
    

//returns the remaineder after division
largeInt largeInt::operator%(largeInt& other){
  largeInt result;
  //how many is the number of times other can go into this
  largeInt how_many = this->operator/(other);
  //highest_multiple is the highest multiple of other that is less than this
  largeInt highest_multiple = how_many * other;
  //result is this minus highest multiple
  result = this->operator-(highest_multiple);
  return result;
}