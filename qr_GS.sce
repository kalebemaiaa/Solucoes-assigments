function [Q,R] = qr_GS(A)
     [m,n] = size(A)
     Q = zeros(m,n)
     R = zeros(n,n)
     for j = 1:n
         v = A(:,j)
         for i = 1:j-1
             R(i,j) = Q(:,i)' * A(:,j)
             r_ij = R(i,j)
             v = v - (r_ij * Q(:,i))
         end
         R(j,j) = norm(v)
         r = R(j,j)    
         Q(:,j) = v / r
     end
     
endfunction

function [Q,R] = qr_GS2(A)
     [m,n] = size(A)
     Q = zeros(m,n)
     R = zeros(n,n)
     for j = 1:n
         v = A(:,j)
         for i = 1:j-1
             R(i,j) = Q(:,i)' * v
             r_ij = R(i,j)
             v = v - (r_ij * Q(:,i))
         end
         R(j,j) = norm(v)
         r = R(j,j)    
         Q(:,j) = v / r
     end
     
endfunction
