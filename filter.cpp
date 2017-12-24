#include "filter.h"
#include <string>
#include <tuple>

std::vector<std::string> split(const std::string &str, char d)
{
    auto r = std::vector<std::string>();

    std::string::size_type start = 0;
    auto stop = str.find_first_of(d);
    while(stop != std::string::npos)
    {
        r.push_back(str.substr(start, stop - start));

        start = stop + 1;
        stop = str.find_first_of(d, start);
    }

    r.push_back(str.substr(start));

    return r;
}

std::vector<int> str_toip(const std::vector<std::string> &s) {
    auto tmp = std::vector<int> ();

    tmp.reserve(s.size());
    std::transform(s.begin(), s.end(), std::back_inserter(tmp), [](auto &elem){
       return std::stoi(elem);
    });
    return tmp;
}
