This is solution to hacker rank problem https://www.hackerrank.com/challenges/journey-to-the-moon/problem.
Using Depth First Search find the connected components (=countries) and number of nodes (=astronauts
representing country).

One of the interesting test case (Test Case #11) that failed for me:

Input:

    100000 2
    
    1 2
    
    3 4

Expected output:

    4999949998
    
The fix was using uint64_t data type.
