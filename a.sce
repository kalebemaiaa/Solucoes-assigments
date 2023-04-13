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

function [x] = resolve_tril(A,b)
    n = size(A)(1)
    x = zeros(n,1)
    x(1,1) = b(1,1)/A(1,1)
    for i = 2:n
        x(i,1) = (b(i,1) - A(i,:) * x) / A(i,i)
    end
endfunction


function [x, norm_dif, iteracao, norm_residuo] = metodo_gauss_tril(A,b,x0,E,M, type_norma)
    U = triu(A,1)
    L = tril(A,-1)
    D = A - U - L 
    
    M_metodo = (L+D)
    iteracao = 1
    while (iteracao <= M)
        c = b - U * x0
        x = resolve_tril(M_metodo, c)
        
        norm_dif = norm(x - x0, type_norma)
        
        //criterio de parada = norm dif baixa
        if (norm_dif < E)
            break;
        end
       
        iteracao = iteracao + 1;
        x0 = x
    end
    
    //calcular norma residuo
    norm_residuo = norm(b - A * x, type_norma)
endfunction

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

function [M] = matriz_dominante(n)
    M = rand(n,n)
    for i = 1:n
        M(i,i) = rand() + sum(M(i,:)) + 1
    end
endfunction

function [retorno] = get_time_diff(matriz_numeros) 
    N = matriz_numeros
    kl = size(N)(2)

    retorno = zeros(kl, 4)
    for i = 1:kl
        n = N(i)
        b = rand(n,1)   
        M = matriz_dominante(n)     
        x0 = zeros(n,1)
        tic();
        [x, ndif, ite_inv, nres] = metodo_gauss_inv(M, b, x0, 10^-(8), 100, 2)
        time_inv = toc();
        tic();
        [x, ndif, ite_tril, nres] = metodo_gauss_tril(M, b, x0, 10^-(8), 100, 2)
        time_tril = toc();
        retorno(i, :) = [ite_inv, time_inv, ite_tril, time_tril]
    end
    disp("Iterações inversa|| Tempo inversa|| Iterações tril|| Tempo tril")
endfunction
