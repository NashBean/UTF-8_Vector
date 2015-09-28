//
//  main.cpp
//  UTF-8_Vector
//
//  Created by nash on 9/23/15.
//  Copyright © 2015 iBean_Software. All rights reserved.
//

#include <iostream>
#include "Uchar.h"
#include <bitset>
//#include <locale.h>

void display_bits(Uchar& uc)
{
    std::bitset<8>  bs;
    for (size_t i=0; i<uc.size(); ++i) 
    {   bs=uc.ref[i];   std::cout << bs << ' ';}
    std::cout << std::endl; 
};

int main (int argc, const char * argv[])
{
    std::bitset<8>  bs=UCHAR_MAX;//???
    std::string ts="";
    

    Uchar  uc(0x41);
    std::cout <<uc.str() <<' ';
    display_bits(uc);
    uc.appendtostr(ts);
    
    uc=0x03a9;//Ω
    std::cout <<uc.str() <<' ';
    display_bits(uc);
    uc.appendtostr(ts);
    
    uc=0x8c46;
    std::cout<<uc.str()<<' '; 
    display_bits(uc);
    uc.appendtostr(ts);
    
    uc=0xa8a0;
    std::cout <<uc.str() <<' ';
    display_bits(uc);
    uc.appendtostr(ts);
  //  uc=0x0811;//ࠑ   this one moves out of order
 //   uc.appendtostr(ts);

    uc=0x2b147;
    std::cout <<uc.str() <<' ';
    display_bits(uc);
    uc.appendtostr(ts);
    
    uc=0x03ffffff;//max 5 byte Unicode
    display_bits(uc);
    
    uc=0x7fffffff;//max Unicode
    display_bits(uc);
    
    std::cout<<ts<<std::endl;
    
    printf("%ls\n", L"Schöne Grüße,新增暫編戶政用字，,豆");
        
    return 0;
}



