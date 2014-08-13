#!/usr/local/bin/python3
import sys
from pylab import plot,show

velocities = sys.stdin.readlines()

# the last line in the file contains
# vmax     5.6798
#
# so this is a dirty trick
vmax = float(velocities.pop().split()[1])

bin_count = 200
bin_size = vmax/bin_count
bins = {}

for lines in velocities:
  v = float(lines.split()[1])

  index = int(v/bin_size)

  if index in bins:
    bins[index] += 1
  else:
    bins[index] = 1

x = []
y = []

print(bins)

for key, value in bins.items():
  x.append(key * bin_size)
  y.append(bin_count * value/len(velocities))

plot(x,y)
show()
