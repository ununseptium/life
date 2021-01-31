#include <comand_line_parser.h>

uint32_t cl_parsing(int argc, char **argv, uint8_t *width, uint8_t *height, uint16_t *time){
	for (int paramter_index = 0; paramter_index < argc; paramter_index++){
		if (strcmp("-w", argv[paramter_index]) == 0 && paramter_index != argc - 1){
			int value = strtol(argv[paramter_index + 1], (char**)NULL, 10);
			if (value == 0 || errno == ERANGE){
				*width = 0;
				return 1;
			}
			*width = (uint8_t)value;
		} else if (strcmp("-h", argv[paramter_index]) == 0 && paramter_index != argc - 1){
			int value = strtol(argv[paramter_index + 1], (char**)NULL, 10);
			if (value == 0 || errno == ERANGE){
				*height = 0;
				return 1;
			}
			*height = (uint8_t)value;
		} else if (strcmp("-t", argv[paramter_index]) == 0 && paramter_index != argc - 1){
			int value = strtol(argv[paramter_index + 1], (char**)NULL, 10);
			if (value == 0 || errno == ERANGE){
				*time = 0;
				return 1;
			}
			*time = (uint8_t)value;
		}
	}

	return 0;
}
