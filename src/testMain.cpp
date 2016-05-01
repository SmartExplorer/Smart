/*
 * testMain.cpp
 *
 *  Created on: 30 Apr 2016
 *      Author: Kiljaeden
 */
#include <iostream>
#include <vector>
#include <boost/lambda/lambda.hpp>
using namespace std;

int main(void) {
    using namespace boost::lambda;
    typedef std::istream_iterator<int> in;
    std::for_each(
        in(std::cin), in(), std::cout << (_1 * 3) << " " );
}



