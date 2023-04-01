
import control_bridge as cb

def loop(controlLine):
    print("While loop")
    length = 0
    limit = 10000
    while(True):
        if controlLine.isGUI() == False:
            controlLine.makeGUI()
        for i in range(controlLine.numberOfRobots()):
            #print(i)
            #print("Robot number {}".format(controlLine.getRobot().id()))
            #print("Robot tag {}".format(controlLine.getRobot().tag()))
            #print("move forward")
            if i < 10:
                controlLine.takeAction(controlLine.getRobot(), 4)
            else:
                controlLine.takeAction(controlLine.getRobot(), 1)
            #if controlLine.getCollisions(controlLine.getRobot()) > 0:
            #    print(controlLine.getCollisions(controlLine.getRobot()))
            #print("next robot")
            if controlLine.getSensorReadings(controlLine.getRobot())[0] > 0:
                print("Front sensor activated at time step {}".format(length))
            if controlLine.getSensorReadings(controlLine.getRobot())[1] > 0:
                print("Right sensor activated at time step {}".format(length))
            if controlLine.getSensorReadings(controlLine.getRobot())[2] > 0:
                print("left sensor activated at time step {}".format(length))
            #print(controlLine.getSensorReadings(controlLine.getRobot()))
            controlLine.nextRobot()
        controlLine.simulatorUpdate()
        controlLine.updateGUI()
        length += 1
        if length >= limit:
            break
    print("Loop done")

def main():
    cb.test()

    print("World setup start")

    controlLine = cb.PybindControl()

    controlLine.numberOfEntities()

    print("World setup complete")

    """
    print("Is the GUI made yet? {}".format(controlLine.isGUI()))
    print("make gui")
    controlLine.makeGUI()
    print("gui made")
    print("Is the GUI made yet? {}".format(controlLine.isGUI()))
    """
    #if controlLine.isGUI() == False:
    #    controlLine.makeGUI()

    loop(controlLine)
    """
    print("while loop")
    length = 0
    limit = 1000
    while(True):
        if controlLine.isGUI() == False:
            controlLine.makeGUI()
        for i in range(controlLine.numberOfRobots()):
            #print(i)
            #print("Robot number {}".format(controlLine.getRobot().id()))
            #print("Robot tag {}".format(controlLine.getRobot().tag()))
            #print("move forward")
            if i < 10:
                controlLine.takeAction(controlLine.getRobot(), 0)
            else:
                controlLine.takeAction(controlLine.getRobot(), 1)
            #print("next robot")
            controlLine.nextRobot()
        controlLine.simulatorUpdate()
        controlLine.updateGUI()
        length += 1
        if length >= limit:
            break
    print("loop done")
    """

    
    print("Testing complete.")

main()