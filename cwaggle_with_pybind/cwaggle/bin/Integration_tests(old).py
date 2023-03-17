import cwaggle_bridge as cb
import sys

print("Vec2 Test")
testvec = cb.Vec2(8, 9)
print(testvec)
print("X: {} Y: {}".format(testvec.x, testvec.y))

print("Entity Test")
centity = cb.Entity()
print(centity)
print("Entity id is {}".format(centity.id()))
centity.transform = cb.CTransform(cb.Vec2(8, 9))
print("Entity x position is {}".format(centity.transform.p.x))

