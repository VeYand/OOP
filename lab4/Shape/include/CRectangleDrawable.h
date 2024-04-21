#ifndef SHAPE_INCLUDE_CRECTANGLEDRAWABLE_H
#define SHAPE_INCLUDE_CRECTANGLEDRAWABLE_H

#include "CRectangle.h"
#include "ICanvasDrawable.h"

class CRectangleDrawable
	: CRectangle
	, ICanvasDrawable
{
	void Draw(std::shared_ptr<ICanvas>& canvas) override;
};

#endif // SHAPE_INCLUDE_CRECTANGLEDRAWABLE_H
