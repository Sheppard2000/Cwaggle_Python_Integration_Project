import gym
import numpy as np
import matplotlib.pyplot as plt

class RoboCon(gym.Env):
    def __init__(self):
        self.action_space = gym.spaces.Discrete(5)
        self.observation_space = gym.spaces.MultiBinary(8)
    
    def step(self):
        pass

    def render(self):
        pass
    
    def reset(self):
        pass