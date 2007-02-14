import time

class Timer:
    """ A Timer class for all the calculations """

    def __init__(self):
        self.start_time = 0
        self.end_time = 0
        self.wait_time = 0
    
    def start(self):
        # If the timer was started but never stopped, we
        # want to keep the original start time
        if self.start_time == 0:
            self.start_time = time.time()
        
    def stop(self):
        self.end_time = time.time()
        self.wait_time += (self.end_time - self.start_time)
        self.start_time = 0
        self.end_time = 0
    
    def _print_time(self,tm):
        tm = time.localtime(tm)
        print "%d:%d:%d" % (tm[3],tm[4],tm[5])

    def get_waittime(self):
        return self.wait_time
