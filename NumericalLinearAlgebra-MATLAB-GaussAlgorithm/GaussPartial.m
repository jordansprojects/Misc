
function [A,p,ok] = GaussPartial(A)

%
% Given them n*n matrix A the function calculates L and U such that PA=LU (in place in
% the matrix A).
% If it is not possible to calculate PA=LU then ok = 0, otherwise ok = 1.
% p determines a permutation matrix P which has a 1 at position p(i) in row
% i.
%


[n,m] = size(A);
ok    = (n == m);                % only work on quadratic systems
k     = 1;
p     = 1:n;
help  = zeros(1,n);              % to switch rows
while ((k<=n-1) & (ok==1))
    [M,I] = max(abs(A(k:n,k)));
    I     = k+I-1;
    if (M>0) % not the greatest criterium
       %
       % switch the row I and row k if needed
       %
       if (I~=k) 
           help     = A(k,1:n);
           A(k,1:n) = A(I,1:n);
           A(I,1:n) = help;  
           I1       = p(k);
           p(k)     = p(I);
           p(I)     = I1;
       end
       %
       % Elimination
       % 
       for j=k+1:n           
           A(j,k) = A(j,k)/A(k,k);
           for i=k+1:n
               A(j,i) = A(j,i)-A(j,k)*A(k,i);
           end
       end
       k = k + 1;
    else
       ok = 0;
    end
end
end


