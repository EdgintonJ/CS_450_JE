//
// Author: Jordan Edginton
// Class: CS 450
// Project 03
//

#include "Page_tableb.h"
#include <iostream>
#include <fstream>
#include <cmath>
#include <bitset>

using namespace std;

Page_tableb::Page_tableb(){
    p_size = 0;
    v_size = 0;
    offset = 0;
    t_size = 0;
}

void Page_tableb::read_table(char* &input) {
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


void Page_tableb::simulate_b(vector<int> inp) {
    // This is where we simulate the page table for problem b. we take our input vector and go through each input
    // one by one. We first determine it's index and make sure the index is valid. If not, we check it's permissions.
    // if both are 0, we print SEGFAULT, but if the permission isn't 0, then we print PAGEFAULT and prints it's new
    // position in the table. if the index is valid, we print the address.
    int idx, q = 0, clok = 0, pfault = 0;
    string inp_str, f_str, p_add;

    for (int d = 0; d < valid.size(); d++) {
        if (valid[d] == 1){
            clok = d;
            break;
        }
    }

    for (int n = 0; n < inp.size(); n++) {
        idx = floor(inp[n] / t_size);
        p_add = "";
        if (valid[idx] == 0) {
            if (perm[idx] == 0) {
                cout << "SEGFAULT" << endl;
            } else {
                cout << "PAGEFAULT ";
                pfault = 1;
                int v = 0;
                while(true){
                    if (valid[clok] == 0){
                        clok++;
                        v++;
                        if (v > used.size()){
                            cout << "ERROR, No valid entries to evict in list.";
                            exit(1);
                        }
                    }
                    else if (used[clok] > 0){
                        used[clok]--;
                        clok++;
                        v = 0;
                    } else{
                        break;
                    }
                    if (clok == used.size())
                        clok = 0;
                }
                idx = clok;
            }
        }
        if (valid[idx] == 1 || pfault == 1) {
            inp_str = bitset<64>(inp[n]).to_string();
            f_str = bitset<64>(frame[idx]).to_string();

            for (int k = p_size - offset; k > 0; k--) {
                p_add += f_str[f_str.size() - k];
                q++;
                if (q == 4) {
                    q = 0;
                }
            }
            for (int i = offset; i > 0; i--) {
                p_add += inp_str[inp_str.size() - i];
                q++;
                if (q == 4) {
                    q = 0;
                }
            }
            used[idx] += 1;
            cout << bin_to_int(p_add) << endl;
            pfault = 0;
        }
    }
}


int Page_tableb::bin_to_int(string bin){
    // This translates binary into dedcimal for printing.
    int ret = 0, t;;
    for (int i = 0; i < bin.size(); i++){
        if (bin[bin.size() - i - 1] == '0')
            t = 0;
        else
            t = 1;
        ret += t * pow(2, i);
    }
    return ret;
}


void Page_tableb::print_table(){
    // This is used to print the table for debugging purposes.
    for (int i = 0; i < valid.size(); i++){
        cout << valid[i] << " " << perm[i] << " " << frame[i] << " " << used[i] << endl;
    }
}


string Page_tableb::bin_to_hex(string bin){
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
