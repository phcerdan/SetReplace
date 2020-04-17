/* Copyright (C) 2020 Pablo Hernandez-Cerdan
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#include <pybind11/pybind11.h>
// #include "set_replace_common_py.hpp"  // Declare OPAQUE types

namespace py = pybind11;

void init_expression(py::module &m);
void init_rule(py::module &m);
void init_match(py::module &m);
void init_set(py::module &m);

void init_set_replace(py::module &m) {
  init_expression(m);
  init_rule(m);
  init_match(m);
  init_set(m);
}
