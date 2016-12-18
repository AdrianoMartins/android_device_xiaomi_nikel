# Wifi
PRODUCT_PACKAGES += \
    lib_driver_cmd_mt66xx \
    libwpa_client \
    hostapd \
    wpa_supplicant

PRODUCT_COPY_FILES += \
    device/xiaomi/nikel/configs/etc/wifi/wpa_supplicant.conf:system/etc/wifi/wpa_supplicant.conf \
    device/xiaomi/nikel/configs/etc/wifi/wpa_supplicant_overlay.conf:system/etc/wifi/wpa_supplicant_overlay.conf \
    device/xiaomi/nikel/configs/etc/wifi/p2p_supplicant_overlay.conf:system/etc/wifi/p2p_supplicant_overlay.conf