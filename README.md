# RSoft 1.0

The following document is an introduction to the RSoft project. This 
project is meant to be a sharable softness code with slight 
modifications to structure functions listed in Cubuk et. al. PRL 2015.

Original code was written by Robert Ivancic. Please feel free to email
ivancic91 [at] gmail [dot] com. Publications with this code are
forthcoming.

## Structure function definitions

The structure functions currently calculated in this code come in two 
types:

<a href="https://www.codecogs.com/eqnedit.php?latex=G_{\text{R}}(i;&space;\mu,&space;L,&space;X,&space;Y)&space;=&space;\sum_j&space;\text{max}(e^{-(R_{ij}-\mu)^2/L^2}-\epsilon_{\text{R}},&space;0)" target="_blank"><img src="https://latex.codecogs.com/gif.latex?G_{\text{R}}(i;&space;\mu,&space;L,&space;X,&space;Y)&space;=&space;\sum_j&space;\text{max}(e^{-(R_{ij}-\mu)^2/L^2}-\epsilon_{\text{R}},&space;0)" title="G_{\text{R}}(i; \mu, L, X, Y) = \sum_j \text{max}(\text{exp}((R_{ij}-\mu)^2/L^2)-\epsilon_{\text{R}}, 0)" /></a>

<a href="https://www.codecogs.com/eqnedit.php?latex=G_{\text{A}}(i;&space;\xi,&space;\lambda,&space;\zeta,&space;X,&space;Y,&space;Z)&space;=&space;\sum_{j,k}&space;\text{max}(e^{-(R_{ij}^2&plus;R_{jk}^2&plus;R_{ik}^2)/\xi^2}\left(\frac{1&plus;\lambda}{2}\right)^\zeta-\epsilon_{\text{A}},&space;0)" target="_blank"><img src="https://latex.codecogs.com/gif.latex?G_{\text{A}}(i;&space;\xi,&space;\lambda,&space;\zeta,&space;X,&space;Y,&space;Z)&space;=&space;\sum_{j,k}&space;\text{max}(e^{-(R_{ij}^2&plus;R_{jk}^2&plus;R_{ik}^2)/\xi^2}\left(\frac{1&plus;\lambda}{2}\right)^\zeta-\epsilon_{\text{A}},&space;0)" title="G_{\text{A}}(i; \xi, \lambda, \zeta, X, Y, Z) = \sum_{j,k} \text{max}(e^{-(R_{ij}^2+R_{jk}^2+R_{ik}^2)/\xi^2}\left(\frac{1+\lambda}{2}\right)^\zeta-\epsilon_{\text{A}}, 0)" /></a>

where most constants are defined in Cubuk et. al. PRL 2015 and <a href="https://www.codecogs.com/eqnedit.php?latex=\epsilon_i" target="_blank"><img src="https://latex.codecogs.com/gif.latex?e_i" title="\epsilon_i" /></a> are the error tolerances for the radial (R) and angular (A) structure functions. These values should fall between 0 and 1; typically I have choosen 0.01 or 0.05. This formulation is used for two reasons. First, structure functions are smooth allowing for better interpretation of softness as an energy barrier for rearrangement (Schoenholz et. al. Nat. Phys. 2016). Second, it prevents unreasonable choices of parameters by the user.

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


