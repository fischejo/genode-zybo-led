# Installation

## OS Requirements
Install packages in Ubuntu 16.04
```bash
sudo apt-get install -qq libncurses5-dev texinfo autogen autoconf2.64 g++ libexpat1-dev \
		     flex bison gperf cmake libxml2-dev libtool zlib1g-dev libglib2.0-dev \
		     make pkg-config gawk subversion expect git libxml2-utils syslinux \
		     xsltproc yasm iasl lynx unzip qemu tftpd-hpa isc-dhcp-server
```

## Genode Toolchain
Install genode toolchain in `/usr/local/genode-gcc`
```bash
sudo su
cd /
wget -qO- https://nextcloud.os.in.tum.de/s/9idiw8BLbuwp35z/download | tar xj -C .
```

## Genode Repositories

### genode
```bash
git clone https://github.com/argos-research/genode.git
cd genode
git checkout focnados-1604
cd ..
```

## Prepare Ports
```bash
./genode/tool/ports/prepare_port focnados
./genode/tool/ports/prepare_port libc
./genode/tool/ports/prepare_port lwip
./genode/tool/ports/prepare_port stdcxx
./genode/tool/ports/prepare_port dde_linux
```

# Prepare, Build & Run 

## Create Build Directory
```bash
genode/tool/create_builddir focnados_zybo BUILD_DIR=./build_zybo
```

## Update `./build_zybo/etc/build.conf`
```bash
cat <<'EOF' >> ./build_zybo/etc/build.conf
REPOSITORIES += $(GENODE_DIR)/repos/libports
REPOSITORIES += $(GENODE_DIR)/repos/dde_linux
REPOSITORIES += $(GENODE_DIR)/repos/world
REPOSITORIES += $(GENODE_DIR)/../genode-world
REPOSITORIES += $(GENODE_DIR)/../genode-led
EOF
```

## Compile
```bash
make -C build_zybo/ run/led
```

## Prepare SD-Card and U-Boot

1. Creating a SD-Card for the Zybo Board is documented [here](https://argos-research.github.io/documentation/u-boot.html#digilent-zybo).
2. Copy Genode Image `build_zybo/var/run/led/image.elf` to SD-Card.
3. Copy FPGA Bitstream
   `zybo-gpio-led/vivado-2018.2/led/led.runs/impl_1/design_1_wrapper.bit`
   to SD-Card.
4. Connect to Serial UART   
5. Boot into U-Boot
6. Load `design_1_wrapper.bit` into FPGA
   ```
   set env "loadbit_addr 0x100000"
   fatload mmc 0:1 ${loadbit_addr} design_1_wrapper.bit; fpga loadb 0 ${loadbit_addr} 9000000
   ```
7. Load and Boot Genode
   ```
   load mmc 0:1 ${scriptaddr} image.elf; bootelf ${scriptaddr}"
   ```
8. Genode should boot and the LEDs start blinking.
