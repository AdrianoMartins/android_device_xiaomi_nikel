$(call inherit-product, device/jiayu/s3plus_n560a/device_s3plus_n560a.mk)

# Inherit some common CM stuff.
$(call inherit-product, vendor/cm/config/common_full_phone.mk)

## Device identifier. This must come after all inclusions
PRODUCT_DEVICE := s3plus_n560a
PRODUCT_NAME := cm_s3plus_n560a
PRODUCT_BRAND := Jiayu
PRODUCT_MODEL := S3+
PRODUCT_MANUFACTURER := Jiayu
