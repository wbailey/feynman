set xrange[3.0:8.0]
set yrange[-1.0:1.0]

sigma = 3.4
epsilon = 0.997

f6(x) = (sigma/x)**6
f12(x) = f6(x) * f6(x)
lj(x) = -(24 * epsilon/x)*(f12(x) - f6(x))
vlj(x) = (2 * epsilon)*(f12(x) - f6(x))
flj(x) = -(24.0 * epsilon/x)*(2.0 * f12(x) - f6(x))

plot vlj(x), -f6(x), f12(x), flj(x)
