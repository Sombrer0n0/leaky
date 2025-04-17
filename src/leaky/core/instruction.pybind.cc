#include "leaky/core/instruction.pybind.h"

#include <pybind11/cast.h>
#include <pybind11/detail/common.h>
#include <pybind11/pytypes.h>
#include <pybind11/stl.h>

// stim::GateTarget handle_to_gate_target(const pybind11::handle &obj) {
//     try {
//         std::cout<<"leaky:"<<typeid(obj).name()<<std::endl;
//         return py::cast<stim::GateTarget>(obj);
//     } catch (const pybind11::cast_error &ex) {
//         std::cerr <<"cast fail2:"<<ex.what()<<std::endl;
//     }
//     try {
//         return stim::GateTarget{py::cast<uint32_t>(obj)};
//     } catch (const pybind11::cast_error &ex) {
//     }
//     throw std::invalid_argument(
//         "target argument wasn't a qubit index, a result from a `stim.target_*` method, or a `stim.GateTarget`.");
// }

// stim::GateTarget leaky_pybind::obj_to_gate_target(const pybind11::object &obj) {
//     return handle_to_gate_target(obj);
// }
using namespace stim;

GateTarget handle_to_gate_target(const pybind11::handle &obj) {
    try {
        return pybind11::cast<GateTarget>(obj);
    } catch (const pybind11::cast_error &ex) {
    }
    try {
        return GateTarget{pybind11::cast<uint32_t>(obj)};
    } catch (const pybind11::cast_error &ex) {
    }
    throw std::invalid_argument(
        "target argument wasn't a qubit index, a result from a `stim.target_*` method, or a `stim.GateTarget`.");
}

GateTarget obj_to_gate_target(const pybind11::object &obj) {
    return handle_to_gate_target(obj);
}

leaky_pybind::LeakyInstruction::LeakyInstruction(
    const char *name, const std::vector<pybind11::object> &init_targets,const std::vector<double> &gate_args)
    : gate_type(stim::GATE_DATA.at(name).id),gate_args(gate_args){
    for (const auto &obj : init_targets) {
        targets.push_back(obj_to_gate_target(obj));
    }
}

leaky_pybind::LeakyInstruction::LeakyInstruction(
    stim::GateType gate_type, std::vector<stim::GateTarget> targets, std::vector<double> gate_args)
    : gate_type(gate_type), targets(targets), gate_args(gate_args) {
}


stim::CircuitInstruction leaky_pybind::LeakyInstruction::as_operation_ref() const {
    return stim::CircuitInstruction{
        gate_type,
        gate_args,
        targets,
    };
}
leaky_pybind::LeakyInstruction::operator stim::CircuitInstruction() const {
    return as_operation_ref();
}

py::class_<leaky_pybind::LeakyInstruction> leaky_pybind::pybind_instruction(pybind11::module &m) {
    return pybind11::class_<leaky_pybind::LeakyInstruction>(m, "Instruction");
}

void leaky_pybind::pybind_instruction_methods(
    pybind11::module &m, pybind11::class_<leaky_pybind::LeakyInstruction> &c) {
    c.def(
        pybind11::init<const char *, std::vector<pybind11::object>, std::vector<double>>(),
        pybind11::arg("name"),
        pybind11::arg("targets"),
        pybind11::arg("gate_args") = std::make_tuple()
    );
}