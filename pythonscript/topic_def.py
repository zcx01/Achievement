#!/usr/bin/python
import json
import sys
import os

def get_upper_case_name(text):
    lst = []
    last_char = ''
    for index, char in enumerate(text):
        if char.isupper() and index != 0 and last_char.islower():
            lst.append("_")
        lst.append(char)
        last_char = char
    result = "".join(lst).upper()
    return result

if __name__ == "__main__":
    if len(sys.argv) < 3:
        print('Error: input json file(*.json) or out file(*.h) not specified')
        sys.exit()
    f_in = open(sys.argv[1], 'r')
    
    out_file_name = os.path.basename(sys.argv[2]).split('.')[0]

    content = json.loads(f_in.read())
    sorted(content)

    for item in content:
        print('//' + content[item]['desc'])
        line = 'TOPIC_' + get_upper_case_name(out_file_name.split('_')[0]) + '_' + get_upper_case_name(item)
        print(f'vehctrl_status->addSignalAndTop((struct veh_signal *)&CANSIG_GW_5F1__{item}_g, {line});'+ '\n')


