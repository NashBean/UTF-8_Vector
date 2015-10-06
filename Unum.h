//
//  Unum.h
//
//
//  Created by nash on 10/5/15.
//  Copyright© 2015+ iBean Software.
//  All rights reserved.
//

#ifndef iBS_Unum_h
#define iBS_Unum_h

#include <vector>
#include <string>
#include <sstream>

const int Unum_MAJOR_VERSION = 0;
const int Unum_MINOR_VERSION = 1;

namespace iBS
{
    const unsigned char empty=0xdf;
    const unsigned char zero4bit=0x0;
    
    struct  unum    //unaversal  number
    {   //0x0-0x9==0-9  a==A b==+ c==- d==. e==∞ f==Ω
        //0xaeff==Infinity  0xacef==negative Infinity   
        std::vector<unsigned char>  ref;
        
        unum():ref(1){ref[0]=0xdf;};//0xd==beginning, 0xf==end
        unum(std::vector<unsigned char>& c):ref(c.size())
        { for (size_t i=0; i<ref.size(); ++i) {ref[i]=c[i];} };
        ~unum(){if(ref.size())ref.clear();};
        unum(size_t reserve_size):ref(0) {ref.reserve(reserve_size);};
        unum& operator=(const unum& x)
        {
            ref.resize(x.ref.size());   
            for (size_t i=0; i<ref.size(); ++i) 
            {   ref[i]=x.ref[i];   }
            return *this;
        };
        size_t size() const  { return (ref.size()-1)*2; };
        bool  is_signed()
        {
            if(ref.size()==0) return false;
            else if(ref[0]==0xdb||ref[0]==0xdc) return true;
            else    return false;
        };   
        bool has_dec(){return dec_index;};   
        unum& operator=(int& x)
        {
            if(ref.size()==0) ref.clear();//need not equel sign 
            ref.reserve(6);
            if (x>0) {ref[0]=0xab; }
            else if (x<0) {ref[0]=0xac; }
            else if (x==0)
            {   ref.resize(2);
                ref[0]=0xa0;
                ref[1]=0xff;
                return *this;
            }  
            //  if (ref.size()) {ref.clear();}
            //   ref.resize(x.ref.size());   
            //   for (size_t i=0; i<ref.size(); ++i) 
            //   {   ref[i]=x.ref[i];   }
            return *this;
        };
    private:
        size_t dec_index; //dec should atleast have 0 in frount of it, if nothing else.         
        unsigned char leftValue(unsigned char& byte8bit)
        {
            unsigned char  result=  byte8bit>>4;
            return result;
        };
        unsigned char rightValue(unsigned char& byte8bit)
        {
            unsigned char  result=  byte8bit<<4;
            result=  result>>4;
            return result;
        };
    };

    
    
};

#endif // iBS_Unum_h