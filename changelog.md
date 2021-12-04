
# Changelog
> All notable changes to this project will be documented in this file.</br>
The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.0.0/), 
and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).</br>
> To add a tag to the git repository do:
> > git tag -a v2.1.0 -m "Using v5.14.0"</br>
> > git push origin v2.1.0
> 

IMPORTANT: 
- Manually keep the changelog version number in sync with CMakeLists.txt project version.<br>
- Keep the changelog.md up to date, neat and tidy, (as it is a convenient tool for code maintenance).<br>
- Use [Semantic Versioning](https://semver.org/spec/v2.0.0.html) such that<br>
- Given a version number MAJOR.MINOR.PATCH, increment the:<br>
- MAJOR version when you make incompatible API changes,<br>
- MINOR version when you add functionality in a backwards compatible manner, and<br>
- PATCH version when you make backwards compatible bug fixes. <br>
- But there is no need to change the version number for correcting spelling errors, (etc).<br>
- MAKE SURE to tag and update the tag compare list below, (for quick code comparison purposes).<br>

## [Unreleased]
Detailed test cases</br>
Detailed class descriptions in README.md</br>
Correct URL for github, (for source compare)</br>

## [Next Steps]
Adding mock test cases </br>
Adding unit test cases </br>
Updated README.md accordinging</br>

#### 2.1.0 (2021-12-04)
### Changed 
- ImploderInterface
- ParcelInterface
- WrapInterface
- Using v5.14.0 

#### 2.0.0 (2021-12-03)
### Added 
- Added wrap utility
- Added HOWTO-wrap.md files 
### Changed 
- WrapInterface significantly
- Changed test cases
- Using v5.13.0 

#### 1.3.0 (2021-12-01)
### Added 
- Added parcel & implode utilities
- Added HOWTO-parcel.md files 
- Added HOWTO-implde.md files 

#### 1.2.0 (2021-12-01)
### Added 
- Refactored

#### 1.1.3 (2021-11-30)
### Added 
- Added directive

#### 1.1.2 (2021-11-30)
### Added 
- Corrected issue

#### 1.1.1 (2021-11-30)
### Added 
- Added CMakeLists.txt directives

#### 1.1.0 (2021-11-30)
### Added 
- Added instance

#### 1.0.2 (2021-11-30)
### Added 
- extra directive

#### 1.0.1 (2021-11-30)
### Merged 
- Using extras v4.0.1

#### 1.0.0 (2021-11-30)
### Merged 
- Renamed project 
- Renamed namespace

#### 0.9.0 (2021-11-30)
### Merged 
- Merged Parcel/Hex2bin

#### 0.8.0 (2021-11-30)
### Changed 
- Now using v5.5.0
- Added LICENSE.md

#### 0.7.0 (2021-11-29)
### Changed 
- Now using v5.4.0
- Added LICENSE.md

#### 0.6.5 (2021-11-24)
### Changed 
- Now using v5.3.6

#### 0.6.4 (2021-11-24)
### Changed 
- Now using v5.3.5

#### 0.6.3 (2021-11-21)
### Added 
- Fixed script

#### 0.6.2 (2021-11-20)
### Added 
- Using extras 5.3.4
- Muffled the diagnostics 

#### 0.6.1 (2021-11-20)
### Added 
- change behavior for merge()

#### 0.6.0 (2021-11-20)
### Added 
- merge()

#### 0.5.2 (2021-11-20)
### Added 
- Addtional add

#### 0.5.1 (2021-11-20)
### Added 
- Added FileNotFound checks 

#### 0.5.0 (2021-11-20)
### Added 
- Added ImploderInterface

#### 0.4.1 (2021-11-16)
### Added 
- Fixing git

#### 0.4.0 (2021-11-16)
### Added 
- Using extras v5.2.0

#### 0.3.0 (2021-11-14)
### Added 
- ImploderInterface
- MAKE_EXTRAS_ARC_LIBRARY_ONLY support

#### 0.2.0 (2021-11-14)
### Changed 
- Renamed project

#### 0.1.0 (2021-09-03)
### Added
- SHARED library support
- (perriera) extras library support, (3.11.0)
- CPM.cmake support
  * [CPM.cmake](https://github.com/cpm-cmake/CPM.cmake/blob/master/LICENSE) 
  * This allows us to include other Github packages with the ability
    to add package OPTIONS
- FakeIt Mock Library support
  * [FakeIt](https://github.com/eranpeer/FakeIt) 
  * This gives us the ability to mock C++ interfaces, (before implementation)
- Catch2 support
  * [Catch2](https://github.com/catchorg/Catch2)
  * This gives us the ability to test C++ classes, (during implementation)
### Changed
- CMakeLists.txt
  * [ModernCppStarter](https://github.com/TheLartians/ModernCppStarter/blob/master/LICENSE) 
- spdlog is now used as a shared library, (libspdlog.so)
- cpr is now used as a shared library, (libcpr.so)
- placed all source into /src
- placed all headers into /include/extras_arc

#### 0.0.0 (2021-08-26)
### Added
- Fetch_Content support
- changelog.md
- Project VERSION inside CMakeLists.txt & changelog.md
- Adopted new changelog format.
- sudo make install parameters
- shared library support
- sudo checkinstall support
- GoF: Abstract design pattern support
- Debian package support
- extra/interfaces.hpp support
- Unit test casses support, (Catch2)
- Mock framework support, (FakeIt)
### Changed
- CMakeLists.txt revamped & streamlined
- README.md revamped & streamlined
- Added documentation on code
- cxx_std_17 on all targets
- std::filesystem on all targets
### Maintained
- @brief style formatting
- Doxygen support 
### Removed
- Conan package manager deprecated

[Unreleased]: https://github.com/perriera/extras_arc/compare/v2.1.0...HEAD
[2.1.0]: https://github.com/perriera/extras_arc/compare/v2.0.0...v2.1.0
[2.0.0]: https://github.com/perriera/extras_arc/compare/v1.3.0...v2.0.0
[1.3.0]: https://github.com/perriera/extras_arc/compare/v1.2.0...v1.3.0
[1.2.0]: https://github.com/perriera/extras_arc/compare/v1.1.2...v1.2.0
[1.1.3]: https://github.com/perriera/extras_arc/compare/v1.1.2...v1.1.3
[1.1.2]: https://github.com/perriera/extras_arc/compare/v1.1.1...v1.1.2
[1.1.1]: https://github.com/perriera/extras_arc/compare/v1.1.0...v1.1.1
[1.1.0]: https://github.com/perriera/extras_arc/compare/v1.0.2...v1.1.0
[1.0.2]: https://github.com/perriera/extras_arc/compare/v1.0.1...v1.0.2
[1.0.1]: https://github.com/perriera/extras_arc/compare/v1.0.0...v1.0.1
[1.0.0]: https://github.com/perriera/extras_arc/compare/v0.9.0...v1.0.0
[0.9.0]: https://github.com/perriera/extras_arc/compare/v0.8.0...v0.9.0
[0.8.0]: https://github.com/perriera/extras_arc/compare/v0.7.0...v0.8.0
[0.7.0]: https://github.com/perriera/extras_arc/compare/v0.6.5...v0.7.0
[0.6.5]: https://github.com/perriera/extras_arc/compare/v0.6.4...v0.6.5
[0.6.4]: https://github.com/perriera/extras_arc/compare/v0.6.3...v0.6.4
[0.6.3]: https://github.com/perriera/extras_arc/compare/v0.6.2...v0.6.3
[0.6.2]: https://github.com/perriera/extras_arc/compare/v0.6.1...v0.6.2
[0.6.1]: https://github.com/perriera/extras_arc/compare/v0.6.0...v0.6.1
[0.6.0]: https://github.com/perriera/extras_arc/compare/v0.5.2...v0.6.0
[0.5.2]: https://github.com/perriera/extras_arc/compare/v0.5.1...v0.5.2
[0.5.1]: https://github.com/perriera/extras_arc/compare/v0.5.0...v0.5.1
[0.5.0]: https://github.com/perriera/extras_arc/compare/v0.4.1...v0.4.0
[0.4.1]: https://github.com/perriera/extras_arc/compare/v0.3.0...v0.4.1
[0.3.0]: https://github.com/perriera/extras_arc/compare/v0.2.0...v0.3.0
[0.2.0]: https://github.com/perriera/extras_arc/compare/v0.1.0...v0.2.0
[0.1.0]: https://github.com/perriera/extras_arc/releases/tag/v0.1.0

