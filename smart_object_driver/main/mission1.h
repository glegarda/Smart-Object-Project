#pragma once

#include "LP5024.h"
#include "ADXL345.h"


void mission1_start(void *_color_to_display);
void mission1_stop();
void mission1_sample(int16_t *mean_x, int16_t *mean_y);
int8_t mission1_get_random_color();

enum MovingState {
    STATIONNARY,
    MOVING

};

enum MovingState m_movingState;
