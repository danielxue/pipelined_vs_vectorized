import glob
import re
import csv

def run_outputs():
    all_lines = None
    for filename in sorted(glob.glob("o*.txt"), key=lambda s: int(re.findall(r'\d+', s)[0])):
        lines = []
        with open(filename) as f:
            cnt = 0
            for line in csv.reader(f, delimiter="\t"):
                if cnt < 3:
                    cnt += 1
                    continue
                lines.append(line)
        if all_lines is None:
            all_lines = lines
        else:
            for i, line in enumerate(lines):
                all_lines[i] += line
    for line in all_lines:
        print("\t".join(line))

def run_logs_selectivity():
    all_hpcs = []
    for filename in sorted(glob.glob("l*.txt"), key=lambda s: int(re.findall(r'\d+', s)[0])):
        hpcs = [re.findall(r'\d+', filename)[0]]
        with open(filename) as f:
            cnt = 0
            for line in csv.reader(f, delimiter="\t"):
                if cnt == 0 and (len(line) == 0 or line[0] != "number of predicates: 2; pipelined"):
                    continue
                if cnt < 3:
                    cnt += 1
                    continue
                if len(line) == 0:
                    break
                hpcs.append(line[0])
                if len(hpcs) == 3:
                    hpcs.append(str(float(hpcs[1]) / float(hpcs[2])))
                elif len(hpcs) == 6:
                    hpcs.append(str(float(hpcs[4]) / float(hpcs[5])))
                elif len(hpcs) == 9:
                    hpcs.append(str(float(hpcs[7]) / float(hpcs[8])))
        all_hpcs.append(hpcs)
    for hpcs in all_hpcs:
        print("\t".join(hpcs))

def run_logs_predicates():
    all_hpcs = []
    filename = "l99.txt"
    with open(filename) as f:
        hpcs = []
        cnt = 0
        num_preds = 1
        for line in csv.reader(f, delimiter="\t"):
            title = f"number of predicates: {num_preds}; vectorized no simd"
            if cnt == 0 and (len(line) == 0 or line[0] != title):
                continue
            if cnt < 3:
                cnt += 1
                continue
            if len(line) == 0:
                cnt = 0
                num_preds += 1
                all_hpcs.append(hpcs)
                hpcs = []
                continue
            if len(hpcs) == 0:
                hpcs.append(str(num_preds))
            hpcs.append(line[0])
            if len(hpcs) == 3:
                hpcs.append(str(float(hpcs[1]) / float(hpcs[2])))
            elif len(hpcs) == 6:
                hpcs.append(str(float(hpcs[4]) / float(hpcs[5])))
            elif len(hpcs) == 9:
                hpcs.append(str(float(hpcs[7]) / float(hpcs[8])))
        for hpcs in all_hpcs:
            print("\t".join(hpcs))


if __name__ == '__main__':
    run_logs_predicates()