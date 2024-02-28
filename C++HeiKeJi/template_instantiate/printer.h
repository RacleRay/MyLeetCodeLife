#include <deque>
#include <iostream>
#include <list>
#include <set>
#include <unordered_set>
#include <vector>


struct printer {
public:
    printer(): out(std::cout) {}
    printer(std::ostream &out): out(out) {}

    printer(printer &&) = delete;

    ~printer() {
        if (first) {
            return;
        }
        out << "\n";
    }

public:
    template<typename T>
    printer &operator,(T const & t) {
        if (first) {
            first = false;
        } else {
            out << ", ";
        }
        out << t;
        return *this;
    }

    template<class ...Ts>
    printer& operator,(std::tuple<Ts...> const &t) {
        [&]<size_t ...Is>(std::index_sequence<Is...>) {
            (operator,(std::get<Is>(t)), ...);
        }(std::index_sequence_for<Ts...>{});
    }

    template<class T>
    printer &operator,(std::vector<T> const &t) {
        for (auto const &e : t) {
            operator,(e);
        }
        return *this;
    }

    template <class T>
    printer &operator,(std::list<T> const &t) {
        for (auto const &x: t) {
            operator,(x);
        }
        return *this;
    }

    template <class T>
    printer &operator,(std::deque<T> const &t) {
        for (auto const &x: t) {
            operator,(x);
        }
        return *this;
    }

    template <class T>
    printer &operator,(std::set<T> const &t) {
        for (auto const &x: t) {
            operator,(x);
        }
        return *this;
    }

    template <class T>
    printer &operator,(std::unordered_set<T> const &t) {
        for (auto const &x: t) {
            operator,(x);
        }
        return *this;
    }

public:
    std::ostream &out;
    bool first = true;
};