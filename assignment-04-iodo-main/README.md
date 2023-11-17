[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-24ddc0f5d75046c5622901739e7c5dd533143b0c8e959d652212380cedb1ea36.svg)](https://classroom.github.com/a/iwqOVhEf)
# Assignment 04

Neste trabalho queremos identificar lacunas no
 [MorphoBr](http://github.com/LR-POR/MorphoBr) e nos corpora UD:

- https://github.com/universaldependencies/UD_Portuguese-GSD
- https://github.com/cpdoc/dhbb-nlp/tree/master/udp

Para isso, o grupo deverá usar como ponto de partida o script
`check.py`.

**importante**: os dados dos corpora acima não devem ser copiados para
este diretório, usem os dados diretamente dos diretórios onde eles
forem clonados e não incorporem neste diretório. Isto evitará cópia
desnecessária dos dados.

O script quando executado irá produzir saídas como abaixo:

    % python check.py ~/work/morpho-br ~/work/ud-portuguese-gsd/pt_gsd-ud-test.conllu
	...
	test-s423: Depois da sua saída de Guimarães para o Porto no inicio da época 2003 / 2004 não voltou mais a ser chamado.  ['inicio' Lemma:iniciar≠inicio § Cat:VERB≠NOUN]
	...
	test-s661: A premiação dos Jogos da Reme e a abertura da Exposição Artística do Grupo Maturidade, formado pelos mestres da música, do artesanato, da poesia e da decoração de Ladário, marcam a largada das festividades no dia 31 de agosto, sexta - feira.  ['música' Lemma:música≠_ | Lemma:músico≠_ | Lemma:músico≠_ § Cat:ADJ≠NOUN]
	...	

	
No primeiro caso, consultando o MorphoBr, identificamos que a palavra
inicio está grafada de forma errada, faltando o acento. No segundo
caso, também embora as entradas do MorphoBr possam ser questionadas
(por que?), o problema está no corpus, o token está com o campo
features incompleto.

	% cd ~/work/morpho-br/nouns
	% rg "^músic[ao]s?\t"
	nouns-m.dict
	37348:música	música+N+F+SG
	37349:músicas	música+N+F+PL
	37358:música	músico+N+F+SG
	37359:músicas	músico+N+F+PL
	37360:músico	músico+N+M+SG
	37361:músicos	músico+N+M+PL
	
O comando [rg](https://github.com/BurntSushi/ripgrep) é o `grep` mais
eficiente!

As correções feitas no corpus podem ser vistas no commit:

https://github.com/UniversalDependencies/UD_Portuguese-GSD/commit/7932e1454c95f4f0128f86f97693a8d3f81c1792

Feitas as correções destes dois casos, o razoável seria rodar
novamente o script procurando novos casos de possíveis erros. Mas nem
todos os casos podem ser simples como acima e podemos ter situações
onde o MorphoBr esteja inconsistente ou a correção do corpus não seja
óbvia. Para isso, abram issues e discutam entre os colegas e com o
professor.

Suas tarefas:

1. melhorar o script para levar em consideração a anotação de Typo e
   CorrectForm.
   
2. Sugerir uma saída mais eficiente do script, talvez agrupando por
   casos!
   
3. Fazer um relatório detalhado dos erros encontrados, modificações
   feitas no script e dificuldades encontradas para correção.

O relatório deverá indicar as modificações sugeridas nos dados
(MorphoBr e corpus analisado) de forma clara e organizada. 

Cada grupo deve tentar identificar não menos que 10 problemas, os mais
distintos possíveis.


# Referências

- http://www.portaldalinguaportuguesa.org/
- https://doi.org/10.17851/1983-3652.11.3.1-25
- http://universaldependencies.org/guidelines


