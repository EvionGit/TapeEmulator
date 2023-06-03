#include "../include/Tape.h"
#include "../include/TapeSorter.h"
#include "../include/TapeMapping.h"

#include <cassert>
#include <vector>
#include <algorithm>

/* loads data from vector to tmp file and sorts. Then returns sorted values in vector */
std::vector<int> sort_from_mem(std::vector<int>& data)
{   
    std::vector<int> res;
    res.reserve(data.size());

    std::map<std::string,std::string> empty_conf;

    Tape* tmp_input = Tape::open_tape("/tmp/tmp_vals","w+",empty_conf);
    Tape* tmp_output = Tape::open_tape("/tmp/tmp_sorted","w+",empty_conf);

    if(!tmp_input || !tmp_output)
        return res;

    /* load to tape-file from vector */
    TapeMapping::load_from_memory(tmp_input,data.data(),data.size());
    
    TapeSorter sorter(tmp_input,tmp_output,empty_conf);

    /* sorting data */
    sorter.sort();

    
    /* read data to vector */
    int d;
    tmp_output->_seek_start();
    while(tmp_output->_read(d))
    {
        res.push_back(d);
        tmp_output->_next();
    }


    Tape::close_tape(tmp_output);
    Tape::close_tape(tmp_input);
    return res; 
}

/* random generator */
std::vector<int> generate_elements()
{
    std::vector<int> res;
    
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<> randomizer(0, INT16_MAX);

    long long size = randomizer(rng);
    res.reserve(size);

    std::uniform_int_distribution<> randomizer_val(INT32_MIN,INT32_MAX);
    for(long long i = 0; i < size;i++)
    {
        res.push_back(randomizer_val(rng));
    }

    return res;
    
}


int main(int argc, char* argv[])
{
    if(argc < 2)
    {
        printf("<program> <tests amount>\n");
        return -1;
    }

    long long count = atoll(argv[1]);
    if(count < 1)
        return -1;
   
    printf("# Tests amount: %lli #\n",count);
    printf("----------------------\n");

    std::vector<int> res, test_values;
    for(long long i = 0; i < count; i++)
    {
        test_values = std::move(generate_elements());

        printf("Test #%lli: [%li] elements -- ",i+1,test_values.size());
        res = std::move(sort_from_mem(test_values));
    
        /* sort elements in the test-vector */
        std::sort(test_values.begin(), test_values.end());

        /* drops if incorrect */
        assert(res == test_values);

        printf("OK\n");
    }
    
    printf("----------------------\n");
    printf("# Tests successfully completed #\n");
    return 0;
}
