#include <types.h>

#include "lab2.h"

// Includes only the appropriate header to the type of filter.
#if     FILTER_TYPE_SELECTED == FILTER_TYPE_LADDER
    #include "filter_ladder.h"
#elif   FILTER_TYPE_SELECTED == FILTER_TYPE_LATTICE
    #include "filter_lattice.h"
#endif

// Initializes the filter
void filter_init() {

#if     FILTER_TYPE_SELECTED == FILTER_TYPE_LADDER
    ladder_initialize_filter();
#elif   FILTER_TYPE_SELECTED == FILTER_TYPE_LATTICE
    lattice_initialize_filter();
#else
    return;
#endif

}

// Takes a new sample and advances the filter state.
void take_sample(uint16_t sample) {

#if     FILTER_TYPE_SELECTED == FILTER_TYPE_LADDER
    ladder_take_sample();
#elif   FILTER_TYPE_SELECTED == FILTER_TYPE_LATTICE
    lattice_take_sample();
#else
    return;
#endif

}

// Calculates the next output sample, based on the current filter state.
uint16_t next_sample() {

#if     FILTER_TYPE_SELECTED == FILTER_TYPE_LADDER
    ladder_next_sample();
#elif   FILTER_TYPE_SELECTED == FILTER_TYPE_LATTICE
    lattice_next_sample();
#else
    return 0;
#endif

}
