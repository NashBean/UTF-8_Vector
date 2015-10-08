//
//  main.cpp
//  UTF-8_Vector
//
//  Created by nash on 9/23/15.
//  Copyright © 2015+ iBeanSoftware. All rights reserved.
//

#include <iostream>
//#include <bitset>
//#include <locale.h>
#include "Uchar.h"
#include "Ufunc.h"


int main (int argc, const char* argv[])
{
  //  std::bitset<8>  bs=0xff;
    std::string ts="";
    

    iBS::u8char  uc(0x41);
    std::cout <<uc.str() <<' ';
    iBS::display_bits(uc);
    uc.appendtostr(ts);
    
    uc=0x03a9;//Ω
    std::cout <<uc.str() <<' ';
    iBS::display_bits(uc);
    uc.appendtostr(ts);
    
    uc=0x8c46;
    std::cout<<uc.str()<<' '; 
    iBS::display_bits(uc);
    uc.appendtostr(ts);
    
    uc=0xa8a0;
    std::cout <<uc.str() <<' ';
    iBS::display_bits(uc);
    uc.appendtostr(ts);
  //  uc=0x0811;//ࠑ   this one moves out of order
 //   uc.appendtostr(ts);

    uc=0x2b147;
    std::cout <<uc.str() <<' ';
    iBS::display_bits(uc);
    uc.appendtostr(ts);
    
    uc=0x7f;//max 1 byte Unicode
    iBS::display_bits(uc);
    uc=0x07ff;//max 2 byte Unicode
    iBS::display_bits(uc);
    uc=0xffff;//max 3 byte Unicode
    iBS::display_bits(uc);
    uc=0x1fffff;//max 4 byte Unicode
    iBS::display_bits(uc);
    uc=0x03ffffff;//max 5 byte Unicode
    iBS::display_bits(uc);
    uc=0x7fffffff;//max Unicode
    iBS::display_bits(uc);
    
    std::cout<<ts<<std::endl;
    
   // printf("%ls\n", L"Schöne Grüße,新增暫編戶政用字，,豆");
    int x=33;
    
    iBS::display_bits(x);

    iBS::display_bits(INT16_MAX);
    iBS::display_bits(INT32_MAX);
    iBS::display_bits(-INT32_MAX-1);//==INT32_MIN
    iBS::display_bits(INT32_MIN);
    
    iBS::display_bits((size_t)INT64_MAX);
    x=2147483647;//max  int
    iBS::display_bits(x);
    
    
    return 0;
}



