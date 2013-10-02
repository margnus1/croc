@echo Run me in the Visual Studio 2010 command prompt
@rem If the compilation fails, make sure every cpp in the Makefile except
@rem CrocGame.cpp is in the command line below
cl /EHsc /Zi main.cpp Crawler.cpp ToString.cpp ProgressBar.cpp /link wherescrocengine.lib