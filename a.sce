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
/*
function [lambda,x1,k,n_erro] = Metodo_potencia_v1(A,x0,epsilon,M) 
k = 0
x0 = x0 / 1//coordenada de maior módulo de x0
x1 = A * x0 
n_erro = epsilon  + 1
while k <= M or n_erro >= epsilon
    lambda = 1//coordernada de maior módulo de x1
    x1 = x1 / lambda
    n_erro = norm(x1 - x0, %inf)
    x0 = x1
    x1 = A * x0
    k = k + 1
end

end

function [lambda,x1,k,n_erro] = Metodo_potencia_v2(A,x0,epsilon,M) 
k = 0
x0 = x0 / norm(x0, 2)
x1 = A * x0 
n_erro = epsilon  + 1
while k <= M and n_erro >= epsilon
    lambda = x1 * x0
    if lambda < 0
        x1 = -x1
        end
    x1 = x1 / norm(x1, 2)
    n_erro = norm(x1 - x0, 2)
    x0 = x1 
    x1 = A * x0
    k = k + 1
end

end

function [lambda1,x1,k,n_erro] = Potencia_deslocada_inversa (A,x0,epsilon,alfa,M)
k=0
x0 = x0 / norm(x0, 2)
n_erro = epsilon + 1
while k<=M and n_erro >= epsilon

    (A – alfa*I)*x1 = x0
    x1 = x1 /(norma_2 de x1)
    lambda = x1T
    *A*x1 (Quociente de Rayleigh; x1 é unitário)
    Se x1T
        *x0 < 0 então x1 = − x1 (Mantém x1 com mesmo sentido de x0)
    n_erro = norma_2 de x1 – x0
    x0 = x1
    k=k+1
end
lambda1 = ...
end
*/
