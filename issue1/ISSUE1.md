Issue 1
=======

###Background:
        There are two integer arrays both of which size is N(N can be any positive integer).
    In these two integer arrays,there are full of random integers.
    Elements in different arrays can be exchanged each other.


###Expectation:
        After sevral exchanges between the elements of the two arrays.
    Finally,the difference of  summation of elements between the two arrays should be smallest. 


Issue Analyse
-------------
        This issue can be transformed into another issue like this:Devide 2N integers into two
    groups,each group contains N integers.Assume that,the summation of the 2N integers is SUM.
    We intend to find a way to devide these integers,which can make the summation of one of the
    two groups  closest to SUM/2.
    
        The number of the ways to devide the integers can be calculated in this way:
    How many ways there are to pick up N integers from 2N integers?Using the combination method
    in math,we can easily get the result:(2N)!/(N)!.At worst,we can traverse all the available ways
    to figure out the best one.However,the number of the available may be huge!Assuming that,N 
    values 10.Then (20)!/(10)! is approximately equal to 6.7e^11;If N values 100,the number of ways
    is more than 3e^93.A huge number,isn't it?The way simply traverse all the ways and figure out the
    best one seems extremely inefficient.So,we have to try other solutions.

Solutions:
-------------

###Solution 1:Genetic Algorithm





