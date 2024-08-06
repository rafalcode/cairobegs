# help:
# alt+ mouse left lick to pan
# normal mouse left lick to record focus point.
# ESC to leave this script, note that q will not do. In this sense it behaves like alsamixer
# now with window normal, you'll have to maximise window, I have set openbox winkey+x to do this instead of xterm launch.
# ctrl+shift+"+" for zoom in
# ctrl+shift+"-" for zoom out, Note these two not so fast.

import sys, cv2, numpy as np
from pathlib import Path

argquan=len(sys.argv)
if argquan != 2:
    print("This script requires one argument: a JPEG image filename")
    sys.exit(2)

# somewhat incredibly for me, img is a string and now becomes a variable:
img = cv2.imread(sys.argv[1])
# we now use the .shape() method to get widht and height of input image
# print(f"Input jpg width={img.shape[0]} height={img.shape[1]}\n")
# imgrot = cv2.rotate(img, cv2.ROTATE_90_CLOCKWISE)
if img.shape[0] > img.shape[1]:
    img = cv2.rotate(img, cv2.ROTATE_90_COUNTERCLOCKWISE)

# Mouse callback function
global click_list
positions, click_list = [], []

def callback(event, x, y, flags, param):
    if event == 1: click_list.append((x,y))

cv2.namedWindow('img', cv2.WINDOW_NORMAL) # WINDOW_AUTO is the default, but NROMAL is best for my purposes.
cv2.setMouseCallback('img', callback)

# Mainloop - show the image and collect the data
while True:
    cv2.imshow('img', img)    
    # Wait, and allow the user to quit with the 'esc' key
    k = cv2.waitKey(1)
    # If user presses 'esc' break 
    if k == 27: break        
cv2.destroyAllWindows()

# set output text file
fout = Path(sys.argv[1]).stem + ".conft"
with open(fout, 'w') as outfile:
    outfile.write(f"{sys.argv[1]}\n")
    for position in click_list:
        # print(f"%s", position[0])
        # print(f"%s", position[1])
        outfile.write(f"{position[0]}\n")
        outfile.write(f"{position[1]}\n")
