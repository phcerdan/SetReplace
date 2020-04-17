/* Copyright (C) 2020 Pablo Hernandez-Cerdan
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>  // Note: Incompatible with stl_bind.h

#include <sstream>

#include "Set.hpp"
#include "SetReplaceIO.hpp"

namespace py = pybind11;
using namespace SetReplace;

void init_set(py::module &m) {
  py::class_<Set> set(m, "set", "Set that will evolve based on rules.\n");
  set.def(
      py::init([](const std::vector<Rule> &in_rules,
                  const std::vector<AtomsVector> &in_initialExpressions,
                  const Matcher::OrderingSpec &in_orderingSpec,
                  const unsigned int in_randomSeed) {
        if (!std::all_of(in_initialExpressions.begin(),
                         in_initialExpressions.end(), [](const AtomsVector &v) {
                           return std::all_of(
                               v.begin(), v.end(),
                               [](const Atom &atom) { return atom >= 0; });
                         }))
          throw std::domain_error("initial_expressions must be non negative");

        return std::make_unique<Set>(in_rules, in_initialExpressions,
                                     in_orderingSpec, in_randomSeed);
      }),
      py::arg("rules"), py::arg("initial_expressions"), py::arg("ordering"),
      py::arg("random_seed") = 0);
  set.def("expressions", &Set::expressions,
          "List of all expressions in the set, past and present.");
  set.def(
      "replaceOnce",
      [](Set &in) { return in.replaceOnce([]() { return false; }); },
      "Perform a single substitution, create the corresponding event, and "
      "output expressions.\n"
      "@return 1 if substitution was made, 0 if no matches were found.");
  set.def(
      "replace",
      [](Set &in, Set::StepSpecification in_stepSpec) {
        return in.replace(in_stepSpec, []() { return false; });
      },
      py::arg("step_spec"),
      "Run replaceOnce() step_spec.maxEvents times, or until the next "
      "expression violates constraints imposed by step_spec.\n"
      "@return The number of subtitutions made, could be between 0 and "
      "step_spec.maxEvents.");

  set.def(
      "max_complete_generation",
      [](Set &in) { return in.maxCompleteGeneration([]() { return false; }); },
      "Returns the largest generation that has both been reached, and has "
      "no matches that would produce expressions with that or lower "
      "generation.\n"
      "@details Takes O(matches count) + as long as it would take to do the "
      "next "
      "step (because new expressions need to be indexed).");

  set.def("get_termination_reason", &Set::terminationReason,
          "Yields termination reason for the previous evaluation, or "
          "TerminationReason::NotTerminated if no evaluation was done yet.");

  set.def("event_rule_ids", &Set::eventRuleIDs,
          "Yields rule IDs corresponding to each event.");

  /*****************************************************************************/

  py::class_<Set::StepSpecification>(
      set, "step_spec",
      "StepSpecification (Nested, implementation detail of Set).\n")
      .def(py::init())
      .def("__repr__",
           [](const Set::StepSpecification &in) {
             std::stringstream os;
             print(in, os);
             return os.str();
           })
      .def_readwrite("max_events", &Set::StepSpecification::maxEvents)
      .def_readwrite("max_generations_local",
                     &Set::StepSpecification::maxGenerationsLocal)
      .def_readwrite("max_final_atoms", &Set::StepSpecification::maxFinalAtoms)
      .def_readwrite("max_final_atom_degree",
                     &Set::StepSpecification::maxFinalAtomDegree)
      .def_readwrite("max_final_expressions",
                     &Set::StepSpecification::maxFinalExpressions);

  /*****************************************************************************/

  py::enum_<Set::TerminationReason>(
      set, "termination_reason",
      "Status of evaluation / termination reason if evaluation is finished.")
      .value("NotTerminated", Set::TerminationReason::NotTerminated)
      .value("MaxEvents", Set::TerminationReason::MaxEvents)
      .value("MaxGenerationsLocal", Set::TerminationReason::MaxGenerationsLocal)
      .value("MaxFinalAtoms", Set::TerminationReason::MaxFinalAtoms)
      .value("MaxFinalAtomDegree", Set::TerminationReason::MaxFinalAtomDegree)
      .value("MaxFinalExpressions", Set::TerminationReason::MaxFinalExpressions)
      .value("FixedPoint", Set::TerminationReason::FixedPoint)
      .value("Aborted", Set::TerminationReason::Aborted);
}
