# Polyomino solver

## Usage

Prepare file it have your polyomino information.
Use the following format.
Refer to the `example.in`

$C$: number of grid columns

$N$: number of pieces

$G_\*$: each column of the grid

$Pc_\*$: number of columns each piece

$P$: each column of the piece

```
C N

G_1
G_2
...
G_C

Pc_1
P_1_1
P_l_2
...
P_1_{Pc_1}

...

Pc_N
P_N_1
...
P_N_{Pc_N}
```

Enter the following command, the answer will be output to `out.txt`

```bash
./solve.sh puzzle_info_file
```
