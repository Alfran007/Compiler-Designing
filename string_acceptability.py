"""
Syed Alfran Ali
    2015KUCP1032
Python 3.6.4 is used    
'~' is epsilion
"""
from collections import OrderedDict

grammar_rules = []  
firsts = []

# Dictionary to store all the rules
dictionary_all = OrderedDict()
# Dictionary to store all the firsts
dictionary_first = OrderedDict()
# Dictionary that stores all follows
dictionary_follow = OrderedDict()

def nullChecker(rule):
    flag = True
    for i in range(3,len(rule)):
        if rule[i].isupper():
            if '~' not in dictionary_first[rule[i]]:
                flag = False
                break
        else:
            flag = False
            break
    if flag is True:
        dictionary_first[rule[0]].append("~")

def first_finder(rule):
    for i in range(3,len(rule)-1):
        if "~" in dictionary_first[rule[i]]:
            if rule[i+1].isupper():
                for item in dictionary_first[rule[i+1]]:
                    if item != "~":
                        dictionary_first[rule[0]].append(item)
            elif rule[i+1].islower():
                dictionary_first[rule[0]].extend(rule[i+1])
                break
        else:
            break

def finder(rule,var1):
    for i in range(3,len(rule)-1):
        if "~" in dictionary_first[rule[i]]:
            if rule[i+1].isupper():
                for item in dictionary_first[rule[i+1]]:
                    if item != "~":
                        var1.append(item)
            elif rule[i+1].islower():
                var1.extend(rule[i+1])
                break
        else:
            break

    return var1

def follow_finder(rule,ind,nonTerminal):
    if ind+3 == len(rule)-1:
        dictionary_follow[nonTerminal].extend(dictionary_follow[rule[0]])
    for i in range(ind+3,len(rule)-1):
        if "~" in dictionary_first[rule[i]]:
            if rule[i+1].isupper():
                for item in dictionary_first[rule[i+1]]:
                    if item != "~":
                        dictionary_follow[nonTerminal].append(item)
                if i+1 == len(rule)-1 and "~" in dictionary_first[rule[i+1]]:
                    dictionary_follow[nonTerminal].extend(dictionary_follow[rule[0]])
            elif rule[i+1].islower():
                dictionary_follow[nonTerminal].extend(rule[i+1])
                break
        else:
            break

def add_nonTerminal(firsts, grammar_rules):
    for rule in grammar_rules:
        if rule[0][0] not in firsts:
            firsts.append(rule[0][0])
            dictionary_first[rule[0][0]] = []
            dictionary_follow[rule[0][0]] = []

def findOccurences(s,ch):
    return [i for i, letter in enumerate(s) if letter == ch]

with open("input.txt", "r") as fp:
    for line in fp:
        grammar_rules.append(line.strip().split('\n'))


# To find FIRSTS
number_of_rules = len(grammar_rules)
rule_count = first_count = 0
add_nonTerminal(firsts, grammar_rules)


for i in range(20):
    for rule in grammar_rules:
        if rule[0][3].islower() or rule[0][3] is "~":
            dictionary_first[rule[0][0]].extend(rule[0][3])

    for rule in grammar_rules:
        if rule[0][3].isupper():
            for item in dictionary_first[rule[0][3]]:
                if item != "~":
                    dictionary_first[rule[0][0]].append(item)
            first_finder(rule[0])
            nullChecker(rule[0])


FIRST = {}
for key in  dictionary_first:
    FIRST[key] = list(OrderedDict.fromkeys(dictionary_first[key]))


listForRules = []
for rule in grammar_rules:
    listForRules.append(rule[0])

dictionary_follow[listForRules[0][0]].append("$")

for nonTerminal in firsts:
    for rule in listForRules:
        ret = findOccurences(rule[3:],nonTerminal)
        if len(ret) > 0:
            for ind in ret:
                if 3+ind+1<len(rule):
                    if rule[3+ind+1].islower():
                        dictionary_follow[nonTerminal].extend(rule[3+ind+1])
                    else:
                        for item in dictionary_first[rule[3+ind+1]]:
                            if item != "~":
                                dictionary_follow[nonTerminal].append(item)
                        follow_finder(rule,ind+1,nonTerminal)
                else:
                    dictionary_follow[nonTerminal].extend(dictionary_follow[rule[0]])

FOLLOW = {}
for key in  dictionary_follow:
    FOLLOW[key] = list(OrderedDict.fromkeys(dictionary_follow[key]))

# LL(1) check using predictive parsing table
listTerminal = []
listNonTerminal = []
for rule in listForRules:
    listNonTerminal.append(rule[0])
    for i in range(3,len(rule)):
        if rule[i] not in firsts:
            listTerminal.append(rule[i])

listTerminal = list(set(listTerminal))
listTerminal.append("$")
listNonTerminal = list(set(listNonTerminal))

parseTable = OrderedDict()
for nonTerminal in listNonTerminal:
    for val in listTerminal:
        if val != "~":
            parseTable[(nonTerminal,val)] = []

for rule in listForRules:
    var1 = []
    if rule[3].islower() or rule[3] is "~":
        var1.append(rule[3])

    if rule[3].isupper():
        for item in dictionary_first[rule[3]]:
            if item != "~":
                var1.append(item)
        ret = finder(rule,var1)
        var1.extend(ret)


    for first in var1:
        temp = str(rule)
        if first != "~":
            parseTable[(rule[0],first)].append(temp)
        else:
            for val in FOLLOW[rule[0]]:
                parseTable[(rule[0],val)].append(temp)

TABLE = {}
for key in  parseTable:
    TABLE[key] = list(OrderedDict.fromkeys(parseTable[key]))

# The following code is used to check if string will be accepted by the grammar using predictive parsing table
stack = ["$"]
stack.append(listForRules[0][0])
string = "xbxcx$"
i = 0
while len(stack) != 0:
    ch = string[i]
    top = stack.pop()
    if top in listTerminal:
        if top != ch:
            print("String will not be accepted by this C.F.g.")
            break
        else:
            i+=1
    else:
        p = TABLE[(top,ch)]
        if len(p) == 0:
            print("String will not be accepted by this C.F.G.")
            break
        p = p[0]
        p = p[3:]
        p = list(p)
        p.reverse()
        for item in p:
            if item != "~":
                stack.append(item)

if len(stack) == 0:
    print("String will be accepted by this C.F.G")
