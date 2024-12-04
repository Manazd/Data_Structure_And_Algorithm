def find_match(table, word, x, y, n, m, index):
    if len(word) == index:
        return True
    if x < 0 or y < 0 or x >= n or y >= m:
        return False
    if word[index] == table[x][y]:
        tmp = table[x][y]
        table[x][y] = '-'
        result = (find_match(table, word, x - 1, y, n, m, index + 1) or
                  find_match(table, word, x + 1, y, n, m, index + 1) or
                  find_match(table, word, x, y - 1, n, m, index + 1) or
                  find_match(table, word, x, y + 1, n, m, index + 1))
        table[x][y] = tmp
        return result
    else:
        return False


n, m = [int(x) for x in input().split()]
arr = [[]] * n
for i in range(n):
    arr[i] = list(input())
k = int(input())
for i in range(k):
    word = list(input())
    flag = False
    for j in range(n):
        for s in range(m):
            if arr[j][s] == word[0]:
                if find_match(arr, word, j, s, n, m, 0):
                    print(*word, sep='')
                    flag = True
                    break
        if flag:
            break
