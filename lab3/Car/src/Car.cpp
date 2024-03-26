#include "../include/Car.h"

const int MIN_SPEED = 0;
const int MAX_REVERSE_GEAR_SPEED = 20;
const int MAX_FIRST_GEAR_SPEED = 30;
const int MIN_SECOND_GEAR_SPEED = 20;
const int MAX_SECOND_GEAR_SPEED = 50;
const int MIN_THIRD_GEAR_SPEED = 30;
const int MAX_THIRD_GEAR_SPEED = 60;
const int MIN_FOURTH_GEAR_SPEED = 40;
const int MAX_FOURTH_GEAR_SPEED = 90;
const int MIN_FIFTH_GEAR_SPEED = 50;
const int MAX_FIFTH_GEAR_SPEED = 150;

Car::Car()
	: m_isTurnedOn(false)
	, m_direction(Direction::STAY)
	, m_gear(0)
	, m_speed(0)
{
}

bool Car::TurnOnEngine()
{
	m_isTurnedOn = true;
	return true;
}

bool Car::TurnOffEngine()
{
	if (m_gear != 0 || m_speed != 0)
	{
		return false;
	}

	m_isTurnedOn = false;
	return true;
}

void Car::SetDirection()
{
	if (m_speed == 0)
	{
		m_direction = Direction::STAY;
		return;
	}

	if (m_gear > 0)
	{
		m_direction = Direction::FORWARD;
		return;
	}

	m_direction = Direction::BACKWARD;
}

bool Car::SetGear(int gear)
{
	if (gear < -1 || gear > 5)
	{
		return false;
	}

	if (m_speed > 0 && (gear > 0 && m_gear < 0 || m_gear > 0 && gear < 0))
	{
		return false;
	}

	if (gear < 0 && m_direction == Direction::FORWARD
		|| gear > 0 && m_direction == Direction::BACKWARD)
	{
		return false;
	}

	if (gear == -1 && (m_speed < MIN_SPEED || m_speed > MAX_REVERSE_GEAR_SPEED)
		|| gear == 1 && (m_speed < MIN_SPEED || m_speed > MAX_FIRST_GEAR_SPEED)
		|| gear == 2 && (m_speed < MIN_SECOND_GEAR_SPEED || m_speed > MAX_SECOND_GEAR_SPEED)
		|| gear == 3 && (m_speed < MIN_THIRD_GEAR_SPEED || m_speed > MAX_THIRD_GEAR_SPEED)
		|| gear == 4 && (m_speed < MIN_FOURTH_GEAR_SPEED || m_speed > MAX_FOURTH_GEAR_SPEED)
		|| gear == 5 && (m_speed < MIN_FIFTH_GEAR_SPEED || m_speed > MAX_FIFTH_GEAR_SPEED))
	{
		return false;
	}

	m_gear = gear;
	return true;
}

bool Car::SetSpeed(int speed)
{
	if (!m_isTurnedOn)
	{
		return false;
	}

	if (m_gear == 0 && speed > m_speed)
	{
		return false;
	}

	if (m_gear == -1 && (speed < MIN_SPEED || speed > MAX_REVERSE_GEAR_SPEED)
		|| m_gear == 1 && (speed < MIN_SPEED || speed > MAX_FIRST_GEAR_SPEED)
		|| m_gear == 2 && (speed < MIN_SECOND_GEAR_SPEED || speed > MAX_SECOND_GEAR_SPEED)
		|| m_gear == 3 && (speed < MIN_THIRD_GEAR_SPEED || speed > MAX_THIRD_GEAR_SPEED)
		|| m_gear == 4 && (speed < MIN_FOURTH_GEAR_SPEED || speed > MAX_FOURTH_GEAR_SPEED)
		|| m_gear == 5 && (speed < MIN_FIFTH_GEAR_SPEED || speed > MAX_FIFTH_GEAR_SPEED))
	{
		return false;
	}

	m_speed = speed;
	SetDirection();
	return true;
}

bool Car::IsTurnedOn() const
{
	return m_isTurnedOn;
}

Direction Car::GetDirection() const
{
	return m_direction;
}

int Car::GetSpeed() const
{
	return m_speed;
}

int Car::GetGear() const
{
	return m_gear;
}