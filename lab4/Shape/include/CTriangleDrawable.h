#ifndef SHAPE_INCLUDE_CTRIANGLEDRAWABLE_H
#define SHAPE_INCLUDE_CTRIANGLEDRAWABLE_H

#include "CTriangle.h"
#include "ICanvasDrawable.h"

class CTriangleDrawable
: CTriangle, ICanvasDrawable
{
	void Draw(std::shared_ptr<ICanvas>& canvas) override;
};

#endif // SHAPE_INCLUDE_CTRIANGLEDRAWABLE_H
