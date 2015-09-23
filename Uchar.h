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
const int Uchar_MINOR_VERSION = 4;

struct  Uchar
{
    std::vector <unsigned short>  uc_v;
    Uchar():uc_v(1){};//uc_v[0]='\x0000';};
    Uchar(std::vector<unsigned short>& c):uc_v(c){};
    ~Uchar(){};//if(uc_v.size())uc_v.clear();};
//    Uchar(Uchar& c):uc_v(c.uc_v){};
    
    Uchar(unsigned int unacode):uc_v(1)
    {   
        SetUnacode(unacode); 
    };
    
    void resize(size_t x)
    {
        if (uc_v.size()!=x) 
        {   
            if (uc_v.max_size()<x){  }//throw out of memory
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
     
   void SetUnacode(unsigned int unacode)
    {   
        if (unacode<=0x7f) 
        {
            resize(1);    
            uc_v[0]=unacode;
        }  
        else if (unacode>=0x80 && unacode<=0x07ff) 
        {
            resize(2);    
            uc_v[1]=unacode;//   &   0x3f;
            uc_v[1]=uc_v[1]  &   0x3f;
            uc_v[1]=uc_v[1]|0x80;
            
            uc_v[0]=unacode>>6;
            uc_v[0]=uc_v[0]&0x1f;
            uc_v[0]=uc_v[0]|'\xc0';
        }  
        else if (unacode>=0x0800 && unacode<=0xffff) 
        {
            resize(3);    
            unsigned char temp;     
            
            temp=unacode;
            uc_v[2]=temp  &   0x3f;
            uc_v[2]=uc_v[2]|0x80;
            
            temp=unacode>>6;
            uc_v[1]=temp  &   0x3f;
            uc_v[1]=uc_v[1]|0x80;
            
            temp=unacode>>12;
            uc_v[0]=temp&0x1f;
            uc_v[0]=uc_v[0]|0xc0;
        }  
        else if(unacode>=0x010000 && unacode<=0x1fffff) 
        {
            // uc_v.reserve(4);
            resize(4);
            
            uc_v[3]=unacode;//   &   0x3f;
            uc_v[3]=uc_v[3]  &   0x3f;
            uc_v[3]=uc_v[3]|0x80;
            
            uc_v[2]=unacode>>6;//   &   0x3f;
            uc_v[2]=uc_v[2]  &   0x3f;
            uc_v[2]=uc_v[2]|0x80;
            
            uc_v[1]=unacode>>12;
            uc_v[1]=uc_v[1]  &   0x3f;
            uc_v[1]=uc_v[1]|0x80;
            
            uc_v[0]=unacode>>18;
            uc_v[0]=uc_v[0]&0x1f;
            uc_v[0]=uc_v[0]|'\xc0';
        }  
        else if(unacode>=0x200000 && unacode<=0x03ffffff) 
        {
            // uc_v.reserve(5);
            resize(5);
            
            uc_v[4]=unacode;//   &   0x3f;
            uc_v[4]=uc_v[4]  &   0x3f;
            uc_v[4]=uc_v[4]|0x80;
            
            uc_v[3]=unacode>>6;//   &   0x3f;
            uc_v[3]=uc_v[3]  &   0x3f;
            uc_v[3]=uc_v[3]|0x80;
            
            uc_v[2]=unacode>>12;//   &   0x3f;
            uc_v[2]=uc_v[2]  &   0x3f;
            uc_v[2]=uc_v[2]|0x80;
            
            uc_v[1]=unacode>>18;
            uc_v[1]=uc_v[1]  &   0x3f;
            uc_v[1]=uc_v[1]|0x80;
            
            uc_v[0]=unacode>>24;
            uc_v[0]=uc_v[0]&0x1f;
            uc_v[0]=uc_v[0]|'\xc0';
        }  
        else if(unacode>=0x04000000 && unacode<=0x7fffffff) 
        {
            //  uc_v.reserve(6);
            resize(6);
            
            uc_v[5]=unacode;//   &   0x3f;
            uc_v[5]=uc_v[5]  &   0x3f;
            uc_v[5]=uc_v[5]|0x80;
            
            uc_v[4]=unacode>>6;//   &   0x3f;
            uc_v[4]=uc_v[4]  &   0x3f;
            uc_v[4]=uc_v[4]|0x80;
            
            uc_v[3]=unacode>>12;//   &   0x3f;
            uc_v[3]=uc_v[3]  &   0x3f;
            uc_v[3]=uc_v[3]|0x80;
            
            uc_v[2]=unacode>>18;//   &   0x3f;
            uc_v[2]=uc_v[2]  &   0x3f;
            uc_v[2]=uc_v[2]|0x80;
            
            uc_v[1]=unacode>>24;
            uc_v[1]=uc_v[1]  &   0x3f;
            uc_v[1]=uc_v[1]|0x80;
            
            uc_v[0]=unacode>>30;
            uc_v[0]=uc_v[0]&0x1f;
            uc_v[0]=uc_v[0]|'\xc0';
        }  
        else    uc_v[0]='\x0000';
        
    };

    
    std::string to_uc()
    {
        if (uc_v.size()==0) 
        {
            return '\x0000';
        }
        
        std::string result="";
        
        
        if(uc_v.size()==1)
        {
            result+= uc_v[0];
            return result;
        }
        else if(uc_v.size()==2)
        {
            result+= uc_v[0];
            result+= uc_v[1];
            return result;
        }
        else if(uc_v.size()==3)
        {
            result+= uc_v[0];
            result+= uc_v[1];
            result+= uc_v[2];
            return result;
        }
        else if(uc_v.size()==4)
        {
            result+= uc_v[0];
            result+= uc_v[1];
            result+= uc_v[2];
            result+= uc_v[3];
            return result;
        }
        return std::string("Uchar.to_string reached out-of-bounds error");
    }
    
    
      const  char* c_str()  
    {
        if (uc_v.size()==0) 
        {
            return '\x0000';
        }
        
        short sz=uc_v.size();
        char result[sz];
        result[0]= char(uc_v[0]);
        
        if(sz==1)
        {
            result[1]='\n';
        }
        if(sz==2)
        {
            result[1]= char(uc_v[1]);
            result[2]='\n';
        }
        if(sz==3)
        {
            result[1]= char(uc_v[1]);
            result[2]= char(uc_v[2]);
            result[3]= '\n';
        }
        if(sz==4)
        {
            result[1]= char(uc_v[1]);
            result[2]= char(uc_v[2]);
            result[3]= char(uc_v[3]);
            result[4]='\n';
        }
        if(sz==5)
        {
            result[1]= char(uc_v[1]);
            result[2]= char(uc_v[2]);
            result[3]= char(uc_v[3]);
            result[4]=char(uc_v[4]);
            result[5]='\n';
        }
        if(sz==6)
        {
            result[1]= char(uc_v[1]);
            result[2]= char(uc_v[2]);
            result[3]= char(uc_v[3]);
            result[4]=char(uc_v[4]);
            result[5]=char(uc_v[5]);
            result[6]='\n';
        }
        
        return std::string(result).c_str();
  }
    
};


#endif // iBS_Uchar_h
