////////////////////////////////////////////////////////////////////////////////
//
// Filter Cascade
//
// Defines the function prototype for the filter_cascade function. The
// implementation of this function is given in Linear Assembly in
// filter_cascade.sa. Supporting (non-performance-critical) functions are given
// in filter_cascade.c.
//
////////////////////////////////////////////////////////////////////////////////

#ifndef _FILTER_CASCADE_H
#define _FILTER_CASCADE_H

#include <types.h>

/////////////////// Public function prototypes /////////////////////////////////

// Advances the filter state by one time step. The next sample is passed in, and
// the next output value is passed out.
float filter_cascade_advance(
        float sample_in,
        float *filter_state,
        float *feedforward_coefficients,
        float *feedback_coefficients
);

#endif
