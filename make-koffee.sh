#!/bin/bash

VERSION=0.5
DEFCONFIG=
TOOLCHAIN=
KCONFIG=false
CUST_CONF=no
BUILD_NUMBER=
DEVICE=UNKNOWN
KCONF_REPLACE=false
KERNEL_NAME="desktop-gnulinux"
BOEFFLA_VERSION=""
SKIP_MODULES=true
DONTPACK=false
USER=$USER
DATE=`date`
BUILD_PATH=`pwd`
CLEAN=false


usage() {
	echo "Koffee build script v$VERSION"
	echo `date`
	echo "Written by A\$teroid <acroreiser@gmail.com>"
	echo ""
    echo "Usage:"
    echo ""
	echo "make-koffee.sh [-d/-D/-O <file>] [-K] [-U <user>] [-N <BUILD_NUMBER>] [-k] [-R] -t <toolchain_prefix> -d <defconfig>"
	echo ""
	echo "Main options:"
	echo "	-K 			call Kconfig (use only with ready config!)"
	echo "	-d 			defconfig for the kernel. Will try to use already generated .config if not specified"
	echo "	-S 			set device codename (m0 for i9300 or t03g for n7100)"
	echo "	-O <file> 			external/other defconfig."
	echo "	-t <toolchain_prefix> 			toolchain prefix"
	echo ""
	echo "Extra options:"
	echo "	-j <number_of_cpus> 			set number of CPUs to use"
	echo "	-k 			make only zImage, do not pack into zip"
	echo "	-C 			cleanup before building"
	echo "	-R 			save your arguments to reuse (just run make-koffee.sh on next builds)"
	echo "	-U <username> 			set build user"
	echo "	-N <release_number> 			set release number"
	echo "	-v 			show build script version"
	echo "	-h 			show this help"
	
}

prepare() 
{
 	make -j4 clean
}

make_config() 
{
	if [ "$CUST_CONF" != "no" ]; then
		cp $CUST_CONF `pwd`/.config
		echo "Using custom configuration from $CUST_CONF"
		DEFCONFIG=custom
	else
		if [ ! -f "`pwd`/.config" ] || [ "$KCONF_REPLACE" = true ]; then
			make ARCH=arm $JOBS $DEFCONFIG &>/dev/null
		fi
	fi
	if [ "$KCONFIG" = "true" ]; then
		make ARCH=arm $JOBS menuconfig
	fi
}

build_kernel()
{
	make ARCH=arm KBUILD_BUILD_VERSION=$BUILD_NUMBER $JOBS KBUILD_BUILD_USER=$USER CROSS_COMPILE=$TOOLCHAIN zImage
	if [ $? -eq 0 ]; then
		return 0
	else
		return 1
	fi
}

build_modules()
{
	make ARCH=arm KBUILD_BUILD_VERSION=$BUILD_NUMBER $JOBS KBUILD_BUILD_USER=$USER CROSS_COMPILE=$TOOLCHAIN modules
	if [ $? -eq 0 ]; then
		return 0
	else
		return 1
	fi
}

make_flashable()
{

	mkdir -p $REPACK_PATH
	# copy anykernel template over
	if [ "$DEVICE" == "m0" ]; then
		cp -R $BUILD_PATH/anykernel_boeffla-i9300/* $REPACK_PATH
	else
		if [ "$DEVICE" == "t03g" ]; then
			cp -R $BUILD_PATH/anykernel_boeffla-n7100/* $REPACK_PATH
		else
			echo "Attempt to create zip for unknown device. Aborting..."
			exit 0
		fi
	fi

	cd $REPACK_PATH
	# delete placeholder files
	find . -name placeholder -delete

	# copy kernel image
	cp $BUILD_PATH/arch/arm/boot/zImage $REPACK_PATH/zImage

	if [ "$SKIP_MODULES" = "false" ]; then
	{
		# copy modules to either modules folder (CM and derivates) or directly in ramdisk (Samsung stock)
		MODULES_PATH=$REPACK_PATH/modules

		mkdir -p $MODULES_PATH

		# copy generated modules
		find $BUILD_PATH -name '*.ko' -exec cp -av {} $MODULES_PATH \;

		# set module permissions
		chmod 0644 $MODULES_PATH/*

		# strip modules

		${TOOLCHAIN}strip --strip-unneeded $MODULES_PATH/*

	} 2>/dev/null
	
	fi
	# replace variables in anykernel script
	cd $REPACK_PATH
	KERNELNAME="Flashing Koffee (NR)"
	sed -i "s;###kernelname###;'${KERNELNAME}';" META-INF/com/google/android/update-binary;
	COPYRIGHT=$(echo '(c) A\$teroid × ChronoMonochrome × Lord Boeffla, 2019')
	sed -i "s;###copyright###;${COPYRIGHT};" META-INF/com/google/android/update-binary;
	BUILDINFO="Release ${BUILD_NUMBER}, $DATE"
	sed -i "s;###buildinfo###;${BUILDINFO};" META-INF/com/google/android/update-binary;
	SOURCECODE="Official source code:  https://github.com/acroreiser/Koffee"
	sed -i "s;###sourcecode###;${SOURCECODE};" META-INF/com/google/android/update-binary;


	# create zip file
	zip -r9 ${KERNEL_NAME}${BOEFFLA_VERSION}r${BUILD_NUMBER}.zip * -x ${KERNEL_NAME}${BOEFFLA_VERSION}r${BUILD_NUMBER}.zip

	# sign recovery zip if there are keys available
	if [ -f "$BUILD_PATH/tools_boeffla/testkey.x509.pem" ]; then
		java -jar $BUILD_PATH/tools_boeffla/signapk.jar -w $BUILD_PATH/tools_boeffla/testkey.x509.pem $BUILD_PATH/tools_boeffla/testkey.pk8 ${KERNEL_NAME}${BOEFFLA_VERSION}r${BUILD_NUMBER}.zip ${KERNEL_NAME}${BOEFFLA_VERSION}r${BUILD_NUMBER}-signed.zip
		cp ${KERNEL_NAME}${BOEFFLA_VERSION}r${BUILD_NUMBER}-signed.zip $BUILD_PATH/${KERNEL_NAME}${BOEFFLA_VERSION}r${BUILD_NUMBER}-${DEVICE}-signed.zip
		md5sum $BUILD_PATH/${KERNEL_NAME}${BOEFFLA_VERSION}r${BUILD_NUMBER}-${DEVICE}-signed.zip > $BUILD_PATH/${KERNEL_NAME}${BOEFFLA_VERSION}r${BUILD_NUMBER}-${DEVICE}-signed.zip.md5
	else
		cp ${KERNEL_NAME}${BOEFFLA_VERSION}r${BUILD_NUMBER}.zip $BUILD_PATH/${KERNEL_NAME}${BOEFFLA_VERSION}r${BUILD_NUMBER}-${DEVICE}.zip
		md5sum $BUILD_PATH/${KERNEL_NAME}${BOEFFLA_VERSION}r${BUILD_NUMBER}-${DEVICE}.zip > $BUILD_PATH/${KERNEL_NAME}${BOEFFLA_VERSION}r${BUILD_NUMBER}-${DEVICE}.zip.md5
	fi



	cd $BUILD_PATH
	rm -fr .tmpzip
	return 0
}

# Pre

while getopts "hvO:j:Kd:kB:S:N:CU:t:" opt
do
case $opt in
	h) usage; exit 0;;
	v) echo $VERSION; exit 0;;
	t) TOOLCHAIN=$OPTARG;;
	j) THREADS=$OPTARG;;
	O) CUST_CONF=$OPTARG; DEFCONFIG=custom; KCONF_REPLACE=true;;
	C) CLEAN=true;;
	N) BUILD_NUMBER=$OPTARG;;
	S) DEVICE=$OPTARG;;
	K) KCONFIG=true;;
	k) DONTPACK=true;;
	d) DEFCONFIG="$OPTARG"; KCONF_REPLACE=true;;
	U) USER=$OPTARG;;
	*) usage; exit 0;;
esac
done

if [ -z $THREADS ]; then
	JOBS="-j1"
	THREADS=1
else
	JOBS="-j$THREADS"
fi

if [ -d "`pwd`/.tmpzip" ]; then
	rm -fr "`pwd`/.tmpzip"
fi
REPACK_PATH=`pwd`/.tmpzip

# ENTRY POINT
echo "Koffee build script v$VERSION"
echo $DATE

if [ "$DEFCONFIG" == "" ];
then
	if [ ! -f "$BUILD_PATH/.config" ]; then
		echo "FATAL: No config specified!" 
		echo "*** BUILD FAILED ***"
		exit 1 
	fi
	DEFCONFIG=".config"
fi

if [ "$DEFCONFIG" == "lineageos_i9300_defconfig" ]; then
	DEVICE="m0"
fi
 
if [ "$DEFCONFIG" == "lineageos_n7100_defconfig" ]; then
	DEVICE="t03g"
fi

if [ -z $TOOLCHAIN ]; then
	echo "FATAL: No toolchain prefix specified!" 
	echo "*** BUILD FAILED ***"
	exit 1
fi

if [ "$CLEAN" = "true" ]; then
	prepare &>/dev/null
fi 
if [ "$DEFCONFIG" != ".config" ] || [ "$KCONFIG" == "true" ]; then
	make_config
fi
TVERSION=$(${TOOLCHAIN}gcc --version | grep gcc)

if [ -z $BUILD_NUMBER ]; then 
	if [ -f "`pwd`/.version" ]; then
		BVERN=$(cat `pwd`/.version)
	else
		BVERN=1
	fi
else
	BVERN=$BUILD_NUMBER
fi

if [ $? -eq 0 ]; then
	echo "--------------------------------------"
	echo "| Build  date:	$DATE"
	echo "| Version:	$BOEFFLA_VERSION"
	echo "| Configuration file:	$DEFCONFIG"
	echo "| Release:	$BVERN"
	echo "| Building for:	$DEVICE"
	echo "| Build  user:	$USER"
	echo "| Build  host:	`hostname`"
	echo "| Build  toolchain:	$TVERSION"
	echo "| Number of threads:	$THREADS"
	echo "--------------------------------------"
else
	echo "*** CONFIGURATION FAILED ***"
	exit 1
fi
echo "*** NOW WE GO! ***"
echo "---- Stage 1: Building the kernel ----"
build_kernel
if [ $? -eq 0 ]; then
	echo "*** Kernel is ready! ***"
else
	echo "*** zImage BUILD FAILED ***"
	exit 1
fi

if [ "$SKIP_MODULES" = "false" ]; then
	echo "---- Stage 2: Building modules ----"
	build_modules
	if [ $? -eq 0 ]; then
		echo "*** Modules is ready! ***"
	else
		echo "*** MODULE BUILD FAILED ***"
		exit 1
	fi
else
	echo "---- Stage 2(skipped): Building modules ----"
fi

if [ "$DONTPACK" = "false" ]; then
	echo "---- Stage 3: Packing all stuff ----"
	make_flashable
	if [ $? -eq 0 ]; then
		echo "--------------------------------------"
		echo "--------------------------------------"
		echo "| Build  date:	$DATE"
		echo "| Version:	$BOEFFLA_VERSION"
		echo "| Configuration file:	$DEFCONFIG"
		echo "| Release:	$BVERN"
		echo "| Building for:	$DEVICE"
		echo "| Build  user:	$USER"
		echo "| Build  host:	`hostname`"
		echo "| Build  toolchain:	$TVERSION"
		echo "| Number of threads:	$THREADS"
		echo "> Flashable ZIP: $(ls | grep ${KERNEL_NAME}${BOEFFLA_VERSION}r${BUILD_NUMBER}-${DEVICE} | grep .zip | head -n 1)"
		echo "> MD5sum: $(ls | grep ${KERNEL_NAME}${BOEFFLA_VERSION}r${BUILD_NUMBER}-${DEVICE} | grep .md5)"
		echo "--------------------------------------"
		echo "*** Koffee is ready! ***"
	else
		echo "*** KOFFEE ZIP BUILD FAILED ***"
		exit 1
	fi
else
	echo "---- Stage 3(skipped): Packing all stuff ----"
	echo "--------------------------------------"
	echo "--------------------------------------"
	echo "| Build  date:	$DATE"
	echo "| Version:	$BOEFFLA_VERSION"
	echo "| Configuration file:	$DEFCONFIG"
	echo "| Release:	$BVERN"
	echo "| Building for:	$DEVICE"
	echo "| Build  user:	$USER"
	echo "| Build  host:	`hostname`"
	echo "| Build  toolchain:	$TVERSION"
	echo "| Number of threads:	$THREADS"
	echo "> zImage: arch/arm/boot/zImage"
	echo "--------------------------------------"
	echo "*** Koffee is ready! ***"
fi
