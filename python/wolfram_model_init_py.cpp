/* Copyright (C) 2020 Pablo Hernandez-Cerdan
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#include <pybind11/pybind11.h>
namespace py = pybind11;

void init_set_replace(py::module &);

PYBIND11_MODULE(_wolfram_model, m) {
  m.doc() =
      "Core library used for the wolfram model. Proposed as a unifying theory "
      "of physics.";
  init_set_replace(m);
}
