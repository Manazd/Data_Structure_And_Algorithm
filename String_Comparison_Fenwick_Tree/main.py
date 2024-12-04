def check_commands():
    for command in commands_list:
        if command[0] == '0':
            result = list(map(int, command))
            compare(result)
        else:
            change(command)


def convert_to_hash(string):
    str_len = len(string)
    h = [0] * str_len
    for j in range(str_len):
        h[j] = (ord(string[j]) * powers[j]) % m
    hashes.append(h)
    trees.append(create_fenwick_tree(h, str_len))


def create_fenwick_tree(array, n):
    tree = [0] * (n + 1)
    for j in range(n):
        update_bit(tree, n, j, array[j])
    return tree


def update_bit(tree, n, j, v):
    j += 1
    while j <= n:
        tree[j] = (tree[j] + v) % m
        j += j & (-j)


def compare(command):
    string1 = trees[command[1] - 1]
    string2 = trees[command[2] - 1]
    start1 = command[3] - 1
    start2 = command[4] - 1
    end = command[5] - 1
    sub_str1 = (get_sum(string1, start1 + end) - get_sum(string1, start1 - 1)) % m
    sub_str2 = (get_sum(string2, start2 + end) - get_sum(string2, start2 - 1)) % m
    if start1 <= start2:
        sub_str1 = (sub_str1 * powers[start2 - start1]) % m
    else:
        sub_str2 = (sub_str2 * powers[start1 - start2]) % m

    if sub_str1 == sub_str2:
        print('YES')
    else:
        print('NO')


def get_sum(tree, j):
    s = 0
    j += 1
    while j > 0:
        s = (s + tree[j]) % m
        j -= j & (-j)
    return s


def change(command):
    string = trees[int(command[1]) - 1]
    index = int(command[2]) - 1
    new_hash = (ord(command[3]) * powers[index]) % m
    old_hash = hashes[int(command[1]) - 1][index]
    f = new_hash - old_hash
    update_bit(string, len(hashes[int(command[1])-1]), index, f)


n_k = list(map(int, input().split()))
strings_num, commands_num = n_k[0], n_k[1]
commands_list = []
hashes = []
powers = [0] * 500000
power = 1
trees = []
m = (10**9) + 7


for i in range(500000):
    powers[i] = power
    power = (power * 31) % m

for i in range(strings_num):
    line = input()
    if line:
        convert_to_hash(line)
    else:
        break

for i in range(commands_num):
    line = list(input().split())
    if line:
        commands_list.append(line)
    else:
        break

check_commands()