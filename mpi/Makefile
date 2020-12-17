all: adi_3d
adi_3d: adi_3d.c
	mpicc -o adi_3d adi_3d.c -std=c11 -fsanitize=address
report_bg: adi_3d
	./report_script_bg.sh
report_ps: adi_3d
	./report_script_ps.sh
collect:
	./collect.sh
