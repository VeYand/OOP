#ifndef SHAPE_INCLUDE_ICANVASDRAWABLE_H
#define SHAPE_INCLUDE_ICANVASDRAWABLE_H

#include "ICanvas.h"
#include <memory>

class ICanvasDrawable
{
public:
	virtual void Draw(std::shared_ptr<ICanvas>& canvas) = 0;
};

#endif // SHAPE_INCLUDE_ICANVASDRAWABLE_H
