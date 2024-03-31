#ifndef SHAPE_INCLUDE_SHAPECONTROLSERVICE_H
#define SHAPE_INCLUDE_SHAPECONTROLSERVICE_H

#include "CCircle.h"
#include "CLineSegment.h"
#include "CRectangle.h"
#include "CTriangle.h"
#include <memory>
#include <vector>

class ShapeControlService
{
public:
	void ReadShapes(const std::string& inputFileName);
	void PrintShapeWithMaxAreaInfo() const;
	void PrintShapeWithMinPerimeterInfo() const;

private:
	std::vector<std::shared_ptr<IShape>> m_shapes;
};

#endif // SHAPE_INCLUDE_SHAPECONTROLSERVICE_H
