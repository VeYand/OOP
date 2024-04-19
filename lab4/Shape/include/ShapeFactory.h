#ifndef SHAPE_INCLUDE_SHAPEFACTORY_H
#define SHAPE_INCLUDE_SHAPEFACTORY_H

#include "./IShape.h"
#include <memory>

class ShapeFactory
{
public:
	static std::shared_ptr<IShape> constructShape(const std::string& info);

private:
	constexpr static const std::string CLineSegmentName = "line_segment";
	constexpr static const std::string CCircleName = "circle";
	constexpr static const std::string CRectangleName = "rectangle";
	constexpr static const std::string CTriangleName = "triangle";
};

#endif // SHAPE_INCLUDE_SHAPEFACTORY_H
