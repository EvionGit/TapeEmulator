#include "../include/TapeMapping.h"

#include <stdio.h>
#include <cstring>

int main(int argc, char* argv[])
{   
    const char* help = "<program> <output file> <key> <value>\n-------------------------------------\nKeys:\n-R : random int numbers. {value: amount}\n-I : input file for map (format: [ <INT> <DELIMETER> <INT> <DELIMETER> ... ]) {value: path to file}\n";

    if(argc < 4)
    {   
        printf("%s",help);
        return -1;
    }    


    Tape* from = 0, *to = 0;
    FILE* from_file = 0;
    std::map<std::string,std::string> conf;

    if(!strcmp(argv[2],"-R"))
    {
        long long count = (long long)atoll(argv[3]);
        if(count == 0)
        {
            printf("-R value must be greater than 0\n");
            return -1;
        }
        
        to = Tape::open_tape(argv[1],"w+",conf);
        if(!to)
        {
            printf("output-file opening error\n");
            return -1;
        }

        TapeMapping::random_generate(to,count);
        Tape::close_tape(to);
    }
    else if(!strcmp(argv[2],"-I"))
    {
      
        to = Tape::open_tape(argv[1],"w+",conf);
        from_file = fopen(argv[3],"r");

        if(to && from_file)
        {
            TapeMapping::load_from_file(from_file,to);
        }
        Tape::close_tape(to);
        fclose(from_file);
         
    }
    else
    {
        printf("%s",help);
        return -1;
    }

    
    return 0;
}

