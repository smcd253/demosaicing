# EE569 Homework Assignment 1

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