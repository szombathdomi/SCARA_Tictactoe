# SCARA-TicTacToe

Automated parallel SCARA robot for playing physical 4x4 Tic-Tac-Toe against human opponent.

## Features
* 4x4 board configuration, selectable starting player, and two difficulty modes (Easy/Hard).
* Stepper motor control with 1/8 microstepping via pre-calculated coordinate LUT. Vacuum gripper for piece manipulation.
* Human move detection via an analog sensor matrix mapped to the 16 board cells.
* Arduino-based finite state machine, hardware homing calibration, and I2C LCD interface.

## Modules
* `SCARA_Tictactoe_v1.0_release.ino`: Main state machine implementation.
* `MotionControl`: Parallel SCARA movement execution.
* `GameLogic`: Game state evaluation, win detection, and move generation.
* `SensorReader`: Analog polling and threshold evaluation for move detection.
* `VacuumGripper`: End effector control (vacuum pump, gripper) and disc feeder management.
* `LCDDisplay` & `ButtonHandler`: User interface and input logic.
