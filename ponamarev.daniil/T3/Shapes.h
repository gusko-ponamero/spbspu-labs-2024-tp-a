#ifndef SHAPES_H
#define SHAPES_H

#include <iosfwd>
#include <iostream>
#include <algorithm>
#include <functional>
#include <vector>

namespace ponamarev {
	struct Point
	{
		int x, y;
	};

	struct Polygon
	{
		std::vector< Point > points;
	};

	std::istream& operator>>(std::istream& in, Point& point);
	std::istream& operator>>(std::istream& in, Polygon& polygon);

	bool operator==(const Point& point1, const Point& point2);
	bool operator==(const Polygon& polygon1, const Polygon& polygon2);

	double getAreaPolygon(const Polygon& polygon);
	double getAreaPolygons(const std::vector< Polygon >& polygons);

}
#endif // !SHAPES_H
