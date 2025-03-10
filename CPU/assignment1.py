import time

# this is enough for one cpu to reach 100%.
# python gil, will only run the process in single thread on single core.
# Os might pre-empt the thread and schedule it elsewhere?
# t1 -> c11 - 100% usage, c12 - 0% usage
# t2 -> c11 - 0% usage, c12 - 100% usage

# The OS scheduler may not move the thread frequently unless there’s a reason
# If the system has available resources, it may let the thread run on the same core
# for a long time.
def heavy():
    cnt = 0
    
    for _ in range(1000000000):
        cnt += 1
        
    print("number:", cnt)
    
# heavy()

# get one cpu to work ~50%
# python will pick a random core and make it work for half a sec.
# might see less pre-emptions here? because cpu is available for half a sec? 
# pre-empt when another process with higher priority comes up
def sleephalf():
    print("here")
    work_time = 0.5 # work for half
    sleep_time = 0.5 # sleep for half

    while True:
        start = time.time()
        while (time.time() - start) < work_time:
            pass # do nothing

        time.sleep(sleep_time)

# sleephalf()

# idea is to do the above in all cores parallely
import multiprocessing
def sleephalfInAllCores():
    num_cores = 16
    with multiprocessing.Pool(processes=num_cores) as pool:
        for _ in range(num_cores):
            pool.apply_async(sleephalf)
    
        pool.close()  
        pool.join()  
    
# sleephalfInAllCores()

def heavyinAllCores():
    num_cores = 16
    with multiprocessing.Pool(processes=num_cores) as pool:
        for _ in range(num_cores):
            pool.apply_async(heavy)
    
        pool.close()  
        pool.join()  
        
# heavyinAllCores()

