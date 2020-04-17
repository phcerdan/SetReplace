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

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>  // Note: Incompatible with stl_bind.h

#include <sstream>

#include "Rule.hpp"
#include "SetReplaceIO.hpp"

namespace py = pybind11;
using namespace SetReplace;

void init_rule(py::module &m) {
  py::class_<Rule>(m, "rule",
      "Rule used in system evolution.\n"
      "Use negative integers in inputs/outputs to declare Patterns, "
      "that will evolve any atom connected with such a pattern.\n"
      "For example:\n"
      "  wm.rule(inputs=[[-1, -2]], outputs=[[-1, -2, -3]])\n"
      "will create a pattern where ANY atom connected to a different atom will evolve "
      "creating a new atom and connecting it to the original two (hyperedge).\n"
      "With positive integers, the rule only applies to especific atoms "
      "in the graph with that especific id."
      )
      // .def(py::init()) // Default constructor is useless with const members
      .def(py::init([](const std::vector<AtomsVector> &in_inputs,
                       const std::vector<AtomsVector> &in_outputs) {
             return
                 std::make_unique<Rule>(Rule({{in_inputs}, {in_outputs}}));
             }
            ),
           py::arg("inputs"), py::arg("outputs"))
      .def("__repr__",
           [](const Rule &in) {
             std::stringstream os;
             print(in, os);
             return os.str();
           })
      .def_readonly("inputs", &Rule::inputs)
      .def_readonly("outputs", &Rule::outputs);
}
