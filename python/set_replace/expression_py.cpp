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

#include "Expression.hpp"

#include <sstream>

#include "set_replace_common_py.hpp"
#include "SetReplaceIO.hpp"


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
        .def_readwrite("creator_event", & SetExpression::creatorEvent)
        .def_readwrite("destroyer_event", & SetExpression::destroyerEvent)
        .def_readwrite("generation", & SetExpression::generation)
        ;
    py::class_<AtomsIndex>(m, "atoms_index")
        .def(py::init<const std::function<AtomsVector(ExpressionID)>&>())
        .def("removeExpressions", & AtomsIndex::removeExpressions)
        .def("addExpressions", & AtomsIndex::addExpressions)
        .def("expressionsContainingAtom", & AtomsIndex::expressionsContainingAtom)
        ;
}
