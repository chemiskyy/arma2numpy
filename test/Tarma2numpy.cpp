/* This file is part of arma2numpy.
 
 arma2numpy is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.
 
 arma2numpy is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License
 along with arma2numpy.  If not, see <http://www.gnu.org/licenses/>.
 
 */

///@file Tarma2numpy.cpp
///@brief Test for the arma2numpy library
///@version 1.0

#include <armadillo>
#include <boost/python.hpp>
#include <boost/numpy.hpp>
#include <arma2numpy/numpy_arma.hpp>

namespace bp = boost::python;
namespace bn = boost::numpy;
using namespace std;
using namespace arma;

bn::ndarray test_vec_py(bn::ndarray const &y) {
    vec v = array2vec(y);
    return vec2array(v);
}

bn::ndarray test_mat_py(bn::ndarray const &y) {
    mat m = array2mat(y);
    return mat2array(m);
}