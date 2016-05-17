//
//  OldCode.h
//  UTF-8_Vector unused code
//
//  Created by nash on 5/16/16.
//  Copyright 2016 iBean Software.
//  All rights reserved.
//
// ------------------------------------------------------------------------



// ------------------------------------------------------------------------
//   old iBS_Unum.h code
// ------------------------------------------------------------------------
//
//  Unum.h
//
//
//  Created by nash on 10/5/15.
//  Copyright© 2015+ iBean Software. All rights reserved.
//  iBeanSoftware@GMail.com
//  https://www.facebook.com/iBeanSowtware
//  out of order
#ifndef iBS_Unum_h
#define iBS_Unum_h

#include <vector>
#include <string>
#include <sstream>

const int Unum_MAJOR_VERSION = 0;
const int Unum_MINOR_VERSION = 2;

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
// ------------------------------------------------------------------------


// ------------------------------------------------------------------------
//   old iBS_Udata.h code
// ------------------------------------------------------------------------
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
        small_switch(unsigned char& v):sw(v){};
        ~small_switch(){};
        small_switch& operator=(const small_switch& x)
        {   sw=x.sw;   return *this;    };
        bool isOn(unsigned short& index)
        {
            if (index>8) index=8;//should not go here
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
// ------------------------------------------------------------------------



// ------------------------------------------------------------------------
//   old iBS_Ufile.h code
// ------------------------------------------------------------------------
//
//  Ufile.h
//
//
//  Created by nash on 10/6/15.
//  Copyright© 2015+ iBean Software. All rights reserved.
//  iBeanSoftware@GMail.com
//  https://www.facebook.com/iBeanSowtware
//  out of  order

#ifndef iBS_Ufile_h
#define iBS_Ufile_h

#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include "Uchar.h"
#include "Udata.h"

const int Ufile_MAJOR_VERSION = 0;
const int Ufile_MINOR_VERSION = 6;

namespace iBS 
{
    
    
    
    class u8ifile 
    {
    public:
        u8ifile(std::string filename)
        {   
            fin.open(filename.c_str());
            if (fin.fail()) {} 
        };
        ~u8ifile(){ if (fin.is_open())  fin.close(); };
        
        operator bool(){   return fin.fail();  }; 
        bool eof()   {   return fin.eof();  }; 
        void getraw_v(u8str& u8_v)
        {
            unsigned char  temp=0;   
            u8char   u8temp;
            unsigned short sz=0;  
            std::vector<unsigned char> ref; 
            ref.reserve(6);
            
            if (u8_v.ref.size())u8_v.ref.clear();
            u8_v.ref.reserve(sizeof(fin));
            while(fin >> temp)
            {
                if (isTrailByte(temp)) {
                    ref.push_back(temp);  
                }
                else
                {
                    sz = ByteCount(temp);  
                    if (ref.size()) 
                    {
                        u8_v.append(u8char(ref));
                        ref.clear();
                    }
                    ref.resize(sz);
                    ref[0]=temp;
                }
            }
            if (ref.size()) 
            {
                u8_v.append(u8char(ref));
                ref.clear();
            }
            
            fin.close();
        };    
    private:
        std::ifstream    fin   ;      
        
    };
    
    u8ifile& operator >> (u8ifile& in_file , unsigned char& a)
    {
        in_file >> a;
        return in_file;
    };
    
    //-----------------------------------------
    
    class u8ofile 
    {
        
        
    public:
        u8ofile(std::string filename)
        {   
            fout.open(filename.c_str());
            if (fout.fail()) {} 
        };
        ~u8ofile(){ if (fout.is_open())  fout.close(); };
        
        operator bool(){   return fout.fail();  }; 
        bool eof()   {   return fout.eof();  }; 
        
        
    private:
        std::ofstream    fout;      
        
    };
    
    u8ofile& operator << (u8ofile& out_file , unsigned char& a)
    {
        out_file << a;
        return out_file;
    };
    
    //-----------------------------------------
    
    
};//end of iBS namespace

#endif // iBS_Ufile_h
// ------------------------------------------------------------------------



// ------------------------------------------------------------------------
// old iBS_StreamList.h code
// ------------------------------------------------------------------------
const int STREAMLIST_MAJOR_VERSION = 0;
const int STREAMLIST_MINOR_VERSION = 1;

namespace iBS 
{
    struct StreamList
    {
        std::vector<std::stringstream> ref; 
    };
    
}//end of namespace iBS

// ------------------------------------------------------------------------



// ------------------------------------------------------------------------
// old Uchar.h code
// ------------------------------------------------------------------------


struct Uchar
{
    UnicodeInt ref;
    
    Uchar& operator =(Uchar uch){ref = uch.ref; return *this;};
    Uchar& operator =(char ch){ref = (UnicodeInt)ch; return *this;};
    Uchar& operator =(u8char u8ch){ref = decode(u8ch); return *this;};
    
    Uchar& operator +(Uchar uch){ref = ref + uch.ref; return *this;};
    Uchar& operator -(Uchar uch){ref = ref - uch.ref; return *this;};
};

// more compact then UTF-32
// less complucated then UTF-16
// bases for UTF-8
// less compact then ANSII 
struct unicode_string
{
    std::vector<UnicodeInt> ref;   
    
    void append(UnicodeInt uci)
    {
        ref.push_back(uci);
    };
    void append(char c)
    {
        ref.push_back(c);
    };
    //     void append(wchar_t& wc)
    //    {
    //  u8char temp = wc;
    //         ref.push_back((decode(u8char(wc))));
    //     };
    
    void append(u8char uc)
    {
        ref.push_back(decode(uc));
    };
    size_t u8char_count(){return ref.size();};
    bool appendtostr(std::string& str)
    {
        try {u8char u8c=u8char();
            for(size_t i=0; i<ref.size(); ++i) 
            { u8c.encode(ref[i]); u8c.appendtostr(str);} } 
        catch (...) { return false; }
        return true;
    };
    
    std::string str()
    {
        if (ref.size()==0) 
        { return ""; }
        std::stringstream result;
        u8char temp = u8char();
        for (size_t i=0; i<ref.size(); ++i) 
        {
            temp = ref[i];
            temp.appendtostr(result);
        }
        return result.str();
    };
    
    std::vector<UnicodeInt>& vector(){return ref;};
    
};

// ------------------------------------------------------------------------



// ------------------------------------------------------------------------
//
// ------------------------------------------------------------------------

