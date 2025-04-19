#ifndef LEAKY_INSTRUCTION_PYBIND_H
#define LEAKY_INSTRUCTION_PYBIND_H

#include "pybind11/pybind11.h"
#include "stim.h"
#include "stim/circuit/gate_target.h"

namespace py = pybind11;
using namespace py::literals;

namespace leaky_pybind {

struct LeakyInstruction {
    stim::GateType gate_type;
    std::vector<stim::GateTarget> targets;
    std::vector<double> gate_args;

    LeakyInstruction(
        const char *name,const std::vector<pybind11::object>&init_targets,const std::vector<double> &gate_args);
    LeakyInstruction(
        stim::GateType gate_type,
        std::vector<stim::GateTarget> targets,
        std::vector<double> gate_args);      
    stim::CircuitInstruction as_operation_ref() const;
    operator stim::CircuitInstruction() const;
};

py::class_<LeakyInstruction> pybind_instruction(py::module &m);
void pybind_instruction_methods(py::module &m, py::class_<LeakyInstruction> &c);

}  // namespace leaky_pybind


#endif  // LEAKY_INSTRUCTION_PYBIND_H