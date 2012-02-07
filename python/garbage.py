def IsNumber(s):
    try:
        x = int(s)
    except:
        return False
    else:
        return True

def MustBeRoot():
    if not IsRoot():
        print "Error: Must be root to run this script."
        sys.exit(-1)

def IsRoot():
    return os.getuid() == 0

def sortDic(dic):
    tupleList = [(x.lower, dic[x]) for x in dic.keys()]
    tupleList.sort()
    return [x[1] for x in tupleList]
