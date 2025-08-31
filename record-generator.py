import struct
import random

forced_records = [0x1110, 0x1111, 0x37F2, 0x601B]

with open("records.bin", "wb") as f:
    for i in range(1,  65536):

        if i == 0x1110:
            type_val = 0
        elif i in forced_records:
            type_val = 1
        else:
            type_val = random.randint(0, 1)


        if i in forced_records:
            if i == 0x1111:
                rebelled = 0
            else:
                rebelled = 1
        else:
            if type_val == 1:
                if random.random() < 0.3:
                    rebelled = 1
                else:
                    rebelled = 0
            else:
                if random.random() < 0.01:
                    rebelled = 1
                else: 
                    rebelled = 0


        f.write(struct.pack('<iii', i, type_val, rebelled))
