#include <chrono>
#include <iostream>
#include <unistd.h>

#include "../common/store.h"
#include "../common/utils.h"
#include "../common/custom_bitset.h"

#define PLE_FILENAME "data/data.txt"
#define PLE_DATA_TYPE int32_t

using namespace std;

int main(int argc, char* argv[]) {
    int ctl_fd;
    bool time;
    parseArgs(argc, argv, ctl_fd, time);

    Store<PLE_DATA_TYPE> db {PLE_FILENAME};
    vector<string> colNames = {"A", "B", "C", "D", "E", "F", "G"};
    vector<vector<PLE_DATA_TYPE>> table = db.getColTable(colNames);
    Bitset res {db.numRows};

    auto t1 = chrono::high_resolution_clock::now();

    if (ctl_fd != -1) write(ctl_fd, "enable\n", 8);

    for (size_t i = 0; i < db.numRows; i++) {
        if (table[0][i] < 50 && table[1][i] < 50 && table[2][i] < 50 && table[3][i] < 50 && table[4][i] < 50 && table[5][i] < 50 && table[6][i] < 50) {
           res[i] = true;
        }
    }

    if (ctl_fd != -1) write(ctl_fd, "disable\n", 9);

    auto t2 = chrono::high_resolution_clock::now();
    if (time) std::cout << std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1).count() << std::endl;
}
