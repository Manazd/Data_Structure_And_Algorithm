def calculate(n):
    counter = 0
    for i in range(2, int(n ** (1/3) + 1)):
        s = i ** 3
        counter += n // s
    return counter


def binary_search(m):
    left = 8
    right = 8 * m + 1

    while left <= right:
        mid = left + (right - left) // 2
        result = calculate(mid)
        if result == m and (mid == 8 or m > calculate(mid - 1)):
            return mid

        elif result < m:
            left = mid + 1

        else:
            right = mid - 1

    return -1


m = int(input())
print(binary_search(m))