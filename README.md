# Project-Imitatum-Record-Terminal
This application is for use in a D&amp;D session, where my players can interact with a computer terminal at the antagonists base, detailing records on 'project imitatum', where half the staff of a black ops organization are 'imitations' (robots, not 'alive'), and stats ironically reflecting this are displayed. This is my first program written in C.

compiler.py - is a specialised file that allows direct execution of a compile command of the source code, in an IDE or directly with CMD, and an input function from Python to make the screen static to allow the reading of errors or confirm the compile worked.

project_imitatum.c - is the source code of the project, my first time coding in language C. Capable of data processing, specialised for the format of records.bin.

record-generator.py - is a python script that automatically generates the binary file, containing the record number, subject type, and loyalty status, changing them for specific subjects and favouring odds depending on certain circumstance (details in .exe).

records.bin - is the binary file containing all the records for the program to interact with, containing subect number, subject type, and subject loyalty (roughly 35,000 records).

Project-Imitatum-Terminal.exe - is the compiled program, designed for function on Windows devices.
