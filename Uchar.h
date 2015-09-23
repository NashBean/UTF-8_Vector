//
//  Uchar.h
//
//
//  Created by nash on 9/18/15.
//  Copyright 2015+ iBean Software.
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

const int Uchar_MAJOR_VERSION = 0;
const int Uchar_MINOR_VERSION = 7;

const unsigned char endc= '\n';  

//this is a function that turns a unicode into UTF-8 format
extern inline void Setunicode(std::vector<unsigned char>& uc_v, unsigned int& unicode)
{   
    if (unicode<=0x7f) 
    {
        resize(uc_v,1);    
        uc_v[0]=unicode;
    }  
    else if (unicode>=0x80 && unicode<=0x07ff) 
    {
        resize(uc_v,2);    
        uc_v[1]=unicode;//   &   0x3f;
        uc_v[1]=uc_v[1]  &   0x3f;
        uc_v[1]=uc_v[1]|0x80;
        
        uc_v[0]=unicode>>6;
        uc_v[0]=uc_v[0]&0x1f;
        uc_v[0]=uc_v[0]|'\xc0';
    }  
    else if (unicode>=0x0800 && unicode<=0xffff) 
    {
        resize(uc_v,3);    
        unsigned char temp;     
        
        temp=unicode;
        uc_v[2]=temp  &   0x3f;
        uc_v[2]=uc_v[2]|0x80;
        
        temp=unicode>>6;
        uc_v[1]=temp  &   0x3f;
        uc_v[1]=uc_v[1]|0x80;
        
        temp=unicode>>12;
        uc_v[0]=temp&0x1f;
        uc_v[0]=uc_v[0]|0xc0;
    }  
    else if(unicode>=0x010000 && unicode<=0x1fffff) 
    {
        // uc_v.reserve(4);
        resize(uc_v,4);
        
        uc_v[3]=unicode;//   &   0x3f;
        uc_v[3]=uc_v[3]  &   0x3f;
        uc_v[3]=uc_v[3]|0x80;
        
        uc_v[2]=unicode>>6;//   &   0x3f;
        uc_v[2]=uc_v[2]  &   0x3f;
        uc_v[2]=uc_v[2]|0x80;
        
        uc_v[1]=unicode>>12;
        uc_v[1]=uc_v[1]  &   0x3f;
        uc_v[1]=uc_v[1]|0x80;
        
        uc_v[0]=unicode>>18;
        uc_v[0]=uc_v[0]&0x1f;
        uc_v[0]=uc_v[0]|'\xc0';
    }  
    else if(unicode>=0x200000 && unicode<=0x03ffffff) 
    {
        // uc_v.reserve(5);
        resize(uc_v,5);
        
        uc_v[4]=unicode;//   &   0x3f;
        uc_v[4]=uc_v[4]  &   0x3f;
        uc_v[4]=uc_v[4]|0x80;
        
        uc_v[3]=unicode>>6;//   &   0x3f;
        uc_v[3]=uc_v[3]  &   0x3f;
        uc_v[3]=uc_v[3]|0x80;
        
        uc_v[2]=unicode>>12;//   &   0x3f;
        uc_v[2]=uc_v[2]  &   0x3f;
        uc_v[2]=uc_v[2]|0x80;
        
        uc_v[1]=unicode>>18;
        uc_v[1]=uc_v[1]  &   0x3f;
        uc_v[1]=uc_v[1]|0x80;
        
        uc_v[0]=unicode>>24;
        uc_v[0]=uc_v[0]&0x1f;
        uc_v[0]=uc_v[0]|'\xc0';
    }  
    else if(unicode>=0x04000000 && unicode<=0x7fffffff) 
    {
        //  uc_v.reserve(6);
        resize(uc_v,6);
        
        uc_v[5]=unicode;//   &   0x3f;
        uc_v[5]=uc_v[5]  &   0x3f;
        uc_v[5]=uc_v[5]|0x80;
        
        uc_v[4]=unicode>>6;//   &   0x3f;
        uc_v[4]=uc_v[4]  &   0x3f;
        uc_v[4]=uc_v[4]|0x80;
        
        uc_v[3]=unicode>>12;//   &   0x3f;
        uc_v[3]=uc_v[3]  &   0x3f;
        uc_v[3]=uc_v[3]|0x80;
        
        uc_v[2]=unicode>>18;//   &   0x3f;
        uc_v[2]=uc_v[2]  &   0x3f;
        uc_v[2]=uc_v[2]|0x80;
        
        uc_v[1]=unicode>>24;
        uc_v[1]=uc_v[1]  &   0x3f;
        uc_v[1]=uc_v[1]|0x80;
        
        uc_v[0]=unicode>>30;
        uc_v[0]=uc_v[0]&0x1f;
        uc_v[0]=uc_v[0]|'\xc0';
    }  
    else    uc_v[0]='\x0000';
    
};


struct  Uchar//UTF-8    container
{
    std::vector <unsigned char>  uc_v;
    Uchar():uc_v(0){uc_v.reserve(6);};//uc_v[0]='\x0000';};
    Uchar(std::vector<unsigned char>& v):uc_v(v.size())
    {
        for (size_t i=0; i<uc_v.size(); ++i) 
        {   uc_v[i]=v[i];   }
    };
    ~Uchar(){uc_v.clear();};//if(uc_v.size())uc_v.clear();};
    //    Uchar(Uchar& c):uc_v(c.uc_v){};
    
    Uchar(unsigned int unicode):uc_v(1)
    {    Setunicode(uc_v,unicode); };
    
    void resize(size_t x)
    {      
        if (uc_v.size()!=x) 
        {   if (uc_v.max_size()<x){  }//throw out of memory
        else {  uc_v.resize(x); }   
    }
   };       
    
    Uchar& operator=(const Uchar& x)
    {
        if (uc_v.size()!=x.uc_v.size()) 
        {   if (uc_v.size()<x.uc_v.size()) 
        {   if (uc_v.max_size()<x.uc_v.size()) 
        {   return *this;};//throw out of memory
        }
            uc_v.resize(x.uc_v.size());    
        }
        for (size_t i=0; i<uc_v.size(); ++i) 
        {   uc_v[i]=x.uc_v[i];   }
        return *this;
    };
    const  char* c_str()  
    { 
        if (uc_v.size()==0) 
        {
            return 0x00;
        }
        
        size_t sz=uc_v.size();
        char result[sz+1];
        
        for (size_t i=0;i<sz; ++i) 
        {
            result[i]= char(uc_v[i]);
        }
        
        result[sz]  = endc;
        
        return (const char*)*result;

    };
    
};

struct  Ustr//UTF-8    container
{
    std::vector <unsigned char>  str_v;
    
    Ustr():str_v(0){str_v.reserve(6);};
    Ustr(std::vector<unsigned char>& v):str_v(v.size())
    {
        for (size_t i=0; i<str_v.size(); ++i) 
        {   str_v[i]=v[i];   }
    };
    ~Ustr(){str_v.clear();};    
    Ustr(unsigned int unicode):str_v(1)
    {    Setunicode(str_v,unicode);};
    
    void resize(size_t x)
    {  
        if (str_v.size()!=x) 
        {   if (str_v.max_size()<x){  }}//throw out of memory
        else {  str_v.resize(x); }   
   };       
    
    Ustr& operator=(const Ustr& x)
    {
        if (str_v.size()!=x.str_v.size()) 
        {   if (str_v.size()<x.str_v.size()) 
        {   if (str_v.max_size()<x.str_v.size()) 
        {   return *this;};//throw out of memory
        }
            str_v.resize(x.str_v.size());    
        }
        for (size_t i=0; i<str_v.size(); ++i) 
        {   str_v[i]=x.str_v[i];   }
        return *this;
    };
    
    const  char* c_str()  
    { 
        if (str_v.size()==0) 
        {
            return 0x00;
        }
        
        size_t sz=str_v.size();
        char result[sz+1];
        
        for (size_t i=0;i<sz; ++i) 
        {
            result[i]= char(str_v[i]);
        }
        
        result[sz]  = endc;
        
        return (const char*)*result;
        
    };
    
};


#endif // iBS_Uchar_h
