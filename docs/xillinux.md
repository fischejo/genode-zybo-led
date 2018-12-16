# Pay attention
Keep in mind, these instructions are neither bullet-proofed nor complete. It is
just a short guide, how I did it.

# Prepare Xillinux on SD-Card
Please follow the installation documentation of [Xillinux](http://xillybus.com/xillinux).

```bash
wget http://xillybus.com/downloads/xillinux-2.0.img.gz
gunzip xillinux-2.0.img.gz
# replace /dev/mmcblk0 with your USB device
dd if=xillinux-2.0.img of=/dev/mmcblk0 bs=512
```
```bash
wget http://xillybus.com/downloads/xillinux-eval-zybo-2.0c.zip
unzip xillinux-eval-zybo-2.0c.zip
# we assume that your USB stick is /dev/mmcblk0
sudo mkdir /mnt/sdcard
sudo mount /dev/mmcblk0p1 /mnt/sdcard
sudo cp xillinux-zybo/xillinux-eval-zybo-2.0c/bootfiles/boot.bin /mnt/sdcard/
sudo cp xillinux-zybo/xillinux-eval-zybo-2.0c/bootfiles/devicetree.dtb /mnt/sdcard/
```

# Copy FPGA Bitstream to Sd-Card
```bash
# we assume that the first partition of the sd-card is mounted at /mnt/sdcard
cp zybo-gpio-led/vivado-2018.2/led/led.runs/impl_1/design_1_wrapper.bit /mnt/sdcard/xillydemo.bit
```

# Prepare Xillinux
Python is installed on Xillinux, but the `gpio-led.py` need to be copied to the
SD-Card. This can be done manually. In the following, an SSH server is installed
and the `led.py` is copied with `scp`.

Boot Xillinux and login via Serial Console. 
```bash
# install ssh server
sudo apt-get install openssh-server

# set a password for root user, otherwise you can not ssh-login as root.
sudo su
chpasswd
```

Copy `xillinux/gpio-led.py` to Xillinux
```bash
scp xillinux/gpio-led.py root@<IP_of_your_Zybo>:~
```

Now login via ssh and execute the python script.
```bash
ssh root@<IP_of_your_Zybo>
> python gpio-led.py
```

The led should start blinking.

# References
* [Zybo-Quickstart by Lauri](https://lauri.xn--vsandi-pxa.com/hdl/zynq/zybo-quickstart.html)
* [Xillinux Getting-Started for Zync-7000](http://xillybus.com/downloads/doc/xillybus_getting_started_zynq.pdf)

