import matplotlib.pyplot as plt
dimensions = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 20, 50, 80, 100, 150, 200, 300, 450, 600, 750, 900]
serial_time = [0.001, 0.004, 0.004, 0.005, 0.007, 0.009, 0.012, 0.009, 0.014, 0.014, 0.029, 0.086, 0.107, 0.124, 0.308, 0.283, 0.51, 0.728, 0.913, 1.552, 1.202]
parallel_1d = [0.005, 0.004, 0.005, 0.0052, 0.0058, 0.003, 0.004, 0.005, 0.006, 0.004, 0.003, 0.007, 0.006, 0.004, 0.005, 0.006, 0.005, 0.0086, 0.006, 0.008, 0.006]
parallel_2d = [0.076, 0.097, 0.109, 0.12, 0.136, 0.148, 0.167, 0.191, 0.196, 0.228, 0.005, 0.006, 0.004, 0.005, 0.004, 0.007, 0.0075, 0.009, 0.008, 0.007, 0.008]

plt.figure(figsize=(10, 8))
plt.plot(dimensions, serial_time, marker='o', label='Sequential time', linewidth=2)
plt.plot(dimensions, parallel_1d, marker='s', label='1D Parallel Time', linewidth=2)
plt.plot(dimensions, parallel_2d, marker='^', label='2D Parallel time', linewidth=2)

plt.xlabel("Matrix Dimension (n)", fontsize=12)
plt.ylabel("Execution Time (seconds)", fontsize=12)
plt.title("Matrix-Vector Multiplication Performance", fontsize=14)
plt.legend()
plt.grid(True, linestyle='--', alpha=0.6)

plt.xticks(dimensions, rotation=45, ha='right')
plt.tight_layout()
plt.show()