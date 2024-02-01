#ifndef _FILTER_LATTICE_H
#define _FILTER_LATTICE_H

#include <types.h>

// Function prototypes

// Initializes the filter state.
void lattice_initialize_filter();

// Takes a new sample and advances the filter state.
void lattice_take_sample(uint16_t sample);

// Calculates the next output sample value.
uint16_t lattice_next_sample();

#endif
