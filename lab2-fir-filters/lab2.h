#ifndef _LAB2_H
#define _LAB2_H

// Lab settings

#define FILTER_EXPONENT (5)                     // Used to determine filter length. Having powers of 2 makes everything easier.
#define FILTER_LENGTH   (1 << FILTER_EXPONENT)  // The length of the filter.

#define FILTER_TYPE_LADDER  1
#define FILTER_TYPE_LATTICE 2

#define FILTER_TYPE_SELECTED FILTER_TYPE_LADDER // Selects which filter type will be compiled for.

// Function prototypes

// Initializes the filter
void initialize_filter();

// Takes a new sample and advances the filter state.
void take_sample(uint16_t sample);

// Calculates the next output sample, based on the current filter state.
uint16_t next_sample();

#endif _LAB2_H
