# web supplements, J Wang, UMass Dartmouth
# animating a ball released from rest and bouncing off the floor
from visual import *    # get VPython modules for animation

# draw the ball at (0,5,0) and a thin floor at (0,-5,0)
ball = sphere(pos=(0,5,0), radius=1, color=color.yellow)
floor = box(pos=(0,-5,0), length=8, height=0.2, width=4)

y, v, dt = 5.0, 0.0, 0.01   # initial position, velocity, time step
while True:                 # bouncing up and down indefinitely
    rate(400)               # limit animation rate to 400 frames/sec
    y = y + v*dt            # update y position
    ball.pos.y = y          # move ball accordingly
    if y > floor.y + ball.radius:
        v = v - 9.8*dt      # above floor, update velocity
    else:
        v = - v             # below floor, reverse velocity
