//
//  main.cpp
//  UTF-8_Vector
//
//  Created by nash on 9/23/15.
//  Copyright 2015 iBean_Software. All rights reserved.
//

#include <iostream>
#include "Uchar.h"
#include <bitset>

void display_bits(const Uchar& uc)
{
    std::bitset<8>  bs;
    std::cout << uc.size()<<std::endl;
    for (size_t i=0; i<uc.size(); ++i) 
    {   bs=uc.uc_v[i];   std::cout << bs << ' ';}
    std::cout << std::endl; 
};

int main (int argc, const char * argv[])
{
    Uchar  uc(0x0391);//Α
    display_bits(uc);
    
    uc=0x00a9;//©
    display_bits(uc);

    uc=0x2c02;
    display_bits(uc);
    
    uc=0x13a1;
    display_bits(uc);
    
    uc=0x1d230;//
    display_bits(uc);

    uc=0x03a9;//Ω
    display_bits(uc);
    
    return 0;
}



