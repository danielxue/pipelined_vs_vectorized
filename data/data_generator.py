import random
f = open("data.txt", "w")
num_rows = 1000000
f.write(str(num_rows) + "\n")
f.write("A,B,C,D,E,F,G,H,I,J\n")
for i in range(10 * num_rows):
    f.write(str(random.randint(0, 100)) + "\n")
f.close()