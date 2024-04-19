#ifndef SHAPE_INCLUDE_I_SOLID_SHAPE_H
#define SHAPE_INCLUDE_I_SOLID_SHAPE_H

#include "IShape.h"

class ISolidShape : public IShape
{
public:
	[[nodiscard]] virtual uint32_t GetFillColor() const = 0;

	~ISolidShape() override = default;
};

#endif // SHAPE_INCLUDE_I_SOLID_SHAPE_H