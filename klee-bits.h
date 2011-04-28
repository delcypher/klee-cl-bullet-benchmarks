static int float_bitwise_eq(float a, float b) {
  union {
    float f;
    uint32_t i;
  } au, bu;
  au.f = a; bu.f = b;
  return au.i == bu.i;
}
