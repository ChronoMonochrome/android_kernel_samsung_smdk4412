set -x

REBUILD_RAMDISK=1

if [ $REBUILD_RAMDISK -eq 1 ] ; then
rm -rf ramdisk
cp rootfs.cpio.lzma ramdisk.cpio.lzma
mkdir -p ramdisk
cp ramdisk.cpio ramdisk
cd ramdisk
cpio -idv < ramdisk.cpio
rm ramdisk.cpio
cd ..
fi


BUILDROOT=/media/system/root/buildroot
rm $BUILDROOT/output/build/_fakeroot.fs

echo '#!/bin/sh' > $BUILDROOT/output/build/_fakeroot.fs
echo "set -e" >> $BUILDROOT/output/build/_fakeroot.fs
echo "chown -h -R 0:0 $BUILDROOT/output/target" >> $BUILDROOT/output/build/_fakeroot.fs
printf '   \n' >> $BUILDROOT/output/build/_users_table.txt
$BUILDROOT/support/scripts/mkusers $BUILDROOT/output/build/_users_table.txt $BUILDROOT/output/target >> $BUILDROOT/output/build/_fakeroot.fs
cat $BUILDROOT/system/device_table.txt > $BUILDROOT/output/build/_device_table.txt
printf '        /bin/busybox                     f 4755 0  0 - - - - -\n /dev/console c 622 0 0 5 1 - - -\n\n' >> $BUILDROOT/output/build/_device_table.txt
echo "$BUILDROOT/output/host/bin/makedevs -d $BUILDROOT/output/build/_device_table.txt $BUILDROOT/output/target" >> $BUILDROOT/output/build/_fakeroot.fs
printf "        cd  /media/system/root/LOS16/kernel/samsung/smdk4412/ramdisk && find . | cpio --quiet -o -H newc > $BUILDROOT/output/images/rootfs.cpio" >> $BUILDROOT/output/build/_fakeroot.fs
printf '\n' >> $BUILDROOT/output/build/_fakeroot.fs
chmod a+x $BUILDROOT/output/build/_fakeroot.fs
$BUILDROOT/output/host/bin/fakeroot -- $BUILDROOT/output/build/_fakeroot.fs
rootdir=$BUILDROOT/output/target
table='$BUILDROOT/output/build/_device_table.txt'
/usr/bin/install -m 0644 $BUILDROOT/support/misc/target-dir-warning.txt $BUILDROOT/output/target/THIS_IS_NOT_YOUR_ROOT_FILESYSTEM
$BUILDROOT/output/host/bin/lzma -9 -c $BUILDROOT/output/images/rootfs.cpio > ramdisk.cpio.lzma
