//
//  Uchar.h
//
//
//  Created by nash on 9/18/15.
//  Copyright 2015+ iBean Software.
//  https://www.facebook.com/iBeanSowtware
//
//  a struct to hold a multi length UTF-8 char
//  and still compile with c++98
//  Constructs using 0-4 unsigned char
//  to hold all the 8 bit section of a UTF-8 char.
//  Should be std::vector safe
//  And should be fast.

#ifndef iBS_Uchar_h
#define iBS_Uchar_h
#include <vector>
#include "Udata.h"

const int Uchar_MAJOR_VERSION = 0;
const int Uchar_MINOR_VERSION = 11;

struct  Uchar
{
    std::vector <BitBull>  uc_v;
    Uchar():uc_v(0){uc_v.reserve(6);};//uc_v[0]='\x0000';};
    Uchar(std::vector<BitBull>& c):uc_v(c.size())
    {   
        if(c.size()>6)    resize(6);//making 6 max size
        for (size_t i=0; i<uc_v.size(); ++i) 
        {   uc_v[i]=c[i];   }
    };
    ~Uchar(){};//if(uc_v.size())uc_v.clear();};
    Uchar(unsigned int unicode):uc_v(1)
    {   
        setUnicode(unicode); 
    };
    Uchar& operator=(const Uchar& x)
    {
        resize(x.uc_v.size());   
        for (size_t i=0; i<uc_v.size(); ++i) 
        {   uc_v[i]=x.uc_v[i];   }
        return *this;
    };
    Uchar& operator=(unsigned int unicode)
    {
        setUnicode(unicode); 
        return *this;
    };
    inline void setUnicode(unsigned int& unacode)
    {   
        if (unacode<=0x7f) 
        {
            resize(1);    
            uc_v[0]=unacode;
        }  
        else if (unacode>=0x80 && unacode<=0x07ff) 
        {
            resize(2);    
            unsigned char temp;     
            temp=unacode;
            uc_v[1]=temp&0x3f;
            uc_v[1]=uc_v[1]|0x80;
            temp=unacode>>6;
            uc_v[0]=temp&0x1f;
            uc_v[0]=uc_v[0]|0xc0;//'\xc0';
        }  
        else if (unacode>=0x0800 && unacode<=0xffff) 
        {
            resize(3);    
            unsigned char temp;     
            temp=unacode;
            uc_v[2]=temp&0x3f;
            uc_v[2]=uc_v[2]|0x80;
            temp=unacode>>6;
            uc_v[1]=temp&0x3f;
            uc_v[1]=uc_v[1]|0x80;
            temp=unacode>>12;
            uc_v[0]=temp&0x1f;
            uc_v[0]=uc_v[0]|0xc0;
        }  
        else if(unacode>=0x010000 && unacode<=0x1fffff) 
        {
            resize(4);
            unsigned char temp;     
            temp=unacode;
            uc_v[3]=temp&0x3f;
            uc_v[3]=uc_v[3]|0x80;
            temp=unacode>>6;
            uc_v[2]=temp&0x3f;
            uc_v[2]=uc_v[2]|0x80;
            temp=unacode>>12;
            uc_v[1]=temp&0x3f;
            uc_v[1]=uc_v[1]|0x80;
            temp=unacode>>18;
            uc_v[0]=temp&0x1f;
            uc_v[0]=uc_v[0]|0xc0;
        }  
        else if(unacode>=0x200000 && unacode<=0x03ffffff) 
        {
            resize(5);
            unsigned char temp;     
            temp=unacode;
            uc_v[4]=temp & 0x3f;
            uc_v[4]=uc_v[4]|0x80;
            temp=unacode>>6;
            uc_v[3]=temp & 0x3f;
            uc_v[3]=uc_v[3]|0x80;
            temp=unacode>>12;
            uc_v[2]=temp & 0x3f;
            uc_v[2]=uc_v[2]|0x80;
            temp=unacode>>18;
            uc_v[1]=temp & 0x3f;
            uc_v[1]=uc_v[1]|0x80;
            temp=unacode>>24;
            uc_v[0]=temp&0x1f;
            uc_v[0]=uc_v[0]|0xc0;
        }  
        else if(unacode>=0x04000000 && unacode<=0x7fffffff) 
        {
            resize(6);
            unsigned char temp;     
            temp=unacode;
            uc_v[5]=temp & 0x3f;
            uc_v[5]=uc_v[5]|0x80;
            temp=unacode>>6;
            uc_v[4]=temp & 0x3f;
            uc_v[4]=uc_v[4]|0x80;
            temp=unacode>>12;
            uc_v[3]=temp & 0x3f;
            uc_v[3]=uc_v[3]|0x80;
            temp=unacode>>18;
            uc_v[2]=temp & 0x3f;
            uc_v[2]=uc_v[2]|0x80;
            temp=unacode>>24;
            uc_v[1]=temp & 0x3f;
            uc_v[1]=uc_v[1]|0x80;
            temp=unacode>>30;
            uc_v[0]=temp&0x1f;
            uc_v[0]=uc_v[0]|0xc0;
        }  
        else    uc_v[0]=0x00;
    };
    const  char* c_str()  
    {
        short sz=uc_v.size();
        if (sz==0)  {    return '\x0000';     }
        char result[sz+1];
        for (size_t i=0;i<sz; ++i) 
        {
            result[i]= char(uc_v[i]);
        }
        result[sz]='\n';
     return (const char*)*result; 
    };
    
    private:
        void resize(size_t x)
    {
        if (uc_v.size()!=x) 
        {   
            if (uc_v.max_size()<x){  }//throw out of memory
            else {  uc_v.resize(x); }   
        }
    };       
};
#endif // iBS_Uchar_h
