#include "Maths_TestApp.h"

int main() {
	
	// allocation
	auto app = new Maths_TestApp();

	// initialise and loop
	app->run("AIE", 1280, 720, false);

	// deallocation
	delete app;

	return 0;
}