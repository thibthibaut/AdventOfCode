

initial_state = {
    1: 175,
    2: 33,
    3: 32,
    4: 28,
    5: 32,
}

precomputed_for_one_fish = {
    248: 3053201612,
    249: 3369186778,
    250: 3649885552,
    251: 3989468462,
    252: 4368232009,
    253: 4726100874,
    254: 5217223242,
    255: 5617089148,
    256: 6206821033,
}


grand_total = 0
for i in range(1, 6):
    total = initial_state[i]*precomputed_for_one_fish[257-i]
    grand_total += total


print(grand_total)
