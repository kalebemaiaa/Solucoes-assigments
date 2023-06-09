function [U,R] = qr_House(A)
    [m,n] = size(A)
    U = zeros(m,m)
    
    for i = 1:n
        x = A(i:m,i)
        if x(1) > 0
            x(1) = x(1) - norm(x)
        else x(1) = x(1) + norm(x)   
        end
        u = x / norm(x)
        U(i:m, i) = u
        A(i:m, i:n) = A(i:m, i:n) - (2 * u * (u' * A(i:m, i:n)))
    end
    R = triu(A)
endfunction

function [U,R] = qr_House2(A)
    [m,n] = size(A)
    k = min(m-1, n)
    U = zeros(m,k)
    
    for i = 1:k
        x = A(i:m,i)
        if x(1) > 0
            x(1) = x(1) - norm(x)
        else x(1) = x(1) + norm(x)   
        end
        u = x / norm(x)
        U(i:m, i) = u
        A(i:m, i:n) = A(i:m, i:n) - (2 * u * (u' * A(i:m, i:n)))
    end
    R = triu(A)
endfunction

function [Q] = constroi_Q_House(U)
    [m,n] = size(A)
    Q = eye(m,m)
    for i = 1:m
        u = U(:, i)
        Q = Q - (2 * Q * (u * u')) 
    end
endfunction

function [Q] = constroi_Q_House2(U)
    [m,n] = size(A)
    k = min(m - 1, n)
    Q = eye(m,m)
    for i = 1:k
        u = U(:, i)
        Q = Q - (2 * Q * (u * u')) 
    end
endfunction
