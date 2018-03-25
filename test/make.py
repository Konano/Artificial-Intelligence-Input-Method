# -*- coding: utf-8 -*-

from pypinyin import pinyin, lazy_pinyin, Style
import jieba

def foobar(char):
    return 'fuck'

A = open('answer.txt', 'r', encoding='gbk')
I = open('input.txt', 'w')

while True:
	line = A.readline()
	if not line:
		break
	I.write(' '.join(lazy_pinyin(jieba.cut(line, cut_all=False), errors=foobar))+'\n')

A.close()
I.close()
