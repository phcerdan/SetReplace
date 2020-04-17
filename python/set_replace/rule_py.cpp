/* Copyright (C) 2020 Pablo Hernandez-Cerdan
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

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
