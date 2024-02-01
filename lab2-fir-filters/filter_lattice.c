#include <types.h>

#include "filter_lattice.h"
#include "lab2.h"

float lattice_coefficients[FILTER_LENGTH + 1];

float filter_state[FILTER_LENGTH + 1];

static uint16_t output;

// Private function prototypes

void calculate_lattice_coefficients();

void initialize_state();

// Public funtion bodies

// Initializes the filter state.
void lattice_initialize_filter() {

    calculate_lattice_coefficients();
    initialize_state();

}

// Takes a new sample and advances the filter state.
void lattice_take_sample(uint16_t sample) {

    float accumulator;                  // Progressively adds up the "f" value of the filter.
    float current_stage_last_state;     // The last state of the filter stage currently being calculated.
                                        // Equivalent to g_i[n-1] from the notes.
    float preceding_stage_last_state;   // The last state of the filter stage preceding this one.
                                        // Equivalent to g_(i-1)[n-1] from the notes.

    accumulator = (float)sample;                            // f0[n] = x[n]
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


}

// Calculates the next output sample value.
uint16_t lattice_next_sample() {
    return output;
}

// Private function bodies

void calculate_lattice_coefficients() {

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

void initialize_state() {

    uint16_t i;
    for (i = 0; i < FILTER_LENGTH + 1; i++) {
        filter_state[i] = 0;
    }

}
