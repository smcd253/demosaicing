# EE569 Homework Assignment 1
# Spencer McDonough
# 6341617166
# shmcdono@usc.edu

# Instructions for TA (Finished Problems and How to Compile/Run them)
1. a) g++ blerpDemosaic.cpp -o blerpDemosaic
1. a) ./blerpDemosaic HW1_images/cat.raw HW1_images/cat_blerpDemosaic.raw 1 390 300 3
1. b) g++ mhcDemosaic.cpp -o mhcDemosaic
1. b) ./mhcDemosaic HW1_images/cat.raw HW1_images/cat_mhcDemosaic.raw 1 390 300 3

2. a) g++ uniformDenoise.cpp -o uniformDenoise
2. a) ./uniformDenoise HW1_images/pepper_uni.raw HW1_images/pepper_denoiseUniform.raw 1 256 256 1 <3,5,7>

2. a.1) g++ gaussianDenoise.cpp -o gaussianDenoise
2. a.2) ./gaussianDenoise HW1_images/pepper_uni.raw HW1_images/pepper_denoiseGaussian.raw 1 256 256 1 <3,5,7>


SOURCES:
Gaussian Filter: https://homepages.inf.ed.ac.uk/rbf/HIPR2/gsmooth.htm
Passing 3D Array by Ref: https://www.geeksforgeeks.org/pass-2d-array-parameter-c/


# problem 2.1: subtract clean image from noisy image to find noise distribution

# problem 2.2: see p 269 of textbook

NOTE: See original online pdf to view equations in 1.b

Questions for TA:
1.a and 2.2, why does my code not crash without taking into account edge cases?
Should I take care of them anyway?
1.c 
- How do I select the size of each bin for the histogram? 256 discrete bins?
- which formula should I be using?
# buckets for p2 is H*W/256
2.2 Am I using the correct gaussian filter equation?
- Are n1 and n2 just nh - i and nw - j?
ANS: use only exponential term for each location
- add these up and divide each exponential term by sum of all exp terms to get weight for each location
2.3 What are the spread parameters? ans: default variance, play around
2.4 What is h (filter paramter)? ans: default variance, play around

TODO:
1. Finish implementation of Gaussian Filter
2. Separate blerp into smaller functions
3. Edge cases for blerp
4. Edge cases for uniform filter
5. Separate Gaussian filter into smaller functions
6. Edge cases for Gaussian filter
7. Implement MHC on top of blerp
8. Histogram Manipulation p 272

Questions for TA 01/22:
1. Bilateral Filter: can you explain ||I(i,j) - I(k,l)||^2?
2. 
TODO 01/22:
1. Implement MHC on top of blerp
2. Histogram Manipulation
3. Finish




