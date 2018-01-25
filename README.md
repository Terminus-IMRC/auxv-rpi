# auxv-rpi

Describe `/proc/self/auxv` mainly on Raspberry Pi platforms.


## Building

```
$ make
```


## Running

* Raspberry Pi 1 (BCM2835)

```
HWCAP: JAVA FAST_MULT EDSP VFP
PAGESZ: 4096
CLKTCK: 100
HWCAP2:
PLATFORM: v6l
```

* Raspberry Pi 2 (BCM2836)

```
HWCAP: FAST_MULT EDSP VFP VFPv3 VFPv4 VFPD32 NEON IDIVA IDIVT
PAGESZ: 4096
CLKTCK: 100
HWCAP2:
PLATFORM: v7l
```

* Raspberry Pi 3 (BCM2837)

```
HWCAP: FAST_MULT EDSP VFP VFPv3 VFPv4 VFPD32 NEON IDIVA IDIVT
PAGESZ: 4096
CLKTCK: 100
HWCAP2: CRC32
PLATFORM: v7l
```
