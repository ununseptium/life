#include <stdio.h>
#include <life_gui.h>
#include <config_parser.h>
#include <comand_line_parser.h>

int main (int argc, char** argv){
	uint8_t width_cl = 0;
	uint8_t height_cl = 0;
	uint16_t time_cl = 0;
	if (cl_parsing(argc, argv, &width_cl, &height_cl, &time_cl) != 0){
		puts("Command line arguments are incorrect");
		return 1;
	}

	uint8_t width_conf;
	uint8_t height_conf;
	uint16_t time_conf;
	uint32_t err_val = conf_parsing(&width_conf, &height_conf, &time_conf);
	if (err_val != 0){
		if (err_val == 1)
			puts("Configuration file does not exist");
		if (err_val == 2)
			puts("Configuration file is corrupt");
		return 1;
	}
	
	uint8_t width;
	if (width_cl != 0) width = width_cl;
	else width = width_conf;

	uint8_t height;
	if (height_cl != 0) height = height_cl;
	else height = height_conf;

	uint16_t time;
	if (time_cl != 0) time = time_cl;
	else time = time_conf;

	event_loop el = init_event_loop(argv);
	create_gui(10, 10, 0);
	start_event_loop(el);
	return 0;
}
