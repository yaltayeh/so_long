# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    create_xpm2.py                                     :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yaltayeh <yaltayeh@student.42amman.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/07 20:30:42 by yaltayeh          #+#    #+#              #
#    Updated: 2024/12/30 17:09:12 by yaltayeh         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

import PIL.Image
import numpy as np
import sys
import os
import PIL
import math

def toggle_alpha(pix:np.uint32):
    pix ^= 0x00000000
    pix ^= 0xFF000000
    return pix

def image_to_raw(image_path):
    image = PIL.Image.open(image_path)
    buffer = image.tobytes('raw', 'BGRA')
    image_np = np.frombuffer(buffer, np.uint32).reshape(image.height, image.width)
    return image_np

def write_data_to_xpm(xpm_path, raw_data:np):
    color = 0
    color_table = {}
    color_map = []
    colors = np.unique(raw_data)

    cpp = 0
    colors_count = len(colors)
    while colors_count > 0:
        cpp += 1
        colors_count = int(colors_count / 16)
    #cpp = math.ceil(len(colors)/16)

    # width, height = raw_data.shape[::-1]
    # colors_dict = dict(zip(colors, range(len(colors))))
    # print(colors_dict)
    # exit(0)


    for row in raw_data:
        line = ""
        for pix in row:
            pix = toggle_alpha(pix)
            if pix not in color_table:
                color_table[pix] = ("{:0" + str(cpp) + "x}").format(color)
                color += 1
            line += color_table[pix]
        color_map.append(line)
    head = " ".join(map(str, [*raw_data.shape[::-1], len(color_table), cpp]))
    with open(xpm_path, "w") as f:
        table_lines = "\t".join(list(map(lambda color: f"\"{color[1]} c #{color[0]:08x}\",\n", color_table.items())))
        map_lines = ",\n\t".join(list(map(lambda line: f"\"{line}\"", color_map)))
        f.write('static char *sample_%d__%d[] = {\n'
                '    "%s ",\n' # width height color_count cpp
                '    %s\n'      # table colors
                '    %s\n'      # image buffer
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