#ifndef SHAPE_INCLUDE_CCIRCLEDRAWABLE_H
#define SHAPE_INCLUDE_CCIRCLEDRAWABLE_H

#include "CCircle.h"
#include "ICanvasDrawable.h"


class CCircleDrawable
: CCircle, ICanvasDrawable
{
	void Draw(std::shared_ptr<ICanvas>& canvas) override;
};

#endif // SHAPE_INCLUDE_CCIRCLEDRAWABLE_H
