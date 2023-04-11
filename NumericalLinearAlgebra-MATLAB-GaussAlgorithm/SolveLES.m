function [x, ok]  = SolveLES(A,b)

% Tries to solve nxn linear equation systems Ax = b. 
% Use the function Gauss Partial to calculate the LU decomposition of P*A

[n,~] = size(A); % If it has an LU decomposition it is an nxn matrix 

% preallocate 1xn vectors x and y 
x  = zeros(n,1);         
y = zeros(n,1);           
[LU, p, ok] = GaussPartial(A);


% Create Permutation Matrix 
P = zeros(n,n);
for i = 1: n
    location = p(i);
    P(i,location) = 1;
end

L = tril(LU); % retrieve lower triangular matrix from LU
U = triu(LU); % retrieve upper triangular matrix from LU

% replace diagonal with ones
% MATLAB has functions for this but this is real nice and easy to do 
for i = 1:n
   L(i,i) = 1;
end


pb = P*b;
% First perform forward substitution for L*y = P *b
for i = 1:n
    y(i) = pb(i); 
    for j = 1:i-1
        y(i) = y(i) - L(i,j) *y(j); % subtract all known LHS values from RHS value
    end
    y(i) = y(i)/L(i,i); % finally divide RHS by LHS value for the current variable
end

% Then perform backward substitution for Ux = y

for i = n:-1:1 % start at bottom
    x(i) = y(i) / U(i, i); % solve for unknown value
    for j = i-1:-1:1 
        y(j) = y(j) - U(j, i) * x(i); % substitute into each equation above
    end
end



