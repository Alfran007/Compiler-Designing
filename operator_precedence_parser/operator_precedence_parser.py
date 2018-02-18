"""
Name : Syed Alfran Ali
ID : 2015KUCP1032

This program is built using python 3.6

The NULL is represented by ~

Each production in the input must be provided on separate line.
"""

import csv
import sys


def main():
    inputString = 'i+i*i'
    inputList = list(inputString)
    inputList.append('$')

    root = {}
    nonTerminals = []
    grammar = open('input.txt', 'r')

    for row in grammar:
        row = row.strip()
        row = row.split("->")
        root[row[1]] = row[0]
        if row[0] not in nonTerminals:
            nonTerminals.append(row[0])

    preference_table = []
    #Storing the table from order file
    with open('table.csv', 'rU') as file2:
        preference = csv.reader(file2)
        for row in preference:
            preference_table.append(row)

    operators = preference_table[0]

    # Processing the input string
    stack = list()
    stack.append('$')

    flag1 = 1
    while flag1:

        inputStorage = inputList[0]
        t1 = operators.index(str(inputStorage))
        if stack[-1] in nonTerminals:
            buffer_stack = stack[-2]
        else:
            buffer_stack = stack[-1]
        t2 = operators.index(str(buffer_stack))

        precedence = preference_table[t2][t1]

        if precedence == '<':
            toDo = 'shift'
        elif precedence == '>':
            toDo = 'reduce'

        if toDo == 'shift':
            stack.append(inputStorage)
            inputList.remove(inputStorage)
        elif toDo == 'reduce':
            a = ''.join(stack[-1:])
            b = ''.join(stack[-3:])
            flag2 = 0
            for key, value in root.items():
                if str(key) == str(buffer_stack):
                    stack[-1] = value
                    flag2 = 1
                    break
                elif key == b:
                    stack[-3:] = value
                    flag2 = 1

            if inputList[0] == '$' and len(stack) == 2:
                flag1 = 0
                flag2 = 1

            if flag2 is 0:
                print("Invalid String")
                break

        if flag1 == 0:
            print("The String is Accepted by the Grammar!!")


if __name__ == "__main__":
    main()
