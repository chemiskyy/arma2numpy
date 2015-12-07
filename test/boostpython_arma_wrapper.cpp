
#include <armadillo>
#include <boost/python.hpp>
#include <boost/numpy.hpp>
#include <arma2numpy/numpy_arma.hpp>
#include "Tarma2numpy.hpp"

namespace bp = boost::python;
namespace bn = boost::numpy;
using namespace std;
using namespace arma;

BOOST_PYTHON_MODULE(Tarma2numpy) {

//    Py_Initialize();
    bn::initialize();
    
    // Register the from-python converters
    bp::def("test_vec", test_vec_py);
    bp::def("test_mat", test_mat_py);
}