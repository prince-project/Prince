dir_path = "C:/OpenAPIG/Data/"

def read_trinfo(trcode, dir_path):
    lines = []
    on_off = False
    for line in open("%s/kfoptrinfo.dat"%dir_path,"r"):
        curline = line.split("\n")
        #rint(line)
        #print(curline)
        if curline[0] == '[%s_TRINFO]'%trcode:
            on_off = True
            continue
            #print(curline[0])
        if on_off:
            if curline[0][10:16] == 'TRINFO':
                break
            else:
                lines.append(curline[0].split("\t"))
        else:
            continue

    return lines

def parse_trinfo(trcode, lines):

    trinfo = {"trcode": trcode, "input": [], "output": []}
    on_input = False
    on_output = False
    for i, x in enumerate(raw_info):

        if x[0] == '[%s_INPUT]'%trcode:
            on_input = True
            continue

        if on_input:
            if x[0] == '':
                trinfo["input"].append(x[1])
                continue
            if x[0][0] == '[':
                on_input = False
                continue

        if x[0][1:16] == '%s_OCCURS'% trcode:
            on_output = True
            continue

        if on_output:
            if len(x) == 1:
                continue
            elif x[0] == '':
                trinfo["output"].append(x[1][:-1])

    return trinfo
