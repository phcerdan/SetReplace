/* Copyright (C) 2020 Pablo Hernandez-Cerdan
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#include <iostream>

#include "Match.hpp"
#include "Rule.hpp"
#include "Set.hpp"

namespace SetReplace {

/*****************************************************************************/
/* Set */
/*****************************************************************************/
void print(const Set::StepSpecification &in, std::ostream &os) {
  os << "maxEvents: " << in.maxEvents << std::endl;
  os << "maxGenerationsLocal: " << in.maxGenerationsLocal << std::endl;
  os << "maxFinalAtoms: " << in.maxFinalAtoms << std::endl;
  os << "maxFinalAtomDegree: " << in.maxFinalAtomDegree << std::endl;
  os << "maxFinalExpressions: " << in.maxFinalExpressions << std::endl;
};

std::string to_string(const Set::Error &in) {
  switch (in) {
    case Set::Error::Aborted:
      return "Aborted";
      break;
    case Set::Error::DisconnectedInputs:
      return "DisconnectedInputs";
      break;
    case Set::Error::NonPositiveAtoms:
      return "NonPositiveAtoms";
      break;
    case Set::Error::AtomCountOverflow:
      return "AtomCountOverflow";
      break;
    default:
      return "Set::Error case to_string not implemented";
  }
};
void print(const Set::Error &in, std::ostream &os) {
  os << to_string(in) << std::endl;
}

std::string to_string(const Set::TerminationReason &in) {
  switch (in) {
    case Set::TerminationReason::NotTerminated:
      return "NotTerminated";
      break;
    case Set::TerminationReason::MaxEvents:
      return "MaxEvents";
      break;
    case Set::TerminationReason::MaxGenerationsLocal:
      return "MaxGenerationsLocal";
      break;
    case Set::TerminationReason::MaxFinalAtoms:
      return "MaxFinalAtoms";
      break;
    case Set::TerminationReason::MaxFinalAtomDegree:
      return "MaxFinalAtomDegree";
      break;
    case Set::TerminationReason::MaxFinalExpressions:
      return "MaxFinalExpressions";
      break;
    case Set::TerminationReason::FixedPoint:
      return "FixedPoint";
      break;
    case Set::TerminationReason::Aborted:
      return "Aborted";
      break;
    default:
      return "Set::TerminationReason case to_string not implemented";
  }
};
void print(const Set::TerminationReason &in, std::ostream &os) {
  os << to_string(in) << std::endl;
}

/*****************************************************************************/
/* Expression */
/*****************************************************************************/
void print(const AtomsVector &in, std::ostream &os) {
  os << "{ ";
  for (const auto &a : in) {
    os << a << ", ";
  }
  os << "}";
}

void print(const std::vector<AtomsVector> &in, std::ostream &os) {
  os << "{\n";
  for (const auto &atoms_vector : in) {
    print(atoms_vector, os);
    os << ",\n";
  }
  os << "}"
     << "\n";
}

void print(const SetExpression &in, std::ostream &os) {
  os << "atoms: ";
  print(in.atoms, os);
  os << std::endl;
  os << "creatorEvent: " << in.creatorEvent << std::endl;
  os << "destroyerEvent: " << in.destroyerEvent << std::endl;
  os << "generation: " << in.generation << std::endl;
}

/*****************************************************************************/
/* Rule */
/*****************************************************************************/
void print(const Rule &in, std::ostream &os) {
  os << "inputs: ";
  print(in.inputs, os);
  os << "outputs: ";
  print(in.outputs, os);
}

/*****************************************************************************/
/* Match */
/*****************************************************************************/

void print(const Match &in, std::ostream &os) {
  os << "rule: " << in.rule << std::endl;
  os << "inputExpressions: ";
  print(in.inputExpressions, os);
  os << std::endl;
}

std::string to_string(const Matcher::OrderingFunction &in) {
  switch (in) {
    case Matcher::OrderingFunction::SortedExpressionIDs:
      return "SortedExpressionIDs";
      break;
    case Matcher::OrderingFunction::ReverseSortedExpressionIDs:
      return "ReverseSortedExpressionIDs";
      break;
    case Matcher::OrderingFunction::ExpressionIDs:
      return "ExpressionIDs";
      break;
    case Matcher::OrderingFunction::RuleID:
      return "RuleID";
      break;
    default:
      return "Matcher::OrderingFunction case to_string not implemented";
  }
};
void print(const Matcher::OrderingFunction &in, std::ostream &os) {
  os << to_string(in) << std::endl;
}

std::string to_string(const Matcher::OrderingDirection &in) {
  switch (in) {
    case Matcher::OrderingDirection::Normal:
      return "Normal";
      break;
    case Matcher::OrderingDirection::Reverse:
      return "Reverse";
      break;
    default:
      return "Matcher::OrderingDirection case to_string not implemented";
  }
};
void print(const Matcher::OrderingDirection &in, std::ostream &os) {
  os << to_string(in) << std::endl;
}

}  // namespace SetReplace

