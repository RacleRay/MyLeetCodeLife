#include <iomanip>
#include <iostream>
#include <fstream>

#include <cxxopts.hpp>
#include <range/v3/view/chunk.hpp>


// std::ranges::input_range is a concept.
// range must satisfy some constraints.
void hexdump(std::ranges::input_range auto const &range, std::size_t width = 16) {
    using T = std::ranges::range_value_t<decltype(range)>;

    std::size_t addr = 0;
    std::vector<char> saved_to_print;

    for (auto chunk: range | ranges::views::chunk(width)) {
        // print address
        std::cout << std::setw(8) << std::setfill('0') << std::hex << addr << ' ';

        // print hex and save the chars
        for (auto c: chunk) {
            std::cout << ' ' << std::right << std::hex << std::setw(2 * sizeof(T)) << std::setfill('0');
            std::cout << (std::uint64_t)(std::make_unsigned_t<T>)(c);
            ++addr;
            if constexpr (sizeof(T) == sizeof(char) && std::convertible_to<T, char>) {
                saved_to_print.push_back(static_cast<char>(c));
            }
        }

        // print ASCII
        if constexpr (sizeof(T) == sizeof(char) && std::convertible_to<T, char>) {
            // std::cout << ' ' << std::string_view(saved_to_print.data(), saved_to_print.size());
            // saved_to_print.clear();
            
            // not enough to fit a line
            if (addr % width != 0) {
                for (std::size_t i = 0; i < (width - addr % width) * 3; i++) {
                    std::cout << ' ';
                }
            }
            std::cout << " |";
            for (auto c: saved_to_print) {
                if (!std::isprint(c)) {
                    c = '.';
                }
                std::cout << c;
            }
            std::cout << "|";
            saved_to_print.clear();
        }

        std::cout << '\n';
    }
}


struct IfstreamRange {
    std::istreambuf_iterator<char> mBegin, mEnd;

    IfstreamRange(std::istream &ifs) 
    : mBegin(std::istreambuf_iterator<char>(ifs))
    , mEnd(std::istreambuf_iterator<char>()) 
    {}

    [[nodiscard]]
    auto begin() const {
        return mBegin;
    }

    [[nodiscard]]
    auto end() const {
        return mEnd;
    }
};


int main(int argc, char**argv) {
    cxxopts::Options options("hexodump", "print hexadecimal and ASCII representation of a file.");
    options.add_options()("f,file", "input file", cxxopts::value<std::string>()->default_value("-"));
    options.add_options()("w,width", "number of bytes per line", cxxopts::value<std::size_t>()->default_value("16"));

    options.add_options()("h, help", "print help infos");
    auto args = options.parse(argc, argv);
    if (args.count("help")) {
        std::cout << options.help() << std::endl;
        return 0;
    }

    auto path = args["file"].as<std::string>();
    auto width = args["width"].as<std::size_t>();

    if (path == "-") {
        // hex dump from stdin file name
        hexdump(IfstreamRange{std::cin}, width);
        return 0;
    }

    // From command line path
    std::ifstream ifs(path);
    if (!ifs.good()) {
        std::cerr << std::strerror(errno) << ": " << path << std::endl;
        return errno;
    }

    // hex dump
    hexdump(IfstreamRange{ifs}, width);

    return 0;
}