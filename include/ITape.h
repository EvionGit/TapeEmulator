#ifndef TAPE_INTERFACE_HEADER_H
#define TAPE_INTERFACE_HEADER_H

/* interface for Tape I/O with manipulating INT32 values */
class ITape
{
   
protected:
    virtual int _read(int& data) = 0;
    virtual int _write(const int& data) = 0;
    virtual int _next() = 0;
    virtual int _prev() = 0;
    virtual int _seek_start() = 0;
    virtual int _seek_end() = 0;


};

#endif

