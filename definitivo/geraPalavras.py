import random as rand

vogais = ["A", "U", "Y"]
consoantes = ["B", "J", "R", "S", "T"]

def palavraAleatoria(n):
    r = []
    for k in range(n):
        cOrV = rand.randint(1,2)
        tamanhoPalavra = rand.randint(2,8)
        palavra = []
        for i in range(tamanhoPalavra):
            if cOrV == 1:
                if i % 2 == 0:
                    palavra.append(rand.choice(vogais))
                else:
                    palavra.append(rand.choice(consoantes))
            else:
                if i % 2 == 0:
                    palavra.append(rand.choice(consoantes))
                else:
                    palavra.append(rand.choice(vogais))
        
        r.append("".join(palavra))
    
    return r
        
        
def geraArquivo(n):
    palavras = palavraAleatoria(n)
    
    with open("wr_{}.txt".format(n), 'w') as f:
        f.write("{}\n".format(n))
        for x in palavras:
            f.write("{}\n".format(x))
            

geraArquivo(int(input("Digite um inteiro: ")))            