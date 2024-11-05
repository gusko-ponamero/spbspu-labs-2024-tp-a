#include "Comands.h"
#include <algorithm>
#include <functional>
#include <iterator>
#include <iomanip>
#include <string>
#include <map>
#include <iostream>
#include <vector>
#include <limits>
#include <numeric>

namespace ponamarev
{
    void area(std::istream& in, std::ostream& out, const std::vector< Polygon >& polygons)
    {
        double sum = 0.0;
        std::map< std::string, std::function< double() > > area;
        {
            area["EVEN"] = std::bind(getAreaEven, polygons);
            area["ODD"] = std::bind(getAreaOdd, polygons);
            area["MEAN"] = std::bind(getAreaMean, polygons);
        }
        std::string arg;
        in >> arg;
        if (arg == "MEAN" || arg == "ODD" || arg == "EVEN")
        {
            if (polygons.empty() && arg == "MEAN")
            {
                throw std::logic_error("<INVALID COMMAND>");
            }
            sum = area[arg]();
        }
        else
        {
            size_t number = std::stoull(arg);
            if (number < 3)
            {
                throw std::logic_error("<INVALID COMMAND>");
            }
            sum = getAreaNum(polygons, number);
        }
        out << std::fixed << std::setprecision(1) << sum << '\n';
    }
    template < typename PredicateOneVariable >
    double getAreaIf(const std::vector< Polygon >& polygons, PredicateOneVariable predicate)
    {
        std::vector< Polygon > select;
        select.reserve(polygons.size());
        std::copy_if(polygons.cbegin(), polygons.cend(), std::back_inserter(select), predicate);
        return getAreaPolygons(select);
    }

    bool isEven(const Polygon& polygon)
    {
        return (polygon.points.size() % 2 == 0);
    }

    bool isOdd(const Polygon& polygon)
    {
        return (polygon.points.size() % 2 != 0);
    }

    double getAreaEven(const std::vector< Polygon >& polygons)
    {
        return getAreaIf(polygons, isEven);
    }

    double getAreaOdd(const std::vector< Polygon >& polygons)
    {
        return getAreaIf(polygons, isOdd);
    }

    double getAreaMean(const std::vector< Polygon >& polygons)
    {
        return (getAreaPolygons(polygons) / polygons.size());
    }

    bool isNum(const Polygon& polygon, size_t number)
    {
        return number == polygon.points.size();
    }

    double getAreaNum(const std::vector< Polygon >& polygons, size_t number)
    {
        using namespace std::placeholders;
        return getAreaIf(polygons, std::bind(isNum, _1, number));
    }
void max(std::istream& in, std::ostream& out, const std::vector< Polygon >& polygons)
    {
        std::map< std::string, std::function< double() > > maxArea;
        {
            maxArea["AREA"] = std::bind(getAreaMax, polygons);
        }

        std::map< std::string, std::function< size_t() > > maxTop;
        {
            maxTop["TOP"] = std::bind(getTopMax, polygons);
        }

        std::string arg;
        in >> arg;
        if (polygons.empty())
        {
            throw std::logic_error("<INVALID COMMAND>");
        }
        if (arg == "TOP")
        {
            out << maxTop[arg]() << '\n';
        }
        else
        {
            out << std::fixed << std::setprecision(1);
            out << maxArea[arg]() << '\n';
        }
    }

    double getAreaMax(const std::vector< Polygon >& polygons)
    {
        std::vector< double > area;
        area.reserve(polygons.size());
        std::transform(polygons.cbegin(), polygons.cend(), std::back_inserter(area), getAreaPolygon);
        auto max = std::max_element(area.cbegin(), area.cend());
        if (max == area.cend())
        {
            throw std::logic_error("<INVALID COMMAND>");
        }
        return *max;
    }

    size_t getTop(const Polygon& polygon)
    {
        return polygon.points.size();
    }

    size_t getTopMax(const std::vector< Polygon >& polygons)
    {
        std::vector< double > top;
        top.reserve(polygons.size());
        std::transform(polygons.cbegin(), polygons.cend(), std::back_inserter(top), getTop);
        auto max = std::max_element(top.cbegin(), top.cend());
        if (max == top.cend())
        {
            throw std::logic_error("<INVALID COMMAND>");
        }
        return *max;
    }
void min(std::istream& in, std::ostream& out, const std::vector< Polygon >& polygons)
    {
        std::map< std::string, std::function< double() > > minArea;
        {
            minArea["AREA"] = std::bind(getAreaMin, polygons);
        }

        std::map< std::string, std::function< size_t() > > minTop;
        {
            minTop["TOP"] = std::bind(getTopMin, polygons);
        }

        std::string arg;
        in >> arg;
        if (polygons.empty())
        {
            throw std::logic_error("<INVALID COMMAND>");
        }
        if (arg == "TOP")
        {
            out << minTop[arg]() << '\n';
        }
        else
        {
            out << std::fixed << std::setprecision(1);
            out << minArea[arg]() << '\n';
        }
    }

    double getAreaMin(const std::vector< Polygon >& polygons)
    {
        std::vector< double > area;
        area.reserve(polygons.size());
        std::transform(polygons.cbegin(), polygons.cend(), std::back_inserter(area), getAreaPolygon);
        auto min = std::min_element(area.cbegin(), area.cend());
        if (min == area.cend())
        {
            throw std::logic_error("<INVALID COMMAND>");
        }
        return *min;
    }

    size_t getTopMin(const std::vector< Polygon >& polygons)
    {
        std::vector< double > tops;
        tops.reserve(polygons.size());
        std::transform(polygons.cbegin(), polygons.cend(), std::back_inserter(tops), getTop);
        auto min = std::min_element(tops.cbegin(), tops.cend());
        if (min == tops.cend())
        {
            throw std::logic_error("<INVALID COMMAND>");
        }
        return *min;
    }
void count(std::istream& in, std::ostream& out, const std::vector< Polygon >& polygons)
    {
        std::map< std::string, std::function< size_t() > > count;
        {
            count["EVEN"] = std::bind(getCountEven, polygons);
            count["ODD"] = std::bind(getCountOdd, polygons);
        }
        std::string arg;
        in >> arg;
        if (arg == "EVEN" || arg == "ODD")
        {
            out << count[arg]() << '\n';
        }
        else
        {
            size_t num = std::stoull(arg);
            if (num < 3)
            {
                throw std::logic_error("<INVALID COMMAND>");
            }
            size_t res = getCountNum(polygons, num);
            out << res << "\n";
        }
    }

    size_t getCountEven(const std::vector< Polygon >& polygons)
    {
        return std::count_if(polygons.cbegin(), polygons.cend(), isEven);
    }

    size_t getCountOdd(const std::vector< Polygon >& polygons)
    {
        return std::count_if(polygons.cbegin(), polygons.cend(), isOdd);
    }

    size_t getCountNum(const std::vector< Polygon >& polygons, size_t number)
    {
        using namespace std::placeholders;
        return std::count_if(polygons.cbegin(), polygons.cend(), std::bind(isNum, _1, number));
    }

    bool isEqual(const Point& point1, const Point& point2)
    {
        return point1 == point2;
    }

    bool isPoint(const Point& point, const Polygon& polygon)
    {
        Point sample = point;
        auto pred1 = std::bind(isEqual, std::placeholders::_1, sample);
        auto it_forward = std::find_if(polygon.points.cbegin(), polygon.points.cend(), pred1);
        Point inverted({ point.y, point.x });
        auto pred2 = std::bind(isEqual, std::placeholders::_1, inverted);
        auto it_reverse = std::find_if(polygon.points.cbegin(), polygon.points.cend(), pred2);
        return it_forward != polygon.points.cend() || it_reverse != polygon.points.cend();
    }
bool isPerms(const Polygon& polygon, const Polygon& sample)
    {
        if (polygon.points.size() != sample.points.size())
        {
            return false;
        }
        using namespace std::placeholders;
        auto pred = std::bind(isPoint, _1, sample);
        size_t count = std::count_if(polygon.points.cbegin(), polygon.points.cend(), pred);
        size_t num = std::distance(polygon.points.cbegin(), polygon.points.cend());
        return count == num;
    }

    void perms(std::istream& in, std::ostream& out, const std::vector< Polygon >& polygons)
    {
        Polygon sample;
        in >> sample;
        if (!in || in.peek() != '\n' || sample.points.empty())
        {
            throw std::logic_error("<INVALID COMMAND>");
        }
        using namespace std::placeholders;
        auto pred = std::bind(isPerms, _1, sample);
        size_t count = std::count_if(polygons.cbegin(), polygons.cend(), pred);
        out << count << '\n';
    }
bool isSame(const Polygon& p1, const Polygon& p2)
    {
        if (p1.points.size() != p2.points.size())
        {
            return false;
        }
        using namespace std::placeholders;
        auto comp = std::bind(&isSameTwo, p1.points[0], _1, p1, p2);
        return std::find_if(p2.points.cbegin(), p2.points.cend(), comp) != p2.points.cend();
    }

    bool deltaCheck(const Point& point, const Polygon& polygon, const Point& delta)
    {
        using namespace std::placeholders;
        auto comp = std::bind(&isSameDelta, point, _1, delta);
        return std::find_if(polygon.points.cbegin(), polygon.points.cend(), comp) != polygon.points.cend();
    }

    bool isSameDelta(const Point& p1, const Point& p2, const Point& delta)
    {
        return (p2.x - p1.x == delta.x) && (p2.y - p1.y == delta.y);
    }

    bool isSameTwo(const Point& p1, const Point& p2, const Polygon& pol1, const Polygon& pol2)
    {
        Point delta = getDelta(p1, p2);
        using namespace std::placeholders;
        auto compWithDelta = std::bind(&deltaCheck, _1, pol2, delta);
        using diff_t = std::vector< Polygon >::difference_type;
        auto pol1CBegin = pol1.points.cbegin();
        auto pol1CEnd = pol1.points.cend();
        return std::count_if(pol1CBegin, pol1CEnd, compWithDelta) == static_cast<diff_t>(pol1.points.size());
    }
    Point getDelta(const Point& p1, const Point& p2)
    {
        return { p2.x - p1.x, p2.y - p1.y };
    }
    void same(std::istream& in, std::ostream& out, const std::vector< Polygon >& polygons)
    {
        std::istream::sentry sentry(in);
        if (!sentry)
        {
            return;
        }
        Polygon mask;
        in >> mask;
        if (!in || in.peek() != '\n')
        {
            throw std::invalid_argument("<INVALID ARGUMENT>");
        }
        if (mask.points.size() < 3)
        {
            throw std::logic_error("<MASK CANT HAVE LESS THAN 3 TOP>");
        }
        using namespace std::placeholders;
        auto comp = std::bind(isSame, _1, mask);
        out << std::count_if(polygons.cbegin(), polygons.cend(), comp) << '\n';
    }
}
