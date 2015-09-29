# UTF-8_Vector

Is a UTF-8 Char in C++

Creates a UTF-8 vector of <unsigned char> from a Unicode.

Note: Even though Bjarn Stroustrup was not a direct contributor.  His vector was used and his lectures were a big influence.

UTF-8_Vector Lib Consist:


Uchar.h
    Simply by putting this header in your C++ project you can have a 
        container for a single UTF-8 char.

    iBS::Uchar struct v1.0 is ready.
        - Encode from an Unicode to UTF-8 formatted Uchar.
            iBS::Uchar uc = 0x03a9;//Ω    
        - Decode returning a Unicode as an unsigned integer.
            unsigned int unicode = uc.Decode();   

Ufunc.h 
    
    iBS::BitBull
       - short iBS::BitBull::ByteCount(unsigned char byte) 
            returns 0 if not lead byte or not UTF-8 formated 
            else returns number of ,8 bit bytes, it takes to contain it. 
       -  bool iBS::BitBull::isTrailByte(unsigned char byte) 
            returns true if it is a trailing byte in UTF-8 format   

Udat.h  
    inop, still under construction.

Ustr.h
    inop, still under construction.
