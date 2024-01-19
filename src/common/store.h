#ifndef PIPELINED_VS_VECTORIZED_STORE_H
#define PIPELINED_VS_VECTORIZED_STORE_H

#include <array>
#include <fstream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

template<typename T>
class Store {
private:
    vector<string> colNames;
    unordered_map<string, vector<T>> cols;
public:
    size_t numRows {};

    Store(const string& fileName) {
        ifstream fin {fileName};

        // Parse db file.
        fin >> numRows;

        string colNamesStr;
        fin >> colNamesStr;
        istringstream ss(colNamesStr);
        string colName;
        while (std::getline(ss, colName, ',')) {
            colNames.push_back(colName);
        }

        T curVal;
        for (string& colName : colNames) {
            vector<T>& curCol = cols[colName];
            for (size_t j = 0; j < numRows; j++) {
                fin >> curVal;
                curCol.push_back(curVal);
            }
        }
    }

    vector<vector<T>> getColTable() {
        return getColTable(colNames);
    }

    vector<vector<T>> getColTable(const vector<string>& proj)  {
        vector<vector<T>> table;
        for (const string& colName : proj) {
            table.push_back(cols[colName]);
        }
        return table;
    }

    template<size_t N>
    vector<array<T, N>> getRowTable()  {
        return getRowTable<N>(colNames);
    }

    template<size_t N>
    vector<array<T, N>> getRowTable(const vector<string>& proj) {
        vector<array<T, N>> table;
        for (size_t i = 0; i < numRows; i++) {
            array<T, N> row;
            for (size_t j = 0; j < proj.size(); j++) {
                row[j] = cols[proj[j]][i];
            }
            table.emplace_back(row);
        }
        return table;
    }
};

#endif
