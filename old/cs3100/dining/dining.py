#!/usr/bin/python

# Joshua Braegger
# CS3100
# Dining Philosopher Problem

import random, time
from threading import Lock, Thread
from timer import Timer

NUM_PHILOSOPHERS = 5    # Number of philosophers.
RUN_TIME = 60           # Approximately how long to run (in seconds)

class ChopsticksBusy(Exception):  
    """ This is an exception when a philosopher can't get 
        both chopsticks """
    pass

def wait(seconds):
    """ Wait a random time, with the max time in seconds """
    time.sleep(random.random() * seconds)

class Philosopher(Thread):

    def __init__(self, id, run_time=RUN_TIME):
        Thread.__init__(self)
        # Init class variables
        self.id = id
        self.left_chopstick = chopsticks[id]
        self.right_chopstick = chopsticks[(id + 1) % NUM_PHILOSOPHERS]
        self.stop_time = time.time() + run_time
        self.feedings = 0
        self.chopstick_timer = Timer()

    def run(self):
        """ Called when the thread is started.  Keeps trying to eat
            until it's time to stop """
        while time.time() < self.stop_time:
            self.chopstick_timer.start()
            try: 
                self.think()
                if time.time() >= self.stop_time: break
                self.acquire_chopsticks()  # may raise ChopsticksBusy
                self.chopstick_timer.stop()
                self.eat()
                self.release_chopsticks()      
            except ChopsticksBusy:
                pass

    def think(self):
        """ Philosophers like to think in between feedings  """
        #print "philosopher %d thinking" % self.id
        wait(4)

    def eat(self):
        """ Mmmm.... food """
        self.feedings = self.feedings + 1
        #print "philosopher %d on feeding #%d" % (self.id, self.feedings)
        wait(2)

    def acquire_chopsticks(self):
        """ Acquires the chopsticks. """
        self.left_chopstick.acquire()
        
        # We don't want to hold on to the left chopstick
        # forever, so we release it and try again
        if not self.right_chopstick.acquire(0): 
            self.left_chopstick.release()
            raise ChopsticksBusy

    def release_chopsticks(self):
        """ Releases both chopsticks """
        self.left_chopstick.release()
        self.right_chopstick.release()

    def get_waittime(self):
        """ Returns the total amount of time the philosopher
            has waited """
        return self.chopstick_timer.get_waittime()
    
    def get_feedings(self):
        """ Returns the total amount of feedings """
        return self.feedings

if __name__ == "__main__":

    # Create the chopsticks.
    chopsticks = []
    for i in range(NUM_PHILOSOPHERS):      # 1 chopstick for every philosopher
        chopsticks.append(Lock())

    timer1 = Timer()
    timer1.start()
        
    # Create the philosophers and get them feeding
    philosophers = []
    for i in range(NUM_PHILOSOPHERS):
        p = Philosopher(i)
        philosophers.append(p)
        p.start()

    # Wait for everyone to finish.
    for p in philosophers:
        p.join()
    
    timer1.stop()
    
    # Print all totals
    print "\nTime each philosopher waited:"
    for p in philosophers:
        print "Philosopher %d wait time: %.2f seconds" % ( p.id, p.get_waittime() )
        
    print "\nTotal time: %.2f seconds" % timer1.get_waittime()
    
    print "\nNumber of times eaten: "
    for p in philosophers:
        print "Philosopher %d ate %d times" % ( p.id, p.get_feedings() )   
