Issue2
========
###Background:
        There are a positive integer N,and a number character C. C can be any integer from 0 to 9. 
        
###Expectation:
        Figure out the total times character C occurs in integers range from 0 to N.
        
Solutions:
--------
##Solution 1:Traversion(rule.cpp > Job::Traversion())
        The most directly solution:calculate each time C occurs in integers range from 0 to N and then
    add the results together.But using this solution,the speed seems extremly slow.Algorithm complexity
    is O(NlogN).
    
##Solution 2:Find rules in recursion(rule.cpp > Job::RuleRecursion())
        Compared with Solution1,Solution 2 is  more efficient.We can find rules in integer N.Assuming
    that,characters in integer N like this:"abcdef"(a > 0).Define f(X) is total times character C occurs 
    in integers range from 0 to X.Then:
        (1)If C < a,f("abcdef") = a * f(99999) + 100000 + f("bcdef");
        (2)If C = a,f("abcdef") = a * f(99999) + ("bcdef" + 1) + f("bcdef");
        (3)If C > a,f("abcdef") = a * f(99999) + f("bcdef");
    So,the solution can be realized in recursion.The end of the recursion is :
        (4)If X < 10 and X >=C ,f(X) = 1;
        (5)If X < 10 and X < C ,f(X) = 0.
    In addition,it is a particular situation if C = 0.The rule may be a little different form above,it is
    also realized in code:"rule.cpp".
    The alogrithm complexity of solution 2 is O(logN).

###Solution 3:Find rules in circulation(rule.cpp > Job::RuleCirculation())
        Solution 3 is a converse way of Solution2.But circulation seems more efficient than recursion in
    real runtime.The code can show the time used in each solution.
