#include "../include/CarControlService.h"
#include "../include/Car.h"
#include "../include/StringUtils.h"
#include <format>
#include <iostream>

const std::string INFO_COMMAND = "info";
const std::string ENGINE_ON_COMMAND = "engine_on";
const std::string ENGINE_OFF_COMMAND = "engine_off";
const std::string SET_GEAR_COMMAND = "set_gear";
const std::string SET_SPEED_COMMAND = "set_speed";
const std::string EXIT_COMMAND = "exit";

void PrintDirection(Direction direction)
{
	std::cout << "Direction: ";
	switch (direction)
	{
	case Direction::FORWARD:
		std::cout << "forward";
		break;
	case Direction::BACKWARD:
		std::cout << "backward";
		break;
	case Direction::STAY:
		std::cout << "standing still";
		break;
	default:
		std::cout << "unknown";
		break;
	}
	std::cout << std::endl;
}

void PrintEngineState(bool isTurnedOn)
{
	std::cout << std::format("Engine state: {}", isTurnedOn ? "on" : "off") << std::endl;
}

void PrintCarSpeed(int speed)
{
	std::cout << std::format("Speed: {}", speed) << std::endl;
}

void PrintCarGear(int gear)
{
	std::cout << std::format("Gear: {}", gear) << std::endl;
}

void PrintCarStatus(const Car& car)
{
	PrintEngineState(car.IsTurnedOn());
	PrintDirection(car.GetDirection());
	PrintCarSpeed(car.GetSpeed());
	PrintCarGear(car.GetGear());
}

bool HandleEngineOnCommand(Car& car)
{
	car.TurnOnEngine();
	PrintEngineState(car.IsTurnedOn());
	return true;
}

bool HandleEngineOffCommand(Car& car)
{
	if (!car.TurnOffEngine())
	{
		std::cout << "Cannot turn off engine" << std::endl;
		return false;
	}
	PrintEngineState(car.IsTurnedOn());
	return true;
}

bool HandleSetGearCommand(Car& car)
{
	std::cout << "gear=";
	std::string gearLine;
	int gear;
	if (!std::getline(std::cin, gearLine))
	{
		std::cerr << "Cannot read input buffer" << std::endl;
		return false;
	}
	try
	{
		gear = std::stoi(gearLine);
	}
	catch (const std::exception&)
	{
		std::cout << "Invalid gear" << std::endl;
		return false;
	}

	if (!car.SetGear(gear))
	{
		std::cout << "Unable to set gear to " << gear << std::endl;
		return false;
	}

	PrintCarGear(gear);
	return true;
}

bool HandleSetSpeedCommand(Car& car)
{
	std::cout << "speed=";
	std::string speedLine;
	int speed;
	if (!std::getline(std::cin, speedLine))
	{
		std::cerr << "Cannot read input buffer" << std::endl;
		return false;
	}

	try
	{
		speed = std::stoi(speedLine);
	}
	catch (const std::exception&)
	{
		std::cout << "Invalid speed" << std::endl;
		return false;
	}

	if (!car.SetSpeed(speed))
	{
		std::cout << "Unable to set speed to " << speed << std::endl;
		return false;
	}

	PrintCarSpeed(speed);
	return true;
}

void RunCarControlService()
{
	Car car;

	std::cout << std::format(
		"Available commands: {}, {}, {}, {}, {}, {}",
		INFO_COMMAND,
		ENGINE_ON_COMMAND,
		ENGINE_OFF_COMMAND,
		SET_GEAR_COMMAND,
		SET_SPEED_COMMAND,
		EXIT_COMMAND)
			  << std::endl;

	std::string command;
	while (std::cout << ">" && std::getline(std::cin, command))
	{
		Trim(command);
		Lower(command);
		if (command == INFO_COMMAND)
		{
			PrintCarStatus(car);
		}
		else if (command == ENGINE_ON_COMMAND)
		{
			HandleEngineOnCommand(car);
		}
		else if (command == ENGINE_OFF_COMMAND)
		{
			HandleEngineOffCommand(car);
		}
		else if (command == SET_GEAR_COMMAND)
		{
			HandleSetGearCommand(car);
		}
		else if (command == SET_SPEED_COMMAND)
		{
			HandleSetSpeedCommand(car);
		}
		else if (command == EXIT_COMMAND)
		{
			break;
		}
		else
		{
			std::cout << std::format("Unknown command '{}'", command) << std::endl;
		}
	}

	std::cout << "Bye" << std::endl;
}