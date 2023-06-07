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
        
    for p in r:
        print(p)
        
        
def geraArquivo(n):
    palavras = palavraAleatoria(n)
    
    with open(f"palavras_{n}.txt", "w") as f:
        f.write(f"{n}\n")
        for x in palavras:
            f.write(x)
            f.write("\n")
            

geraArquivo(int(input("Digite um inteiro: ")))            