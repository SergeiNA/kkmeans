#pragma once

#include <vector>
#include <iostream>

#include "common.hpp"


void print(const std::vector<sample_type>& points,
        const std::vector<int>& cluster_class, std::ostream& out = std::cout);

