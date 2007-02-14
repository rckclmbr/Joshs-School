import time

class Timer:
    """ A Timer class for all the calculations.
        The wait time accumulates upon start and stop. """

    def __init__(self):
        self.wait_time = 0  # Wait time (in millis)
        self.started = 0
        self.t = timing()
    
    def start(self):
        # If the timer was started but never stopped, we
        # want to keep the original start time
        if self.started == 0:
            self.t.start()
            self.started = 1
        
    def stop(self):
        self.t.finish()
        self.wait_time += self.t.milli()        
        self.started = 0
    
    def get_waittime(self):
        return self.wait_time / 1000.00


class timing:
    """ This class is essentially the timing module
        as a class, since we need a separate instantiation
        for each Timer class (otherwise we'll get incorrect
        values) """
    def __init__(self): self.t0 = self.t1 = 0
    def start(self):    self.t0 = time.time()
    def finish(self):   self.t1 = time.time()
    def seconds(self):  return int(self.t1 - self.t0)
    def milli(self):    return int((self.t1 - self.t0) * 1000)
    def micro(self):    return int((self.t1 - self.t0) * 1000000)
