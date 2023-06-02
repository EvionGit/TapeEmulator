#include "Tape.h"
#include "TapeMapping.h"
#include "TapeSorter.h"

#include<iostream>
#include<fstream>

#pragma warning(disable: 4996)

int main()
{
    std::map<std::string, std::string>* conf = 0;

    std::ifstream f_conf("confs.txt", std::ios_base::in);

    if(f_conf)
    {
        conf = new std::map<std::string, std::string>;

        std::string line;
        while (std::getline(f_conf, line))
        {
            if (line[0] == '#')
                continue;

            int delim = line.find('=');
            conf->insert(std::make_pair(line.substr(0, delim), line.substr(delim + 1)));
        }
    }
   




    Tape* in_t = Tape::open_tape("vals.txt", "w+", conf);
    Tape* ou_t = Tape::open_tape("sorted_vals.txt", "w+", conf);

    std::vector<int> v{ 1,-2,525,15,7845684,515,-525,-525,-6463,-625,-512,4677 };
    TapeMapping::load_from_memory(in_t, v.data(), v.size());


    TapeSorter sorter(in_t, ou_t, conf);

    std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();
    size_t elems = sorter.sort();
    printf("%zu elements sorted in %lli ms\n", elems, (std::chrono::high_resolution_clock::now() - t1).count() / 1000000);

    delete conf;
    Tape::close_tape(in_t);
    Tape::close_tape(ou_t);

    
	return 0;
}