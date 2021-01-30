#ifndef _CONFIG_PARSER_H
#define _CONFIG_PARSER_H

#include <errno.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

uint32_t conf_parsing(uint8_t *width, uint8_t *height, uint16_t *time);

#endif
