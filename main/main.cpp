#include "RC.hpp"

extern "C" void app_main(void) {
	pizda::RC::getInstance().start();
}