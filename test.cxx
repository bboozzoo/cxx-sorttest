/**
 * vector vs. set test
 * Copyright (C) 2015  Maciej Borzecki
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */

#include <random>
#include <vector>
#include <set>
#include <algorithm>
#include <iostream>
#include <string>
#include <chrono>
#include <boost/program_options.hpp>

using namespace std;
namespace po = boost::program_options;

class timer {
public:
    timer(const string &text)
        : start(chrono::high_resolution_clock::now()),
          msg(text) {

    }

    ~timer() {
        auto now = chrono::high_resolution_clock::now();
        auto elapsed = now - start;
        cerr << "TIMER " << msg << " " << elapsed.count() << endl;
    }

private:
    chrono::high_resolution_clock::time_point start;
    string msg;
};

int main(int argc, char *argv[])
{
    po::options_description desc("Options");

    size_t count;
    size_t upper_range;

    desc.add_options()
        ("help,h", "Show help")
        (",r", po::value<size_t>(&upper_range)->default_value(255), "Upper range of random number set")
        (",e", po::value<size_t>(&count)->default_value(100000), "Data set size")
        ;

    po::variables_map opts;
    try {
        po::store(po::parse_command_line(argc, argv, desc), opts);
        po::notify(opts);
    } catch (exception &e) {
        cerr << "failed to parse command line: " << e.what() << endl;
        cerr << desc << endl;
        return -1;
    }

    if (opts.count("help")) {
        cerr << desc << endl;
        return 0;
    }

    cerr << "starting with values: " << endl
         << "  data set size: " << count << endl
         << "  value upper range: " << upper_range << endl;

    default_random_engine eng;
    uniform_int_distribution<> dis(0, upper_range);

    vector<int> random_nums(count);

    generate(random_nums.begin(), random_nums.end(),
             [&] { return dis(eng); });

    cerr << "size before: " << random_nums.size() << endl;

    {
        vector<int> temp(random_nums.begin(), random_nums.end());
        timer t("sort/unique/resize");

        sort(temp.begin(), temp.end());
        auto end_pos = unique(temp.begin(), temp.end());
        temp.resize(distance(temp.begin(), end_pos));
        cerr << "size after: " << temp.size() << endl;
    }

    {
        timer t("set");

        set<int> s(random_nums.begin(), random_nums.end());
        vector<int> temp(s.begin(), s.end());
        cerr << "size after: " << temp.size() << endl;
    }

    return 0;
}
