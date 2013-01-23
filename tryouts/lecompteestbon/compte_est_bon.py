#!/usr/bin/env python
# from: https://gist.github.com/raw/2944220/2f571764310beaeec7b21efd0d65ccc60d75006e/compte_est_bon.py
## Yassine chaouche
## yacinechaouche@yahoo.com
## http://ychaouche.wikispot.org
## Jun 16 2012 - 19:21

import sys

def main():
    numbers = sys.argv[1:-1]
    result  = sys.argv[-1]
    solutions  = []
    iterations = 0
    found      = False
    for possibility in combo(numbers):
        possibility = possibility[1:-1] # removes protecting parentheses
        evaluation  = evaluate(possibility)
        if evaluation !=None and int(evaluation) == int(result):
            print "found one solution after %s tries" % (number_pprint(iterations)),possibility," = ",result
            found = True
            solutions.append(possibility)
        iterations += 1

    if not found:
        string =  "there seems to be no solution to this problem. I've exhausted all %s combinations (for %s numbers)"
        print string % (iterations,len(sys.argv[1:-1]))
        return

    for s in solutions :
        print s, "=", result

    string = "found %s solutions to this problem amongst a total of %s possible combinations (%s numbers)"
    print string % (number_pprint(len(solutions)),number_pprint(iterations),len(sys.argv[1:-1]))

def evaluate(expression):
    if is_number(expression):
        return int(expression)
    left,operation,right = tokenize(expression)
    if left != None and right != None and operation != None and is_operation(operation):
        return do_op(evaluate(remove_parens(left)),operation,evaluate(remove_parens(right)))

def tokenize(s):
    s = remove_spaces(s)
    if s[0] not in ('(',')') :
        # we're reading a number
        # XXX : it can't be an operand otherwise the expression is malformed -> crash
        first  = read_number(s)
        second = s[len(first)]
        third  = s[len(first)+1:]
    else:
        # we're reading an expression
        pos    = next_token(s)
        first  = s[0:pos+1]
        second = s[pos+1]
        third  = s[pos+2:]
    return first,second,third

def next_token(s):
    n   = 0
    pos = 0
    for x in s:
        if x == '(':
            n += 1
        elif x == ')':
            n -= 1
        if n == 0:
            # function should always exit here
            return pos
        pos += 1
    # this should only happen when parentheses are unablanced
    return pos

def read_number(s):
    c = ""
    while s[0].isdigit():
        c += s[0]
        s = s[1:] # s++;
    return c

def do_op(left,operation,right):
    # TODO :  Can we optimise thise function a little bit and get rid of all those ifs ?
    # print "do_op(%s,%s,%s)" % (left,operation,right)

    if left == None or right == None: # Left or Right might be None in a case of a previous
        return                        # impossible operation, like division by zero.

    if operation == "+" :
        return left + right

    elif operation == "*" :
        return left * right

    elif operation == "/" :
        if right != 0 :
            result =  left / right
            if not left % right : # we don't allow fractions
                return result

    elif operation == "-" :
        return left - right

def is_number(s):
    return s.isdigit()

def is_operation(s):
    return s in ["+","/","*","-"]

def remove_spaces(s):
    return "".join(s.split(" "))

def is_parenthized(s):
    return s.startswith("(")

def remove_parens(s):
    # defensive programming
    if is_parenthized(s) :
        return s[1:-1]
    return s

def combo(S):
    if len(S) == 2: # If there's only two numbers remaining in the stack
        for c in _combo(S[0],S[1]):
            yield ("("+c+")")
        return

    original = list(S)

    for e in original:
        S.remove(e)
        #s = combo(S) # don't throw away the yields ! use the generator
        for es in combo(S) :
            for c in _combo(e,es):
                yield ("("+c+")")
        S.append(e)

def _combo(a,b):
    L = []
    L.append(a+"+"+b)
    L.append(a+"-"+b)
    L.append(a+"*"+b)
    L.append(a+"/"+b)

    L.append(b+"/"+a)
    L.append(b+"-"+a)
    #L.append( b+"+"+a) # addition and multiplication are abelian,
    #L.append( b+"*"+a) # no need to repeat them
    return L

def number_pprint(number):
    string_number = list(str(number))
    i             = 0
    result        = []
    while string_number:
        if i and not (i % 3):
            result+="."
        n = string_number.pop()
        result+=n
        i += 1

    result.reverse()
    return "".join(result)

if __name__ == "__main__":
    main()

