#ifndef ROMAN_INT_H
#define ROMAN_INT_H
#include <string>
#include <iostream>

class Roman_int{
public:
    Roman_int(const std::string&);
    bool is_valid(const std::string&);
    class Bad_roman_numeral{};

    int as_int() const{return num;}
private:
    int num=0;
};

std::ostream& operator<<(std::ostream&,const Roman_int&);
std::istream& operator>>(std::istream&,Roman_int&);
#endif