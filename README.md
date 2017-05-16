# Autonomous Localization
Research project for the Freshman Research Initiative's Autonomous Robots stream. This projects involves getting the Building-Wide Intelligence robots at the University of Texas at Austin to autonomously and accurately localize.

## Installation
This project uses ROS Indigo.

## Build
1) ensure amcl.launch file has min particles = 10,000 and max particles = 40,000
$ roscd segbot_navigation
$ geany launch/amcl.launch
2) compile
$ catin_make --pkg=auto_localize
3) run
$ rosrun auto_localize localize

 






