
#include <armadillo>
#include <boost/python.hpp>
#include <boost/numpy.hpp>
#include <arma2numpy/numpy_arma.hpp>
#include <arma2numpy/list_vector.hpp>
#include "Tarma2numpy.hpp"

namespace bp = boost::python;
namespace bn = boost::numpy;
using namespace std;
using namespace arma;
using namespace arma2numpy;

BOOST_PYTHON_MODULE(Tarma2numpy) {

//    Py_Initialize();
    bn::initialize();
    
    // Register the from-python converters
    bp::def("test_vec_int", test_vec_int);
    bp::def("test_mat_int", test_mat_int);
    bp::def("test_vec_double", test_vec_double);
    bp::def("test_mat_double", test_mat_double);
    bp::def("test_vector_list_double", test_vector_list_double);
    bp::def("test_vector_list_int", test_vector_list_int);
    bp::def("test_vector_list_string", test_vector_list_string);
}