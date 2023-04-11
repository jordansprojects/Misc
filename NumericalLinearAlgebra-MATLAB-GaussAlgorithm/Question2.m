% Script for Question 2 

% Use SolveLES to solve LES in the form
%   A * x = b


% for  n = 50, 100, 150, 200 and 250.
n_values = [ 50, 100, 150, 200, 250];

for i=1:5
        n = n_values(i);
        % generate a random positive definite nxn matrix
        A = randn(n);
        A = A+A';
        A = A + 2*norm(A,inf)*eye(n);
           % generate b
        b = randn(n,1) ;
        % Try to solve Ax = b using SolveLES
        [x, ok] = SolveLES(A,b);
        fprintf("n = %d \n", n)
        fprintf("||A * x  -b||  = %d \n", norm((A*x) -b ))
end