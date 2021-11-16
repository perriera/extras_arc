

# perriera/cpp_starter
Welcome to the perriera/cpp_starter project. 

[![CMake](https://github.com/mattcoding4days/extras/actions/workflows/cmake.yml/badge.svg?branch=dev)](https://github.com/mattcoding4days/extras/actions/workflows/cmake.yml)

<div align="center">
  <img width="442" height="320" src="assets/extras.png">
  <br>
</div>

## Who would want to use this?
> This project aims to get you up and running with C++17 based project with a 'git clone' operation. As well, this particular C++ project template comes with builtin [CPM](https://github.com/cpm-cmake/CPM.cmake) support. This means that you can incorporate other [github](https://github.com) projects, (or anything that uses the git tool) into your project with the simple inclusion of a CPM directive in in your CMakeLists.txt file. 

## Prerequisites
To use this template you will need a Linux environment, (Ubuntu is idea).

 1. [Install pip](https://linuxize.com/post/how-to-install-pip-on-ubuntu-18.04/), (either pip 2 or pip 3)
 2. [Install cmake](https://cmake-python-distributions.readthedocs.io/en/latest/installation.html) using pip, (cmake 3.2.1 or better required)
 3. Create project on [Github.com](https://github.com) using **perriera/cpp_starter** out of the box, (or as a Github template).
 
Once you have established these THREE STEPS you may do the following

	git clone https://github.com/<your project>
	cd <your project>
	mkdir build
	cd build
	cmake ..
	make
	cd ..
	build/run-unittests-cpp_starter

If you have done everything correctly, you will see a Catch2 diagnostic with all green, (similar to the following):

	perry@ubuntu:~/Projects/cpp_starter$ build/run-unittests-cpp_starter 
	===============================================================================
	All tests passed (1 assertion in 2 test cases)

However, you not done yet:

Inside your favorite editor, (or search & replace command utility):

 1. Global search and replace **cpp_starter** to <project_name> (case sensitive)
 2. Global search and replace **CPP_STARTER** to <PROJECT_NAME> (case sensitive)
 3. change directory name '**include/cpp_starter**' to '**include/<project_name>**'

Then do the following:

	rm -rf build
	cd build
	make
	cd ..
This will re-create the project now with all references to cpp_starter changed to <your_project_name>. To test this do  the following:

	build/run-unittests-<your_project_name>

## Changelog.md
When you go to make changes to your changelog.md you should maintain the version number of your project using 'include/version.hpp'. For example, in your version.hpp will look something similiar to the following but all referenced to CPP_STARTER will be changed to <YOUR_PROJECT_NAME>

	#ifndef _CPP_STARTER_VERSION_HPP
	#define _CPP_STARTER_VERSION_HPP

	/**
	 * @file version.hpp
	 * @author Matt Williams (matt@perriera.com)
	 * @author Perry Anderson (perry@perriera.com)
	 * @brief Adds version support for Cmake script
	 * @date 2021-08-08
	 */

	#define CPP_STARTER_VER_MAJOR 0
	#define CPP_STARTER_VER_MINOR 5
	#define CPP_STARTER_VER_PATCH 4

	#define CPP_STARTER_VERSION \
	  (CPP_STARTER_VER_MAJOR * 10000 + CPP_STARTER_VER_MINOR * 100 + CPP_STARTER_VER_PATCH)

	#endif// _CPP_STARTER_VERSION_HPP

From here add this to your github project and you are good to go:

	git add .
	git commit -m "Initial content"
	git push

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
This project is already setup for use with [Jira (software)](https://en.wikipedia.org/wiki/Jira_(software)). Anyone familiar with writing JIRA entries as part of morning [SCRUM](https://en.wikipedia.org/wiki/Scrum_(software_development)) meetings, (or bi-weekly [SCRUM SPRINT](https://en.wikipedia.org/wiki/Scrum_Sprint) meetings) will find **perriera/cpp_starter** to be well suited to the needs of JIRA/SCRUM/SPRINT.

## Conclusion
Your brand new C++ project is now setup and ready for use with **[perriera/extras](https://github.com/perriera/extras)**, (which  comes bundled with [spdlog](https://github.com/gabime/spdlog), [cpr](https://github.com/libcpr/cpr), and [nlohmann json](https://github.com/nlohmann/json) support, plus others). 
