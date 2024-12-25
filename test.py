import requests
import time
for i in range(63):
    break
    if i == 12 or i == 45 or i == 13:
        continue
    requests.get(f'http://192.168.0.42/rc5?dev=16&code={i}&release=1')
    print(i)
    time.sleep(1)

for i in range(79,80):
    for j in range(10):
     requests.get(f'http://192.168.0.42/rc5x?dev=16&code={i}&release=1')
     print(i)
     time.sleep(0.5)
    