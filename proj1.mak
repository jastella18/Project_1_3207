all: cpuinfo meminfo processes

cpuinfo/meminfo: memcpu.c
    gcc -o memcpuinfo memcpu.c


processes: ps.c
    gcc -o ps ps.c

clean:
    rm -f memcpuinfo ps