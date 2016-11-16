#ifndef ARL_INTERFACES_MUSCLE_INTERFACE_H
#define ARL_INTERFACES_MUSCLE_INTERFACE_H

#include <hardware_interface/internal/hardware_resource_manager.h>
#include <cassert>
#include <string>

namespace arl_interfaces {

  class MuscleHandle {

  public:
    MuscleHandle() : name_(), desired_pressure_(), current_pressure_(), tension_() {}

    MuscleHandle(const std::string &name, double* desired_pressure, double* current_pressure, double* tension)
      : name_(name), desired_pressure_(desired_pressure), current_pressure_(current_pressure), tension_(tension) {

      if (!desired_pressure)
      {
        throw hardware_interface::HardwareInterfaceException("Cannot create handle for desired pressures of muscle " + name);
      }
      if (!current_pressure)
      {
        throw hardware_interface::HardwareInterfaceException("Cannot create handle for current pressures of muscle " + name);
      }
      if (!tension)
      {
        throw hardware_interface::HardwareInterfaceException("Cannot create handle for tensions of muscle " + name);
      }

    }

    std::string getName() const { return name_; }

    double getDesiredPressure() const {assert(desired_pressure_); return *desired_pressure_; }
    void setDesiredPressure(double desired_pressure) {assert(desired_pressure_); *desired_pressure_ = desired_pressure; }

    double getCurrentPressure() const {assert(current_pressure_); return *current_pressure_; }
    void setCurrentPressure(double current_pressure) {assert(current_pressure_); *current_pressure_ = current_pressure; }

    double getTension() const {assert(tension_); return *tension_; }
    void setTension(double tension) {assert(tension_); *tension_ = tension; }


  private:
    std::string name_;
    double* desired_pressure_;
    double* current_pressure_;
    double* tension_;

  };


  class MuscleInterface : public hardware_interface::HardwareResourceManager<MuscleHandle> {
  };

}

#endif //ARL_INTERFACES_MUSCLE_INTERFACE_H
