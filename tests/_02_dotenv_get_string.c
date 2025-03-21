#include <string.h>

#include "allocators/allocator.h"
#include "parsers/dotenv.h"
#include "testing/assert.h"


int main() {
	Allocator a = form_std_allocator();
	char *buffer = "Zero=TheOne\n"
				   "Architect=Galatea\n"
				   "Simulation=Emulation";
	Dotenv *dotenv = parse_dotenv(&a, buffer);

	const char *val = dotenv->get_string(dotenv, "Zero");
	assert_str_equals(val, "TheOne");

	val = dotenv->get_string(dotenv, "Architect");
	assert_str_equals(val, "Galatea");

	val = dotenv->get_string(dotenv, "Simulation");
	assert_str_equals(val, "Emulation");

	return 0;
}