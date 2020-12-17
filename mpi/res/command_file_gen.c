#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    FILE * f = fopen(argv[1], "w");
    fprintf(f, "# @ job_type = bluegene\n# @ class = large\n# @ wall_clock_limit = 00:05:00\n# @ bg_size = %s\n# @ queue\n/bgsys/drivers/ppcfloor/bin/mpirun ../adi_3d %s %s\n", argv[2], argv[3], argv[4]);
    fclose(f);
}
