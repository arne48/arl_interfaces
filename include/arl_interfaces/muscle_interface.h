#ifndef ARL_INTERFACES_MUSCLE_INTERFACE_H
#define ARL_INTERFACES_MUSCLE_INTERFACE_H

#include <hardware_interface/internal/hardware_resource_manager.h>
#include <vector>
#include <string>

namespace arl_interfaces {

  class MuscleHandle {

  public:
    MuscleHandle() : names_(), desired_pressures_(), current_pressures_(), tensions_() {}

    MuscleHandle(const std::vector <std::string> &names, std::vector<double> &desired_pressures, std::vector<double> &current_pressures,
                    std::vector<double> &tensions) : names_(names), desired_pressures_(desired_pressures),
                                                     current_pressures_(current_pressures), tensions_(tensions) {
      /*if (!names)
      {
        throw HardwareInterfaceException("Cannot create handle for muscle names");
      }
      if (!desired_pressures)
      {
        throw HardwareInterfaceException("Cannot create handle for desired pressures");
      }
      if (!current_pressures)
      {
        throw HardwareInterfaceException("Cannot create handle for current pressures");
      }
      if (!tensions)
      {
        throw HardwareInterfaceException("Cannot create handle for tensions");
      }*/

    }

    std::string getName() const {return "";}
    std::vector<std::string> getNames() const {return names_;}
    std::vector<double> getDesiredPressures() const {return desired_pressures_;}
    std::vector<double> getCurrentPressures() const {return current_pressures_;}
    std::vector<double> getTensions() const {return tensions_;}



  private:
    std::vector<std::string> names_;
    std::vector<double> desired_pressures_;
    std::vector<double> current_pressures_;
    std::vector<double> tensions_;


  };

  class MuscleInterface : public hardware_interface::HardwareResourceManager<MuscleHandle> {
  public:
    std::string getName() const {return "";}

  };

}

#endif //ARL_INTERFACES_MUSCLE_INTERFACE_H
