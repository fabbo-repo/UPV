# Ejecución de test

### 2 formas de hacer test

##### 	1.  Comandos 

​	 -BL, --blevensh       basic levenshtein distance.
​	 -RL, --rlevensh       restricted levenshtein distance.
​	 -IL, --ilevensh       intermediate levenshtein distance.
​	 -Th threshold, --threshold threshold

```shell
python searcher.py index/2015_index.bin -T .\test\test_alt.txt -BL -Th 2
```

##### 	2.  test_alt.py

```shell
 python .\test\test_alt.py            
```
