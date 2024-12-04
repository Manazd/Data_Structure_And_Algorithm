def sieve_find_prime(num):
    prime_numbers = [True for i in range(16000001)]
    p = 2
    while p * p <= 16000001:
        if prime_numbers[p]:
            for i in range(p * p, 16000001, p):
                prime_numbers[i] = False
            prime_numbers[p ** 2] = True
        p += 1
    return multiply_numbers(prime_numbers, num)


def multiply_numbers(prime_numbers, num):
    counter = 0
    result_number = 1
    p = 2
    while counter < num:
        if prime_numbers[p]:
            counter += 1
            result_number *= p
            result_number %= 1000000007
        p += 1
    return result_number


print(sieve_find_prime(int(input())))

