#pragma once

#include <functional>
#include <limits>
#include <string>
#include <sstream>
#include <vector>

#define VERY_SMALL_NUM (10.0*std::numeric_limits<double>::epsilon())

#define ADD_NUM2(x, y) x #y
#define ADD_NUM(x, y) ADD_NUM2(x, y)
#define ASSERT_TRUE(x) if ((x) == false) throw std::string(ADD_NUM(__FILE__ ":", __LINE__) ": "#x);
#define ASSERT_FALSE(x) if ((x) == true) throw std::string(ADD_NUM(__FILE__ ":", __LINE__) ": " #x);
#define ASSERT_APPROX_EQUAL(x, y) if ((x) - VERY_SMALL_NUM > (y) || (x) + VERY_SMALL_NUM < (y))\
	 { std::ostringstream os; os << ADD_NUM(__FILE__ ":", __LINE__) ": (" #x ", " #y ") was: " << x << " " << y; throw std::string(os.str()); };

#define BEGIN_TEST_SUITE(name) TestContainer name() { TestContainer tests;
#define END_TEST_SUITE return tests; }
#define BEGIN_TEST(name) tests.emplace_back(name, []() -> bool {
#define END_TEST return true;});

typedef std::vector<std::pair<std::string, std::function<bool()>>> TestContainer;

