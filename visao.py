# -*- coding: utf-8 -*-

from __future__ import print_function

from nltk import FeatStruct as fs
import re
import json
import conllu
from io import open
from conllu import parse_incr
import sys
import os
from collections import defaultdict


def eprint(*args, **kwargs):
    print(*args, file=sys.stderr, **kwargs)

with open('morphobr_to_bosque.json', encoding="utf8") as f:
    morphobr_to_bosque = json.load(f)


def check(token_fst,entries):
    """Return the list of conflicting attribute-value pairs between a
    treebank feature structure for a token and a list of dictionary
    entries for this token. If the structures unify with at least one
    entry, return the empty list. Otherwise return the inconsistencies
    collected by means of the function find_error.

    """
    errors=[]
    for entry in entries:
        if entry.unify(token_fst):
            return []
        else:
            errors.append(entry)
    return [find_error(error,token_fst) for error in errors]


def token_to_fst(token,lemma,cat,feats):
    d =[('Form',token),('Lemma',lemma),('Cat',cat)]
    if type(feats) is dict:
        for feat in feats.keys():
            d.append((feat,feats[feat]))
    return fs(dict(d))

def entry_to_fst(entry="simples simples+A+F+PL"):
    ls = re.split(r"[ \+\t]", entry)
    #ls é uma lista das propriedades (['A','F','PL'], por exempo)
    d = [('Form', ls[0]),('Lemma', ls[1])]
    for l in ls[2:]:
        # l se refere a cada propriedade
        ms = morphobr_to_bosque.get(l.strip())
        for m in ms:
            f = re.split(r"[\=]",m)
            d.append((f[0],f[1]))
    
    #devolve uma lista da propriedade e do valor que ela tem
    return (ls[0], fs(dict(d)))


def find_error(fs1,fs2):
    attributes=set(fs1.keys()).union(fs2.keys())
    errors=[]
    for k in attributes:
        v1=fs1.get(k)
        v2=fs2.get(k)
        if v1 and v2 and v1 != v2:
            errors.append([k,v1,v2])
    return errors


def extract_entries(d, infile):
    #infile é o caminho do arquivo (C:\Users\b47133\Downloads\MorphoBr-master\nouns, por exemplo)
    with open(infile, encoding="utf8") as f:
        for line in f.readlines():
            # cada linha possui a forma PALAVRA     PALAVRA+forma+caracteristicas
            form, fs = entry_to_fst(line)
            # dicionario[palavra] = atributos
            d[form].append(fs)


def readMorpho(path):
    adict = defaultdict(list)
    dirs = ["nouns","adjectives","adverbs","verbs"]
    
    # acessa cada diretorio do morpho br
    for d in dirs:
        eprint("Loading %s." % d)
        # acessa cada subpasta
        for root, _ , files in os.walk(os.path.join(path,d), topdown=False):
            for file in files:
                # para cada arquivo executa a função abaixo
                # o parametro adict funciona para add algo
                extract_entries(adict, os.path.join(root,file))
    return adict


def errors2string(errors):
    return " | ".join([ " § ".join([ "%s:%s≠%s" %(e[0],e[1],e[2]) for e in ue]) for ue in errors])


def proc1(morpho, content):
    with open(r"C:\Users\b47133\Documents\t.txt", "w", encoding="utf8") as f:
        for sent in conllu.parse_incr(content):
            msg = "\n%s: %s " % (sent.metadata.get('sent_id'), sent.metadata.get('text'))
            flag = False
            for token in sent:
                if token["upos"] in ["ADJ","ADV","NOUN","VERB"]:
                    tfs = token_to_fst((token["form"]).lower(),token["lemma"],token["upos"],token["feats"])
                    candidates = morpho.get((token["form"]).lower())
                    if candidates:
                        errors = check(tfs, candidates)
                        if len(errors)>0:
                            msg = msg + " ['%s' %s] " %(token,errors2string(errors))
                            flag = True
                    else:
                        msg = msg + " ['%s' NF] " % token
                        flag = True
            if flag:
                print(msg)
                f.write(f"{msg}\n")
                    

def execute():
    morpho = readMorpho(sys.argv[1])
    for path in sys.argv[2:]:
        with open(path, encoding="utf8") as content:
            proc1(morpho, content)

def usage():
    print("\nUsage:\n\tpython check.py path-morphobr conllu1 conllu2 ... \n\n")

if __name__ == "__main__":
    if len(sys.argv) < 3:
        usage()
    else:
        execute()

