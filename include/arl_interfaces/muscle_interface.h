#ifndef ARL_INTERFACES_MUSCLE_INTERFACE_H
#define ARL_INTERFACES_MUSCLE_INTERFACE_H

#include <hardware_interface/internal/hardware_resource_manager.h>
#include <cassert>
#include <string>

namespace arl_interfaces {

  /**
   * Handle to interact with robot's muscles by a muscle interface containing several of this handles
   */
  class MuscleHandle {

  public:
    /**
     * Default Constructor
     * @return
     */
    MuscleHandle() : name_(), desired_pressure_(), current_pressure_(), tension_(), activation_() {}

    /**
     * Constructor to initialize instance with pointers to muscle's data
     * @param name name of muscle
     * @param desired_pressure sets an initial desired pressure
     * @param current_pressure sets an initial current pressure
     * @param tension sets an initial tension
     * @return
     */
    MuscleHandle(const std::string &name, double* desired_pressure, double* current_pressure, double* tension, double* activation)
      : name_(name), desired_pressure_(desired_pressure), current_pressure_(current_pressure), tension_(tension), activation_(activation) {

      if (!desired_pressure)
      {
        throw hardware_interface::HardwareInterfaceException("Cannot create handle for desired pressure of muscle " + name);
      }
      if (!current_pressure)
      {
        throw hardware_interface::HardwareInterfaceException("Cannot create handle for current pressure of muscle " + name);
      }
      if (!tension)
      {
        throw hardware_interface::HardwareInterfaceException("Cannot create handle for tension of muscle " + name);
      }
      if (!activation_)
      {
        throw hardware_interface::HardwareInterfaceException("Cannot create handle for activation of muscle " + name);
      }

    }

    /**
     * Getter for muscle's name
     * @return name of muscle
     */
    std::string getName() const { return name_; }

    /**
     * Getter for muscle's desired pressure
     * @return desired muscle pressure
     */
    double getDesiredPressure() const {assert(desired_pressure_); return *desired_pressure_; }

    /**
     * Setter for muscle's desired pressure
     * @param desired_pressure
     */
    void setDesiredPressure(double desired_pressure) {assert(desired_pressure_); *desired_pressure_ = desired_pressure; }

    /**
     * Getter for muscle's current pressure
     * @return current muscle pressure
     */
    double getCurrentPressure() const {assert(current_pressure_); return *current_pressure_; }

    /**
     * Setter for muscle's current pressure
     * @param current_pressure
     */
    void setCurrentPressure(double current_pressure) {assert(current_pressure_); *current_pressure_ = current_pressure; }

    /**
     * Getter for muscle's tension
     * @return muscle tension
     */
    double getTension() const {assert(tension_); return *tension_; }

    /**
     * Setter for muscle's tension
     * @param tension
     */
    void setTension(double tension) {assert(tension_); *tension_ = tension; }

    /**
     * Getter for muscle's activation
     * @return muscle tension
     */
    double getActivation() const {assert(activation_); return *activation_; }

    /**
     * Setter for muscle's activation
     * @param tension
     */
    void setActivation(double activation) {assert(activation_); *activation_ = activation; }


  private:
    std::string name_; /**< Saves muscle's name */
    double* desired_pressure_; /**< Saves pointer to muscle's desired pressure stored within the robot hardware interface */
    double* current_pressure_; /**< Saves pointer to muscle's current pressure stored within the robot hardware interface */
    double* tension_; /**< Saves pointer to muscle's tension stored within the robot hardware interface */
    double* activation_; /**< Saves pointer to muscle's normalized muscle activation stored within the robot hardware interface */

  };


  /**
   * Interface to keep several MuscleHandles
   */
  class MuscleInterface : public hardware_interface::HardwareResourceManager<MuscleHandle> {
  };

}

#endif //ARL_INTERFACES_MUSCLE_INTERFACE_H
