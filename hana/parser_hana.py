import numpy  as np

def read_res(res_code, res_type):
    if res_type == 'tr':
        dir_path = "C:/1Q OpenAPI/1QApiAgent/TranRes"
    if res_type == 'real':
        dir_path = "C:/1Q OpenAPI/1QApiAgent/RealRes"

    res_info = {}
    res_info['input'] = {}
    res_info['output'] = {}

    input_line = False
    output_line = False
    i = 0
    for line in open("%s/%s.res" % (dir_path, res_code), "r"):
        curline = line.split("\n")[0].split(", ")
        if len(curline) > 1:
            rec_name_line = curline[0].split("\t\t")

            if len(rec_name_line) > 1:

                if (rec_name_line[1][:8] == 'REC_NAME') & ~input_line:
                    input_line = True
                    res_info['input']['rec_name'] = rec_name_line[1][9:]
                    res_info['input']['items'] = pd.DataFrame(columns=['item', 'caption'])
                    continue

                if (input_line) & (curline[1][:4] == 'ITEM'):
                    res_info['input']['items'].loc[i, 'item'] = curline[1][5:]
                    res_info['input']['items'].loc[i, 'caption'] = curline[4][8:]
                    i  += 1
                    continue

                if (rec_name_line[1][:8] == 'REC_NAME') & input_line:
                    input_line = False
                    output_line = True 
                    i = 0
                    res_info['output']['rec_name'] = rec_name_line[1][9:]
                    res_info['output']['items'] = pd.DataFrame(columns=['item', 'caption'])
                    continue                

                if (output_line) & (curline[1][:4] == 'ITEM'):
                    res_info['output']['items'].loc[i, 'item'] = curline[1][5:]
                    res_info['output']['items'].loc[i, 'caption'] = curline[4][8:]
                    i  += 1
                    continue

    return res_info
