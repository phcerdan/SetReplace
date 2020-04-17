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

#ifndef SET_REPLACE_IO_HPP
#define SET_REPLACE_IO_HPP

#include <iostream>

#include "Match.hpp"
#include "Rule.hpp"
#include "Set.hpp"

namespace SetReplace {

/*****************************************************************************/
/* Set */
/*****************************************************************************/
inline void print(const Set::StepSpecification &in, std::ostream &os) {
  os << "maxEvents: " << in.maxEvents << std::endl;
  os << "maxGenerationsLocal: " << in.maxGenerationsLocal << std::endl;
  os << "maxFinalAtoms: " << in.maxFinalAtoms << std::endl;
  os << "maxFinalAtomDegree: " << in.maxFinalAtomDegree << std::endl;
  os << "maxFinalExpressions: " << in.maxFinalExpressions << std::endl;
};

inline std::string to_string(const Set::Error &in) {
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
inline void print(const Set::Error &in, std::ostream &os) {
  os << to_string(in) << std::endl;
}

inline std::string to_string(const Set::TerminationReason &in) {
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
inline void print(const Set::TerminationReason &in, std::ostream &os) {
  os << to_string(in) << std::endl;
}

/*****************************************************************************/
/* Expression */
/*****************************************************************************/
inline void print(const AtomsVector &in, std::ostream &os) {
  os << "{ ";
  for (const auto &a : in) {
    os << a << ", ";
  }
  os << "}";
}

inline void print(const std::vector<AtomsVector> &in, std::ostream &os) {
  os << "{\n";
  for (const auto &atoms_vector : in) {
    print(atoms_vector, os);
    os << ",\n";
  }
  os << "}"
     << "\n";
}

inline void print(const SetExpression &in, std::ostream &os) {
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
inline void print(const Rule &in, std::ostream &os) {
  os << "inputs: ";
  print(in.inputs, os);
  os << "outputs: ";
  print(in.outputs, os);
}

/*****************************************************************************/
/* Match */
/*****************************************************************************/

inline void print(const Match &in, std::ostream &os) {
  os << "rule: " << in.rule << std::endl;
  os << "inputExpressions: ";
  print(in.inputExpressions, os);
  os << std::endl;
}

inline std::string to_string(const Matcher::OrderingFunction &in) {
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
inline void print(const Matcher::OrderingFunction &in, std::ostream &os) {
  os << to_string(in) << std::endl;
}

inline std::string to_string(const Matcher::OrderingDirection &in) {
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
inline void print(const Matcher::OrderingDirection &in, std::ostream &os) {
  os << to_string(in) << std::endl;
}

}  // namespace SetReplace

#endif
