@echo Run me in the Visual Studio 2010 command prompt
@rem If the compilation fails, make sure every cpp in the Makefile except
@rem CrocGame.cpp is added to the project
msbuild /t:Rebuild /p:Configuration=Release
