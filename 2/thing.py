import random

class Thing:
    def __init__ (self,level,wunit,hunit):
        #default construction
        self.px = random.randint(0.05 * wunit, 0.95 * hunit)
        self.py = random.randint(0.05 * wunit,0.95 * hunit)
        self.vx = random.randint(-0.025 * wunit, 0.025 * hunit)
        self.vy = random.randint(-0.025 * wunit, 0.025 * hunit)
        self.level = level
    
    def display(self):
        print "X: ", self.px
        print "Y: ", self.py
        print "VX: ", self.vx
        print "VY: ", self.vy
        print "level: " ,self.level
        
    def move(self):
        #change the position of thing
        self.px += self.vx
        self.py += self.vy
       

class Bomb:
    def __init__(self,x,y):
        self.px = x
        self.py = y
        self.level = -1

    def move(self):
        #bomd only move on z axis
        self.level += 1
