#include "roman_int_class.h"

int main()
{
    try
    {
        //Add more test cases
        Roman_int test{"i"};
        std::cout<<test<<'\n';
        std::cout << __cplusplus << '\n';
        Roman_int wrong{"vl"};
        /*
        Some Invalid Roman values
        Roman_int roman_complx_4{"VL"};
        Roman_int roman_complx_5{"iiv"};
        Roman_int roman_complx_6{"iviv"};

        std::cout<<roman_complx_4<<'\n'; 
        std::cout<<roman_complx_5<<'\n'; 
        std::cout<<roman_complx_6<<'\n';
        */

        /*
        //Provide values from terminal
        Roman_int custom_num{"i"};//Default value for Roman_int does not exist, hence you must provide a valid variable first
        std::cout<<"Provide a roman numeral\n";
        std::cin>>custom_num;
        std::cout<<custom_num<<'\n';
        */
    }
    catch(Roman_int::Bad_roman_numeral)
    {
        std::cerr << "Invalid Roman numeral creation attempt!"<< '\n';
    }
    
}