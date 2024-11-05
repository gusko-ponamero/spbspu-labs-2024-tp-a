#include "Shapes.h"
#include <algorithm>
#include <functional>
#include <iterator>
#include <numeric>

#include "Delimeter.h"

std::istream& ponamarev::operator>>(std::istream & in, Point & point)
{
    std::istream::sentry sentry(in);
    if (!sentry)
    {
        return in;
    }
    Point unpoint;
    in >> DelimeterIO{ '(' };
    in >> unpoint.x;
    in >> DelimeterIO{ ';' };
    in >> unpoint.y;
    in >> DelimeterIO{ ')' };
    if (!in)
    {
        in.setstate(std::ios::failbit);
    }
    else
    {
        point = unpoint;
    }
    return in;
}

std::istream& ponamarev::operator>>(std::istream& in, Polygon& polygon)
{
    std::istream::sentry sentry(in);
    if (!sentry)
    {
        return in;
    }
    Polygon unpolygon;
    std::size_t size;
    in >> size;
    std::copy_n(std::istream_iterator<Point>{in}, size, std::back_inserter(unpolygon.points));
    if (!in)
    {
        in.setstate(std::ios::failbit);
    }
    else
    {
        polygon = unpolygon;
    }
    return in;
}
bool ponamarev::operator==(const Point& point1, const Point& point2)
{
    return point1.x == point2.x && point1.y == point2.y;
}

bool ponamarev::operator==(const Polygon& polygon1, const Polygon& polygon2)
{
    return polygon1.points == polygon2.points;
}

struct calculatArea
{
    ponamarev::Point point0;
    ponamarev::Point changPoint;
    double operator()(const ponamarev::Point& nextPoint)
    {
        double area = 0.5 * std::abs((nextPoint.x - point0.x) * (changPoint.y - point0.y) - (changPoint.x - point0.x) * (nextPoint.y - point0.y));
        changPoint = nextPoint;
        return area;
    }
};

double ponamarev::getAreaPolygon(const Polygon& polygon)
{
    auto area_func = calculatArea{ polygon.points[0], polygon.points[0] };
    std::vector< double > summandArea(polygon.points.size());
    std::transform(polygon.points.cbegin(), polygon.points.cend(), std::back_inserter(summandArea), area_func);
    return std::accumulate(summandArea.cbegin(), summandArea.cend(), 0.0);
}

double ponamarev::getAreaPolygons(const std::vector< Polygon >& polygons)
{
    std::vector< double > area(polygons.size());
    std::transform(polygons.cbegin(), polygons.cend(), std::back_inserter(area), getAreaPolygon);
    return std::accumulate(area.cbegin(), area.cend(), 0.0);
}
