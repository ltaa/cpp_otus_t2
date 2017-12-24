#pragma once

#include <cassert>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <tuple>
#include <type_traits>

// ("",  '.') -> [""]
// ("11", '.') -> ["11"]
// ("..", '.') -> ["", "", ""]
// ("11.", '.') -> ["11", ""]
// (".11", '.') -> ["", "11"]
// ("11.22", '.') -> ["11", "22"]





template <typename Container>
void print_reverse_ip(Container &container);

template <typename Container>
void printIp(const Container &container);

template <typename Container, typename Cmp>
auto filter(const Container &container, Cmp cmp);

template <typename Container>
void printOne(Container container);

template <typename Container>
void printFirstTwo(Container container);

template <typename Container>
void printAny(Container container);

std::vector<int> str_toip(const std::vector<std::string> &container);
std::vector<std::string> split(const std::string &str, char d);


template <typename Container>
void print_reverse_ip(Container &container) {

    std::sort(container.begin(), container.end(),[](auto &v1, auto &v2) {
        return !std::lexicographical_compare(v1.begin(), v1.end(), v2.begin(), v2.end());
    });
    printIp(container);
}



template <typename Container>
void printIp(const Container &container) {
    for(const auto &c : container) {
        for (const auto &ip_part : c) {
            if( &ip_part != &c.front() ) {
                std::cout<<".";
            }
            std::cout<<ip_part;
        }
        std::cout<<std::endl;
    }
}

template <typename Container>
auto _filterSequence(const Container& container, size_t) {
    return container;
}

template <typename Container, typename T, typename... Args>
auto _filterSequence(const Container& container, size_t idx, T t, Args... args);


template <typename Container, typename... Args>
auto filterSequence(const Container& container, Args... args){
    return _filterSequence(container, 0, args...);
}


template <typename Container, typename T, typename... Args>
auto _filterSequence(const Container& container, size_t idx, T t, Args... args) {
    auto r = filter(container, [idx,t](auto elem) {
        if (elem.at(idx) == t)
            return true;
        return false;
    });

    auto r2 = _filterSequence(r, idx + 1, args...);
    return r2;


}


template <typename Container, typename Cmp>
auto filter(const Container &container, Cmp cmp) {
    typename std::remove_cv<typename std::remove_reference<decltype (container)>::type>::type c;

        for (const auto &elem: container) {
            if (cmp(elem)) {
                c.push_back(elem);
            }
        }
    return c;
}


template <typename Container, typename... Args>
void printIpSequence(const Container& container, Args... args) {
    auto r = filterSequence(container, args...);
    printIp(r);
}


template <typename Container>
void printAny(Container container, uint8_t ip_val) {

    typename std::remove_cv<typename std::remove_reference<decltype (container)>::type>::type r;
    std::copy_if(container.begin(), container.end(), std::back_inserter(r), [ip_val](auto &tv){
        return std::any_of(tv.begin(), tv.end(), [ip_val] (auto &av){
            return av == ip_val;
        });
    });

    printIp(r);
}




