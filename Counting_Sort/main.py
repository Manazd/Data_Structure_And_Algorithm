def counting_sort_giant(my_list):
    max_value = 1 + max([i for i in giant_list])
    storing_array = [[] for i in range(max_value)]

    for i in range(len(my_list)):
        storing_array[my_list[i][0]].append(my_list[i])

    result_arr = []
    for arr in storing_array:
        for i in range(len(arr)):
            result_arr.append(arr[i][1])

    return result_arr


number = int(input())
giant_list = list(map(int, input().split()))

indexes = [[0 for i in range(2)] for j in range(number)]
for i in range(number):
    indexes[i][0], indexes[i][1] = giant_list[i], i + 1

sorted_giant = counting_sort_giant(indexes)
print(*sorted_giant)
