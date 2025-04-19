#include "leaky/core/gatetarget_trans.h"

#include <pybind11/cast.h>
#include <pybind11/detail/common.h>
#include <pybind11/pytypes.h>
#include <pybind11/stl.h>

stim::GateTarget handle_to_gate_target(const pybind11::handle &obj) {
    try {
        return pybind11::cast<stim::GateTarget>(obj);
    } catch (const pybind11::cast_error &ex) {
    }
    try {
        return stim::GateTarget{pybind11::cast<uint32_t>(obj)};
    } catch (const pybind11::cast_error &ex) {
    }
    if (pybind11::hasattr(obj, "value")) {
        try {
            auto v = pybind11::cast<uint32_t>(obj.attr("value"));
            return stim::GateTarget{v};
        } catch (const pybind11::cast_error &) {
        }
    }
    throw std::invalid_argument(
        "target argument wasn't a qubit index, a result from a `stim.target_*` method, or a `stim.GateTarget`.");
}

stim::GateTarget obj_to_gate_target(const pybind11::object &obj) {
    return handle_to_gate_target(obj);
}