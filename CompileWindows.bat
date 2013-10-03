@echo Run me in the Visual Studio 2010 command prompt
@rem If the compilation fails, make sure every cpp in the Makefile except
@rem CrocGame.cpp is in the command line below
cl /EHsc /O2 /Og /Zi /D WIN32 main.cpp Crawler3.cpp dijkstra.cpp ToString.cpp ProgressBar.cpp console.cpp /link wherescrocengine.lib