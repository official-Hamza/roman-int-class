## TABLE OF CONTENTS

- [WHAT IT IS](#what-it-is)
    - [Canonically valid](#canonically-valid)
    - [Limitations](#limitations)
- [WHY THIS PROGRAM?](#why-this-program)
- [HOW IT WORKS](#how-it-works)
    - [is_valid()](#is_valid)
    - [core_roman_val()](#core_roman_val)
- [HOW TO RUN IT](#how-to-run-it)
    - [Prerequisite(s)](#prerequisites)
    - [Structure](#structure)
    - [Build and Run](#build-and-run)



## WHAT IT IS

A Roman numeral class that accepts a canonically valid Roman numeral, converts it to an integer, and stores the value as an int.

#### **Canonically valid?**

There are many ways of representing Roman numerals.
Canonical implies a standard and modern way of writing Roman numerals.

Roman numerals are split into 4 decimal places, with each place having a limited number of valid notations [see is_valid()](#is_valid);

* Thousands

* Hundreds

* Tens

* Ones/Units

#### **Limitations**

1. The standard form that this class supports consists of numbers 1 (I) to 3999 (MMMCMXCIX).

2. It does not support negative numbers, even for numbers in the valid range (1 to 3999).

3. It does not support fractions.

## WHY THIS PROGRAM

This class is an exercise from _Programming: Principles and Practice using C++, Third Edition (PPP3)_ by Bjarne Stroustrup.

After not being able to find a version that establishes an invariant for the canonical structure online, I decided to get my version working and make it free for anyone in a similar situation or for someone who simply wants to understand how Roman numerals are structured.

_But first, I had to understand it myself._

## HOW IT WORKS
```
class Roman_int{
public:
    Roman_int(const std::string&);
    bool is_valid(const std::string&);
    class Bad_roman_numeral{};

    int as_int() const{return num;}
private:
    int num=0;
};
```
The operator>> and operator<< have been overloaded for _Roman_int_.

The constructor takes a string which is then passed to _is_valid()_. The class is **not** case-sensitive (i.e. vii == VII == vII).

_bool is_valid()_ checks the string against some functions which together constitute an invariant for the class. If the string is not a valid Roman numeral, an exception is thrown. Otherwise, the numeral is converted to an int and stored in _num_.

_int as_int()_ returns the value of the numeral stored by Roman_int.

### _core_roman_val()_

_int core_roman_val(char)_ -returns the value of a valid Roman numeral character\
_int core_roman_val(const string&)_ -returns the value of a valid subtractive pair

**Why Overload core_roman_val()**

This makes the action more explicit. When core_roman_val(const string&) is used, it is clear that the argument is more likely to be a subtractive pair rather than a single Roman numeral. Interchanging them would result in an error.  

### _is_valid()_

A standard Roman numeral should follow the following rules.

* It should consist of valid Roman numeral characters (i.e. I=1, V=5, X=10, L=50, C=100, D=500, M=1000). Unlike Arabic numerals, there is no notation for zero. The word "nulla" referred to zero.

* The individual characters that make up a Roman numeral are generally in descending order from left to right.\
Moving from a character with a bigger value to a character with a smaller value or equal value signifies an addition (eg. II==1+1==2).\
Moving from a character with a smaller value to a character with a bigger value signifies subtraction (eg. IV==5-1==4, IX==10-1==9). These are called subtractive pairs and only a few of them are allowed.

* Only the characters I, X, C and M can be repeated and the maximum number of repetitions is 3.

* A Roman numeral is made up of decimal places, with each decimal place having a fixed number of valid characters.\
```
    vector<string> thousands{"null","m","mm","mmm"};
    vector<string> hundreds{"null","c","cc","ccc","cd","d","dc","dcc","dccc","cm"};
    vector<string> tens{"null","x","xx","xxx","xl","l","lx","lxx","lxxx","xc"};
    vector<string> ones{"null","i","ii","iii","iv","v","vi","vii","viii","ix"};
```
**Helper functions that make up _is_valid()_**
```
bool has_valid_roman_chars(const string&);
bool has_valid_repetition(const string&);
bool has_valid_order(const string&);
bool is_canonically_valid(const string&);
```
1. _has_valid_roman_chars()_ - this function checks if the string contains only valid Roman characters. For Roman numerals containing only one character, this function is all you need. All other functions immediately return true if _string.size()==1_.

2. _has_valid_repetition()_ -checks if the string contains only valid repetitions.

3. _has_valid_order()_ -checks for valid overall descending progression. Whenever a subtractive pair is encountered, its validity is checked and it is treated as a single character. This ensures that the overall progression is descending.

4. _is_canonically_valid()_ -uses the _split_roman_numeral()_ to split the Roman numeral into its respective decimal places. "null" is used to represent an empty decimal place. Each decimal place value is checked against the vector of valid characters for that decimal place.\
For example,\
"mix" => {"m","null","null","ix"}//converts to 1009\
All decimal place values are valid; hence, the function returns true.

## HOW TO RUN IT

### Prerequisite(s)

C++ version 17 and above is recommended.

### Structure

```
roman_int_class/
├── roman_int_class.h
├── roman_int_class.cpp
├── main.cpp
└── README.md
```
_roman_int_class_ -contains the class interface\
_roman_int_class.cpp_ -contains member and helper function definitions\
_main.cpp_ - entry point for creating objects, testing and debugging

### Build and run

```
//terminal commands
g++ main.cpp roman_int_class.cpp -o result

result.exe
```
_Kindly check your terminal's build and run commands_