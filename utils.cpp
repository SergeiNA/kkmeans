#include "utils.hpp"

#include <string>
#include <sstream>

std::vector<sample_type> getSamples(std::istream& in) {
    std::vector<sample_type> samples;
    char delim;
    for (std::string line; std::getline(in, line);) {
        if (!line.empty()) {
            std::istringstream iss(std::move(line));
            sample_type m;
            iss>>m(0)>>delim>>m(1);
            samples.push_back(m);
        }
    }
    return samples;
}