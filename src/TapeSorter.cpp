#include "TapeSorter.h"

TapeSorter::TapeSorter(Tape* input, Tape* output, std::map<std::string, std::string>* conf) : cur_tmp(0),
                                                                                                  last_is_min(true),
                                                                                                  max_elements(-1)
{
    this->input = input;
    this->output = output;

    if (conf)
    {
        /* set restrictive using elements in memory */
        int elems = atoi(conf->at("MAX_ELEM").c_str());
        max_elements = elems >= 0 ? elems : UINT32_MAX;
    }

    /* create tmp files */
    tmps[0] = Tape::open_tape("tmp1.txt", "w+", conf);
    tmps[1] = Tape::open_tape("tmp2.txt", "w+", conf);
    tmp_size[0] = 0;
    tmp_size[1] = 0;

}

size_t TapeSorter::sort()
{
    /* sorts elements in the tree and saves data to a tmp file then merges temp files */
    /* MERGING SORT (N logN ) */

    std::multiset<int> tree;

    int data, m = 0, status = 0;
    while ((status = input->_read(data)) || !tree.empty())
    {
        if (status)
            tree.insert(data);

        /* if memory is full or input out of stock - flush data to tmp */
        if (!status || ++m >= max_elements)
        {
            int inner_data;
            tmps[cur_tmp]->_prev();
            while (!tree.empty() || tmp_size[cur_tmp])
            {

                /* 1. if remained only in a temp */
                if (tree.empty())
                {
                    tmps[cur_tmp]->_read(inner_data);
                    tmps[cur_tmp]->_prev();
                    tmp_size[cur_tmp]--;

                }
                /* 2. if remained only in the tree*/
                else if (!tmp_size[cur_tmp])
                {
                    inner_data = *tree.begin();
                    tree.erase(tree.begin());

                }

                /* 3. if remained in the both streams */
                else
                {

                    tmps[cur_tmp]->_read(inner_data);

                    /* need to sort data without rewinding file */
                    /*                                          */
                    /* if elements in tmp file are decreasing   */
                    if (last_is_min)
                    {
                        auto tree_min = tree.begin();
                        if (*tree_min > inner_data)
                        {
                            tmps[cur_tmp]->_prev();
                            tmp_size[cur_tmp]--;
                        }
                        else
                        {
                            inner_data = *tree_min;
                            tree.erase(tree_min);
                        }
                    }
                    /* if elements in tmp file are increasing */
                    else
                    {
                        auto tree_max = --tree.end();
                        if (*tree_max <= inner_data)
                        {
                            tmps[cur_tmp]->_prev();
                            tmp_size[cur_tmp]--;
                        }
                        else
                        {
                            inner_data = *tree_max;
                            tree.erase(tree_max);
                        }
                    }


                }

                /* add value to another tmp file */
                tmps[(cur_tmp + 1) % 2]->_write(inner_data);
                tmps[(cur_tmp + 1) % 2]->_next();
                tmp_size[(cur_tmp + 1) % 2]++;
            }

            /* change tmp file to next */
            cur_tmp = (cur_tmp + 1) % 2;
            /* change ordered in tmp */
            last_is_min = !last_is_min;
            m = 0;
        }


        input->_next();
    }




    /* write sorted data to output */
    int sorted_data;
    size_t int_count = 0;

    if (!last_is_min)
        tmps[cur_tmp]->_seek_start();

    tmps[cur_tmp]->_prev();
    while (tmp_size[cur_tmp])
    {
        tmps[cur_tmp]->_read(sorted_data);
        output->_write(sorted_data);
        output->_next();
        last_is_min ? tmps[cur_tmp]->_prev() : tmps[cur_tmp]->_next();
        tmp_size[cur_tmp]--;
        int_count++;
    }

    return int_count;
}

TapeSorter::~TapeSorter()
{
    Tape::close_tape(tmps[0]);
    Tape::close_tape(tmps[1]);
}
