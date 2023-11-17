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

with open('morphobr_to_bosque.json',  encoding="utf8") as f:
    morphobr_to_bosque = json.load(f)


def check(token_fst, entries):
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
    d = [('Form', ls[0]),('Lemma', ls[1])]
    for l in ls[2:]:
        ms = morphobr_to_bosque.get(l.strip())
        for m in ms:
            f = re.split(r"[\=]",m)
            d.append((f[0],f[1]))
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
    with open(infile,  encoding="utf8") as f:
        for line in f.readlines():
            form, fs = entry_to_fst(line)
            d[form].append(fs)


def readMorpho(path):
    adict = defaultdict(list)
    dirs = ["nouns","adjectives","adverbs","verbs"]
    for d in dirs:
        eprint("Loading %s." % d)
        for root, _ , files in os.walk(os.path.join(path,d), topdown=False):
            for file in files:
                extract_entries(adict, os.path.join(root,file))
    return adict


def errors2string(errors):
    return " | ".join([ " § ".join([ "%s:%s≠%s" %(e[0],e[1],e[2]) for e in ue]) for ue in errors])


def proc1(morpho, content):
    data_errors = {}

    for sent in conllu.parse_incr(content):
        msg = "\n%s: %s " % (sent.metadata.get('sent_id'), sent.metadata.get('text'))
        flag = False
        key = None
        for token in sent:
            if token["upos"] in ["ADJ","ADV","NOUN","VERB"]:
                ################################################
                ## Podemos fazer de duas formas:
                token_form = token["form"]
                if token["misc"] and "CorrectForm" in token["misc"]:
                    token_form = token["misc"]["CorrectForm"]
                tfs = token_to_fst((token_form).lower(),token["lemma"],token["upos"],token["feats"])
                
                ################################################
                # OU ASSIM:
                #nao sei se todo typo = Yes significa que haverá uma forma correta
                # if isinstance(token["feats"], dict):
                #     if "Typo" in token["feats"] and token["feats"]["Typo"] == "Yes":
                #         token_form = token["misc"]["CorrectForm"]
                
                candidates = morpho.get(token_form.lower()) 
                if   token_form.lower() == "filha":
                    print("entries -> ", candidates)
                    print("token fst -> ", tfs)
                    
                if candidates:
                    errors = check(tfs, candidates)
                    if len(errors)>0:
                        errors_string = errors2string(errors)
                        # Key para o dicionario 'data_errors'
                        key = f"DI-{token}"
                        msg = msg + " ['%s' %s] " %(token, errors_string)
                        flag = True
                else:
                    # Key para o dicionario 'data_errors'
                    key = f"NF-{token}"
                    
                    msg = msg + " ['%s' NF] " % token
                    flag = True
        
        if flag:
            print(msg)
            # Para um mesmo erro, adiciona todas ocorrências
            if not key in data_errors:
                data_errors[key] = [f"{msg}"]
            else:
                data_errors[key].append(f"{msg}")
                
    return data_errors
                    

def execute():
    # morpho = {}
    morpho = readMorpho(sys.argv[1])
    errors = {}
    

    for path in sys.argv[2:]:
        with open(path,  encoding="utf8") as content:
            erro_file = proc1(morpho, content)
            
            # Aqui para baixo concatena os erros em um dicionario maior para 
            # imprimir no final, após achar todos erros de um mesmo tipo em um arquivo
            # (talvez seja bom especificar o arquivo)
            for key, value in erro_file.items():
                if key in errors:
                    errors[key] = errors[key]  + value
                else:
                    errors[key] = value
    
    with open("./data.txt", "w", encoding = "utf8") as f:
        # Ordena o dict em ordem de maior ocorrencia do erro
        errors = dict(sorted(errors.items(), key=lambda x:len(x[1]), reverse=True))
        for e in errors:
            # Escreve arquivo no diretorio corrente.
            f.write(f"{e} {len(errors[e])}\n")
            for txt in errors[e]:
                f.write(f"\t{txt}\n")
            f.write("\n\n")
        
            

def usage():
    print("\nUsage:\n\tpython check.py path-morphobr conllu1 conllu2 ... \n\n")

if __name__ == "__main__":
    if len(sys.argv) < 3:
        usage()
    else:
        execute()

