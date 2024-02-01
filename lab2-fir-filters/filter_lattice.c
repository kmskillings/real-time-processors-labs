#include <types.h>

#include "filter_lattice.h"
#include "lab2.h"

static float lattice_coefficients[FILTER_LENGTH + 1];

static float filter_state[FILTER_LENGTH + 1];

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



}

// Calculates the next output sample value.
uint16_t lattice_next_sample() {
    return 0;
}
