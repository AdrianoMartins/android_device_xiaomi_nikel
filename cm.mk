# Release Name
PRODUCT_RELEASE_NAME := Redmi Note 4

# Inherit some common CM stuff.
$(call inherit-product, vendor/cm/config/common_full_phone.mk)

# Inherit device configuration
$(call inherit-product, device/xiaomi/nikel/full_nikel.mk)

## Device identifier. This must come after all inclusions
PRODUCT_DEVICE := nikel
PRODUCT_NAME := cm_nikel
PRODUCT_BRAND := Xiaomi
PRODUCT_MODEL := Redmi Note 4
PRODUCT_MANUFACTURER := Xiaomi
