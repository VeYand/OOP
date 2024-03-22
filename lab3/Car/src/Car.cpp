#include "../include/Car.h"

Car::Car()
	: m_isTurnedOn(false)
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

bool Car::SetGear(int gear)
{
	if (gear < -1 || gear > 5)
	{
		return false;
	}

	if (gear == 0)
	{
		m_gear = 0;
		return true;
	}

	if ((m_gear > 0 && gear < 0 || m_gear < 0 && gear > 0) && m_speed != 0)
	{
		return false;
	}

	if (gear == 1 && (m_speed < 0 || m_speed > 30)
		|| gear == 2 && (m_speed < 20 || m_speed > 50)
		|| gear == 3 && (m_speed < 30 || m_speed > 60)
		|| gear == 4 && (m_speed < 40 || m_speed > 90)
		|| gear == 5 && (m_speed < 50 || m_speed > 150))
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

	if (speed < 0 || speed > 150)
	{
		return false;
	}

	if (m_gear == -1 && speed > 20
		|| m_gear == 1 && speed > 30
		|| m_gear == 2 && (speed < 20 || speed > 50)
		|| m_gear == 3 && (speed < 30 || speed > 60)
		|| m_gear == 4 && (speed < 40 || speed > 90)
		|| m_gear == 5 && speed < 50)
	{
		return false;
	}

	m_speed = speed;
	return true;
}

bool Car::IsTurnedOn() const
{
	return m_isTurnedOn;
}

Direction Car::GetDirection() const
{
	if (m_speed == 0)
	{
		return Direction::STAY;
	}
	if (m_gear == -1)
	{
		return Direction::BACKWARD;
	}
	return Direction::FORWARD;
}

int Car::GetSpeed() const
{
	return m_speed;
}

int Car::GetGear() const
{
	return m_gear;
}