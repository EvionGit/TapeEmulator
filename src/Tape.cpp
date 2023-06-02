#include "Tape.h"


Tape::Tape(FILE* f, std::map<std::string, std::string>* conf) : f(f), io_delay(0),re_delay(0),shift_delay(0)
{
    /* set configs if exist */
    fstat(fileno(f), &meta);
    if (conf)
    {
        io_delay = atoi(conf->at("IO_DELAY").c_str());
        re_delay = atoi(conf->at("RE_DELAY").c_str());
        shift_delay = atoi(conf->at("SHIFT_DELAY").c_str());
    }
}

Tape::~Tape()
{
    fclose(f);
}

Tape* Tape::open_tape(const char* filename, const char* mode, std::map<std::string, std::string>* conf)
{
    /* returns pointer to Tape or 0 if error */
    FILE* inner = 0;
    if ((inner = fopen(filename, mode)) == 0)
        return 0;

    Tape* t = new Tape(inner, conf);
    return t;
}

void Tape::close_tape(Tape* tape)
{
    if (tape)
        delete tape;
}

int Tape::_read(int& data)
{
    /* delay simulation ( processor context +10-15ms in average) */
    std::this_thread::sleep_for(std::chrono::milliseconds(io_delay));

    /* reads int from current block and returns cursor at the beginning */
    int pos = ftell(f);
    if (fscanf(f, "|%i", &data) <= 0)
        return 0;

    fseek(f, pos, SEEK_SET);

    return 1;
}

int Tape::_write(const int& data)
{
    /* delay simulation ( processor context +10-15ms in average) */
    std::this_thread::sleep_for(std::chrono::milliseconds(io_delay));

    /* creates block and returns cursor at the beginning */
    int pos = ftell(f);
    std::string block, data_str = std::move(std::to_string(data));

    block.reserve(13);
    block = "|" + data_str + std::string(11 - data_str.size(), ' ') + "|";
    fwrite(block.c_str(), 1, BLOCKLEN, f);

    fseek(f, pos, SEEK_SET);

    return 1;
}

int Tape::_seek_start()
{
    /* delay simulation ( processor context +10-15ms in average) */
    std::this_thread::sleep_for(std::chrono::milliseconds(re_delay));

    fseek(f, 0, SEEK_SET);
    return 1;
}

int Tape::_seek_end()
{
    /* delay simulation ( processor context +10-15ms in average) */
    std::this_thread::sleep_for(std::chrono::milliseconds(re_delay));

    fseek(f, 0, SEEK_END);
    return 1;
}

int Tape::_next()
{
    /* delay simulation ( processor context +10-15ms in average) */
    std::this_thread::sleep_for(std::chrono::milliseconds(shift_delay));

    /* if not EOF sets cursor at the next block */
    int pos = ftell(f);
    fseek(f, 0, SEEK_END);


    if (pos == ftell(f))
        return 0;

    fseek(f, pos + BLOCKLEN, SEEK_SET);

    return 1;
}

int Tape::_prev()
{
    /* delay simulation ( processor context +10-15ms in average) */
    std::this_thread::sleep_for(std::chrono::milliseconds(shift_delay));

    /* if not start-pos sets cursor at the prev block */
    if (!ftell(f))
        return 0;

    fseek(f, -BLOCKLEN, SEEK_CUR);

    return 1;

}