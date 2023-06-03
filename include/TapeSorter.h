#ifndef TAPE_SORTER_HEADER_H
#define TAPE_SORTER_HEADER_H

#include "Tape.h"

/* sorts elements in Tape */
class TapeSorter
{
private:
    Tape* tmps[2]; // pointers to the temp files
    size_t tmp_size[2]; // count elements in temp files
    int cur_tmp; // current temp file to write

    bool last_is_min; // flag for fetching the last element in a temp file without rewinding

    Tape* input, * output; // pointers to the I/O tapes
    uint32_t max_elements; // max elements saved in memory at the same time

public:
    TapeSorter(Tape* input, Tape* output, std::map<std::string, std::string>& conf);
   
    /* sort elements from INPUT to OUTPUT */
    size_t sort();

    ~TapeSorter();
};

#endif
