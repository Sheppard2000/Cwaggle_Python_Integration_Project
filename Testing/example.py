import example
import time

#print(example.add(1, 2))
#print(example.sub(5, 4))
#print(example.sna(10, 5, 3))
#print(example.reverse("Hello"))
example.test_suite()
example.printMessage()
example.newTracker(1, "nemo", 2, 1)
print("I am at {} and {}".format(example.getPosX(), example.getPosY()))
print("I sleep")
time.sleep(2)
print("I wake and move")
example.updatePos(5, 3)
print("I am now at {} and {}".format(example.getPosX(), example.getPosY()))
myPet = example.pet(4, 1998)
print("I have a pet. Its age and birthdate is")
myPet.getStats()
myPet2 = example.pet(15, 1993)
print("I have another pet. Its age and birthdate is")
myPet2.getStats()
print("Testing is complete =)")