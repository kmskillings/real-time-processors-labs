#include <types.h>

#include "filter_ladder.h"
#include "lab2.h"

#define SAMPLE_INDEX_MASK (FILTER_LENGTH - 1)

extern float impulse_response[FILTER_LENGTH];   // The impulse response that this filter should have. Defined in lab2.h.

static float    coefficients[FILTER_LENGTH];    // The array of filter coefficients.
static uint16_t samples[FILTER_LENGTH];         // The array of current and previously-used samples.

static uint16_t sample_index_newest;    // The index of the most recently-taken (newest) sample in samples.
static uint16_t sample_index_oldest;    // The index of the least recently-taken (oldest) sample in samples.

// Initializes the filter state.
void ladder_initialize_filter() {

    // Sets all the samples to 0 (Shouldn't be rigorously necessary, but just to be safe).
    for (uint16_t i = 0; i < FILTER_LENGTH; i++) {
        samples[i] = 0;
    }

    // Sets up the filter response.
    coefficients = impulse_response;

}

// Takes a new sample and advances the filter state.
void ladder_take_sample(uint16_t sample) {

    // Stores the sample.
    samples[sample_index_oldest] = sample;

    // The newly taken sample is the newest sample.
    sample_index_newest = sample_index_oldest;

    // The second-oldest sample becomes the oldest sample.
    sample_index_oldest = (sample_index_oldest - 1) & SAMPLE_INDEX_MASK;

}

// Calculates the next output sample value.
uint16_t ladder_next_sample() {

    float accumulator   = 0;                    // Accumulates the value of the output sample.
    float sample_cursor = sample_index_newest;  // The index of the sample that is currently being operated on.

    for (uint16_t i = 0; i < FILTER_LENGTH; i++) {

        // Accumulates the next rung of the ladder
        accumulator = accumulator + samples[sample_cursor] * coefficients[i];

        // Advances the sample cursor
        sample_cursor = (sample_cursor + 1) & SAMPLE_INDEX_MASK;
    }

    // Casts the accumulator to a uint16_t, then returns
    return (uint16_t) accumulator;

}
