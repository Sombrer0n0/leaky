#pragma once


#include "pybind11/pybind11.h"
#include "stim.h"
#include "stim/circuit/gate_target.h"

stim::GateTarget obj_to_gate_target(const pybind11::object &obj);
stim::GateTarget handle_to_gate_target(const pybind11::handle &obj);