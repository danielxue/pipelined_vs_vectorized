#ifndef PIPELINED_VS_VECTORIZED_BITSET_H
#define PIPELINED_VS_VECTORIZED_BITSET_H

#include <cstring>

class Bitset {
private:
    bool* data;
    size_t len;
public:
    Bitset(size_t len) : len(len) {
        data = (bool*)malloc(len);
        clear();
    }

    ~Bitset() {
        free(data);
    }

    void operator&=(Bitset& rhs) {
        if (len != rhs.size()) return;
        for (size_t i = 0; i < len; i++) {
            data[i] &= rhs[i];
        }
    }

    bool& operator[](size_t index) {
        return data[index];
    }

    size_t size() {
        return len;
    }

    void clear() {
        memset(data, 0, len);
    }
};

#endif
