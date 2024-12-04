def merge_sort(numbers):
    if len(numbers) < 2:
        return numbers

    mid = len(numbers) // 2

    left = numbers[:mid]
    right = numbers[mid:]

    left = merge_sort(left)
    right = merge_sort(right)

    i = j = 0
    numbers = []
    while i < len(left) and j < len(right):
        if left[i][0] < right[j][0]:
            numbers += [left[i]]
            i += 1
        else:
            numbers += [right[j]]
            j += 1
    numbers += left[i:] + right[j:]
    return numbers


def main_function(numbers):
    final = [0] * numberOfShops
    n = odd = even = min_distance = 0
    length = len(numbers)
    for i in range(length):
        if i % 2 == 0:
            final[numbers[i][1]] = odd
            min_distance += odd
            odd += numbers[i][0]
        else:
            x = n
            min_distance += x
            n += numbers[i][0]
            even -= numbers[i][0]
            final[numbers[i][1]] = even
    return final, min_distance / length


numberOfShops = int(input())
shopsList = input().split()
shopsList = [int(item) for item in shopsList]
copy = shopsList

shop_and_index = [[0 for i in range(2)] for j in range(numberOfShops)]
for i in range(numberOfShops):
    shop_and_index[i][0], shop_and_index[i][1] = shopsList[i], i
shop_and_index = merge_sort(shop_and_index)
result, m = main_function(shop_and_index)
print('%.7f' % m)
print(*result)