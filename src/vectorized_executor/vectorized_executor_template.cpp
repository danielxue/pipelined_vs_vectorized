#include <chrono>
#include <iostream>
#include <unistd.h>

#include "../common/store.h"
#include "../common/utils.h"
#include "../common/custom_bitset.h"

/*[[[cog
    import cog

    cog.outl("#define VE_FILENAME \"%s\"" % filename)
    cog.outl("#define VE_DATA_TYPE %s" % data_type)

    pred_words = predicates.split()

    col_names = []

    for i in range(len(pred_words)):
        if pred_words[i] == "AND":
            pred_words[i] = "&&"
        elif pred_words[i] == "=":
            pred_words[i] = "=="
        elif pred_words[i].isalpha():
            if pred_words[i] not in col_names:
                col_names.append(pred_words[i])
            pred_words[i] = "table[%d][i]" % col_names.index(pred_words[i])
]]]*/
//[[[end]]]

using namespace std;

int main(int argc, char* argv[]) {
    int ctl_fd;
    bool time;
    parseArgs(argc, argv, ctl_fd, time);

    Store<VE_DATA_TYPE> db {VE_FILENAME};
    /*[[[cog
        cog.outl("vector<string> colNames = {\"%s\"};" % "\", \"".join(col_names))
    ]]]*/
    //[[[end]]]
    vector<vector<VE_DATA_TYPE>> table = db.getColTable(colNames);
    Bitset res {db.numRows};
    Bitset cur {db.numRows};

    auto t1 = chrono::high_resolution_clock::now();

    if (ctl_fd != -1) write(ctl_fd, "enable\n", 8);

    /*[[[cog
        cog.outl((
           "for (size_t i = 0; i < db.numRows; i++) {\n"
           "   res[i] = %s;\n"
           "}"
        ) % " ".join(pred_words[:3]))
        for i in range(4, len(pred_words), 4):
            cog.outl((
               "for (size_t i = 0; i < db.numRows; i++) {\n"
               "   cur[i] = %s;\n"
               "}"
            ) % " ".join(pred_words[i:i+3]))
            cog.outl("res &= cur;")
    ]]]*/
    //[[[end]]]

    if (ctl_fd != -1) write(ctl_fd, "disable\n", 9);

    auto t2 = chrono::high_resolution_clock::now();
    if (time) std::cout << std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1).count() << std::endl;
}
