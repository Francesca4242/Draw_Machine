from PIL import Image, ImageOps
import numpy
import os
image_name=input("Name of your picture")
#dir = os.path.join("C:\\","Users","Francesca","Documents","Arduino",image_name)
#if not os.path.exists(dir):
#	os.mkdir(dir)
arduino_file= open(r"C:\Users\Francesca\Documents\Arduino\send_sketch\\"+image_name+".ino","a")
im = Image.open("pixil-frame-0.png")
im_flip = ImageOps.mirror(im)
np_im = numpy.array(im_flip)
dimensions=np_im.shape
x_total=dimensions[1]
y_total=dimensions[0]
y=0
arduino_file.write("unsigned char colour_number [] = {")
while y<y_total:
	x=0
	while x<x_total:
		arduino_file.write(str(np_im[y][x][0]))
		arduino_file.write(",")
		x=x+1
	arduino_file.write("\n")
	y=y+1
arduino_file.write("};")
arduino_file.write("\nint x_total="+str(x_total)+";")
arduino_file.write("\nint y_total="+str(y_total)+";")
arduino_file.close()