#include "shapes.hpp"
#include <istream>
#include <iterator>
#include <algorithm>
#include <functional>
#include <numeric>
#include <Delimiter.hpp>

std::istream& artemev::operator>>(std::istream& in, Point& point)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }

  using delChar = artemev::DelimiterCharI;
  int x, y;
  in >> delChar({'('}) >> x >> delChar({';'}) >> y >> delChar({')'});
  if (in)
  {
    point.x = x;
    point.y = y;
  }
  return in;
}

bool artemev::Point::operator==(const Point& oth) const
{
  return x == oth.x && y == oth.y;
}

std::istream& artemev::operator>>(std::istream& in, Polygon& polygon)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }

  int countTop;
  in >> countTop;
  if (countTop < 3)
  {
    in.setstate(std::ios::failbit);
    return in;
  }

  std::vector< Point > points;
  std::copy_n(std::istream_iterator< Point >{ in }, countTop, std::back_inserter(points));

  if (in)
  {
    polygon.points = std::move(points);
  }

  return in;
}

double artemev::Polygon::getArea() const
{
  using namespace std::placeholders;
  auto accumulateArea = std::bind(AccumulateArea{ points.at(1) }, _1, _2, points.at(0));
  return std::accumulate(points.cbegin(), points.cend(), 0.0, accumulateArea);
}

double countArea(const artemev::Point& first, const artemev::Point& second, const artemev::Point& third)
{
  return std::abs((second.x - first.x) * (third.y - first.y) - (third.x - first.x) * (second.y - first.y)) / 2;
}

double artemev::AccumulateArea::operator()(double area, const Point& second, const Point& third)
{
  area += countArea(first, second, third);
  first = second;
  return area;
}

int artemev::Polygon::countRightAngle() const
{
  auto countAngle = AccumulateAngle{ points[points.size() - 1], points[points.size() - 2] };
  return std::count_if(points.cbegin(), points.cend(), countAngle);
}

bool artemev::AccumulateAngle::operator()(const Point& third)
{
  Point side1 = { second.x - first.x, second.y - first.y };
  Point side2 = { third.x - first.x, third.y - first.y };

  first = second;
  second = third;

  return side1.x * side2.x + side1.y * side2.y == 0;
}
