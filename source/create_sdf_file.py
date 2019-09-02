import math

for i in range(150):
  filename = "anim_%d.sdf" % (i + 1)
  f = open(filename, "a+")
  inital = open("initial.sdf", "r")
  if inital.mode == 'r':
      inital_contents = inital.read()
  f.write(inital_contents)
  angle = float(((i + 1) / 150) * 2 * math.pi)
  f.write("transform  b_1 scale 2 4 2\ntransform b_1 translate 3 0 2\ntransform b_1 rotate %.9f 0 0 1" % angle)
  f.close()
  inital.close()
