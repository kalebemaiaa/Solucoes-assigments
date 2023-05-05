function [M] = matriz_simetrica(n)
    M = zeros((n,n))
    i = 1
    while i <= n
        linha = rand((1,n + 1 - i))
        M(i,i:n) = linha
        i = i + 1
    end
    M = int(100 * (M + M'))
endfunction

function [lambda,x1,k,n_erro] = Metodo_potencia_v1(A,x0,epsilon,M) 
k = 0
[nmax_abs, coord] = max(abs(x0))
x0 = x0 / x0(coord)
x1 = A * x0 
n_erro = epsilon  + 1
while k <= M & n_erro >= epsilon
    [nmax_abs, coord] = max(abs(x0))
    lambda = x1(coord)
    x1 = x1 / lambda
    n_erro = norm(x1 - x0, %inf)
    x0 = x1
    x1 = A * x0
    k = k + 1
end

endfunction

function [lambda,x1,k,n_erro] = Metodo_potencia_v2(A,x0,epsilon,M) 
k = 0
x0 = x0 / norm(x0)
x1 = A * x0 
n_erro = epsilon  + 1
while k <= M & n_erro >= epsilon
    lambda = x1' * x0
    if lambda < 0
        x1 = -x1
    end
    x1 = x1 / norm(x1)
    n_erro = norm(x1 - x0)
    x0 = x1 
    x1 = A * x0
    k = k + 1
end

endfunction

function [lambda1,x1,k,n_erro] = Potencia_deslocada_inversa (A,x0,epsilon,alfa,M)
k=0
n = size(A)(1)
x0 = x0 / norm(x0)
n_erro = epsilon + 1
matriz_ca = A - alfa * eye((n,n))
while k<=M & n_erro >= epsilon
    disp(matriz_ca)
    x1 = matriz_ca \ x0
    x1 = x1 / norm(x1)
    lambda1 = x1' * A * x1
    if x1' * x0 < 0
        x1 = -x1
    end
    n_erro = norm(x1 - x0)  
    x0 = x1
    k = k + 1
end
endfunction
