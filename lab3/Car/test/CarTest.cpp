#include "../include/Car.h"
#include <gtest/gtest.h>

TEST(CarTest, InitialState)
{
	Car car;
	ASSERT_FALSE(car.IsTurnedOn());
	ASSERT_EQ(car.GetGear(), 0);
	ASSERT_EQ(car.GetSpeed(), 0);
	ASSERT_EQ(car.GetDirection(), Direction::STAY);
}

TEST(CarTest, EngineOnOff)
{
	Car car;

	ASSERT_TRUE(car.TurnOnEngine());
	ASSERT_TRUE(car.IsTurnedOn());

	ASSERT_TRUE(car.TurnOffEngine());
	ASSERT_FALSE(car.IsTurnedOn());
}

TEST(CarTest, EngineTurnOffWhileMoving)
{
	Car car;
	car.TurnOnEngine();

	ASSERT_TRUE(car.SetGear(1));
	ASSERT_TRUE(car.SetSpeed(20));

	ASSERT_FALSE(car.TurnOffEngine());
	ASSERT_TRUE(car.IsTurnedOn());
}

TEST(CarTest, GearShift)
{
	Car car;
	car.TurnOnEngine();

	ASSERT_TRUE(car.SetGear(1));
	ASSERT_EQ(car.GetGear(), 1);

	ASSERT_FALSE(car.SetGear(2));
	ASSERT_EQ(car.GetGear(), 1);

	ASSERT_TRUE(car.SetSpeed(30));
	ASSERT_TRUE(car.SetGear(2));
	ASSERT_EQ(car.GetGear(), 2);
}

TEST(CarTest, SpeedLimitations)
{
	Car car;
	car.TurnOnEngine();

	ASSERT_TRUE(car.SetGear(1));

	ASSERT_TRUE(car.SetSpeed(30));
	ASSERT_EQ(car.GetSpeed(), 30);

	ASSERT_FALSE(car.SetSpeed(40));
	ASSERT_EQ(car.GetSpeed(), 30);
}
TEST(CarTest, ShiftToReverse)
{
	Car car;
	car.TurnOnEngine();

	ASSERT_TRUE(car.SetGear(-1));
	ASSERT_EQ(car.GetGear(), -1);
}

TEST(CarTest, CannotShiftToReverseWhileMoving)
{
	Car car;
	car.TurnOnEngine();
	car.SetGear(1);
	car.SetSpeed(10);

	ASSERT_FALSE(car.SetGear(-1));
	ASSERT_EQ(car.GetGear(), 1);
}

TEST(CarTest, CannotTurnOffEngineInInvalidConditions)
{
	Car car;
	car.TurnOnEngine();
	car.SetGear(1);
	car.SetSpeed(10);

	ASSERT_FALSE(car.TurnOffEngine());
	ASSERT_TRUE(car.IsTurnedOn());

	car.SetGear(0);
	ASSERT_FALSE(car.TurnOffEngine());
	ASSERT_TRUE(car.IsTurnedOn());

	car.SetSpeed(0);
	ASSERT_TRUE(car.TurnOffEngine());
	ASSERT_FALSE(car.IsTurnedOn());
}

TEST(CarTest, DirectionChange)
{
	Car car;
	car.TurnOnEngine();

	ASSERT_TRUE(car.SetGear(1));
	ASSERT_TRUE(car.SetSpeed(10));
	ASSERT_EQ(car.GetDirection(), Direction::FORWARD);

	ASSERT_TRUE(car.SetGear(0));
	ASSERT_TRUE(car.SetSpeed(0));

	ASSERT_TRUE(car.SetGear(-1));
	ASSERT_TRUE(car.SetSpeed(10));
	ASSERT_EQ(car.GetDirection(), Direction::BACKWARD);
}

TEST(CarTest, ShiftToNeutralWhenEngineOff)
{
	Car car;
	ASSERT_TRUE(car.SetGear(1));
	car.SetSpeed(10);
	ASSERT_FALSE(car.TurnOffEngine());
	ASSERT_EQ(car.GetGear(), 1);

	ASSERT_TRUE(car.SetGear(0));
	ASSERT_EQ(car.GetGear(), 0);
}

GTEST_API_ int main(int argc, char** argv)
{
	std::cout << "Running tests" << std::endl;
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}