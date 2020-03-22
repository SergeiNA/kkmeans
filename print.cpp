#include "print.hpp"

void print(const std::vector<sample_type>& samples,
                  const std::vector<int>& cluster_class, std::ostream& out)
{
    assert(samples.size() == cluster_class.size());
    for (size_t i = 0; i < samples.size(); ++i) {
        out << samples[i](0) << ','
            << samples[i](1) << ','
            << cluster_class[i] << '\n';
    }
}
