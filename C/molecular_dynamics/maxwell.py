#!/usr/local/bin/python3
import sys
import matplotlib.pyplot as pyplot
import numpy as np

velocities = np.loadtxt(sys.stdin)

# bin_size = vmax/bin_count
# bins = {}

# for v in velocities:
#   # v = float(lines.split()[1])

#   index = int(v/bin_size)

#   if index in bins:
#     bins[index] += 1
#   else:
#     bins[index] = 1

pyplot.hist(velocities, bins = 20)
pyplot.show()

# sys.exit(0)
# x = []
# y = []

# for key, value in bins.items():
#   x.append(key * bin_size)
  # y.append(bin_count * value/len(velocities))

# plot(x,y)
# show()
