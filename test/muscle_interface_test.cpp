#include <string>
#include <gtest/gtest.h>
#include <ros/console.h>
#include <arl_interfaces/muscle_interface.h>

using std::string;
using namespace arl_interfaces;

TEST(MuscleHandleTest, HandleConstruction) {
  string name = "name1";
  double desired_pressure, current_pressure, tension, activation;
  EXPECT_NO_THROW(MuscleHandle tmp(name, &desired_pressure, &current_pressure, &tension, &activation));
  EXPECT_THROW(MuscleHandle(name, 0, &current_pressure, &tension, &activation), hardware_interface::HardwareInterfaceException);
  EXPECT_THROW(MuscleHandle(name, &desired_pressure, 0, &tension, &activation), hardware_interface::HardwareInterfaceException);
  EXPECT_THROW(MuscleHandle(name, &desired_pressure, &current_pressure, 0, &activation), hardware_interface::HardwareInterfaceException);
  EXPECT_THROW(MuscleHandle(name, &desired_pressure, &current_pressure, &tension, 0), hardware_interface::HardwareInterfaceException);

// Print error messages
// Requires manual output inspection, but exception message should be descriptive
  try { MuscleHandle(name, 0, &current_pressure, &tension, &activation); }
  catch (const hardware_interface::HardwareInterfaceException &e) { ROS_ERROR_STREAM(e.what()); }

  try { MuscleHandle(name, &desired_pressure, 0, &tension, &activation); }
  catch (const hardware_interface::HardwareInterfaceException &e) { ROS_ERROR_STREAM(e.what()); }

  try { MuscleHandle(name, &desired_pressure, &current_pressure, 0, &activation); }
  catch (const hardware_interface::HardwareInterfaceException &e) { ROS_ERROR_STREAM(e.what()); }

  try { MuscleHandle(name, &desired_pressure, &current_pressure, &tension, 0); }
  catch (const hardware_interface::HardwareInterfaceException &e) { ROS_ERROR_STREAM(e.what()); }
}

#ifndef NDEBUG // NOTE: This test validates assertion triggering, hence only gets compiled in debug mode

TEST(MuscleHandleTest, AssertionTriggering) {
  MuscleHandle h;

// Data with invalid pointers should trigger an assertion
  EXPECT_DEATH(h.getDesiredPressure(), ".*");
  EXPECT_DEATH(h.getCurrentPressure(), ".*");
  EXPECT_DEATH(h.getTension(), ".*");
  EXPECT_DEATH(h.getActivation(), ".*");
}

#endif // NDEBUG

class MuscleInterfaceTest : public ::testing::Test {
public:
  MuscleInterfaceTest()
    : des1(1.0), cur1(2.0), ten1(3.0), act1(4.0),
      des2(5.0), cur2(6.0), ten2(7.0), act2(8.0),
      name1("name_1"),
      name2("name_2"),
      h1(name1, &des1, &cur1, &ten1, &act1),
      h2(name2, &des2, &cur2, &ten2, &act2) {}

protected:
  double des1, cur1, ten1, act1;
  double des2, cur2, ten2, act2;
  string name1;
  string name2;
  MuscleHandle h1, h2;
};

TEST_F(MuscleInterfaceTest, ExcerciseApi) {
  MuscleInterface iface;
  iface.registerHandle(h1);
  iface.registerHandle(h2);

// Get handles
  EXPECT_NO_THROW(iface.getHandle(name1));
  EXPECT_NO_THROW(iface.getHandle(name2));

  MuscleHandle h1_tmp = iface.getHandle(name1);
  EXPECT_EQ(name1, h1_tmp.getName());
  EXPECT_DOUBLE_EQ(des1, h1_tmp.getDesiredPressure());
  EXPECT_DOUBLE_EQ(cur1, h1_tmp.getCurrentPressure());
  EXPECT_DOUBLE_EQ(ten1, h1_tmp.getTension());
  EXPECT_DOUBLE_EQ(act1, h1_tmp.getActivation());

  MuscleHandle h2_tmp = iface.getHandle(name2);
  EXPECT_EQ(name2, h2_tmp.getName());
  EXPECT_DOUBLE_EQ(des2, h2_tmp.getDesiredPressure());
  EXPECT_DOUBLE_EQ(cur2, h2_tmp.getCurrentPressure());
  EXPECT_DOUBLE_EQ(ten2, h2_tmp.getTension());
  EXPECT_DOUBLE_EQ(act2, h2_tmp.getActivation());

// This interface does not claim resources
  EXPECT_TRUE(iface.getClaims().empty());

// Print error message
// Requires manual output inspection, but exception message should contain the interface name (not its base class)
  try {
    iface.getHandle("unknown_name");
  }

  catch (const hardware_interface::HardwareInterfaceException &e) { ROS_ERROR_STREAM(e.what()); }
}

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}