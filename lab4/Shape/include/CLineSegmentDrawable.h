#ifndef SHAPE_INCLUDE_CLINESEGMENTDRAWABLE_H
#define SHAPE_INCLUDE_CLINESEGMENTDRAWABLE_H

#include "CLineSegment.h"
#include "ICanvasDrawable.h"

class CLineSegmentDrawable
	: CLineSegment
	, ICanvasDrawable
{
	void Draw(std::shared_ptr<ICanvas>& canvas) override;
};

#endif // SHAPE_INCLUDE_CLINESEGMENTDRAWABLE_H
