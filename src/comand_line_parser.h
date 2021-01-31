#ifndef _COMAND_LINE_PARSER_H
#define _COMAND_LINE_PARSER_H

#include <stdint.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>

uint32_t cl_parsing(int argc, char **argv, uint8_t *width, uint8_t *height, uint16_t *time);

#endif
