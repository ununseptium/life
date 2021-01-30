#include <config_parser.h>

uint32_t conf_parsing(uint8_t *width, uint8_t *height, uint16_t *time){
	*width = 0;
	*height = 0;
	*time = 0;

	FILE* config = fopen(".config", "r");
	if (config == NULL) return 1;

	char cur_str[255];
	for (int i = 0; i < 3; i++){
		if (fgets(cur_str, 255, config) == NULL){
			fclose(config);
			return 2;
		}

		char *tab_char = strchr(cur_str, '\t');
		if (tab_char == NULL){
			fclose(config);
			return 2;
		}
		
		int value = strtol(tab_char + 1, (char**)NULL, 10);
		if (value == 0 || errno == ERANGE){
			fclose(config);
			return 2;
		}

		if (strncmp("width", cur_str, strlen("width")) == 0){
			*width = (uint8_t)value;
		} else if (strncmp("height", cur_str, strlen("height")) == 0){
			*height = (uint8_t)value;
		} else if (strncmp("time", cur_str, strlen("time")) == 0){
			*time = (uint16_t)value;
		} else {
			fclose(config);
			return 2;
		}

	}

	fclose(config);
	if (*width == 0 || *height == 0 || *time == 0) return 2;

	return 0;
}
