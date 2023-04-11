function [x, norm_dif, iteracao, norm_residuo] = metodo_gauss_inv(A,b,x0,E,M, type_norma)
    U = triu(A,1)
    L = tril(A,-1)
    D = A - U - L  
    
    inv_LD = inv (L+D)
    matriz_metodo = -inv_LD * U
    c_metodo = inv_LD * b
    
    iteracao = 1
    while (iteracao <= M)
        x = matriz_metodo * x0 +  c_metodo
        
        norm_dif = norm(x - x0, type_norma)
        
        //criterio de parada = norm dif baixa
        if (norm_dif < E)
            break;
        end
       
        x0 = x
        iteracao = iteracao + 1;
    end
    
    //calcular norma residuo
    norm_residuo = norm(b - A * x, type_norma)
endfunction
