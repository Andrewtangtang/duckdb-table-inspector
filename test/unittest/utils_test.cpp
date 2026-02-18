
#include "catch/catch.hpp"

#include "util.hpp"

using namespace duckdb; // NOLINT

TEST_CASE("FormatPercentage formats block percentages", "[util]") {
	// Zero total blocks returns 0.0%.
	REQUIRE(FormatPercentage(0, 0) == "0.0%");
	REQUIRE(FormatPercentage(5, 0) == "0.0%");

	// 0% when no blocks used.
	REQUIRE(FormatPercentage(0, 100) == "0.0%");

	// 50%.
	REQUIRE(FormatPercentage(50, 100) == "50.0%");

	// 100%.
	REQUIRE(FormatPercentage(100, 100) == "100.0%");

	// Fractional percentage.
	REQUIRE(FormatPercentage(1, 3) == "33.3%");
	REQUIRE(FormatPercentage(2, 3) == "66.7%");
}
