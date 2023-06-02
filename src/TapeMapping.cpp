#include "TapeMapping.h"

size_t TapeMapping::load_from_file(FILE* from, Tape* to)
{
    if (!from || !to)
        return 0;
    /* fills and returns cursor at the beggining of tape */
    int val;
    size_t count = 0;
    while (fscanf(from, "%i", &val) > 0)
    {
        to->_write(val);
        to->_next();
        count++;
    }
    to->_seek_start();
    return count;
}

int TapeMapping::random_generate(Tape* to, size_t amount)
{
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<> randomizer(INT32_MIN, INT32_MAX);

    /* fills and returns cursor at the beggining of tape */
    for (size_t i = 0; i < amount; i++)
    {
        to->_write(randomizer(rng));
        to->_next();
    }
    to->_seek_start();

    return 1;
}

int TapeMapping::load_from_memory(Tape* to, int* mem, size_t len)
{
    if (!mem)
        return 0;
    /* fills and returns cursor at the beggining of tape */

    for (size_t i = 0; i < len; i++)
    {
        to->_write(mem[i]);
        to->_next();
    }

    to->_seek_start();

    return 1;
}
