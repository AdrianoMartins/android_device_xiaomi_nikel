LOCAL_PATH := device/jiayu/s3plus_n560a

DEVICE_PACKAGE_OVERLAYS += $(LOCAL_PATH)/overlay

# Device uses high-density artwork where available
PRODUCT_AAPT_CONFIG := normal xhdpi xxhdpi
PRODUCT_AAPT_PREF_CONFIG := xxhdpi

# Recovery allowed devices
TARGET_OTA_ASSERT_DEVICE := s3plus_n560a,S3H

PRODUCT_PACKAGES += \
   libmtk_symbols \
   libstlport

# Lights
PRODUCT_PACKAGES += \
    lights.mt6753

# Audio
PRODUCT_COPY_FILES += \
    $(LOCAL_PATH)/configs/audio/audio_device.xml:system/etc/audio_device.xml \
    $(LOCAL_PATH)/configs/audio/audio_policy_configuration.xml:system/etc/audio_policy_configuration.xml \
    $(LOCAL_PATH)/configs/audio/a2dp_audio_policy_configuration.xml:/system/etc/a2dp_audio_policy_configuration.xml

# Media
PRODUCT_COPY_FILES += \
	$(LOCAL_PATH)/configs/media_codecs.xml:system/etc/media_codecs.xml \
	$(LOCAL_PATH)/configs/media_profiles.xml:system/etc/media_profiles.xml

# Keyboard layout
PRODUCT_COPY_FILES += \
    $(LOCAL_PATH)/configs/mtk-kpd.kl:system/usr/keylayout/mtk-kpd.kl \
    $(LOCAL_PATH)/configs/ACCDET.kl:system/usr/keylayout/ACCDET.kl \
    $(LOCAL_PATH)/configs/AVRCP.kl:system/usr/keylayout/AVRCP.kl

# Ramdisk
PRODUCT_COPY_FILES += \
    $(LOCAL_PATH)/rootdir/factory_init.project.rc:root/factory_init.project.rc \
    $(LOCAL_PATH)/rootdir/factory_init.rc:root/factory_init.rc \
    $(LOCAL_PATH)/rootdir/fstab.mt6735:root/fstab.mt6735 \
    $(LOCAL_PATH)/rootdir/init.modem.rc:root/init.modem.rc \
    $(LOCAL_PATH)/rootdir/init.mt6735.rc:root/init.mt6735.rc \
    $(LOCAL_PATH)/rootdir/init.mt6735.usb.rc:root/init.mt6735.usb.rc \
    $(LOCAL_PATH)/rootdir/meta_init.modem.rc:root/meta_init.modem.rc \
    $(LOCAL_PATH)/rootdir/meta_init.project.rc:root/meta_init.project.rc \
    $(LOCAL_PATH)/rootdir/meta_init.rc:root/meta_init.rc \
    $(LOCAL_PATH)/rootdir/ueventd.mt6735.rc:root/ueventd.mt6735.rc \
    $(LOCAL_PATH)/rootdir/init.recovery.mt6735.rc:root/init.recovery.mt6735.rc

# TWRP
PRODUCT_COPY_FILES += \
    $(LOCAL_PATH)/recovery/etc/twrp.fstab:recovery/root/etc/twrp.fstab

# Thermal
PRODUCT_COPY_FILES += \
    $(LOCAL_PATH)/configs/thermal/.ht120.mtc:system/etc/.tp/.ht120.mtc \
    $(LOCAL_PATH)/configs/thermal/thermal.conf:system/etc/.tp/thermal.conf \
    $(LOCAL_PATH)/configs/thermal/thermal.off.conf:system/etc/.tp/thermal.off.conf \
    $(LOCAL_PATH)/configs/thermal/.thermal_policy_00:system/etc/.tp/.thermal_policy_00

# NFC
PRODUCT_PACKAGES += \
    com.android.nfc_extras \
    libmtknfc_dynamic_load_jni \
    libnfc_mt6605_jni \
    Nfc \
    Tag

PRODUCT_COPY_FILES += \
    frameworks/native/data/etc/android.hardware.nfc.xml:system/etc/permissions/android.hardware.nfc.xml \
    frameworks/native/data/etc/android.hardware.nfc.hce.xml:system/etc/permissions/android.hardware.nfc.hce.xml \
    frameworks/native/data/etc/com.android.nfc_extras.xml:system/etc/permissions/com.android.nfc_extras.xml

# Dalvik/HWUI
$(call inherit-product, frameworks/native/build/phone-xhdpi-2048-dalvik-heap.mk)

# Common stuff
$(call inherit-product, vendor/mad/config/common.mk)

# Vendor
$(call inherit-product, vendor/jiayu/s3plus_n560a/s3plus_n560a-vendor.mk)