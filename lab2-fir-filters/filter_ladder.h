#ifndef _FILTER_LADDER_H
#define _FILTER_LADDER_H

#include <types.h>

// Function prototypes

// Initializes the filter state.
void ladder_initialize_filter();

// Takes a new sample and advances the filter state.
void ladder_take_sample(uint16_t sample);

// Calculates the next output sample value.
uint16_t ladder_next_sample();

#endif
