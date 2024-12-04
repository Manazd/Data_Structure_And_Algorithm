def find_max(positions):
    max_distance = positions[0]

    for i in range(len(positions) - 1):
        dif = positions[i + 1] - positions[i]
        if dif > max_distance:
            max_distance = dif

    print(max_distance)


def insert(array, array_len, to_be_inserted):
    i = array_len - 1

    while i >= 0 and array[i] > to_be_inserted:
        array[i + 1] = array[i]
        i -= 1

    array[i + 1] = to_be_inserted
    return array


line1 = list(map(int, input().split()))
cut_positions = list(map(int, input().split()))
n, q = line1[0], line1[1]
cuts = [0]

for j in range(q):
    cuts = insert(cuts, len(cuts) - 1, cut_positions[j])
    cuts.append(n)
    find_max(cuts)