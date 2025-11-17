# Ergoslide

## Repo layout

- .github
  - Workflows that build the firmware(s) for the microcontroller that runs the keyboard
- 3d files
  - The source Fusion 360 projects that produce the models for the case
- boards
  - The ZMK shield configuration
- config
  - Global ZMK shield configuration
- images
  - Images (e.g. PNGs, DXFs) needed to create the board or case
- models
  - Output models from Fusion 360 for the case
- pcb
  - The Kicad project for the keyboard PCB
- plates
  - Layouts exported from KLE, useful for creating either 3d models or DXFs for having the top plate manufactured, or automating the layout of the PCB
- zephyr
  - Root Zephyr config
