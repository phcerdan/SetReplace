/* Copyright (c) 2020 Pablo Hernandez-Cerdan
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE. */

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




