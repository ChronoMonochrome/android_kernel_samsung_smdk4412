SRC=/media/system/root/LOS16/kernel/samsung/smdk4412
KERNEL_OUT=/media/system/root/LOS16/out/target/product/i9300/obj/KERNEL_OBJ
ANDROID_OUT=/media/system/root/LOS16/out
GCC=/media/system1/root/CM14/prebuilts/gcc/linux-x86/arm/arm-eabi-4.8/bin/arm-eabi-
RAMDISK=$SRC/ramdisk
DTS=exynos4412-trats2
#GCC=/media/system/root/LOS15/prebuilts/gcc/linux-x86/arm/arm-eabi-4.8/bin/arm-eabi-
#GCC=/media/system/root/LOS16/prebuilts/gcc/linux-x86/arm/arm-linux-androideabi-4.9/bin/arm-linux-androideabi-
#GCC=/media/system/root/LOS15/prebuilts/gcc/linux-x86/arm/arm-eabi-7.4/bin/arm-linux-gnueabi-
#GCC=/media/system/root/LOS16/linaro-7.4/bin/arm-linux-gnueabihf-
MKBOOTFS=/media/system/root/LOS16/out/host/linux-x86/bin/mkbootfs
LZMA=/media/system/root/buildroot/output/host/bin/lzma

#$ANDROID_OUT/host/linux-x86/bin/mkbootfs -d $ANDROID_OUT/target/product/i9300/system      \
#     $ANDROID_OUT/target/product/i9300/root_los16  | $ANDROID_OUT/host/linux-x86/bin/minigzip > \
#     $ANDROID_OUT/target/product/i9300/ramdisk.img

#$ANDROID_OUT/host/linux-x86/bin/mkbootfs $ANDROID_OUT/target/product/i9300/1  | $ANDROID_OUT/host/linux-x86/bin/minigzip > \
#     $ANDROID_OUT/target/product/i9300/ramdisk.img

#make -j8  CFLAGS_MODULE="-fno-pic" -C $SRC O=$KERNEL_OUT ARCH=arm CROSS_COMPILE="`which ccache` $GCC" ubuntu_i9300_defconfig
make -j8  CFLAGS_MODULE="-fno-pic" -C $SRC O=$KERNEL_OUT ARCH=arm CROSS_COMPILE="`which ccache` $GCC" lineageos_i9300_defconfig
make -j8 -k  CFLAGS_MODULE="-fno-pic" -C $SRC O=$KERNEL_OUT ARCH=arm CROSS_COMPILE="`which ccache` $GCC" zImage 
make -j8 -k  CFLAGS_MODULE="-fno-pic" -C $SRC O=$KERNEL_OUT ARCH=arm CROSS_COMPILE="`which ccache` $GCC" dtbs
make -j8 -k  CFLAGS_MODULE="-fno-pic" -C $SRC O=$KERNEL_OUT ARCH=arm CROSS_COMPILE="`which ccache` $GCC" modules

cp $KERNEL_OUT/drivers/usb/gadget/*.ko $RAMDISK/lib/modules/3.10.0/kernel/drivers/usb/gadget/
WD=$PWD
cd $SRC
#$MKBOOTFS $RAMDISK > $SRC/ramdisk.cpio
#$LZMA -9 -c $SRC/ramdisk.cpio > $SRC/ramdisk.cpio.lzma
rm $SRC/ramdisk.cpio.lzma
bash build_ramdisk.sh

#  --ramdisk /media/system1/root/CM13/out/target/product/i9300/ramdisk.img \
#  --ramdisk /media/system1/root/CM14/out/target/product/i9300/los16.img \
#  --ramdisk /media/system1/root/CM14/out/target/product/i9300/ramdisk.img \

#  --ramdisk /media/system/root/LOS16/out/target/product/i9300/ramdisk.img \

cat $KERNEL_OUT/arch/arm/boot/zImage $KERNEL_OUT/arch/arm/boot/dts/$DTS.dtb > $ANDROID_OUT/target/product/i9300/kernel

#  --ramdisk /media/system/root/LOS16/out/target/product/i9300/ramdisk.img \

#  --kernel $ANDROID_OUT/target/product/i9300/kernel \
#  --ramdisk $SRC/ramdisk.cpio.lzma \
#  --kernel /media/system/root/buildroot/output/images/zImage.exynos4412-trats2 \

$ANDROID_OUT/host/linux-x86/bin/mkbootimg  \
  --kernel $ANDROID_OUT/target/product/i9300/kernel \
  --ramdisk $SRC/ramdisk.cpio.lzma \
  --base 0x40000000 \
  --pagesize 2048 \
  --cmdline "console=ttySAC2,115200 buildvariant=userdebug" \
  --os_version 7.1.2 \
  --os_patch_level 2018-09-05  \
  --output $ANDROID_OUT/target/product/i9300/boot.img

size=$(for i in $ANDROID_OUT/target/product/i9300/boot.img; do stat --format "%s" "$i" | tr -d '\n'; echo +; done; echo 0);
total=$(( $( echo "$size" ) ));
printname=$(echo -n "$ANDROID_OUT/target/product/i9300/boot.img" | tr " " +);
img_blocksize=4224;
twoblocks=$((img_blocksize * 2)); onepct=$(((((8650752 / 100) - 1) / img_blocksize + 1) * img_blocksize));
reserve=$((twoblocks > onepct ? twoblocks : onepct));
maxsize=$((8650752 - reserve));

echo "$printname maxsize=$maxsize blocksize=$img_blocksize total=$total reserve=$reserve";

if [ "$total" -gt "$maxsize" ]; then 
  echo "error: $printname too large ($total > [8650752 - $reserve])"; false;
elif [ "$total" -gt $((maxsize - 32768)) ]; then
  echo "WARNING: $printname approaching size limit ($total now; limit $maxsize)";
fi
