# AsyEOS Software [![license](https://img.shields.io/badge/License-GPLv3-blue.svg)](COPYRIGHT) [![DOI](https://zenodo.org/badge/DOI/10.5281/zenodo.14291386.svg)](https://doi.org/10.5281/zenodo.14291386)

[![static analysis](https://github.com/R3BRootGroup/asyeos/actions/workflows/static_analysis.yml/badge.svg)](https://github.com/R3BRootGroup/asyeos/actions/workflows/static_analysis.yml) [![CI-CD](https://github.com/R3BRootGroup/asyeos/actions/workflows/main.yml/badge.svg)](https://github.com/R3BRootGroup/asyeos/actions/workflows/main.yml)

## The AsyEOS Framework
The AsyEOS (Asymmetric-matter Equation-Of-State) directory within the [R3BRoot](https://github.com/R3BRootGroup/R3BRoot) framework provides the full detector definitions, Monte Carlo simulation tools, and digitization algorithms for the detectors used in the AsyEOS/R3B (Reactions with Relativistic Radioactive Beams) experimental campaign at the GSI/FAIR (Facility for Antiproton and Ion Research) facility. AsyEOS-R3BRoot, developed on top of the FairRoot framework, is a versatile toolkit for performing Monte Carlo simulations and processing experimental data to measure the flows of neutrons and light charged particles produced in Nucleus-Nucleus collisions in order to investigate symmetry energy of the nuclear equation of state at densities above the saturation one. The AsyEOS software package is a source distribution with recurring releases for MacOS and Linux.

## License
AsyEOS is distributed under the terms of the GNU Lesser General Public Licence version 3 ([LGPLv3](https://github.com/R3BRootGroup/asyeos/blob/dev/LICENSE)).

## Release Information
Please see [releases](https://github.com/R3BRootGroup/asyeos/releases)

## Discussion Forum
For the software-related user support you can post a new topic on our [forum](https://forum.gsi.de/index.php?t=index&cat=40&) or you could use the GitHub issues.

## Contributing
Please ask your questions, request features, and report issues by [creating a github issue](https://github.com/R3BRootGroup/asyeos/issues/new/choose).

## Code Formatting
The AsyEOS project (as part of R3BRoot) uses clang-format-16 to ensure a common code formatting. The script "apply-format.sh" can be used for this purpose: 
~~~bash
. apply-format.sh
~~~

## Step by Step Installation

### Required Software

First, you will need to install FairSoft, FairRoot and R3BRoot. For more details:

1. Install [FairSoft](https://github.com/FairRootGroup/FairSoft), required version Nov22p1 or later

2. Install [FairRoot](https://github.com/FairRootGroup/FairRoot), required version 18.8.1 or later

3. Install [R3BRoot](https://github.com/R3BRootGroup/R3BRoot), required version jun24 or later

### Installation of AsyEOS as part of R3BRoot

~~~bash
export SIMPATH=%PATH_TO_FAIRSOFT%
export FAIRROOTPATH=%PATH_TO_FAIRROOT%
git clone https://github.com/R3BRootGroup/R3BRoot.git
cd R3BRoot
git clone https://github.com/R3BRootGroup/asyeos.git
cd ..
mkdir build
cd build
cmake ../R3BRoot/
. config.sh
make -j8
~~~

### Some Details of the AsyEOS Setup

- Chimera:
COMPLETE DESCRIPTION

- KRATA:
COMPLETE DESCRIPTION

- 

## Simulations (ongoing work)

Some simulations will be included inside the asyeos directory. You can find the subdirectories:

### geometry

This directory contains all the detector geometries generated from the macros located at ./asyeos/macros/geo. The existing geometries are:

## Data Analysis (ongoing work)

Data analysis is included inside the asyeos directory. You can find the subdirectories :

### asyeosdata

This directory contains all the data TCloneArray structures for the different levels of the detection system.

### asyeossource

This directory contains all the readers related to asyeos detectors :

- R3BChimeraReader for the Chimera detector
- 
and UCESB data structures are located at asyeossource/ext :

- ext_h101_chimera.h

this allows to get data at mapped level (raw data of each detector).

### chimera

This directory contains all the classes to analyse the single chimera data and move the raw data into cal and hit data levels.

### asyeosonline

This directory contains all the online analysis classes to correlate the data collected by the AsyEOS detectors.

### asyeosana

This directory contains all the analysis classes to correlate the data collected by the asyeos detectors.

### macros/

This directory contains some macros for online and offline analysis.

## Tested systems

The following systems are tested regularly.

| **OS Name** | **Arch** | **OS Version** | **Compiler**  | **CMake**       | **C++ Version** |
| ----------- | -------- | -------------- | ------------- | --------------- | --------------- |
| Almalinux   | x86\_64  | 9.3            | GCC 11.4.1    | 3.27.9 / 4.0.3  | C++17 / C++20 / C++23 |
| Almalinux   | x86\_64  | 9.4            | GCC 14.2.0    | 3.30.6          | C++17           |
| Almalinux   | x86\_64  | 9.7            | GCC 11.4.1    | 4.2.0           | C++17 / C++20 / C++23 |
| Almalinux   | x86\_64  | 10.1           | GCC 14.2.0    | 4.0.3           | C++17 / C++20 / C++23 |
| Almalinux   | x86\_64  | 10.2           | GCC 14.3.1    | 4.0.3           | C++17 / C++20 / C++23 |
| RHEL        | x86\_64  | 9.6            | GCC 14.2.0    | 3.30.6          | C++17           |
| Debian      | x86\_64  | 11             | GCC 10.2.1    | 3.27.4 / 3.30.0 | C++17           |
| Debian      | x86\_64  | 12             | GCC 12.2.0    | 3.27.4 / 4.0.3  | C++17 / C++20   |
| Debian      | x86\_64  | 13             | GCC 14.2.0    | 3.31.6 / 4.0.3  | C++17 / C++20 / C++23 |
| Debian      | x86\_64  | 14             | GCC 15.2.0    | 3.31.6 / 4.0.3  | C++17 / C++20 / C++23 |
| Ubuntu      | x86\_64  | 24.04          | GCC 13.3.0    | 3.28.3 / 4.0.3  | C++17 / C++20 / C++23 |
| Ubuntu      | x86\_64  | 25.04          | GCC 14.2.0    | 3.31.6          | C++17 / C++20   |
| Ubuntu      | x86\_64  | 26.04          | GCC 15.2.0    | 3.31.6 / 4.0.3  | C++17 / C++20 / C++23 |
| MacOS       | arm64    | 15.3           | AppleClang 15 |  4.0.3          | C++17           |

## More Information

* [Static analyzer using Clang-tidy](https://github.com/R3BRootGroup/R3BRoot/blob/dev/config/clang_tidy/README.md)
* [CMake build system for R3BRoot/asyeos](https://github.com/R3BRootGroup/R3BRoot/blob/dev/doc/cmake_usage.md)
* [How to use an unmerged pull request](https://github.com/R3BRootGroup/R3BRoot/blob/dev/doc/git_usage.md#fetch-the-update-from-an-unmerged-pull-request-pr)
