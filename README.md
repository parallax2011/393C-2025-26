Files overview:

main.cpp - preAuton, auton, main functions
config.cpp - configuring robot devices
ROBOT.cpp - chassis constructor and drive functions (ex. PID, FPS)

controls/controls.cpp - macros, chassis control, intake control, optical sorting
controls/driver.cpp - usercontrol function and settings

calc/PID.cpp - PID class and constructor
calc/FPS.cpp - odom class and constructor (Field Positioning System) -- taken from JAR 2775V template
calc/calc.cpp - utility functions (ex. normalizing angles and converting pct -> voltage)

auton folder - different kinds of autos
