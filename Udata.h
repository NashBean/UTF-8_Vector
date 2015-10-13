//
//  Udata.h
//
//
//  Created by nash on 9/24/15.
//  Copyright© 2015+ iBean Software. All rights reserved.
//  iBeanSoftware@GMail.com
//  https://www.facebook.com/iBeanSowtware
//  Out of order

#ifndef iBS_Udata_h
#define iBS_Udata_h

#include "Uchar.h"
#include <vector>


const int Udata_MAJOR_VERSION = 0;
const int Udata_MINOR_VERSION = 8;

namespace iBS 
{
    

    struct raw_u8str 
    {
        std::vector <unsigned char> ref;
    };
    
    struct small_switch 
    {
        unsigned char sw;
        small_switch():sw(0x0000){};
        small_switch(unsigned int& v):sw(v){};
        ~small_switch(){};
        small_switch& operator=(const small_switch& x)
        {   sw=x.sw;   return *this;    };
        bool isOn(unsigned short& index)
        {
            if (index>31) index=31;
            return  !((sw & 1<<index)==0);
        };  
        void flip(unsigned short& index)
        {   
            if (index<8)  
            sw=sw^1<<index;    
        };
    };

struct switch_board 
{
    unsigned int sw;
    switch_board():sw(0x00000000){};
    switch_board(unsigned int& v):sw(v){};
    ~switch_board(){};
    switch_board& operator=(const switch_board& x)
    {   sw=x.sw;   return *this;    };
    bool isOn(unsigned short& index)
    {// 32  bool switches  indexes: 0-31
        if (index>31) index=31;
        return  !((sw & 1<<index)==0);
    };  
    void flip(unsigned short& index)
    {   
        if (index>31) index=31; 
        sw=sw^1<<index;    
    };
};

struct small_v 
{
    std::vector <unsigned char> ref;
    
    small_v():ref(0){ref.reserve(6);};
    small_v(std::vector<unsigned char>& v):ref(1)
    {   
        resize(v.size());
        for (size_t i=0; i<ref.size(); ++i) 
        {   ref[i]=v[i];   }
    };
    ~small_v(){if(ref.size())ref.clear();};
    bool resize(size_t nsize)
    {
        if (ref.size()!=nsize) 
        {   if(nsize>6)         nsize=6;//make6maxSize
            if(ref.max_size()<nsize){ return false; }//out of memory
            else {ref.resize(nsize); }   
        }
        return true;
    };  
};

struct data_v//for UTF-8 formatted data   
{
    std::vector <unsigned char>  d_v;
    
    data_v():d_v(0){d_v.reserve(125);};//uc_v[0]='\x0000';};
    data_v(std::vector<unsigned char>& v):d_v(v.size())
    {
        for (size_t i=0; i<d_v.size(); ++i) 
        {   d_v[i]=v[i];   }
    };
    ~data_v(){if(d_v.size())d_v.clear();};
    data_v(data_v& datav):d_v(datav.size())
    {
        for (size_t i=0; i<d_v.size(); ++i) 
        {   d_v[i]=datav.d_v[i];   }
    };
    data_v& operator=(const data_v& x)
    {
        if (!resize(x.d_v.size())){return *this;};//out of memory
        for (size_t i=0; i<d_v.size(); ++i) 
        {   d_v[i]=x.d_v[i];   }
        return *this;
    };
    data_v& operator+=(const data_v& x)
    {
        size_t i=d_v.size(),i2=0;
        if (!resize(d_v.size()+x.d_v.size())){return *this;};//out of memory
        for (; i<d_v.size(); ++i) 
        {   d_v[i]=x.d_v[i2++];   }
        return *this;
    };
    data_v& operator=(std::vector<unsigned char>& v)
    {
        if (!resize(v.size())){return *this;};//out of memory
        for (size_t i=0; i<d_v.size(); ++i) 
        {   d_v[i]=v[i];   }
        return *this;
    };
    data_v& operator+=(std::vector<unsigned char>& v)
    {
        size_t i=d_v.size(),i2=0;
        if (!resize(d_v.size()+v.size())){return *this;};//out of memory
        for (; i<d_v.size(); ++i) 
        {   d_v[i]=v[i2++];   }
        return *this;
    };
    unsigned char operator[](size_t index){return  d_v[index]; };  
    size_t size(){return d_v.size();}; 
    bool resize(size_t nsize)
    {
        if (d_v.size()!=nsize) 
        {   
            if (d_v.max_size()<nsize){ return false; }//out of memory
            else {  d_v.resize(nsize); }   
        }
        return true;
    };  
};

struct uint_v//for raw unicodes and others
{
    std::vector <unsigned int>  i_v;
    
    uint_v():i_v(0){i_v.reserve(30);};//uc_v[0]='\x0000';};
    uint_v(std::vector<unsigned int>& v):i_v(v.size())
    {
        for (size_t i=0; i<i_v.size(); ++i) 
        {   i_v[i]=v[i];   }
    };
    ~uint_v(){if(i_v.size())i_v.clear();};
    
    uint_v& operator=(const uint_v& x)
    {
        if (!resize(x.i_v.size())){return *this;};//out of memory
        for (size_t i=0; i<i_v.size(); ++i) 
        {   i_v[i]=x.i_v[i];   }
        return *this;
    };
    unsigned int operator[](size_t index){return  i_v[index]; };  
    size_t size(){return i_v.size();}; 
    bool resize(size_t nsize)
    {
        if (i_v.size()!=nsize) 
        {   
            if (i_v.max_size()<nsize){ return false; }//out of memory
            else {  i_v.resize(nsize); }   
        }
        return true;
    };  
};


struct ulong_v//for 64 bit conversions
{
    std::vector <unsigned long>  i_v;
    
    ulong_v():i_v(0){i_v.reserve(30);};
    ulong_v(std::vector<unsigned long>& v):i_v(v.size())
    {
        for (size_t i=0; i<i_v.size(); ++i) 
        {   i_v[i]=v[i];   }
    };
    ~ulong_v(){if(i_v.size())i_v.clear();};
    
    ulong_v& operator=(const ulong_v& x)
    {
        if (!resize(x.i_v.size())){return *this;};//out of memory
        for (size_t i=0; i<i_v.size(); ++i) 
        {   i_v[i]=x.i_v[i];   }
        return *this;
    };
    unsigned int operator[](size_t index){return  i_v[index]; };  
    size_t size(){return i_v.size();}; 
    bool resize(size_t nsize)
    {
        if (i_v.size()!=nsize) 
        {   
            if (i_v.max_size()<nsize){ return false; }//out of memory
            else {  i_v.resize(nsize); }   
        }
        return true;
    };  
};
    
};//end of namespace iBS

#endif // iBS_Udata_h
