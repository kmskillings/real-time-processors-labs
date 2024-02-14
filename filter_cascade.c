#include "filter_cascade.h"

// The filter state, in the form [0, d0[n-1], d0[n-2], 0, d1[n-1], d1[n-2], ...]
float filter_state[12] = {0};

// The feedforward coefficients, in the form [b00, b01, b02, b10, a11, ...]
float feedforward_coefficients[12] = {
  1,
  0,
  -1,
  1,
  0,
  -1,
  1,
  0,
  -1,
  1,
  0,
  -1
};

// The feedback coefficients, in the form [a00, a01, a02, a10, a11, ...]
float feedback_coefficients[12] = {
  1,
  -0.8450571299,
  0.9449364543,
  1,
  -1.465843081,
  0.9449364543,
  1,
  -1.265697837,
  0.8551633358,
  1,
  -1.010648012,
  0.8362827301
};

// The gain coefficients, in the form [g0, 0, 0, g1, 0, 0, ...]
float gain_coefficients[12] = {
  0.1945419908, 0, 0,
  0.1945419908, 0, 0,
  0.1092029065, 0, 0,
  0.9440608621, 0, 0
};
