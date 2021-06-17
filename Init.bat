set /P UserInput="Insert IDE abbreviation i.e (vs2015, vs2017, vs2019 ...): "
call .\vendor\bin\premake5\premake5.exe %UserInput%
PAUSE