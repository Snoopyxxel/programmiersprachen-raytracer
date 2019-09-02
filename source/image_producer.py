import sys
import os

for i in range(150):
    os.system("./raytracer " + "/home/vito/Desktop/Raytracer-Animation/anim_%d.sdf " % (i + 1) + "/home/vito/Desktop/Raytracer-Animation/images/image_%d.ppm" % (i + 1))
