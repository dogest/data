@echo off
if "%1"=="" goto loop
echo TEST
echo Test%1
copy news%1.in news.in >nul
time <enter
news
time <enter
fc news%1.out news.out
pause
del news.in
del news.out
goto end
:loop
  for %%i in (0 1 2 3 4 5 6 7 8 9 10) do call %0 %%i
:end