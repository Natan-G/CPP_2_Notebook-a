#pragma once
#include <string>
#include <iostream>
#include "Direction.hpp"
using namespace std;

namespace ariel{
    
   
    class Notebook
    {
   
        public:
        
            void write(unsigned int page ,unsigned int row ,unsigned int col , Direction dir , string const & input);
            static string read(unsigned int page ,unsigned int row ,unsigned int col , Direction dir , unsigned int length);
            void erase(unsigned int page , unsigned int row, unsigned int col, Direction dir, unsigned int lenght);
            void show(unsigned int page);


    };
    
    
    


}