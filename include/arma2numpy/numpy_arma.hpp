
#pragma once

#include <armadillo>
#include <boost/python.hpp>
#include <boost/numpy.hpp>

arma::vec array2vec(const boost::numpy::ndarray&);

arma::mat array2mat(const boost::numpy::ndarray&);

boost::numpy::ndarray vec2array(const arma::vec&);

boost::numpy::ndarray mat2array(const arma::mat&);