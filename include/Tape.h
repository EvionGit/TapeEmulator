#ifndef TAPE_EMULATOR_HEADER_H
#define TAPE_EMULATOR_HEADER_H


#include "ITape.h"
#include<stdio.h>
#include<map>
#include<set>
#include<string>
#include<chrono>
#include<thread>


#define BLOCKLEN 13 // block len in file (11 chars for INT32 value + 2 for delimeters)

/* Tape<INT32> emulator */
class Tape : public ITape
{

private:
    FILE* f;
    int io_delay, re_delay, shift_delay;

private:
    Tape(FILE* f, std::map<std::string, std::string>& conf);
    ~Tape();


public:
    /* open tape context */
    static Tape* open_tape(const char* filename, const char* mode, std::map<std::string, std::string>& conf);
    
    /* close tape context */
    static void close_tape(Tape* tape);

    /* read block from tape */
    virtual int _read(int& data) override;

    /* write to block */
    virtual int _write(const int& data) override;

    /* set cursor to the first block */
    virtual int _seek_start() override;

    /* set cursor to the end block */
    virtual int _seek_end() override;

    /* set cursor to the next block */
    virtual int _next() override;
    
    /* set cursor to the prev block */
    virtual int _prev() override;
        

};

#endif
