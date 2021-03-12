import numpy  as np

dir_path = "C:/OpenAPIG/Data/"

def read_trinfo(trcode, dir_path):
    lines = []
    on_off = False
    for line in open("%s/kfoptrinfo.dat"%dir_path,"r"):

        curline = line.split("\n")
        
        if curline[0] == '[%s_TRINFO]'%trcode:
            on_off = True
            continue

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
    on_output_single = False
    on_output_multi = False

    for i, x in enumerate(lines):
        #print(i)
        #print(x[0])
        if x[0] == '[%s_INPUT]'%trcode:
            on_input = True
            trinfo["input"].append({})
            continue

        if on_input:
            if x[0][0:5] == 'Title':
                input_name = x[0].split("=")[1].strip()
                trinfo["input"][0][input_name] = []
                continue
            if np.sum([k == '=' for k in x]) == 1 or np.sum([k == '= ' for k in x]) == 1:
                trinfo["input"][0][input_name].append(x[0])
                continue

            if x[0][0] == '[':
                on_input = False
                continue

        if x[0] == '[%s_OUTPUT]' % trcode:
            on_input = False
            on_output_single = True
            trinfo["output"].append({})
            continue

        if on_output_single:
            if x[0][0:5] == 'Title':
                single_name = 'single' #x[0].split("=")[1].strip()
                trinfo["output"][0][single_name] = []
                continue
            if np.sum([k == '=' for k in x]) == 1:
                trinfo["output"][0][single_name].append(x[1])
                continue                

        if x[0][1:16] == '%s_OCCURS'% trcode:
            on_output_single = False
            on_output_multi = True
            if len(trinfo['output']) == 0:
                trinfo["output"].append({})
            continue

        if on_output_multi:
            if x[0][0:5] == 'Title':
                multi_name = 'multi' #x[0].split("=")[1].strip()
                trinfo["output"][0][multi_name] = []
                continue            
            if np.sum([k == '=' for k in x]) == 1:
                trinfo["output"][0][multi_name].append(x[1])
                continue    

    return trinfo
