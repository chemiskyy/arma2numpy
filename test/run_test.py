#!/usr/bin/python

import numpy as np
import Tarma2numpy

x = np.random.rand(6)
y = Tarma2numpy.test_vec(x)
np.testing.assert_array_equal(x,y)

x = np.random.rand(3,2)
y = Tarma2numpy.test_mat(x)
np.testing.assert_array_equal(x,y)
