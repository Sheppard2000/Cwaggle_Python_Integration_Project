#!/usr/bin/env python

import cwaggle_bridge
import time

pose = (300, 300, 0)
nearby_robot_poses = [(500, 200, 1.57), (30, 100, -1.4)]
nearby_target_positions = [(10, 20), (99, 42)]

start_time = time.time()

for i in range(2):
    result = cwaggle_bridge.control(pose, nearby_robot_poses, nearby_target_positions)
    print("result: {}".format(result))

elapsed_time = time.time() - start_time
print("time per loop: {}".format(elapsed_time / 1000))
print("frequency per loop: {}".format(1000 / elapsed_time))
