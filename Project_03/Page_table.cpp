//
// Author: Jordan Edginton
// Class: CS 450
// Project 03
//

#include "Page_table.h"
#include <iostream>
#include <fstream>
#include <cmath>
#include <bitset>

using namespace std;

Page_table::Page_table(){
    p_size = 0;
    v_size = 0;
    offset = 0;
    t_size = 0;
}

void Page_table::read_table(char* &input) {
    // This is where we read the input table and fill out our page table.
    int hold;
    ifstream ifile(input);
    if (!ifile.is_open()) {
        cout << "Unable to open input file: " << input;
        exit(1);
    }
    ifile >> v_size;
    ifile >> p_size;
    ifile >> t_size;
    offset = log2(t_size);
    int i = 0;
    while(ifile >> hold){
        if (i == 0) {
            valid.push_back(hold);
            i++;
        }
        else if (i == 1) {
            perm.push_back(hold);
            i++;
        }
        else if (i == 2) {
            frame.push_back(hold);
            i++;
        }
        else if (i == 3) {
            used.push_back(hold);
            i = 0;
        }
    }
    ifile.close();
}


void Page_table::simulate_a(vector<int> inp){
    // This is where we simulate the page table for problem a. We take our input vector and go through each input
    // one by one. We first determine it's index and make sure the index is valid. If not, we check it's permissions.
    // if both are 0, we print SEGFAULT, but if the permission isn't 0, then we print DISK.
    // If the index is valid, we print the address.
    int idx, q = 0;
    string inp_str, f_str, p_add;

    for (int n = 0; n < inp.size(); n++){
        idx = floor(inp[n] / t_size);
        p_add = "";
        if (valid[idx] == 0){
            if (perm[idx] == 0){
                cout << "SEGFAULT" << endl;
            }
            else{
                cout << "DISK" << endl;
            }
        }
        else{
            inp_str = bitset<64>(inp[n]).to_string();
            f_str = bitset<64>(frame[idx]).to_string();

            for (int k = p_size - offset; k > 0; k--){
                p_add += f_str[f_str.size() - k];
                q++;
                if (q == 4){
                    q = 0;
                }
            }
            for (int i = offset; i > 0; i--){
                p_add += inp_str[inp_str.size() - i];
                q++;
                if (q == 4){
                    q = 0;
                }
            }
            cout << bin_to_int(p_add) << endl;
        }
    }
}


int Page_table::bin_to_int(string bin){
    // This translates binary into dedcimal for printing.
    int ret = 0, t;
    for (int i = 0; i < bin.size(); i++){
        if (bin[bin.size() - i - 1] == '0')
            t = 0;
        else
            t = 1;
        ret += t * pow(2, i);
    }
    return ret;
}


void Page_table::print_table(){
    // This is used to print the table for debugging purposes.
    for (int i = 0; i < valid.size(); i++){
        cout << valid[i] << " " << perm[i] << " " << frame[i] << " " << used[i] << endl;
    }
}


string Page_table::bin_to_hex(string bin){
    // This is used to translate binary into hexadecimal.
    // This is for the optional hexadecimal output, but is not used.
    string ret, t;
    int hold = 0;
    for (int i = 0; i < bin.size(); i++){
        hold = (int)bin[bin.size() - i - 1] * pow(16, i);
        if (hold > 9){
            if (hold == 10)
                t = "a";
            else if (hold == 11)
                t = "b";
            else if (hold == 12)
                t = "c";
            else if (hold == 13)
                t = "d";
            else if (hold == 14)
                t = "e";
            else
                t = "f";
            ret += t;
        }
        else
            ret += to_string(hold);
    }
    return ret;
}


