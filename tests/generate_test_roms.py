from pathlib import Path
import sys

output = Path(sys.argv[1])

script_name = "[GENERATE_TEST_ROM]"

blank_memory = 512
memory_size = 4096
max_rom_size = memory_size - blank_memory

roms = {
    "Load.ch8": [0x01] * max_rom_size,
    "OP_0x00E0.ch8":   [0x00, 0xE0],
}

# output = Path("test_roms")
output.mkdir(parents=True, exist_ok=True)

for filename, program in roms.items():
    if len(program) > max_rom_size:
        print(script_name + " Rom is to large: " + 
              filename + "size: " + str(len(program)) + " bytes")
    (output / filename).write_bytes(bytes(program))