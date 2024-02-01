#include <types.h>

#include "filter_lattice.h"
#include "lab2.h"

static float lattice_coefficients[FILTER_LENGTH + 1];

static float filter_current_state[FILTER_LENGTH + 1];
static float filter_previous_state[FILTER_LENGTH + 1];

static uint16_t output;

// Initializes the filter state.
void lattice_initialize_filter() {

    float alpha[FILTER_LENGTH + 1];
    float beta[FILTER_LENGTH + 1];

    uint16_t i;
    for (i = 0; i < FILTER_LENGTH; i++) {
        alpha[i + 1] = impulse_response[i];
        beta[i] = impulse_response[FILTER_LENGTH - i - 1];
    }
    alpha[0] = 1.0f;
    beta[FILTER_LENGTH] = 1.0f;

    for (i = FILTER_LENGTH; i > 0; i--) {
        lattice_coefficients[i] = alpha[i];
        float k = alpha[i];
        float d = 1 - k * k;

        uint16_t j;
        for (j = 0; j < i; j++) {
            alpha[j] = (alpha[j] - k * beta[j]) / d;
        }

        for (j = 0; j < i; j++) {
            beta[j] = alpha[i - j - 1];
        }
    }

    lattice_coefficients[0] = 1.0f;
}

// Takes a new sample and advances the filter state.
void lattice_take_sample(uint16_t sample) {

    // A better way to do things. Marginally more elegant, but uses twice as much memory to store state information.
    float accumulator;

    uint16_t i;
    for (i = 1; i < FILTER_LENGTH + 1; i++) {

        // First, copy out this stage's previous state.
        filter_previous_state[i] = filter_current_state[i];

        // Calculate this stage's new state.
        filter_current_state[i] = lattice_coefficient[i] * accumulator + filter_previous_state[i - 1];  // g_i[n] = k_i * f_(i-1) + g_(i-1)[n-1];

        // Calculate the new accumulator value.
        accumulator = accumulator + lattice_coefficient[i] * filter_previous_state[i - 1];              // f_i[n] = f_(i-1)[n] + k_i * g_(i-1)[n-1];
    }

    // Now the accumulator should have the value of the output of the lattice filter.
    // However, since the impulse response has an extraneous 1 at the beginning, we need to subtract
    // off the initial value again.
    output = (uint16_t)accumulator - sample;

    // Kind of a dumb, clunky way to do things tbh. But it's the first I thought of.
    /*
    float accumulator;                  // Progressively adds up the "f" value of the filter.
    float current_stage_last_state;     // The last state of the filter stage currently being calculated.
                                        // Equivalent to g_i[n-1] from the notes.
    float preceding_stage_last_state;   // The last state of the filter stage preceding this one.
                                        // Equivalent to g_(i-1)[n-1] from the notes.

    accumulator = (float)sample;                    // f0[n] = x[n]
    preceding_stage_last_state = filter_state[0];   // Sets up for loop
    filter_state[0] = accumulator;                  // g0[n] = x[n]


    uint16_t i;
    for (i = 1; i < FILTER_LENGTH + 1; i++) {

        // Saves g_m[n-1]
        current_stage_last_state = filter_state[i];

        // g_i[n] = k_i * f_i + g_(i-1)[n-1]
        filter_state[i] = lattice_coefficients[i] * accumulator + preceding_stage_last_state;

        // f_i[n] = f_(i-1)[n] + k_i * g_(i-1)[n-1]
        accumulator = accumulator + lattice_coefficients[i] * preceding_stage_last_state;

        // Sets up for the next loop around.
        preceding_stage_last_state = current_stage_last_state;
    }

    // The accumulator should now be equal to the output of the filter.
    // However, since we have an extra 1 at the beginning of the impulse response,
    // we need to subtract the original sample value to get the value to output.
    output = (uint16_t)accumulator - sample;
    */

}

// Calculates the next output sample value.
uint16_t lattice_next_sample() {
    return output;
}
