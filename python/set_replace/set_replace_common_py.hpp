/* Copyright (C) 2020 Pablo Hernandez-Cerdan
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef SET_REPLACE_COMMON_PY_HPP
#define SET_REPLACE_COMMON_PY_HPP

// #include <pybind11/pybind11.h>
// #include <pybind11/stl_bind.h>
// using vints_t = std::vector<int>;
// PYBIND11_MAKE_OPAQUE(std::vector<int>); // std::vector<ExpressionID>
// using vints64_t = std::vector<int64_t>;
// PYBIND11_MAKE_OPAQUE(std::vector<int64_t>); // AtomsVector
// using vvints64_t = std::vector<vints64_t>;
// PYBIND11_MAKE_OPAQUE(std::vector<vints64_t>); // std::vector<AtomsVector>

// insert the following in cpp file (do not include pybind/stl.h)
// auto vints_py = py::bind_vector<std::vector<int>>(m, "vints");
// auto vints64_py = py::bind_vector<std::vector<int64_t>>(m, "vints64");
// auto vvints64_py = py::bind_vector<std::vector<vints64_t>>(m, "vvints64");
  // vints_py.def(py::init([](py::list &l) {
  //   auto out = std::make_unique<vints_t>();
  //   out->reserve(l.size());
  //   for (const auto &e : l) {
  //     out->push_back(e.cast<int>());
  //   }
  //   return out;
  // }));
  // vvints64_py.def("__repr__", [](const vvints64_t &in) {
  //   std::stringstream os;
  //   SetReplace::print(in, os);
  //   return os.str();
  // });
#endif




