#include "Units.h"
#include "Testing.h"

BEGIN_TEST_SUITE(makeTests)
	BEGIN_TEST("kg comparisons")
		auto x = 57_kg;
		auto y = 42_kg;
		ASSERT_TRUE(x > y)
		ASSERT_TRUE(y < x)
		ASSERT_TRUE(x != y)
		ASSERT_TRUE(y == y)
		ASSERT_TRUE(y <= y)
		ASSERT_TRUE(y >= y)
		ASSERT_TRUE(y <= x)
		ASSERT_TRUE(x >= y)
	END_TEST
	BEGIN_TEST("unary minus")
		auto x = 57_kg;
		auto y = -57_kg;
		ASSERT_TRUE(x != y)
		ASSERT_TRUE(y < x)
		ASSERT_TRUE(x > y)
		ASSERT_APPROX_EQUAL(y.value, -57)
		// TODO : This as -y, x yields ambiguity issues
		ASSERT_APPROX_EQUAL((-y).value, x.value)
	END_TEST
	BEGIN_TEST("Compare two masses")
		auto x = 57_kg;
		auto y = 57_M;
		ASSERT_TRUE(x < y)
		ASSERT_TRUE(y > x)
		ASSERT_TRUE(x <= y)
		ASSERT_FALSE(x > y)
		ASSERT_TRUE(y >= x)
		ASSERT_FALSE(y < x)
	END_TEST
	BEGIN_TEST("Process two masses")
		auto x = 57_kg;
		auto y = 57_M;

		// assert conversion types
		SolarMass conversionTest = y + x;
		Kilogram conversionTest2 = x + y;
		SolarMass conversionTest3 = y - x;
		Kilogram conversionTest4 = x - y;
	END_TEST
	BEGIN_TEST("Gram Ctors")
		auto ull = 10_g;
		auto ld = 10.0_g;
		ASSERT_APPROX_EQUAL(ull, ld)

		Gram fromSolarMass(10.0_M);
		ASSERT_APPROX_EQUAL(1.9891e34_g, fromSolarMass)

		Gram fromKilogram(10.0_kg);
		ASSERT_APPROX_EQUAL(10000.0_g, fromKilogram)
	END_TEST
	BEGIN_TEST("Kilogram Ctors")
		auto ull = 10_kg;
		auto ld = 10.0_kg;
		ASSERT_APPROX_EQUAL(ull, ld)

		Kilogram fromSolarMass(10.0_M);
		ASSERT_APPROX_EQUAL(1.9891e31_kg, fromSolarMass)

		Kilogram fromGram(1000.0_g);
		ASSERT_APPROX_EQUAL(1_kg, fromGram)
	END_TEST
	BEGIN_TEST("SolarMass Ctors")
		auto ull = 10_M;
		auto ld = 10.0_M;
		ASSERT_APPROX_EQUAL(ull, ld)

		SolarMass fromKilogram(1.9891e30_kg * 2.0);
		ASSERT_APPROX_EQUAL(2.0_M, fromKilogram)

		SolarMass fromGram(1.9891e33_g * 2.0);
		ASSERT_APPROX_EQUAL(2.0_M, fromGram)
	END_TEST
END_TEST_SUITE








