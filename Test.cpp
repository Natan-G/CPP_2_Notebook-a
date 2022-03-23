#include "doctest.h"
#include "Notebook.hpp"
#include <iostream>
#include <string>
#include <algorithm>

using namespace ariel;
using namespace std;


string custom_string(int length){
    string s;
    for(int i=0 ; i<length ; i++){
        s+="!";
    }
return s;
}



TEST_CASE("check write function and write after erase"){
    Notebook test_note;

    string s_101 = custom_string(101);
    string s_100 = custom_string(100);
    string s_50 = custom_string(50);
    string s_25 = custom_string(25);
    string s_1 = custom_string(1);
    
    
    //write over the end of Horizontal line
    CHECK_THROWS(test_note.write(0 , 0 , 0 , Direction::Horizontal ,s_101));
    CHECK_THROWS(test_note.write(27 , 32 , 80 , Direction::Horizontal ,s_25));
    CHECK_THROWS(test_note.write(27 , 202 , 302 , Direction::Horizontal ,s_101));
    CHECK_THROWS(test_note.write(1, 2, 100, Direction::Horizontal, s_1 ));
    
    
    //good inputs Horizontal write
    CHECK_NOTHROW(test_note.write(0 , 0 , 0 , Direction::Horizontal ,s_25));
    CHECK_NOTHROW(test_note.write(0 , 0 , 25 , Direction::Horizontal ,s_50));
    CHECK_NOTHROW(test_note.write(0 , 0 , 75 , Direction::Horizontal ,s_25));
    CHECK_NOTHROW(test_note.write(0 , 1 , 0 , Direction::Horizontal , s_100));


    //good inputs Vertical write
    CHECK_NOTHROW(test_note.write(1 , 0 , 0 , Direction::Vertical ,s_25));
    CHECK_NOTHROW(test_note.write(1 , 0 , 1 , Direction::Vertical , s_101));
  
    //write over written Horizontal line
    CHECK_THROWS(test_note.write(0 , 0 , 0 , Direction::Horizontal ,s_25));
    CHECK_THROWS(test_note.write(0 , 0 , 75 , Direction::Horizontal ,s_25));
    CHECK_THROWS(test_note.write(0 , 0 , 40 , Direction::Horizontal ,s_25));
    CHECK_THROWS(test_note.write(0 , 1 , 0 , Direction::Horizontal ,s_100));

    //write over written Verical line 
    CHECK_THROWS(test_note.write(1 , 0 , 0 , Direction::Vertical ,s_25));
    CHECK_THROWS(test_note.write(1 , 24 , 0 , Direction::Vertical ,s_25));
    CHECK_THROWS(test_note.write(1 , 4 , 1 , Direction::Vertical ,s_100));


    //write over written Verical and Horizontal lines , basic Ver and Hor tests are in pages 0,1
    CHECK_THROWS(test_note.write(0 , 0 , 0 , Direction::Vertical ,s_25));
    CHECK_THROWS(test_note.write(0 ,1 ,22 , Direction::Vertical ,s_50));
    CHECK_THROWS(test_note.write(1 , 100 , 1 , Direction::Horizontal ,s_25));
    CHECK_THROWS(test_note.write(1 , 11 , 0 , Direction::Horizontal ,s_25));

    //write after erase function
    test_note.erase(0 , 0 , 0 , Direction::Horizontal , 1);
    CHECK_THROWS(test_note.write(0 , 0 , 0 , Direction::Horizontal , s_1));
    test_note.erase(1 , 0 , 0 , Direction::Vertical , 23);
    CHECK_THROWS(test_note.write(1 , 0 , 0 , Direction::Vertical , s_1));
    test_note.erase(1 , 55 , 1 , Direction::Vertical , 77);
    CHECK_THROWS(test_note.write(1 , 67 , 1 , Direction::Vertical , s_50));
}

TEST_CASE("read function and read after erase function"){
    Notebook test_note;


    string s_50 = custom_string(50);
    
    string s_5 = custom_string(5);

    test_note.write(0 , 0 , 0 , Direction::Horizontal , s_50);
    test_note.write(0 , 1 , 0 , Direction::Vertical , s_50);
    test_note.write(1 , 0 , 0 , Direction::Horizontal , s_5);
    test_note.write(1 , 1 , 0 , Direction::Vertical , s_5);


    //read horizontal lines
    CHECK_NOTHROW(test_note.read(0 , 0 , 0 , Direction::Horizontal , 50));//whole word
    CHECK_NOTHROW(test_note.read(0 , 0 , 3 , Direction::Horizontal , 27));//part of word
    CHECK_THROWS(test_note.read(0 , 0 , 77 , Direction::Horizontal , 50));//read over col 100
    
    
    //read vertical lines
    CHECK_NOTHROW(test_note.read(0 , 1 , 0 , Direction::Vertical , 50));//whole word
    CHECK_NOTHROW(test_note.read(0 , 22 , 0 , Direction::Vertical , 12));//part of word
    
    //good input read
    CHECK(test_note.read(2,14,22 , Direction::Horizontal , 3) == "___");
    CHECK(test_note.read(1 , 0 , 0 , Direction::Horizontal , 5) == "!!!!!");
    CHECK(test_note.read(1 , 1 , 0 , Direction::Vertical , 5) == "!!!!!");

    //read after erase
    test_note.erase(0 , 0 , 0 , Direction::Horizontal , 3);
    CHECK(test_note.read(0 , 0 , 0 , Direction::Horizontal , 3)=="~~~");
    
    test_note.erase(0 , 3 , 0 , Direction::Vertical , 6);
    CHECK(test_note.read(0 , 4 , 0 , Direction::Vertical , 2)=="~~");

    test_note.erase(1 , 0 , 0 , Direction::Horizontal , 5);
    CHECK(test_note.read(1, 0 , 0 , Direction::Horizontal , 1)=="~");
    
    test_note.erase(1 , 1 , 0 , Direction::Vertical , 5);
    CHECK(test_note.read(1 , 1 , 0 , Direction::Vertical , 5) == "~~~~~");
}




