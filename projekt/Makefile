URL = https://downloads.openwrt.org/releases/21.02.1/targets/bcm27xx/bcm2711/openwrt-sdk-21.02.1-bcm27xx-bcm2711_gcc-8.4.0_musl.Linux-x86_64.tar.xz
ARCHIVE_NAME = openwrt-sdk-21.02.1-bcm27xx-bcm2711_gcc-8.4.0_musl.Linux-x86_64.tar.xz
DIR_NAME = openwrt-sdk-21.02.1-bcm27xx-bcm2711_gcc-8.4.0_musl.Linux-x86_64

package: openwrt-sdk
	cd openwrt-sdk && ./scripts/feeds update skps
	cd openwrt-sdk && ./scripts/feeds install -p skps -a
	make -j1 V=s -C openwrt-sdk package/server/compile
	cp -f ./openwrt-sdk/bin/packages/aarch*/skps/server*.ipk -t .

$(ARCHIVE_NAME):
	wget "$(URL)"

openwrt-sdk: $(ARCHIVE_NAME)
	tar xf "$(ARCHIVE_NAME)"
	mv "$(DIR_NAME)" openwrt-sdk
	make -C openwrt-sdk defconfig
	cp -f openwrt-sdk-template/feeds.conf.default openwrt-sdk
	cd openwrt-sdk && ./scripts/feeds update skps
	cd openwrt-sdk && ./scripts/feeds install -p skps -a
	cp -f openwrt-sdk-template/.config openwrt-sdk
