#include <life_gui.h>

int main (int argc, char** argv){
	event_loop el = init_event_loop(argv);
	create_gui(10, 10, 0);
	start_event_loop(el);
	return 0;
}
