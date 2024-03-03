#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;


struct Memory {
    int offset{0};
    int size{0};
};


int main() {
    int malloc_size;
    cin >> malloc_size;

    if (malloc_size <= 0 || malloc_size > 100) {
        cout << -1 << endl;
        return 0;
    }

    vector<Memory> used_memory;
    do {
        int offset, size;
        cin >> offset >> size;
        used_memory.push_back({offset, size});
    } while (!cin.eof());
    sort(used_memory.begin(), used_memory.end(), [](Memory& lhs, Memory& rhs) {
        return lhs.offset < rhs.offset;
    });


    int malloc_offset = -1;
    int min_malloc_size = 100;
    int free_offset = 0;
    for (const auto &used: used_memory) {
        if (used.offset < free_offset || used.offset > 99 || used.size <= 0 || used.size > 100 - used.offset) {
            cout << -1 << endl;
            return 0;
        }
        
        if (used.offset > free_offset) {
            int free_memory_size = used.offset - free_offset;
            if (free_memory_size >= malloc_size && free_memory_size < min_malloc_size) {
                malloc_offset = free_offset;
                min_malloc_size = free_memory_size;
            }
        }

        free_offset = used.offset + used.size;
    }

    int last_free_memory_size = 100 - free_offset;
    if (last_free_memory_size >= malloc_size && last_free_memory_size < min_malloc_size) {
        malloc_offset = free_offset;
        min_malloc_size = last_free_memory_size;
    }

    cout << malloc_offset << endl;

    return 0;
}