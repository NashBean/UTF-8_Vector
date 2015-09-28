//
//  Uchar.h
//
//
//  Created by nash on 9/18/15.
//  Copyright 2015+ iBean Software.
//  https://www.facebook.com/iBeanSowtware
//
//  a struct to hold a multi length UTF-8 char
//  Constructs using 0-6: 8 bit bytes
//  to hold a UTF-8 char.
//  Should be std::vector safe
//  And should be fast.

#ifndef iBS_Uchar_h
#define iBS_Uchar_h
#include <vector>
#include <string>
#include <sstream>

const int Uchar_MAJOR_VERSION = 0;
const int Uchar_MINOR_VERSION = 14;

#define BitBull uint8_t    //unsigned char

struct  Uchar
{
    std::vector <BitBull>  ref;//always keeps data in a UTF-8 format.
    
    Uchar():ref(0){ref.reserve(6);};//ref[0]='\x0000';};
    Uchar(std::vector<BitBull>& c):ref(c.size())
    {   
        if(c.size()>6)    resize(6);//making 6 max size
        for (size_t i=0; i<ref.size(); ++i) 
        {   ref[i]=c[i];   }
    };
    ~Uchar(){if(ref.size())ref.clear();};
    Uchar(unsigned int unicode):ref(1)
    {   
        setUnicode(unicode); 
    };
    Uchar& operator=(const Uchar& x)
    {
        resize(x.ref.size());   
        for (size_t i=0; i<ref.size(); ++i) 
        {   ref[i]=x.ref[i];   }
        return *this;
    };
    Uchar& operator=(unsigned int unicode)
    {
        setUnicode(unicode); 
        return *this;
    };
    size_t size() const  { return ref.size(); };
    void   encode(unsigned int& unicode){setUnicode(unicode);}; 
    unsigned int decode()//returns a Unicode
    {
        unsigned int result=0;
        if (size()==0) { return result;}
        if (size()==1) { return (result +=ref[0]); }
        if (size()==2) { result=ref[0] & 0x1f; }
        else if (size()==3) { result=ref[0] & 0x0f; }
        else if (size()==4) { result=ref[0] & 0x07; }
        else if (size()==5) { result=ref[0] & 0x03; }
        else if (size()==6) { result=ref[0] & 0x01; }
        for (size_t i=1; i<size(); ++i) 
        { result=result<<6; result+=ref[i] & 0x3f; }
        return result;
    };   
    inline void setUnicode(unsigned int& unicode)
    {  
        if (unicode<=0x7f) 
        {
            resize(1);    
            ref[0]=  unicode;
        }  
        else if (unicode>=0x80 && unicode<=0x07ff) 
        {
            resize(2);    
            unsigned char temp;     
            temp=unicode;
            ref[1]=temp&0x3f;
            ref[1]=ref[1]|0x80;
            temp=unicode>>6;
            ref[0]=temp&0x1f;
            ref[0]=ref[0]|0xc0;
        }  
        else if (unicode>=0x0800 && unicode<=0xffff) 
        {
            resize(3);    
            unsigned char temp;     
            temp=unicode;
            ref[2]=temp&0x3f;
            ref[2]=ref[2]|0x80;
            temp=unicode>>6;
            ref[1]=temp&0x3f;
            ref[1]=ref[1]|0x80;
            temp=unicode>>12;
            ref[0]=temp&0x0f;
            ref[0]=ref[0]|0xe0;
        }  
        else if(unicode>=0x010000 && unicode<=0x1fffff) 
        {
            resize(4);
            unsigned char temp;     
            temp=unicode;
            ref[3]=temp&0x3f;
            ref[3]=ref[3]|0x80;
            temp=unicode>>6;
            ref[2]=temp&0x3f;
            ref[2]=ref[2]|0x80;
            temp=unicode>>12;
            ref[1]=temp&0x3f;
            ref[1]=ref[1]|0x80;
            temp=unicode>>18;
            ref[0]=temp&0x07;
            ref[0]=ref[0]|0xf0;
        }  
        else if(unicode>=0x200000 && unicode<=0x03ffffff) 
        {
            resize(5);
            unsigned char temp;     
            temp=unicode;
            ref[4]=temp & 0x3f;
            ref[4]=ref[4]|0x80;
            temp=unicode>>6;
            ref[3]=temp & 0x3f;
            ref[3]=ref[3]|0x80;
            temp=unicode>>12;
            ref[2]=temp & 0x3f;
            ref[2]=ref[2]|0x80;
            temp=unicode>>18;
            ref[1]=temp & 0x3f;
            ref[1]=ref[1]|0x80;
            temp=unicode>>24;
            ref[0]=temp&0x03;
            ref[0]=ref[0]|0xf8;
        }  
        else if(unicode>=0x04000000 && unicode<=0x7fffffff) 
        {
            resize(6);
            unsigned char temp;     
            temp=unicode;
            ref[5]=temp & 0x3f;
            ref[5]=ref[5]|0x80;
            temp=unicode>>6;
            ref[4]=temp & 0x3f;
            ref[4]=ref[4]|0x80;
            temp=unicode>>12;
            ref[3]=temp & 0x3f;
            ref[3]=ref[3]|0x80;
            temp=unicode>>18;
            ref[2]=temp & 0x3f;
            ref[2]=ref[2]|0x80;
            temp=unicode>>24;
            ref[1]=temp & 0x3f;
            ref[1]=ref[1]|0x80;
            temp=unicode>>30;
            ref[0]=temp&0x01;
            ref[0]=ref[0]|0xfc;
        }  
        else    ref[0]=0x00;
    };
    
    bool appendtostr(std::string& str)
    {
        try { for(size_t i=0; i<ref.size(); ++i) 
                { str+= ref[i]; } } 
        catch (...) { return false; }
        return true;
    };
    
    std::string str()
    {
        if (ref.size()==0) 
        { return ""; }
        std::stringstream result;
        try { for (size_t i=0; i<ref.size(); ++i) 
                { result<< char(ref[i]); } } 
        catch (...) { return "Uchar.str:error"; }
        return result.str();
    };
    
    //std::string ts="";
    //char jc2[3]="豆";       
    //std::cout<<jc;//dose Not work
    //ts+=jc2;
    //std::cout<<ts;//dose Not work
    //char* do not work printing most multi chars??
/*
    const char* c_str()  //still not working  
    {
        size_t sz=ref.size();
        if (sz==0)  { return 0x0000; }// '\x0000'
        char result[sz+1];
        //std::string result  ="";
        for (size_t i=0;i<sz; ++i) 
        {
            //result+= char(ref[i]);
            result[i]= char(ref[i]);
         //   result[i]= ref[i];
        }
      //  result[sz]='\n';
      //  const  char*    r=result;
     //   return r;
     return (const char*)*result; 
      //  return result.c_str();
    };
//*/
    
    private:
        void resize(size_t x)
    {
        if (ref.size()!=x) 
        {   
            if (ref.max_size()<x){  }//throw out of memory
            else {  ref.resize(x); }   
        }
    };       
};
struct Uchar; 

#endif // iBS_Uchar_h
