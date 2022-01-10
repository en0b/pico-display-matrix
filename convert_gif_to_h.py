from PIL import Image, ImageFilter

# Open image file
im = Image.open('test3.gif')

print("\n** Analysing image **\n")

# Display image format, size, colour mode
print("Format:", im.format, "\nWidth:", im.width, "\nHeight:", im.height, "\nMode:", im.mode)

# Check if GIF is animated
frames = im.n_frames
print("Number of frames: " + str(frames))

# Convert to RGB
rgb_im = im.convert('RGB')

print("\n** Converting image **\n")

f = open("image.h", "w")
f.write("const uint16_t image_LUT[] = { 0x00A0,0x01C0,0x02A0,0x1CE2,0x0060,0x0020,0x0140,0x1702,0x22A4,0x572A,0x2124,0x4AA9,0xE75C,0x7CAF,0,0};\n")
f.write("const uint8_t images[] = {\n")

colors = []
# Iterate through frames and pixels, top row first
for z in range(frames):

    # Go to frame
    im.seek(z)
    odd = False
    byte = 0
    rgb_im = im.convert('RGB')

    for y in range(im.height):
        for x in range(im.width):

            # Get RGB values of each pixel
            r, g, b = rgb_im.getpixel((x, y))
            color = r<<16+g<<8+b
            if (color not in colors):
                colors.append(color)
                print("Color "+str(colors.index(color))+": R: "+str(r)+": G: "+str(g)+": B: "+str(b))
            if not odd:
                byte = colors.index(color)
                odd = True
            else:
                byte = byte*16 + colors.index(color)
                odd = False
                if(x != im.width and y !=im.height and z != frames):
                    f.write(str(byte) + ", ")
        f.write("\n")
f.write("};\n")            
f.close()
