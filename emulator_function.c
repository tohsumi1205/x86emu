#include "emulator_function.h"

uint32_t get_code8(Emulator *emu, int index) {
  return emu->memory[emu->eip + index];
}

int32_t get_sign_code8(Emulator *emu, int index) {
  return (int8_t)emu->memory[emu->eip + index];
}

uint32_t get_code32(Emulator *emu, int index) {
  int i;
  uint32_t ret = 0;

  // little endian
  for (i = 0; i < 4; i++) {
    ret |= get_code8(emu, index + i) << (i * 8);
  }
  return ret;
}

int32_t get_sign_code32(Emulator *emu, int index) {
  return (int32_t)get_code32(emu, index);
}

uint32_t get_register32(Emulator *emu, int index) {
  return emu->registers[index];
}

uint32_t get_memory8(Emulator *emu, uint32_t address) {
  return emu->memory[address];
}

uint32_t get_memory32(Emulator *emu, uint32_t address) {
  int i;
  uint32_t ret = 0;
  for (i = 0; i < 4; i++) {
    ret |= get_memory8(emu, address + i) << (8 * i);
  }
  return ret;
}

void set_memory8(Emulator *emu, uint32_t address, uint32_t value) {
  emu->memory[address] = value & 0xFF;
}

void set_memory32(Emulator *emu, uint32_t address, uint32_t value) {
  int i;
  for (i = 0; i < 4; i++) {
    set_memory8(emu, address + i, value >> (i * 8));
  }
}

void set_register32(Emulator *emu, int index, uint32_t value) {
  emu->registers[index] = value;
}

void push32(Emulator *emu, uint32_t value) {
  uint32_t address = get_register32(emu, ESP) - 4;
  set_register32(emu, ESP, address);
  set_memory32(emu, address, value);
}

uint32_t pop32(Emulator *emu) {
  uint32_t address = get_register32(emu, ESP);
  uint32_t ret = get_memory32(emu, address);
  set_register32(emu, ESP, address + 4);
  return ret;
}
