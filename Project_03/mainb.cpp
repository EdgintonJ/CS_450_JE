//
// Author: Jordan Edginton
// Class: CS 450
// Project 03
// This is the main file for the page table simulator project. In the main file we take the command line argument,
// read the file that was input, and create a page table using the info on the file. After the table is created we
// take the redirected input from the user and read the file via multiple cin statements and put them into a vector.
//

#include <iostream>
#include <vector>
#include <cmath>
#include "Page_tableb.h"

using namespace std;

vector<int> read_input();
int hex_to_decimal(string hex);


vector<int> read_input(){
    // This is where we read our input from the redirected file. We also call the hex_to_decimal function to translate
    // the hex numbers when needed.
    vector<int> retvec;
    string hold;
    int dec;
    while (cin >> hold){
        if (hold[1] == 'x')
            dec = hex_to_decimal(hold);
        else
            dec = stoi(hold);
        retvec.push_back(dec);}
    return retvec;
}


int hex_to_decimal(string h){
    // Since some of the inputs are hexadecimal, we need to convert them into decimal. I didn't know of any
    // quick way to do it so i made a function.
    int ret = 0, hold;
    for (int i = h.size() - 1; i > 1; i--){
        if (h[i] == 'a' || h[i] == 'b' || h[i] == 'c' || h[i] == 'd' || h[i] == 'e' || h[i] == 'f'){
            if (h[i] == 'a')
                hold = 10;
            else if (h[i] == 'b')
                hold = 11;
            else if (h[i] == 'c')
                hold = 12;
            else if (h[i] == 'd')
                hold = 13;
            else if (h[i] == 'e')
                hold = 14;
            else
                hold = 15;
        }
        else{
            hold = static_cast<int>(h[i]) - 48;
        }
        ret += hold * pow(16, h.size() - i - 1);
    }
    return ret;
}

int main(int argc, char* argv[]) {
    // Here we read the command line and use the first argument to create a page table. After that we call
    // read_input() to create our input vector for testing. When we have both ready, we simulate the page table.
    if (argc != 2) {
        cout << "Incorrect input. Correct format: ./<exectuable.out> <inputtable.txt>\n";
        return 1;
    }

    Page_tableb table;

    table.read_table(argv[1]);

    vector<int> input_vec = read_input();

    table.simulate_b(input_vec);

    return 0;
}
