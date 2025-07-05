
bool isBitSet(byte value, byte bitPosition) {
  return (value & (1 << bitPosition)) != 0;
}

void setBitHigh(byte &value, int bitPosition) {
  value |= (1 << bitPosition); // Set the specified bit to HIGH
}

void setBitLow(byte &value, int bitPosition) {
  value &= ~(1 << bitPosition); // Clear the specified bit (set it to LOW)
}
