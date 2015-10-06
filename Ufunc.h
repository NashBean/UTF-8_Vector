//
//  Ufunc.h
//
//
//  Created by nash on 9/28/15.
//  Copyright 2015 iBean Software.
//
//  Distributed under the Apache License, Version 2.0.
//  See the accompanying file LICENSE or http://www.apache.org/licenses/LICENSE-2.0.html
//

#ifndef iBS_Ufunc_h//  Unicode and UTF-8 Functions.
#define iBS_Ufunc_h//  Also yoUr Funk :)   

#include "Uchar.h"


const int Ufunc_MAJOR_VERSION = 0;
const int Ufunc_MINOR_VERSION = 5;

namespace iBS 
{
    
   
    bool isOn(unsigned char byte, short index)
    { return (byte & 1<<index); };

    void display_bits(unsigned char uc)
    {
        std::bitset<8>  bs;
        bs=uc;   
        std::cout << uc << bs << std::endl; 
    };
    void display_bits(unsigned short us)
    {
        std::bitset<16>  bs;
        bs=us;   
        std::cout << us << bs << std::endl; 
    };
    void display_bits(unsigned int ui)
    {
        std::bitset<32>  bs;
        bs=ui;   
        std::cout << ui <<'=' <<bs << std::endl; 
        
    };
    void display_bits(int i)
    {
        std::bitset<32>  bs;
        bs=i;   
        std::cout << i <<'='<< bs << std::endl; 
    };
    void display_bits(size_t i)
    {
        std::bitset<64>  bs;
        bs=i;   
        std::cout << i <<'='<< bs << std::endl; 
    };


}//end of iBS namespace  

#endif // iBS_Ufunc_h