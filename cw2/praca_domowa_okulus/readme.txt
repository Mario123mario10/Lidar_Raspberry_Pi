Obraz został pobrany z:
https://downloads.openwrt.org/releases/19.07.3/targets/armvirt/64/

Zgodnie z:
https://openwrt.org/docs/guide-user/virtualization/qemu#openwrt_in_qemu_aarch64

Skrypt run.sh uruchamia maszynę wirtualną. Port 80 jest udostępniony jako
8888, dzięki czemu można używać LuCI.

/etc/config/network lan został zmieniony na:
```
config interface 'lan'
	option ifname 'eth0'
	option proto 'dhcp'
```
zgodnie z instrukcją z wykładu, tak żeby maszyna miała dostęp do internetu.

Plików openwrt-19.07.3-armvirt-64-Image i openwrt-19.07.3-armvirt-64-root.ext4
nie umieściłem w repozytorium ze względu na rozmiar.

Kod do generowania fal znajduje się w katalogu wave, pliki
wave/zm-czestotliwosc.py i wave/zm-wypelnienie.py. Fale wyświetlają się w
pyplocie, nie wiedziałem jednak jak odpowiednio to zrealizować w maszynie
wirtualnej OpenWRT.
