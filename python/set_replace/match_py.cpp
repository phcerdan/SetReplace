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

#include "Match.hpp"
#include "SetReplaceIO.hpp"

namespace py = pybind11;
using namespace SetReplace;

void init_match(py::module &m) {
  py::class_<Matcher> matcher(m, "matcher",
                              "Set that will evolve based on rules.\n");
  matcher.def(
      py::init(
          [](const std::vector<Rule> &in_rules, AtomsIndex &in_atomsIndex,
             const std::function<AtomsVector(ExpressionID)> &in_getAtomsVector,
             const Matcher::OrderingSpec &in_orderingSpec,
             const unsigned int in_randomSeed) {
            return std::make_unique<Matcher>(in_rules, in_atomsIndex,
                                             in_getAtomsVector,
                                             in_orderingSpec, in_randomSeed);
          }),
      py::arg("rules"), py::arg("atoms_index"), py::arg("get_atoms_vector"),
      py::arg("ordering"), py::arg("random_seed") = 0);
  matcher.def("add_matches_involving_expressions",
              &Matcher::addMatchesInvolvingExpressions);
  matcher.def("remove_matches_involving_expressions",
              &Matcher::removeMatchesInvolvingExpressions);
  matcher.def("empty", &Matcher::empty);
  matcher.def("nextMatch", &Matcher::nextMatch);
  matcher.def("substitute_missing_atoms_if_possible",
              &Matcher::substituteMissingAtomsIfPossible);
  matcher.def("all_matches", &Matcher::allMatches);

  /*****************************************************************************/

  py::enum_<Matcher::OrderingDirection>(matcher, "ordering_direction",
                                        "OrderingDirection for Matcher.")
      .value("Normal", Matcher::OrderingDirection::Normal)
      .value("Reverse", Matcher::OrderingDirection::Reverse);

  /*****************************************************************************/

  py::enum_<Matcher::OrderingFunction>(matcher, "ordering_function",
                                       "OrderingFunction for Matcher.")
      .value("SortedExpressionIDs",
             Matcher::OrderingFunction::SortedExpressionIDs)
      .value("ReverseSortedExpressionIDs",
             Matcher::OrderingFunction::ReverseSortedExpressionIDs)
      .value("ExpressionIDs", Matcher::OrderingFunction::ExpressionIDs)
      .value("RuleID", Matcher::OrderingFunction::RuleID);
}
