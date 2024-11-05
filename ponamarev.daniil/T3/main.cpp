#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <limits>
#include <iterator>
#include <map>
#include <functional>
#include <numeric>

#include "Shapes.h"
#include "Commands.h"

int main(int argc, char* argv[])
{
    using namespace ponamarev;
    std::vector< Polygon > polygons;
    if (argc < 2)
    {
        std::cout << "There are not enough vertices\n";
        return 1;
    }
    std::ifstream file(argv[1]);
    if (!file.is_open())
    {
        std::cout << "The file does not open\n";
        return 2;
    }

    while (!file.eof())
    {
        std::copy(std::istream_iterator< Polygon >{file}, std::istream_iterator< Polygon >{}, std::back_inserter(polygons));
        file.clear();
        file.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }

    using namespace std::placeholders;
    std::map< std::string, std::function< void(std::istream&, std::ostream&) > > commands;
    {
        commands["AREA"] = std::bind(area, _1, _2, polygons);
        commands["MAX"] = std::bind(max, _1, _2, polygons);
        commands["MIN"] = std::bind(min, _1, _2, polygons);
        commands["COUNT"] = std::bind( count, _1, _2, polygons);
        commands["PERMS"] = std::bind(perms, _1, _2, polygons);
        commands["LESSAREA"] = std::bind(lessArea, _1, _2, polygons);
        commands["SAME"] = std::bind(same, _1, _2, polygons);
    }

    std::string command;
    while (std::cin >> command)
    {
        try
        {
            commands.at(command)(std::cin, std::cout);
        }
        catch (const std::out_of_range&)
        {
            std::cout << "<INVALID COMMAND>" << '\n';
        }
        catch (const std::logic_error& e)
        {
            std::cout << e.what() << '\n';
        }
        std::cin.clear();
        std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }

    return 0;
}
