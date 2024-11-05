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
}
