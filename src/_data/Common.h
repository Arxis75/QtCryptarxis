#pragma once

#include <givaro/modular-integer.h>
#include <map>
#include <chrono>

using Givaro::Integer;

using std::time_t;

using std::string;
using std::vector;
using std::map;

using std::stoi;

using std::ostream;
using std::dec;
using std::hex;
using std::min;
using std::endl;
using std::cout;
using std::cerr;

struct cmp_str { bool operator()(char const *a, char const *b) const { return strcmp(a, b) < 0; } };
static const map<const char*, const uint8_t, cmp_str> map_hexa_chars = { {"0", 0}, {"1", 1}, {"2", 2}, {"3", 3},
                                                            {"4", 4}, {"5", 5}, {"6", 6}, {"7", 7},
                                                            {"8", 8}, {"9", 9}, {"a", 10}, {"A", 10},
                                                            {"b", 11}, {"B", 11}, {"c", 12}, {"C", 12},
                                                            {"d", 13}, {"D", 13}, {"e", 14}, {"E", 14},
                                                            {"f", 15}, {"F", 15} };


