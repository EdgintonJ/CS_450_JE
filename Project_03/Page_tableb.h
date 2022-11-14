//
// Author: Jordan Edginton
// Class: CS 450
// Project 03
//

#include <vector>
#include <iostream>

using namespace std;

class Page_tableb {
public:
    Page_tableb(); // constructor
    void read_table(char* &input); // reads the table from the file in the command line argument
    void simulate_b(vector<int> inp); // simulates the page table using a vector created from user inputs

private:
    void print_table(); // prints table for debugging
    int bin_to_int(string bin); // converts a binary string to an integer
    string bin_to_hex(string bin); // converts a binary string into hexadecimal

    vector<int> valid; // our valid column of the page table
    vector<int> perm; // our permissions column of the page table
    vector<int> frame; // our frame column of the page table
    vector<int> used; // our used column of the page table
    int p_size; // physical memory size
    int v_size; // virtual memory size
    int t_size; // table size
    int offset; // how many bits is the offset
};

