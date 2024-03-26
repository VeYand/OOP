#pragma once
#ifndef CAR_SRC_CAR_H
#define CAR_SRC_CAR_H

enum class Direction
{
	FORWARD,
	BACKWARD,
	STAY
};

class Car
{
public:
	Car();
	bool TurnOnEngine();
	bool TurnOffEngine();
	bool SetGear(int gear);
	bool SetSpeed(int speed);
	[[nodiscard]] bool IsTurnedOn() const;
	[[nodiscard]] Direction GetDirection() const;
	[[nodiscard]] int GetSpeed() const;
	[[nodiscard]] int GetGear() const;

private:
	void SetDirection();
	Direction m_direction;
	bool m_isTurnedOn;
	int m_gear;
	int m_speed;
};

#endif // CAR_SRC_CAR_H
