include $(TOPDIR)/rules.mk
 
PKG_NAME:=server
PKG_VERSION:=1.0
PKG_RELEASE:=1
 
CMAKE_INSTALL:=1
CMAKE_BINARY_SUBDIR:=.

include $(INCLUDE_DIR)/package.mk
include $(INCLUDE_DIR)/cmake.mk

define Package/server
	CATEGORY:=custom
	TITLE:=Server
	DEPENDS:=+libstdcpp
endef

define Package/server/install
	$(INSTALL_DIR) $(1)/usr/bin
	$(INSTALL_BIN) $(PKG_INSTALL_DIR)/usr/bin/server $(1)/usr/bin
endef

$(eval $(call BuildPackage,server))
