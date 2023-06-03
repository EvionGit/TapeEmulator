#include "../include/Tape.h"
#include "../include/TapeSorter.h"

#include<iostream>
#include<fstream>
#include<map>
#include<cstring>

int main(int argc, char* argv[])
{
    

    if(argc < 3)
    {
        printf("Need more arguments: <program> <input file> <output file> [-c {conf file path}]\n");
        return -1;
    }
   


    std::map<std::string, std::string> conf;
    std::ifstream f_conf;

    if(argc >= 5 && !strcmp(argv[3],"-c"))
        f_conf.open(argv[4]);
    

    if(f_conf.is_open())
    {

        std::string line;
        while (std::getline(f_conf, line))
        {
            if (line[0] == '#')
                continue;

            int delim = line.find('=');
            conf.insert(std::make_pair(line.substr(0, delim), line.substr(delim + 1)));
        }
     }
   
   
    Tape* in_t = Tape::open_tape(argv[1], "r", conf);
    Tape* ou_t = Tape::open_tape(argv[2], "w+", conf);

    TapeSorter sorter(in_t,ou_t,conf);

    std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();
    size_t elems = sorter.sort();
    printf("%zu elements sorted in %li ms\n", elems, (std::chrono::high_resolution_clock::now() - t1).count() / 1000000);

    Tape::close_tape(in_t);
    Tape::close_tape(ou_t);

    
	return 0;
}
