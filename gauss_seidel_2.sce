function [x] = resolve_tril(A,b)
    n = size(A)(1)
    x = zeros(n,1)
    x(1,1) = b(1,1)/A(1,1)
    for i = 2:n
        x(i,1) = (b(i,1) - A(i,:) * x) / A(i,i)
    end
endfunction

function [M] = reordena(A)
    n = size(A)(1)
    for i = 1:n
        if A(i,i) < sum(A(i,:) - A(i,i)
            k = i
            for j = 1: n
                if j = i
                    continue
                end
                if( A(j,i) > k
                    k = j
                end
            end
            r = A(i,i)
            A()
        end    
                
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
