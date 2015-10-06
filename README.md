# UTF-8_Vector

Is a UTF-8 Char in C++

Creates a UTF-8 vector of <unsigned char> from a Unicode.

Note: Even though Bjarn Stroustrup was not a direct contributor.  His vector was used and his lectures were a big influence.

UTF-8_Vector Lib Consist:

Simply by putting this header in your C++ project you can have a 
container for a single UTF-8 char.


Uchar.h
    iBS::u8char struct v1.1 is ready.

        - Encode from an Unicode to UTF-8 formatted Uchar.
            iBS::Uchar uc = 0x03a9;//Ω    

        - Decode returning a Unicode as an unsigned integer.
            unsigned int unicode = uc.Decode();   

        - short iBS::ByteCount(unsigned char byte) 
            returns 0 if not lead byte or not UTF-8 formated 
            else returns number of ,8 bit bytes, it takes to contain it. 

        -  bool iBS::isTrailByte(unsigned char byte) 
            returns true if it is a trailing byte in UTF-8 format   

Ufunc.h 
    bool iBS::isOn(unsigned char byte, short index)
    void iBS::display_bits(unsigned char uc)
    void iBS::display_bits(unsigned short us)
    void iBS::display_bits(unsigned int ui)
    void iBS::display_bits(int i)
    void iBS::display_bits(size_t i)

Unum.h      // under construction, new formate for a compact string number 
    
    struct  unum    //unaversal  number
        //0x0-0x9==0-9  a==A b==+ c==- d==. e==∞ f==Ω

        unum& operator=(const unum& x)
        size_t size() const 
        bool  is_signed()
        bool has_dec(){return dec_index;};   
        unum& operator=(int& x)


Udat.h  
    inop, still under construction.

Ustr.h
    inop, still under construction.
