# perriera/extras_arc
Welcome to the perriera/extras_arc project. 

[![CMake](https://github.com/mattcoding4days/extras/actions/workflows/cmake.yml/badge.svg?branch=dev)](https://github.com/mattcoding4days/extras/actions/workflows/cmake.yml)

<div align="center">
  <img width="442" height="320" src="assets/extras.png">
  <br>
</div>

## Who would want to use this?
> This project specializes in compressing zip archives into hexadecimal format as well as performing an operation were files that do not need to be sent across a socket connection are removed, (but restored later). See the following for more information:

 - HOWTO-implode.md
 - HOWTO-parcel.md
 - HOTTO-wrap.md

## Prerequisites
To use this template you will need a Linux environment, (Ubuntu is idea).

 1. [Install pip](https://linuxize.com/post/how-to-install-pip-on-ubuntu-18.04/), (either pip 2 or pip 3)
 2. [Install cmake](https://cmake-python-distributions.readthedocs.io/en/latest/installation.html) using pip, (cmake 3.2.1 or better required)
 3. Create project on [Github.com](https://github.com) using **perriera/extras_arc** out of the box, (or as a Github template).
 
Once you have established these THREE STEPS you may do the following

	git clone https://github.com/perriera/extras_rsi.git
	cd extras_arc
	mkdir build
	cd build
	cmake ..
	make
	cd ..
	build/run-unittests-extras_arc

If you have done everything correctly, you will see a Catch2 diagnostic with all green, (similar to the following):

	perry@ubuntu:~/Projects/extras_arc$ build/run-unittests-extras_arc 
	===============================================================================
	All tests passed (1 assertion in 2 test cases)


## CPM Optimization
> Note: Be sure to have the desired **VERSION** of perrier/extras specified in the **VERSION** keyword of the CPMAddPackage specification, (in your CMakeLists.txt). Also, to optimize CPM support on your projects be sure to set the CPM_SOURCE_CACHE environment variable for shared CPM libraries. Typically you would add this to your `.bashrc` script. With this environment variable set, the CPM package manager will not need to reload after successive build/ directory resets, (aka. `rm -rf build`). 

	export CPM_SOURCE_CACHE=$HOME/.cache/CPM

## Visual Studio Code (build/ directory) Compilation Fail Safe
The industry practice of compiling to a build/ directory is supported here. When you detect some funny business going on with your development environment, (for example if the cmake utility keeps rebuilding everything), merely delete the build/ directory, (aka. `rm -rf build`) and recreate it. If you are using the Visual Studio Code environment you can press **SHIFT-CTRL-B**, (see `.vscode/tasks.conf`) which will force a rebuild of the directory, (including re-creating `build/` for you).

> Please note: At present whenever you re-open your project with Visual Studio Code the cmake utility may or may not be in sync with the projects, (you'll notice this when all the source files keep getting rebuilt). To correct this open a Terminal window **inside** the Visual Studio Code environment and delete the build/ directory, (aka. `rm -rf build`)then rebuild the project with **SHIFT-CTRL-B**.

## FakeIt2 C++ Mocking Framework
This project is already setup for use with [FakeIt](https://github.com/eranpeer/FakeIt). Anyone familiar with writing interface mocks, (as in [Mock Object](https://en.wikipedia.org/wiki/Mock_object) should find the built-in support for mocking interfaces using the FakeIt framework to be indispensible here).

## Catch2 C++ Test Case Framework
This project is already setup for use with [Catch2](https://github.com/catchorg/Catch2). Anyone familiar with writing test cases, (as in [TDD - Test Driven Development](https://en.wikipedia.org/wiki/Test-driven_development) should find the built-in support for Catch2 to be indispensible here).

## JIRA/Confluence/Bitbucket support 
This project is already setup for use with [Jira (software)](https://en.wikipedia.org/wiki/Jira_(software)). Anyone familiar with writing JIRA entries as part of morning [SCRUM](https://en.wikipedia.org/wiki/Scrum_(software_development)) meetings, (or bi-weekly [SCRUM SPRINT](https://en.wikipedia.org/wiki/Scrum_Sprint) meetings) will find **perriera/extras_arc** to be well suited to the needs of JIRA/SCRUM/SPRINT.

## Conclusion
Your brand new C++ project is now setup and ready for use with **[perriera/extras](https://github.com/perriera/extras)**, (which  comes bundled with [spdlog](https://github.com/gabime/spdlog), [cpr](https://github.com/libcpr/cpr), and [nlohmann json](https://github.com/nlohmann/json) support, plus others). 
