# TapeEmulator
Tape I/O emulator over file. Tape doesn't have random access and manipulates only integers (INT32_T).
___

## Build
```
mkdir build
cd build
cmake ..
cmake --build .

```

## Structure of a tape file
The file is divided into blocks of 13 bytes (2 bytes for delimeters).
11 chars fit the entire range of an INTEGER [-2147483648; 2147483647].

```
|-2147483648||-99900     ||105        ||1          ||147483     |...
```

This structure allows you to overwrite an cell without the need to recreate the file or shift elements.

___

## Executable files
+ ```TapeSorter <input file> <output file> [-c config]```
  + Sorts elements from INPUT-tape to OUTPUT-tape
  + ```-c``` config file sets I/O delays and maximum number of processed items in RAM.
  + To sort into the available RAM, the data is loaded sequentially and sorted in a binary tree. 
  Then the sorted data is dumped into temporary files and a new portion of elements is uploaded to the tree. 
  Then there is a merge sort between the data in the tree and in the temporary file.
  
+ ```TapeMapper <output file> [-R elem amount | -I input file]```
  + ```-R``` generates N random elements and saves them into OUTPUT-tape
  + ```-I``` converts data from a delimited input file. 

+ ```TapeSorterTests <tests amount>```
  + creates ```N``` random tests of random length and tests the sorter

___

## Config file
The configuration file emulates I/O delays ```IO_DELAY```, carriage offsets ```SHIFT_DELAY```, and tape rewinds ```RE_DELAY```. 
And also sets the maximum number of elements that can be processed in RAM at the same time ```MAX_ELEMS```
```
# Tape emulating configuration
# Format:
#   KEY=VALUE
#
# Delay in ms
IO_DELAY=10
RE_DELAY=100
SHIFT_DELAY=5
#
# Max elements using in memory(INT32_T)
MAX_ELEM=100
```

