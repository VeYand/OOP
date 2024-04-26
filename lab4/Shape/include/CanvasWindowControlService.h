#ifndef SHAPE_INCLUDE_CANVASWINDOWCONTROLSERVICE_H
#define SHAPE_INCLUDE_CANVASWINDOWCONTROLSERVICE_H

#include "CCanvas.h"
#include "ShapeControlService.h"

class CanvasWindowControlService
{
public:
	CanvasWindowControlService();
	void DrawShapes(std::istream& input);

private:
	ShapeControlService m_shapeController;
	std::shared_ptr<CCanvas> m_canvas;
};

#endif // SHAPE_INCLUDE_CANVASWINDOWCONTROLSERVICE_H
