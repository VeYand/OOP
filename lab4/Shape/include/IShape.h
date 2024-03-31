#ifndef SHAPE_INCLUDE_I_SHAPE_H
#define SHAPE_INCLUDE_I_SHAPE_H

#include <cstdint>
#include <string>

class IShape
{
public:
	[[nodiscard]] virtual double GetArea() const = 0;
	[[nodiscard]] virtual double GetPerimeter() const = 0;
	[[nodiscard]] virtual std::string ToString() const = 0;
	[[nodiscard]] virtual uint32_t GetOutlineColor() const = 0;
};

#endif // SHAPE_INCLUDE_I_SHAPE_H