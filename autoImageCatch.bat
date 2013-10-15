cd /d %~dp0
set PATH=%PATH%;C:\Tools\wget\bin
set /a interval=0*1000
set booth=06
rem set imgPath=http://tokati1829.sakura.ne.jp/t8_private/img/
set imgPath=http://192.168.2.2/image/

@echo off
setlocal enabledelayedexpansion
set fName=init
set /a j=1
:LOOP
	echo !j!
	if !j! GEQ 10 ( 
		set name=%booth%_0%num%!j!.jpg
		set fName=%imgPath%!name!
	 ) ELSE if !j! GEQ 100 ( 
		set fName=%imgPath%%booth%_%num%!j!.jpg
	 ) ELSE ( 
		set name=%booth%_00%num%!j!.jpg
		set fName=%imgPath%!name!
	 ) 
	echo fName !fName!
	
	if exist ../catche/tmp1.jpg ( 
		del ../catche/tmp1.jpg
	 ) 
	if exist ../catche/tmp2.jpg ( 
		del ../catche/tmp2.jpg
	 ) 

	wget !fName! -T 60 -t 4 -O ../catche/tmp1.jpg
	for %%i in ( ../catche/tmp1.jpg ) do ( 
		set size1=%%~zi
		echo %size1%
	 ) 

	:LOOP2

	wget !fName! -T 60 -t 4 -O ../catche/tmp2.jpg
	for %%i in ( ../catche/tmp2.jpg ) do ( 
		set size2=%%~zi
		echo %size2%
	 ) 

	if %size2% GTR %size1% (  
		if exist ../catche/tmp1.jpg ( 
			del ../catche/tmp1.jpg
	 	)
		move ../catche/tmp2.jpg ../catche/tmp1.jpg
		set /a size1 = %size2%
	 ) else if %size1% NEQ 0 ( 
		if %size2% EQU %size1% (
			goto :OUTLOOP
		 ) 
	 ) 

	goto :LOOP2

	:OUTLOOP
	move ../catche/tmp1.jpg !name!
	set /a j+=1
	set /p continue="to continue press return"

goto :LOOP

endlocal
@echo on
