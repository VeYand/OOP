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
	void ReadShapes(std::istream& input);
	void ReadShapes(const std::string& inputFileName);
	void PrintShapeWithMaxAreaInfo() const;
	void PrintShapeWithMinPerimeterInfo() const;

private:
	std::vector<std::shared_ptr<IShape>> m_shapes;
};

#endif // SHAPE_INCLUDE_SHAPECONTROLSERVICE_H






/*
Интерфейс объектов, которые могут быть нарисованы на холсте
interface ICanvasDrawable
	+ Draw(canvas: ICanvas)

Интерфейс "Холст". Объявляет операции рисования основных графических примитивов: Линии, заливака, многоугольников, рисование и заливка окружностей и кругов
interface ICanvas
	+ DrawLine(from: CPoint, to: CPoint, lineColor: uint32_t)
	+ FillPolygon(points: vector<CPoint>, fillColor: uint32_t)
	+ DrawCircle(center: CPoint, radius: double, lineColor: uint32_t)
	+ FillCircle
)
*/
