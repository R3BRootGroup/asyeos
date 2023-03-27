# AsyEOS Software

## The AsyEOS Framework
AsyEOS folder inside R3BRoot describes the AsyEOS detectors which are going to be employed in the AsyEOS/R3B experiments.

The R3BRoot software is based on the FairRoot framework and can be used to perform Monte Carlo simulations and experimental data analysis of the R3B (Reactions with Relativistic Radioactive Beams) nuclear physics experiments at the GSI-FAIR research center (Facility for Antiproton and Ion Research).

## Discussion Forum
For the software-related user support you can post a new topic on our [forum](https://forum.gsi.de/index.php?t=index&cat=40&) or you could use the GitHub issues.

## Release Information
Please visit [releases](https://github.com/R3BRootGroup/asyeos/releases)

## Contributing
Please ask your questions, request features, and report issues by [creating a github issue](https://github.com/R3BRootGroup/asyeos/issues/new/choose).

## Code Formatting
The AsyEOS project (as part of R3BRoot) uses clang-format-15 to ensure a common code formatting. The script "apply-format.sh" can be used for this purpose: 
~~~bash
source apply-format.sh
~~~

## Step by Step Installation

### Required Software

First, you will need to install FairSoft and FairRoot. For more details:

1. Install [FairSoft](https://github.com/FairRootGroup/FairSoft)

2. Install [FairRoot](http://fairroot.gsi.de)

### Installation of R3BRoot and AsyEOS (as part of R3BRoot)

~~~bash
export SIMPATH=%PATH_TO_FAIRSOFT%
export FAIRROOTPATH=%PATH_TO_FAIRROOT%
git clone -b dev https://github.com/R3BRootGroup/R3BRoot.git
cd R3BRoot
git clone -b dev https://github.com/R3BRootGroup/macros.git
git clone -b dev https://github.com/R3BRootGroup/asyeos.git
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

- 

### asyeos/macros/

This directory contains the macros to simulate the asyeos experiment. 

~~~bash
cd %BUILD_DIRECTORY_FOR_R3BROOT%
. ./config.sh
cd ./asyeos/macros/
root -l 
.L runsim.C
runsim(100)
~~~
where 100 is the number of events.

This will create an output file `sim.root` with the simulation results and a parameter file `par.root` with geometry and magnetic field parameters.

After the simulation :

1. To start an event display:

~~~bash
root -l eventDisplay.C
~~~

2. To perform a quick analysis with GUI :

~~~bash
root -l sim.root
[] evt->StartViewer();
~~~


After the simulation :

1. To start an event display :

~~~bash
root -l eventDisplay.C
~~~

2. To perform a quick analysis with GUI :

~~~bash
root -l sim.root
[] evt->StartViewer();
~~~

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

This directory contains all the macros for online and offline analysis.

#### macros/online

This directory contains the online analysis macro. Execute it as:

~~~bash
root -b main_online.C
~~~
after defining the stream data server and the port number for data visualization.


#### macros/unpack

This directory contains the offline macros for the experiment analysis. There are two macros:

- unpack_offline.C for producing a root file with the mapped/raw data of all the detectors
- cal_offline.C for producing a root file with the cal and hit data levels of all the detectors

After defining the paths to the input files of each macro, one can execute it as follows:

~~~bash
1) If all the parameters are right by default
   root -l unpack_offline.C
2) If one wants to select a RunId, for instance 'RunId = 273'
   root -l 'unpack_offline.C(273)'
3) If one wants to select a RunId and max number of events, for instance 'RunId = 273' and 'nev = 200'
   root -l 'unpack_offline.C(273,200)'
~~~
or

~~~bash
1) If all the parameters are right by default
   root -l cal_offline.C
2) If one wants to select a RunId, for instance 'RunId = 273'
   root -l 'cal_offline.C(273)'
3) If one wants to select a RunId and max number of events, for instance 'RunId = 273' and 'nev = 200'
   root -l 'cal_offline.C(273,200)'
~~~
