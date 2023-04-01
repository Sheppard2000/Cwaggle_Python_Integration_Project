
import cwaggle_bridge as cb

#world = cb.makeSquareWorld(800, 800, 20, 10, 250, 10)
world = cb.World(200, 200)
print("World Created!")
bot1 = world.addEntity("TestBot")
print(bot1.id())
bot2 = world.addEntity("TestBot")
print(bot2.id())
bot3 = world.addEntity("TestBot")
print("Test Bots(3) Created!")
count = 0
for b in world.getEntities("TestBot"):
    print("I am Test Bot Number {}".format(count))
    count += 1
print("Test Complete!")