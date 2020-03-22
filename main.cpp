#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>

#include <dlib/clustering.h>
#include <dlib/rand.h>

#include "common.hpp"
#include "print.hpp"
#include "utils.hpp"

using namespace std;
using namespace dlib;


int main(int argc, char* argv[]){
    if (argc <= 1) {
        cout << "kkmeans <n> \n"
                "n -- clusters number\n"
                "Example: cat input.txt | kkmeans 4\n";
        return 0;
    }

    std::string nClusters(argv[1]);

    if (!(std::all_of(nClusters.begin(), nClusters.end(), ::isdigit))) {
        std::cerr << "Number of clusrers is incorrect" << std::endl;
        return 1;
    }
    std::size_t nclst = std::stoul(nClusters);
    // Now we are making a typedef for the kind of kernel we want to use.  I picked the
    // radial basis kernel because it only has one parameter and generally gives good
    // results without much fiddling.
    typedef radial_basis_kernel<sample_type> kernel_type;


    // Here we declare an instance of the kcentroid object.  It is the object used to 
    // represent each of the centers used for clustering.  The kcentroid has 3 parameters 
    // you need to set.  The first argument to the constructor is the kernel we wish to 
    // use.  The second is a parameter that determines the numerical accuracy with which 
    // the object will perform part of the learning algorithm.  Generally, smaller values 
    // give better results but cause the algorithm to attempt to use more dictionary vectors 
    // (and thus run slower and use more memory).  The third argument, however, is the 
    // maximum number of dictionary vectors a kcentroid is allowed to use.  So you can use
    // it to control the runtime complexity.  
    kcentroid<kernel_type> kc(kernel_type(0.1),0.01, 8);

    // Now we make an instance of the kkmeans object and tell it to use kcentroid objects
    // that are configured with the parameters from the kc object we defined above.
    kkmeans<kernel_type> test(kc);

    // Read input samples
    std::vector<sample_type> samples = getSamples();
    std::vector<sample_type> initial_centers;

    // tell the kkmeans object we made that we want to run k-means
    test.set_number_of_centers(nclst);

    // You need to pick some initial centers for the k-means algorithm.  So here
    // we will use the dlib::pick_initial_centers() function which tries to find
    // n points that are far apart (basically).  
    pick_initial_centers(nclst, initial_centers, samples, test.get_kernel());

    // now run the k-means algorithm on our set of samples.  
    test.train(samples,initial_centers);

    std::vector<int> clusters;
    clusters.reserve(samples.size());
    for(const auto& s:samples)
        clusters.emplace_back(test(s));

    print(samples,clusters);
     
}