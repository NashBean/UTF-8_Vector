//
//  Ufunc.h
//
//
//  Created by nash on 9/28/15.
//  Copyright 2015 iBean Software.
//
//  Distributed under the Apache License, Version 2.0.
//  See the accompanying file LICENSE or http://www.apache.org/licenses/LICENSE-2.0.html
//

#ifndef iBS_Ufunc_h//  Unicode and UTF-8 Functions.
#define iBS_Ufunc_h//  Also yoUr Funk :)   

namespace iBS 
{
    
class BitBull
{
    //unsigned char lead_byte;      
    
public://-----------------------------
    //setLeadByte(unsigned char byte){lead_byte=byte};
    
    bool isOn(unsigned char byte, short index)//right2left index 
    { return (byte & 1<<index) };

    bool isLeadByte(unsigned char byte)
    { return (byte & 0x80)==0; };
    
    bool isTrailByte(unsigned char byte)
    { return (byte & 0x80)&&(byte & 0x40==0); };

    short ByteCount(unsigned char byte) //has tobe lead byte
    {//  return  0 if not lead byte 
        if ((byte & 0x80)==0) { return 1; }
        short result=0;
        if (byte & 0x80) result++;
        if (byte & 0x40) result++;
        if (result != 2) return 0;//this was not lead byte or not UTF-8 format 
        else return result;
        if (byte & 0x10) result++;
        else return result;
        if (byte & 0x08) result++;
        else return result;
        if (byte & 0x04) result++;  
        else return result;
        if (byte & 0x02) return 0;//this was not UTF-8 format  
        return result;
    };
};


}//end of iBS namespace  

#endif // iBS_Ufunc_h