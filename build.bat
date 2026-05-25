@echo off
cl /Zi demo.c /Fedemo.exe /link /PDB:demo.pdb /incremental:no /subsystem:windows opengl32.lib 
