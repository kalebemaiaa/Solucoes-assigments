function [x, norm_dif, iteracao, norm_residuo] = metodo_jacobi(A,b,x0,E,M, type_norma)
    U = -triu(A,1)
    L = -tril(A,-1)
    D = A - U - L
    n = size(A)(1)    
    identidade = eye(A)
    
    //invertendo D
    for i = 1:n
        D(i,:) = identidade(i,:)/D(i,i)
    end
    
    matriz_metodo = D * (L + U)
    c_metodo = D * b
    
    x = zeros(n,1)
 
    iteracao = 1;
    //criterio de parada = exceder numero maximo
    while (iteracao <= M)
        x = matriz_metodo * x0 + c_metodo
        
        norm_dif = norm(x - x0, type_norma)
        if(norm_dif < E) then
            break
        end
        
        x0 = x
        iteracao = iteracao + 1
    end
    
    //calcular norma residuo
    norm_residuo = norm(b - A * x, type_norma)
   
endfunction
