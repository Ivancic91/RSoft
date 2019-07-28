# RSoft 1.0

The following document is an introduction to the RSoft project. This 
project is meant to be a sharable softness code with slight 
modifications to structure functions listed in Cubuk et. al. PRL 2018.

Original code was written by Robert Ivancic. Please feel free to email
ivancic91 [at] gmail [dot] com. Publications with this code are
forthcoming.

## Mathematical introduction

<a href="https://www.codecogs.com/eqnedit.php?latex=\mathcal{W}(A,f)&space;=&space;(T,\bar{f})" target="_blank"><img src="https://latex.codecogs.com/gif.latex?\mathcal{W}(A,f)&space;=&space;(T,\bar{f})" title="\mathcal{W}(A,f) = (T,\bar{f})" /></a>

## Installation

Here, we assume that installed you have (a) python 3 (b) anaconda, and
(c) git on your system.

**(Step 0)** Go to your home directory and clone this repository. This
can be done through the commands:

```bash
cd ~
git clone https://github.com/Ivancic91/RSoft
``` 

**(Step 1)** Create a conda environment. This will ensure that you can use
the packages you need without interfering with existing packages. You
may do this from the yml environment in the RSoft directory.

```bash
cd ~/RSoft
conda env create -f RSoft.yml
```

Make sure installation completed correctly by reading the conda output. 
To activate/deactive the RSoft environment, use the commands:

```bash
conda activate RSoft
conda deactivate
```

**(Step 2)** Link c++ libraries. We should be able to do this by running:

```bash
cd ~/RSoft
python link_cpp.py
```

Congratulations! You have installed RSoft.

## How to compile and use RSoft C++ codes

## How to use RSoft python codes


