#ifndef TAPE_MAPPER_HEADER_H
#define TAPE_MAPPER_HEADER_H


#include "Tape.h"
#include <stdio.h>
#include <random>

/* creates Tape-format-file */
class TapeMapping
{
    
public:
    /*              fills the tape from file                        */
    /*                                                              */
    /* example: [ INT32 {delimeter} INT32 {delimeter} INT32 ... ]   */
    /*                                                              */
    static size_t load_from_file(FILE* from, Tape* to);

    /* fills the tape by random numbers */
    static int random_generate(Tape* to, size_t amount);

    /* fills the tape from memory */
    static int load_from_memory(Tape* to, int* mem, size_t len);
};

#endif