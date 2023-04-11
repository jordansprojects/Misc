% Script for Question 3

% Use SolveLES  to solve LES 
%               H * x  = b

%for n = 5, 10, 15, 20, 25

n_values = [5,10,15,20,25];

for i =1 :5
    n = n_values(i);
    H = hilb(n);
    b = randn(n,1);
    [x, ok] = SolveLES(H,b);
    fprintf("n = %d \n", n)
    fprintf("||H * x  -b||  = %d \n", norm((H*x) -b ))
end