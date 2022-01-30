min_energy_seam=0
energies = [[24,      22,      30,      15,      18,      19],
            [12,      23,      15,      23,      10,     15],
            [11,      13,      22,      13,      21,      14],
            [13,      15,      17,      28,      19,      21],
            [17,      17,      7,       27,      20,      19]]


prevrow = list(energies[0])
for y in range(1, len(energies)):
    energy_row = energies[y]
    seam_energy_row = []
    
    for x, pixel_energy in enumerate(energy_row):
        x_left = max(x - 1, 0)
        x_right = min(x + 1, len(energy_row) - 1)
        x_range = range(x_left, x_right + 1)

        min_energy_seam = pixel_energy + (min(prevrow[x_i] for x_i in x_range))
        seam_energy_row.append(min_energy_seam)
    prevrow = seam_energy_row
print(min(j for j in prevrow))