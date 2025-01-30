# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    create_xpm.py                                      :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yaltayeh <yaltayeh@student.42amman.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/07 20:30:42 by yaltayeh          #+#    #+#              #
#    Updated: 2024/11/25 16:43:32 by yaltayeh         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

import subprocess
import numpy as np
import sys
import os
import re

def get_width_height(data:str):
    res = str(re.findall(r', \d+x\d+,', data.split("Output")[1])[0])
    return list(map(int, res.strip(" ,").split('x')))

def image_to_raw(image_path):
    command = [
        'ffmpeg',
        '-hide_banner',
        '-i', image_path,
        '-f', 'rawvideo',
        '-pix_fmt', 'abgr',
        '-'
    ]
    process = subprocess.Popen(command, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
    stdout, stderr = process.communicate()

    if process.returncode != 0:
        print(f"FFmpeg error: {stderr.decode('utf-8')}")
        return None
    width, height = get_width_height(stderr.decode())
    image = np.frombuffer(stdout, np.uint32).reshape((height, width))
    return image

def write_data_to_xpm(xpm_path, raw_data:np):
    color = 0
    color_table = {}
    color_map = []
    for row in raw_data:
        line = ""
        for pix in row:
            pix >>= 8
            if pix not in color_table:
                color_table[pix] = "{:03x}".format(color)
                color += 1
            line += color_table[pix]
        color_map.append(line)
    head = " ".join(map(str, [*raw_data.shape[::-1], len(color_table), 3]))
    with open(xpm_path, "w") as f:
        table_lines = "\t".join(list(map(lambda color: f"\"{color[1]} c #{color[0]:08x}\",\n", color_table.items())))
        map_lines = ",\n\t".join(list(map(lambda line: f"\"{line}\"", color_map)))
        f.write('static char *sample_%d__%d[] = {\n'
                '    "%s ",\n'
                '    %s\n'
                '    %s\n'
                '};\n'
                 % (*raw_data.shape[::-1], head, table_lines, map_lines))

if __name__ == "__main__":
    argc = len(sys.argv)
            
    if argc < 2:
        print(f"Usege: {sys.argv[0]} image1 image2 ... ")
        exit(1)
        
    for i in range(1, argc):
        orginal_image_path = sys.argv[i]
        xpm_image_path = os.path.splitext(orginal_image_path)[0] + ".xpm"
        raw_image_data = image_to_raw(orginal_image_path)
        if raw_image_data is not None:
            write_data_to_xpm(xpm_image_path, raw_image_data)
            print(f"{xpm_image_path} -- shape: {raw_image_data.shape[::-1]}")