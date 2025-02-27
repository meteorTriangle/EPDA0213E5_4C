import cv2
import math
import numpy as np
import matplotlib.pyplot as plt
from PIL import ImageFont, ImageDraw, Image
import os

p = os.path.dirname(__file__)


imgpath = p+ '/png/'
ldir = os.listdir(imgpath)

path = p + "/my_img__.c"
f = open(path, 'w')

def get_bit_value(r, g, b):
    if (r,g,b) == (0xFF,0xFF,0x00):
        return 0b10
    if (r,g,b) == (0x00,0x00,0x00):
        return 0b00
    if (r,g,b) == (0xFF,0x00,0x00):
        return 0b11
    return 0b01

try:
    for img_i in range(len(ldir)):
        img_name = ldir[img_i]
        f.write("uint32_t img{:d}[] = {{\n".format(img_i))
        im = cv2.imread(imgpath + img_name)
        im = cv2.cvtColor(im, cv2.COLOR_BGR2RGB)
        print(im.shape)
        img_height = im.shape[0]
        img_width = im.shape[1]*2
        height_font_1b = img_height.to_bytes(1, byteorder="big", signed=False).hex()
        width_font_1b = img_width.to_bytes(2, byteorder="big", signed=False).hex()
        font_name_len_2b = len(img_name).to_bytes(1).hex()
        int32data1 = height_font_1b + width_font_1b + font_name_len_2b
        font_name_bytes = img_name.encode("ansi").hex()
        print(font_name_bytes)
        f.write("    0x{:s}, //height: {:d}, width: {:d}\n    ".format(int32data1, img_height, img_width))
        for i in range((int((len(img_name)*2)/8), int((len(img_name)*2)/8) + 1)[((len(img_name)*2)%8 != 0)]):
            int32_t_data = ''
            for j in range(4):
                if(i*8+j*2 >= len(img_name)*2):
                    int32_t_data = int32_t_data + '0'
                    int32_t_data = int32_t_data + '0'
                else:
                    int32_t_data = int32_t_data + font_name_bytes[i*8+j*2]
                    int32_t_data = int32_t_data + font_name_bytes[i*8+j*2+1]
            f.write("0x{:s}, ".format(int32_t_data))
        f.write("//{:s}\n    ".format(img_name))
        for x in range(im.shape[0]):
            for y in range(int(im.shape[1]/16)+(1,0)[im.shape[1]%16 == 0]):
                data = 0b0
                for y1 in range(16):
                    bit = 0b01
                    if(y*16+y1 >= im.shape[1]):
                        continue
                    r, g, b = im[x, y*16+y1]
                    bit = get_bit_value(r, g, b)
                    data = bit<<((30-y1*2)) | data
                f.write("0x{:s}, ".format(data.to_bytes(4).hex()))
            f.write("\n    ")
        f.write("\n};\n\n\n")
        
    f.write("uint32_t* img_[{:d}] = {{\n".format(len(ldir)))
    for font_i in range(len(ldir)):
        f.write("    img{:d}, \n".format(font_i))

    f.write("};")

except Exception as e:
    print(f"Error processing images: {str(e)}")
    if 'f' in locals():
        f.close()