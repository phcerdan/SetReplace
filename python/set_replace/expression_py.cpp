/* Copyright (C) 2020 Pablo Hernandez-Cerdan
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "Expression.hpp"
#include "SetReplaceIO.hpp"
#include <sstream>

#include <pybind11/pybind11.h>
#include <pybind11/stl.h> // Note: Incompatible with stl_bind.h

namespace py = pybind11;
using namespace SetReplace;

void init_expression(py::module & m) {
    py::class_<SetExpression>(m, "expression")
        .def(py::init())
        .def("__repr__", [](const SetExpression & in){
                std::stringstream os;
                print(in, os);
                return os.str();
                })
        // readwrite is not modifiable using references (append) with stl.h
        // create OPAQUE type with stl_bind.h. But needs work to get niceties back.
        .def_readwrite("atoms", & SetExpression::atoms)
        ;
}
