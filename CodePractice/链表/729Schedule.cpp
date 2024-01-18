#include "../header.h"


class MyCalendar {
public:
    MyCalendar() = default;
    
    bool book(int start, int end) {
        for (auto& [l, r]: booked) {
            if (l < end && start < r) {
                return false;
            }
        }

        booked.emplace_back(start, end);
        return true;
    }

private:
    vector<pair<int, int>> booked;

private:
    set<pair<int, int>> booked_set;

public:
    bool book2(int start, int end) {
        auto it = booked_set.lower_bound({end, 0});

        if (it == booked_set.begin() || (--it)->second <= start) {
            booked_set.emplace(start, end);
            return true;
        }

        return false;
    }
};