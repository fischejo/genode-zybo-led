
from time import sleep
import mmap

with open("/dev/mem", "r+b") as f:
    mm = mmap.mmap(f.fileno(), 4, offset=0x41200000)
    while True:
        try:
            mm[0] = chr(0x01) # 0001
            sleep(0.2)
            mm[0] = chr(0x02) # 0010
            sleep(0.2)
            mm[0] = chr(0x04) # 0100
            sleep(0.2)
            mm[0] = chr(0x08) # 1000
            sleep(0.2)
            mm[0] = chr(0x04)
            sleep(0.2)
            mm[0] = chr(0x02)
            sleep(0.2)            
        except KeyboardInterrupt:
            break
mm.close()
