#include <stdio.h>
#include <life_gui.h>
#include <comand_line_parser.h>

int main (int argc, char** argv){
	uint8_t width_cl = 0;
	uint8_t height_cl = 0;
	uint16_t time_cl = 0;
	if (cl_parsing(argc, argv, &width_cl, &height_cl, &time_cl) != 0){
		puts("Command line arguments are incorrect");
		return 1;
	}

	event_loop el = init_event_loop(argv);
	create_gui(10, 10, 0);
	start_event_loop(el);
	return 0;
}
