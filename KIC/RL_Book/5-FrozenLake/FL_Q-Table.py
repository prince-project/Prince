# -*- coding: utf-8 -*-
import gym
import numpy as np
import matplotlib.pyplot as plt
import random as pr


env = gym.make('FrozenLake-v1')
# env.monitor.start('tmp/Frozenlake8x8-0.2', force= True)
# Q-Table 초기화
Q = np.zeros([env.observation_space.n,env.action_space.n])


num_episodes = 1000

# reward 값과 state 값들을 저장 해놓을 list

rList = []
sList = []

# Q값이 모두 같을때 랜덤한 action을 구해주기 위한 함수
def rargmax(vector):
    m = np.amax(vector)
    indices = np.nonzero(vector ==m)[0]
    return pr.choice(indices)

for i in range(num_episodes):
    # Environment 초기화와 변수 초기화
    s = env.reset()
    rAll = 0
    d = False
    j = 0
    sList=[]
    # The Q-Table 알고리즘
    while not d and j<250:
        j+=1
        # 가장 Q값이 높은 action을 결정함
        a = rargmax(Q[s,:])

        # action을 통해서 next_state, reward, done, info를 받아온다
        s1,r,d,_ = env.step(a)
        if r == 1:
            print(sList)
        # Q-Learning
        Q[s,a]= r+ np.max(Q[s1,:])
        s=s1
        rAll=rAll+r
        sList.append(s)

    rList.append(rAll)


print ("Final Q-Table Values")
print ("          left          down          right          up")
print (Q)
print("성공한 확률 : ", len(rList)/num_episodes)
plt.bar(range(len(rList)),rList, color="Blue")
plt.show()