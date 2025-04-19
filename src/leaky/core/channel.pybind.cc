#include "leaky/core/channel.pybind.h"
#include "leaky/core/gatetarget_trans.h"
#include <pybind11/cast.h>
#include <pybind11/pytypes.h>
#include <pybind11/stl.h>

#include "leaky/core/channel.h"
#include "pybind11/pybind11.h"

py::class_<leaky::LeakyPauliChannel> leaky_pybind::pybind_channel(py::module &m) {
    return {m, "LeakyPauliChannel"};
}

void leaky_pybind::pybind_channel_methods(py::module &m, py::class_<leaky::LeakyPauliChannel> &c) {
    c.def(py::init<bool>(), py::arg("is_single_qubit_channel") = py::bool_(true));
    c.def(
        py::init([](const std::vector<py::object> &independent_target_objs,
                    bool is_single_qubit_channel) {
            std::vector<stim::GateTarget> targets;
            targets.reserve(independent_target_objs.size());
            for (const auto &obj : independent_target_objs) {
                targets.push_back(obj_to_gate_target(obj));  
            }
            return leaky::LeakyPauliChannel(targets, is_single_qubit_channel);
        }),
        py::arg("independent_target"),
        py::arg("is_single_qubit_channel") = true,
        "Construct a LeakyPauliChannel bound to the given independent targets."
    );
    c.def_property_readonly("num_transitions", &leaky::LeakyPauliChannel::num_transitions);
    c.def(
        "add_transition",
        &leaky::LeakyPauliChannel::add_transition,
        py::arg("initial_status"),
        py::arg("final_status"),
        py::arg("pauli_channel_idx"),
        py::arg("probability"));
    c.def(
        "get_prob_from_to",
        &leaky::LeakyPauliChannel::get_prob_from_to,
        py::arg("initial_status"),
        py::arg("final_status"),
        py::arg("pauli_idx"));
    c.def("sample", &leaky::LeakyPauliChannel::sample, py::arg("initial_status"));
    c.def("safety_check", &leaky::LeakyPauliChannel::safety_check);
    c.def("__str__", &leaky::LeakyPauliChannel::str);
    c.def("__repr__", &leaky::LeakyPauliChannel::repr);
}