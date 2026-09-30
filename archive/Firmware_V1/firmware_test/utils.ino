float averaging_filter(float input, float* stored_values, int order, int* index) {
    //your code here
    float sum = 0;
    *(stored_values + *index) = input;

    for (int i = 0; i < order + 1; i++){
      sum += *(stored_values + i);
    }
    *index = (*index + 1) % (order + 1);
  return (sum)/(order + 1);
}
float map(float x, float in_min, float in_max, float out_min, float out_max) {
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}
void rawToScale(uint16_t* x, uint16_t* y, int* xs, int* ys) {
  if (*x < XTMIN) {
    *xs = XMAX; //x is reversed!
  }
  else if (*x > XTMAX) {
    *xs = XMIN;
  }
  else {
    *xs = ((XMIN - XMAX) * (*x) + XMAX * XTMAX - XMIN * XTMIN) / (XTMAX - XTMIN);
  }

  if (*y < YTMIN) {
    *ys = YMIN;
  }
  else if (*y > YTMAX) {
    *ys = YMAX;
  }
  else {
    *ys = ((YMAX - YMIN) * (*y) + YMIN * YTMAX - YMAX * YTMIN) / (YTMAX - YTMIN);
  }
}
