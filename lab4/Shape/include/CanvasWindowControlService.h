#ifndef SHAPE_INCLUDE_CANVASWINDOWCONTROLSERVICE_H
#define SHAPE_INCLUDE_CANVASWINDOWCONTROLSERVICE_H

#include "CCanvas.h"
#include "ShapeControlService.h"

class CanvasWindowControlService : public ShapeControlService
{
public:
	CanvasWindowControlService();
	void DrawShapes();

private:
	CCanvas m_canvas;
};

#endif // SHAPE_INCLUDE_CANVASWINDOWCONTROLSERVICE_H
