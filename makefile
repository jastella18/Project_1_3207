all: cpuinfo meminfo processes

meminfo: meminfo.c
	gcc -o meminfo meminfo.c

cpuinfo: cpuinfo.c
	gcc -o cpuinfo cpuinfo.c

processes: ps.c
	gcc -o ps ps.c

clean:
	rm -f meminfo cpuinfo ps