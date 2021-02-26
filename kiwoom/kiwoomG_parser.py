DIR_PATH = "C:/OpenAPIG/Data/"

def parse_input(item, dir_path):
    fields = []
    on_off = False
    i = 0
    #Repeat for each song in the text file
    for line in open("%s/kfoptrinfo.dat"%dir_path,"r"):
    
        curr_line = line.split("\t")
        if curr_line[0][1:16] == '%s_INPUT]'%item:
            on_off = True
            continue

        if on_off:
            i += 1

        if on_off and i > 1 and len(curr_line) == 1:
            break

        if on_off and i > 1:
            fields.append(curr_line[1])
            continue

    #It is good practice to close the file at the end to free up resources   
    file.close()
    return fields

def parse_output(item, dir_path):
    fields = []
    on_off = False
    i = 0
    #Repeat for each song in the text file
    for line in open("%s/kfoptrinfo.dat"%dir_path,"r"):
    
        curr_line = line.split("\t")
        if curr_line[0][1:16] == '%s_OCCURS'%item:
            on_off = True
            continue

        if on_off:
            i += 1

        if on_off and i > 2 and len(curr_line) == 1:
            break

        if on_off and i > 2:
            fields.append(curr_line[1])
            continue

    #It is good practice to close the file at the end to free up resources   
    file.close()
    return fields