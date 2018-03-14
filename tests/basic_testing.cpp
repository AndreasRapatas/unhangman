#include "../third_party/catch2/single_include/catch.hpp"

#include "../include/hangman.h"

SCENARIO("filters") {

	GIVEN("a filled dictionary") {

		auto dictionary = read_dictionary("../words.txt");

		REQUIRE(dictionary.size() >= 20);

		WHEN("filter_length is called with 5") {
			auto filtered = filter_length(dictionary, 5);

			THEN("all words returned are of length 5") {

				for (const auto &w : filtered) {
					REQUIRE(w.size() == 5);
				}
			}
		}

		WHEN("filter_length is called with 9") {
			auto filtered = filter_length(dictionary, 9);

			THEN("all words returned are of length 9") {

				for (const auto &w : filtered) {
					REQUIRE(w.size() == 9);
				}
			}
		}

		WHEN("filter_pattern is called with a pattern of length 6") {

			auto filtered = filter_pattern(dictionary, "******");

			THEN("all words returned are of length 6") {

				for (const auto &w : filtered) {
					REQUIRE(w.size() == 6);
				}
			}
		}

		WHEN("filter_pattern is called with a pattern '***ato'") {

			auto pattern = "***ato";

			auto filtered = filter_pattern(dictionary, pattern);

			THEN("all words returned match this pattern") {

				for (const auto &w : filtered) {
					for (unsigned i = 0; i < 6; ++i) {
						if (pattern[i] == '*') { continue; }

						REQUIRE(pattern[i] == w[i]);
					}
				}
			}
		}
	}
}

SCENARIO("frequency counter") {

	GIVEN("a word of a's  'aaaa'") {

		std::vector<std::string> dictionary {"aaaa"};

		WHEN("counting frequency") {

			auto freq = count_character_frequency(dictionary);

			THEN("a should be 1 and all other 0") {

				for (auto p : freq) {
					if (p.first == 'a') {
						REQUIRE(p.second == 1);
					} else {
						REQUIRE(p.second == 0);
					}
				}
			}
		}
	}

	GIVEN("two words 'aaaa', 'abbb'") {

		std::vector<std::string> dictionary {"aaaa", "abbb"};

		WHEN("counting frequency") {

			auto freq = count_character_frequency(dictionary);

			THEN("a == 2, b == 1, and all other 0") {

				for (auto p : freq) {
					if (p.first == 'a') {
						REQUIRE(p.second == 2);
					} else if (p.first == 'b') {
						REQUIRE(p.second == 1);
					} else {
						REQUIRE(p.second == 0);
					}
				}
			}
		}

		WHEN("counting frequency with a pattern 'a***'") {

			auto freq = count_character_frequency(dictionary, "a***");

			THEN("a == 1, b == 1, and all other 0") {

				for (auto p : freq) {
					if (p.first == 'a') {
						REQUIRE(p.second == 1);
					} else if (p.first == 'b') {
						REQUIRE(p.second == 1);
					} else {
						REQUIRE(p.second == 0);
					}
				}
			}
		}

		WHEN("counting frequency with a pattern 'abbb'") {

			auto freq = count_character_frequency(dictionary, "abbb");

			THEN("results will be wrong because user should run filter_match beforehand") {

				for (auto p : freq) {
					REQUIRE(p.second == 0);
				}
			}
		}
	}
}

