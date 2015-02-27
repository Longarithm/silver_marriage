@echo off

for %%a in (??) do (
   echo test %%a
   %1.exe < %%a > %%a.out
)