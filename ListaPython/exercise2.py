
def ex2(list):
    g = list.pop(4)
    list.pop(4)
    list.insert(1,g)
    list.insert(len(list),g)
    return list

list = [54,44,27,79,91,41]



print ex2(list)
