@echo off

for /L %%a in (1,1,1000) do (
	echo test %%a
	gen.exe %%a 100 1000 > in 
	%1.exe < in > in.ans   
	%2.exe < in > in.out
	if errorlevel 1 (
		echo RE
		exit
	)
	fc in.ans in.out
	if errorlevel 1 (
		echo WA
		exit
	)  
)