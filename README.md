# RSoft 1.0

The following document is an introduction to the RSoft project. This 
project is meant to be a sharable softness code with slight 
modifications to structure functions listed in Cubuk et. al. PRL 2018.

Original code was written by Robert Ivancic. Please feel free to email
ivancic91 [at] gmail [dot] com. Publications with this code are
forthcoming.

## Installation

Here, we assume that you have (a) python 3 and (b) Anaconda installed
on your system.

(Step 0) Go to your home directory and 

(Step 1) Create a conda environment. This will ensure that you can use
the packages you need without interfering with existing packages. You
may do this from the yml environment in the RSoft directory.

```bash
conda env create -f RSoft.yml
```

Make sure installation completed correctly by reading the conda output. 
To activate/deactive the RSoft environment, use the commands:

```bash
conda activate RSoft
conda deactivate
```

(Step 2) Link c++ libraries. We should be able to do this by running:

```bash
python link_cpp.py
```

Congratulations! You have installed RSoft.

## How to compile and use RSoft C++ codes

## How to use RSoft python codes


