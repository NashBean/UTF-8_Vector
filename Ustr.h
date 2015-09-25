//
//  UStr.h
//
//
//  Created by nash on 9/23/15.
//  Copyright 2015+ iBean Software.
//  https://www.facebook.com/iBeanSowtware
//  all rights reserved.

#ifndef iBS_Ustr_h
#define iBS_Ustr_h

#include "Uchar.h"
#include "Udata.h"

const int Ustr_MAJOR_VERSION = 0;
const int Ustr_MINOR_VERSION = 1;

class  Ustr
{
    data_v  data;
    
    Ustr():data(){};
    Ustr(data_v& _v):data(_v)
    {
    };
    ~Ustr(){};
    
    void resize(size_t x)
    {data.resize(x); };       
    
    Ustr& operator=(const Ustr& x)
    {   
        data=x.data;
        return *this;
    };
    Ustr& operator+=(const Ustr& x)
    {   
        data+=x.data;
        return *this;
    };
    Ustr& operator=(const Uchar& x)
    {   
        data=x.uc_v;
        return *this;
    };
    Ustr& operator+=(const Uchar& x)
    {   
        data+=x.uc_v;
        return *this;
    };
    const char* c_str() 
    {
        if (data.size()==0) 
        {
            return 0x00;
        }
        
        short sz=data.size();
        char result[sz+1];
        for (size_t i=0;i<sz;++i ) 
        {
            result[i]= char(data[i]);
        }
        
        result[sz]='\n';
        return (const char*)*result;
    };
};

#endif // iBS_UStr_h
