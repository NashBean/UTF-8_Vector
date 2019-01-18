//
//  Ufunc.h
//
//
//  Created by nash on 9/28/15.
//  Copyright 2015 iBean Software. All rights reserved.
//  iBeanSoftware@GMail.com
//  https://www.facebook.com/iBeanSowtware
//
//

#ifndef iBS_Ufunc_h//  degrading Unicode and UTF-8 Functions.
#ifndef iBS_Byte_API
#define iBS_Byte_API//  Also yoUr Funk :)   

#include <bitset>
#include "Uchar.h"


const int Byte_API_MAJOR_VERSION = 0;
const int Byte_API_MINOR_VERSION = 9;

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
    
    void display_bits(iBS::u8char& uc)
    {
        std::bitset<8>  bs;
        for (size_t i=0; i<uc.size(); ++i) 
        {   bs=uc.ref[i];   std::cout << bs << ' ';}
        std::cout << std::endl; 
    };
  //  void display_bits(unsigned char us)
  //  {
  //      std::bitset<8>  bs;
  //      bs=us;   
  //      std::cout << us << bs << std::endl; 
  //  };

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

#endif // iBS_Byte_API_h
