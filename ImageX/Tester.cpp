#include "Tester.h"
#include "iostream"

static bool testing;

void Tester::act_testing(bool set_on) {		// activate testing mode (write all print(string) )
	testing = set_on;
}

void Tester::print(const char* chars) {
	if (testing == true) {
		std::string string = chars;
		std::cout << string << std::endl;
	}
}