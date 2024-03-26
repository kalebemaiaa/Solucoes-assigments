import random as rand

vogais = ["A", "U", "Y"]
consoantes = ["B", "J", "R", "S", "T"]

def palavraAleatoria(n):
    r = []
    for k in range(n):
        cOrV = rand.randint(1,2)
        tamanhoPalavra = rand.randint(2,8)
        if(cOrV == 1):
            r.append("".join([rand.choice(consoantes) if i % 2 == 0 else rand.choice(vogais) for i in range(tamanhoPalavra) ]))
        else:
            r.append("".join([rand.choice(vogais) if i % 2 == 0 else rand.choice(consoantes) for i in range(tamanhoPalavra) ]))
        
    return r
        
        
def geraArquivo(n):
    if(n <= 0): return
    palavras = palavraAleatoria(n)
    
    with open("wr_{}.txt".format(n), 'w') as f:
        f.write("{}\n".format(n))
        for x in palavras:
            f.write("{}\n".format(x))
            
geraArquivo(int(input("Digite um inteiro maior que 0: ")))            