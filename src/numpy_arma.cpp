///@file constitutive.hpp
///@brief Constitutive tensors in Voigt notation
///@version 1.0

#include <string.h>
#include <assert.h>
#include <memory>
#include <armadillo>
#include <boost/python.hpp>
#include <boost/numpy.hpp>

namespace bp = boost::python;
namespace bn = boost::numpy;
using namespace arma;

vec array2vec(bn::ndarray const &array) {
    
    int n_dim = array.get_nd();
    assert(n_dim == 1);
    Py_intptr_t const *shape = array.get_shape();
    int n_rows = shape[0];
    vec v = zeros(n_rows);
    for (int i = 0; i < n_rows; ++i) {
        v(i) = bp::extract<double>(array[i]);
    }
    return v;
}

bn::ndarray vec2array(const vec &v) {

    bp::tuple shape = bp::make_tuple(v.n_elem);
    // ...as well as a type for C++ float
    bn::dtype dtype = bn::dtype::get_builtin<double>();
    // Construct an array with the above shape and type
    bn::ndarray a = bn::zeros(shape, dtype);

    for (int i = 0; i < v.n_elem; ++i) {
        a[i] = v(i);
    }
    return a;
}


mat array2mat(bn::ndarray const &array) {
    
    int n_dim = array.get_nd();
    assert(n_dim == 2);
    Py_intptr_t const *shape = array.get_shape();
    int n_rows = shape[0];
    int n_cols = shape[1];
    mat m = zeros(n_rows, n_cols);
    
    Py_intptr_t const * strides = array.get_strides();
    for (int i = 0; i < n_rows; ++i) {
        for (int j = 0; j < n_cols; ++j) {
            m(i,j) = bp::extract<double>(array[i][j]);
            
        }
    }
    return m;
}

bn::ndarray mat2array(const mat &m) {
    
    bp::tuple shape = bp::make_tuple(m.n_rows, m.n_cols);
    // ...as well as a type for C++ float
    bn::dtype dtype = bn::dtype::get_builtin<double>();
    // Construct an array with the above shape and type
    bn::ndarray a = bn::zeros(shape, dtype);
    
    for (int i = 0; i < m.n_rows; ++i) {
        for (int j = 0; j < m.n_cols; ++j) {
            a[i][j] = m(i,j);
        }
    }
    return a;
}