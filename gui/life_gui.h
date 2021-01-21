#ifndef LIFE_GUI_H
#define LIFE_GUI_H

#include <QApplication>
#include <QIcon>
#include <QLayout>
#include <QPalette>
#include <QPixmap>
#include <QPushButton>
#include <QRect>
#include <QString>
#include <QToolButton>
#include <QVBoxLayout>
#include <QWidget>
#include <Qt>
#include <cell.h>
#include <edit_cell_button.h>
#include <start_button.h>
#include <stdio.h>
#include <windows.h>

#define MANAGE_BUTTONS_HE 30
#define START_BORDER_WI 1
#define START_BORDER_HE 1
#define UP_BORDER_WI 9
#define UP_BORDER_HE 1
#define LEFT_BORDER_WI 1
#define LEFT_BORDER_HE 9
#define CELL_WI 9
#define CELL_HE 9

typedef QApplication* event_loop;

void find_max_avalible_free_space(uint16_t *width, uint16_t *height);

uint32_t find_scale_value(uint16_t usage_width, uint16_t usage_height, uint8_t cells_w, uint8_t cells_h);

event_loop init_event_loop(char *argv[]);

void create_gui(uint8_t cells_count_wi, uint8_t cells_count_he, uint16_t ms_delay);

void start_event_loop(event_loop el);

#endif
