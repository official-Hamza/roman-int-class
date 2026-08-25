#include <vector>
#include <string>
#include <sstream>
#include <iostream>
#include <cctype>
#include <stdexcept>
#include "roman_int_class.h"

// error() simply disguises throws
void error(const std::string&);
void error(const std::string&, int);
void error(const std::string&, const std::string&);

//Helper Functions

bool has_valid_roman_chars(const std::string& roman_num){
    std::vector<char> core_nums={'i','v','x','l','c','d','m'};
    
    for(int x=0;x<roman_num.size();++x){
        bool found_core_num=false;//refresh for each roman_num
        if(!isalpha(roman_num[x])) error("Roman numeral contained non-alphabet, ",roman_num[x]);
        //above statement is to prevent unexpected implicit conversions if any
        for(int y=0;y<core_nums.size();++y){
            if(roman_num[x]==core_nums[y]){
                found_core_num=true;
                break;//found, move to next char in roman_num
            }
            if(y==core_nums.size()-1&&found_core_num==false){//last core_num and character still not found
                return false;//not a valid roman numeral
            }
        }
    }
    return true;
}

bool has_valid_repetition(const std::string& roman_num){
    if(roman_num.size()==1) return true;

    char previous=roman_num[0];
    char current=' ';
    int count=1;
    for(int x=1;x<roman_num.size();++x){
        current=roman_num[x];
        if(current==previous&&(current=='l'||current=='v'||
            current=='d')){
                return false;//is a repetition but not a valid one
        }
        if(current==previous){//is a valid repetition
            ++count;
            previous=current;
        }
        else{//not a repetition
            count=1;//current value that is not equal to previous now has a count of 1
            previous=current;
        }
        if(count>3) return false;//valid repetition but exceeds limit

    }
    return true;
}

int core_roman_val(char roman_ch){
    switch (roman_ch)
    {
    case 'i':return 1;
    case 'v':return 5;
    case 'x':return 10;
    case 'l':return 50;
    case 'c':return 100;
    case 'd':return 500;
    case 'm':return 1000;
    default:
        return -1;
    }
}

int core_roman_val(const std::string& roman_chs){
    if(roman_chs.size()<2) error("wrong function used or invalid roman numeral ",roman_chs);
    if(roman_chs=="iv") return 4;
    else if(roman_chs=="ix") return 9;
    else if(roman_chs=="xl") return 40;
    else if(roman_chs=="xc") return 90;
    else if(roman_chs=="cd") return 400;
    else if(roman_chs=="cm") return 900;
    else{
        error("core_roman_val(), invalid subtractive pair ",roman_chs);
    }
    return -1;
}

bool has_valid_order(const std::string& roman_num){
    if(roman_num.size()==1) return true;
    std::vector<std::string> subtractive_pairs{"iv","ix","xl","xc","cd","cm"};
    std::string previous;
    previous+=roman_num[0];
    int previous_val=core_roman_val(previous[0]);
    std::string overall_previous=previous;//for ensuring overall descending progression
    int overall_previous_val=previous_val;//value of overall_previous
    char current=' ';
    int current_val=0;
    std::string intermediate_pair;

    for(int y=1;y<roman_num.size();++y){
        current=roman_num[y];
        current_val=core_roman_val(current);
        bool is_valid_inter_order=false;
        if(previous_val<current_val){
            intermediate_pair+=(previous+current);//previous before current
            for(std::string& num:subtractive_pairs){
                if(num==intermediate_pair){
                    if((overall_previous_val<core_roman_val(intermediate_pair)) && y>1)//y>1 means the subtractive pair is not starting the Roman numeral (eg. IV)
                        return false;//take IIV as an example, I=overall_previous and IV=subtractive pair, this breaks the descending order
                    is_valid_inter_order=true;
                    previous=intermediate_pair;//subtractive pair is treated as a single character
                    previous_val=core_roman_val(previous);
                    overall_previous=previous;//subtractive pair becomes overall previous
                    overall_previous_val=previous_val;
                    intermediate_pair="";//reset 
                    break;
                }
            }
            if(!is_valid_inter_order) return false;//invalid subtractive pair
        }
        else{//valid descending progression
            previous.clear();//make room for new value
            previous+=current;
            previous_val=core_roman_val(previous[0]);
            if(y<roman_num.size()-1&&
               core_roman_val(current)>=core_roman_val(roman_num[y+1])){//not a subtractive pair
                overall_previous.clear();
                overall_previous+=current;
                overall_previous_val=core_roman_val(overall_previous[0]);
               }
               //else maintain the overall previous value
        }      
    }
    return true;
}

void split_roman_numeral(const std::string& roman_num,std::vector<std::string>& slots){
    std::string thousands, hundreds, tens, ones;

    for(int y=0;y<roman_num.size();++y){//previous functions have already ensured descending order
        char current=roman_num[y];
        char next_chr=' ';
        int comparative_val=0;
        std::string comparative_ch;
        
        if(y<roman_num.size()-1){//not the last char in roman_num
            next_chr=roman_num[y+1];
            if(core_roman_val(current)<core_roman_val(next_chr)){
                std::string temp;
                temp+=current;//adding two chars returns int
                temp+=next_chr;
                comparative_ch=temp;
                comparative_val=core_roman_val(temp);
                ++y;//move position by one
            }
            else{//not last char but descends normally (not subtractive pair)
                comparative_ch+=current;
                comparative_val=core_roman_val(current);   
            }
        }
        else{//last char
            comparative_ch+=current;
            comparative_val=core_roman_val(current);
        }

        if(comparative_val>=1000&&comparative_val<=3000){
            thousands+=comparative_ch;
        }
        else if(comparative_val>=100&&comparative_val<=900){
            hundreds+=comparative_ch;
        }
        else if(comparative_val>=10&&comparative_val<=90){
            tens+=comparative_ch;
        }
        else if(comparative_val>=1&&comparative_val<=9){
            ones+=comparative_ch;
        }
    }
    
    std::vector<std::string> number_places{thousands,hundreds,tens,ones};
    for(std::string& place:number_places)//pass by reference to avoid copying
        if(empty(place)) place="null";
    
    slots=number_places;
    
}

bool is_canonically_valid(const std::string& roman_num){
    if(roman_num.size()==1) return true;
    //canonical structure, all standard roman numerals should be composed of the ff
    std::vector<std::string> thousands{"null","m","mm","mmm"};
    std::vector<std::string> hundreds{"null","c","cc","ccc","cd","d","dc","dcc","dccc","cm"};
    std::vector<std::string> tens{"null","x","xx","xxx","xl","l","lx","lxx","lxxx","xc"};
    std::vector<std::string> ones{"null","i","ii","iii","iv","v","vi","vii","viii","ix"};

    std::vector<std::vector<std::string>> decimal_places{thousands,hundreds,tens,ones};
    std::vector<std::string> slots;
    split_roman_numeral(roman_num,slots);
    
    for(int x=0;x<decimal_places.size();++x){
        bool found_value=false;
        for(std::string& current_place:decimal_places[x]){
            if(current_place==slots[x]){
                found_value=true;
                break;
            }
        }
        if(!found_value) return false;
    }
    
    return true;
}

int roman_num_to_int(const std::string& roman_num){
    if(roman_num.size()==1) return core_roman_val(roman_num[0]);
    char current=' ';
    int numeral_as_num=0;
    for(int x=0;x<roman_num.size();++x){
        current=roman_num[x];
        if(x==roman_num.size()-1)//last char
            return numeral_as_num+core_roman_val(current);
        if(x<roman_num.size()-1){
            char next_char=roman_num[x+1];
            if(core_roman_val(current)<core_roman_val(next_char)){
                numeral_as_num-=core_roman_val(current);
            }
            else{
                numeral_as_num+=core_roman_val(current);
            }
        }
    }
    return numeral_as_num;
}

std::ostream& operator<<(std::ostream& os,const Roman_int& r){
    return os<<r.as_int();//as_int() is an inline member function in Roman_int
}
std::istream& operator>>(std::istream& is,Roman_int& r){
    std::string roman_num;
    is>>roman_num;
    if(!is){
        if(is.bad()){
            error("Something bad happened, program terminated!");
        }
        if(is.fail()){
            is.clear();
            is.unget();
            is.clear(std::ios::failbit);
        }
        return is;
    }

    Roman_int temp{roman_num};
    r=temp;
    return is;
}

void error(const std::string& s)	// error() simply disguises throws
{
    throw std::runtime_error(s);
}

void error(const std::string& s, int i)
{
    std::ostringstream os;
    os << s << ": " << i;
    error(os.str());
}

void error(const std::string& s, const std::string& s2)
{
    error(s + s2);
}

//Member Functions

bool Roman_int::is_valid(const std::string& roman_num){
    if(empty(roman_num)) return false;
    if(!has_valid_roman_chars(roman_num)) return false;
    if(!has_valid_repetition(roman_num)) return false;
    if(!has_valid_order(roman_num)) return false;
    if(!is_canonically_valid(roman_num)) return false;

    return true;
}

Roman_int::Roman_int(const std::string& roman_num){
    std::string new_roman_num;//store lowercase version
    for(char i:roman_num) new_roman_num+=tolower(i);
    if(!is_valid(new_roman_num)) throw Bad_roman_numeral{};
    num=roman_num_to_int(new_roman_num);
}


