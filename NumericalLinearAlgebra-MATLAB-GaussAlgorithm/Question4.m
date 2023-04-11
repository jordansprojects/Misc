% Script for Question 4

% Use SolveLES  to solve LES 
%               V * x  = b

%for n = 5, 10, 15, 20, 25

n_values = [5,10,15,20,25];

for i =1 :5
    n = n_values(i);
    V = vander(1:n);
    b = randn(n,1);
    [x, ok] = SolveLES(V,b);
    fprintf("n = %d \n", n)
    fprintf("||V * x  -b||  = %d \n", norm((V*x) -b ))
end