#include <cstdint>
#include <fstream>
#include <vector>

#include "chip8.hpp"

void Chip8::init(void) {
  /* Set the default/starting values of chip8 */
  program_counter = 0x200;
  opcode = 0;
  I = 0;
  stack_pointer = 0;

  /* Clear screen buffer */
  for (auto &pixel : gfx) {
    pixel = 0;
  }

  /* Clear chip8's stack */
  for (auto &byte : stack) {
    byte = 0;
  }

  /* Clear CPU registers */
  for (auto &reg : V) {
    reg = 0;
  }

  /* Clear memory */
  for (auto &byte : memory) {
    byte = 0;
  }

  /* Load Fontset */
  for (short i = 0; i < FONTSET_size; i++) {
    memory.at(i) = fontset.at(i);
  }

  /* Reset Timer */
  // TODO: Implement timer reset!
  delay_timer = 0;
  sound_timer = 0;
}

void Chip8::load(const std::string &path_to_file) {
  std::ifstream rom(path_to_file, std::ios::binary);

  if (!rom) {
    throw std::runtime_error("Failed to open ROM: " + path_to_file);
  }

  rom.seekg(0, std::ios::end);
  const auto rom_size = rom.tellg();
  rom.seekg(0, std::ios::beg);

  constexpr std::size_t program_start = 0x200;
  const std::size_t available = memory.size() - program_start;

  if (rom_size > static_cast<std::streamoff>(available)) {
    throw std::runtime_error("ROM is to large");
  }

  rom.read(reinterpret_cast<char *>(memory.data() + program_start),
           static_cast<std::streamsize>(rom_size));
}

// Care, if you enter empty opcode (0000) 0NNN handler call ans set PC to 0
void Chip8::emulateCycle(void) {
  /* Fetch opcode form memory */
  opcode = (memory.at(program_counter) << 8 | memory.at(program_counter + 1));

  /* Decode opcode */
  // TODO: Man it will be looong switch, do something about it...
  switch (opcode & 0xF000) {
  case 0x0000: // Clear screen
    switch (opcode) {
    case 0x00E0:
      OP_0x00E0_Handler();
      break;
    case 0x00EE:
      OP_0x00EE_Handler();
      break;
    default:
      OP_0x0NNN_Handler();
      break;
    }
    break;

  case 0x1000:
    OP_0x1NNN_Handler();
    break;

  case 0x2000:
    OP_0x2NNN_Handler();
    break;

  case 0x3000:
    OP_0x3XNN_Handler();
    break;

  case 0x6000:
    OP_6XNN_Handler();
    break;

  case 0xA000:
    I = opcode & 0x0FFF;
    program_counter += 2;
    break;

  default:
    throw std::runtime_error("emulateCycle error: Unknown opcode 0x" +
                             std::to_string(opcode) + "\n");
    return;
  }

  if (delay_timer > 0) {
    --delay_timer;
  }

  if (sound_timer > 0) {
    --sound_timer;
  }
}

// void Chip8::setKeys();

/* Chip8 getter functions */
uint16_t Chip8::getOpcode(void) { return opcode; }

std::array<uint8_t, MEMORY_size> Chip8::getMemory(void) const { return memory; }

std::array<uint8_t, CPU_registers_number> Chip8::getV(void) const { return V; }

uint16_t Chip8::getIndex_register(void) { return I; } // index register

uint16_t Chip8::getProgram_counter(void) { return program_counter; }

uint8_t Chip8::getDelay_timer(void) { return delay_timer; }

uint8_t Chip8::getSound_timer(void) { return sound_timer; }

std::array<uint16_t, CPU_stack_size> Chip8::getStack(void) const {
  return stack;
}

uint16_t Chip8::getStack_pointer(void) { return stack_pointer; }

std::array<uint16_t, KEYPAD_size> Chip8::getkey(void) const { return key; }

bool Chip8::getDraw_flag(void) { return draw_flag; }

std::array<uint8_t, SCREEN_width * SCREEN_hight> Chip8::getGfx(void) const {
  return gfx;
}

/* Chip8 OPCode Handler functions */

void Chip8::OP_0x00E0_Handler(void) {
  for (auto &pixel : gfx) {
    pixel = 0;
  }

  program_counter += 2;
}

void Chip8::OP_0x00EE_Handler(void) {
  --stack_pointer;
  program_counter = stack[stack_pointer];
  stack[stack_pointer] = 0x00;
}

void Chip8::OP_0x0NNN_Handler(void) {
  // I don't think this is used bit i implement it anyway
  program_counter = opcode;
}

void Chip8::OP_0x1NNN_Handler(void) { program_counter = (opcode & 0x0FFF); }

void Chip8::OP_0x2NNN_Handler(void) {
  stack[stack_pointer] = program_counter + 0x02;
  ++stack_pointer;

  program_counter = opcode & 0x0FFF;
}

void Chip8::OP_0x3XNN_Handler(void) {
  short x = ((opcode & 0x0F00) >> 8);
  uint8_t nn = (opcode & 0x00FF);

  if (V.at(x) == nn)
    program_counter += 0x02;

  program_counter += 0x02;
}

void Chip8::OP_6XNN_Handler(void) {
  short x = ((opcode & 0x0F00) >> 8);
  uint8_t nn = (opcode & 0x00FF);

  V.at(x) = nn;
  program_counter += 0x02;
}