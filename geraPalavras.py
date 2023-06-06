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
        
        
def geraArquivo():
    palavras100 = palavraAleatoria(100)
    palavras1000 = palavraAleatoria(1000)
    palavras10000 = palavraAleatoria(10000)
    with open("palavras_100.txt", "w") as f:
        f.write("100\n")
        for x in palavras100:
            f.write(x)
            f.write("\n")
            
    with open("palavras_1000.txt", "w") as f:
         f.write("100\n")
         for x in palavras1000:
             f.write(x)
             f.write("\n")
     
    with open("palavras_10000.txt", "w") as f:
         f.write("100\n")
         for x in palavras10000:
             f.write(x)
             f.write("\n")
            

geraArquivo()            