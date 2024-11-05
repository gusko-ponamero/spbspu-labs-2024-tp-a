#ifndef COMMANDS_H
#define COMMANDS_H

#include <iosfwd>
#include <algorithm>
#include <functional>
#include <vector>
#include "Shapes.h"
#include <Delimeter.h>

namespace ponamarev
{
	void area(std::istream& in, std::ostream& out, const std::vector< Polygon >& polygons);
	double getAreaEven(const std::vector< Polygon >& polygons);
	double getAreaOdd(const std::vector< Polygon >& polygons);
	double getAreaMean(const std::vector< Polygon >& polygons);
	double getAreaNum(const std::vector< Polygon >& polygons, size_t number);

	void max(std::istream& in, std::ostream& out, const std::vector< Polygon >& polygons);
	double getAreaMax(const std::vector< Polygon >& polygons);
	size_t getTopMax(const std::vector< Polygon >& polygons);

	void min(std::istream& in, std::ostream& out, const std::vector< Polygon >& polygons);
	double getAreaMin(const std::vector< Polygon >& polygons);
	size_t getTopMin(const std::vector< Polygon >& polygons);

	void count(std::istream& in, std::ostream& out, const std::vector< Polygon >& polygons);
	size_t getCountEven(const std::vector< Polygon >& polygons);
	size_t getCountOdd(const std::vector< Polygon >& polygons);
	size_t getCountNum(const std::vector< Polygon >& polygons, size_t number);

	void perms(std::istream& in, std::ostream& out, const std::vector< Polygon >& polygons);

	void same(std::istream& in, std::ostream& out, const std::vector< Polygon >& polygons);
	Point getDelta(const Point& p1, const Point& p2);
	bool isSame(const Polygon& p1, const Polygon& p2);
	bool isSameTwo(const Point& p1, const Point& p2, const Polygon& pol1, const Polygon& pol2);
	bool deltaCheck(const Point& point, const Polygon& polygon, const Point& delta);
	bool isSameDelta(const Point& p1, const Point& p2, const Point& delta);

	void lessArea(std::istream& in, std::ostream& out, const std::vector< Polygon >& polygons);
	bool areaComparator(const Polygon& lhs, const Polygon& rhs);
}


#endif // !COMMANDS_H
