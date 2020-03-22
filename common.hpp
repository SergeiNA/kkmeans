
#include <dlib/matrix.h>

// Here we declare that our samples will be 2 dimensional column vectors.  
// (Note that if you don't know the dimensionality of your vectors at compile time
// you can change the 2 to a 0 and then set the size at runtime)
typedef dlib::matrix<double,2,1> sample_type;