@echo off
cl /nologo /Zi demo.c /Fedemo.exe /link /PDB:demo.pdb /incremental:no /subsystem:windows opengl32.lib glu32.lib 
