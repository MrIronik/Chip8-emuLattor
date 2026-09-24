from pathlib import Path

roms = {
    "OP_Test_0x00E0.ch8":   [0x00, 0xE0],
}

output = Path(".")

for filename, program in roms.items():
    (output / filename).write_bytes(bytes(program))