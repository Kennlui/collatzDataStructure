//  main.cpp
//  Collatz Sequences Experimental Data Structure
//  Testing Component
//  Created by Kenn Lui on 2021-12-17.
//  kenn_lui@sfu.ca

#include <iostream>
#include "collatz.h"
int main(int argc, const char * argv[])
{
    std::cout << "Testing has started.";
    
    const int TARGET = 50;
    
    OmniNodes::OmniNode::hideDetail();
    CollatzWorkBook wb(TARGET);
    std::cout << "\nUNIQUE SEQUENCES OR BRANCHES, 1 TO " << TARGET;
    wb.printNodes();
    
    std::cout << "\nTesting is complete.";
    return 0;
}
