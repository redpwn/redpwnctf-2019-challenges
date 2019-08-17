#!/bin/python2

import random
import time

BROWNIE_GODDESSLYNESS = 1000

brownie_pro_gamer_moves = [];
for i in range(BROWNIE_GODDESSLYNESS):
    brownie_pro_gamer_moves.append(random.randint(0, 100))

print("Welcome to NotDeGhost's dojo, where we train defense against Brownie!")

punches = ["right leg", "left leg", "right arm", "left arm"];
def fight_rob():
    print("I will go easy on you.")
    print("Just block every punch.")
    rob_patience = 10;
    while (rob_patience > 0):
        target = random.randint(0, 7);
        print("*Rob is " + ("happy*" if target > 3 else "mad*"))
        target %= 4;
        print("Rob throws a punch at your " + punches[target]);
        print("Block your:\n\t0: right leg\n\t1: left leg\n\t2: right arm\n\t3: left arm");
        x = int(raw_input())
        if (x != target):
            print("You have been hit!")
            return;
        print("Good work!")
        rob_patience -= 1;
    return;

def fight_student():
    print("The other student runs away in fear. You win!")
    return;

x = 0;
while ({}=={}):
    print("1. Fight me")
    print("2. Fight a fellow student")
    print("3. Challenge Brownie")
    x = int(raw_input())
    if (x == 1):
        fight_rob();
    elif (x == 2):
        fight_student();
    elif (x == 3):
        break;
    else:
        print("Trolls are not allowed in the dojo of NotDeGhost! The art of defense against Brownie will not be disrespected! *shoos you away*")
        quit();

print("*DUN DUN DUN*")
print("The dojo is on fire")
time.sleep(1)
print("You see Brownie walking toward you slowly")
print("You freeze in place")
print("You can't move")
print("Everything seems to happen in slow motion")
print("You feel slow and heavy")
print("She punches you, and you realise that you are about to die.")
brownie_hp = BROWNIE_GODDESSLYNESS;
while (brownie_hp > 0):
    print("Brownie's HP: " + str(brownie_hp))
    print("Throw a grenade at x = ?:")
    x = int(raw_input())
    if (brownie_pro_gamer_moves[brownie_hp - 1] != x):
        print("You missed!")
        print("Brownie creeps up behind you and stabs you in the back.")
        print("You slowly lose conciousness as the fire around you rages.")
        print("***MISSION FAILED***")
        quit();
    brownie_hp -= 1;

print("Congrats! You did it!")
print("flag{https://www.youtube.com/watch?v=hqURBTpvh0A}")

