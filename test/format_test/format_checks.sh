#!/bin/bash

VERBOSE=""    # set VERBOSE="v" for verbose mode
# that @expression@ will be substituted by the 'confgure' script
EXTENSIONS=" BMP CUT CHEAD DCX DDS DOOM FITS GIF HDR ICNS ICON IFF ILBM JPEG LIF MDL PCX PCD PIC PIX PNG PNM PSD PSP PXR RAW ROT SGI SUN TEXTURE TGA TIFF TPL UTX VTF WAL WBMP XPM BLP IWI FTX DICOM"
# Here are the extensions that should support saving according to docs
#CAN_SAVE=" BMP DDS HDR ICO JPEG PCX PNG PPM PSD RAW SGI TGA TIF XPM " RAW and XPM are problematic...
CAN_SAVE="BMP DDS EXR HDR ICO JP2 JPEG PCX PNG PPM PSD SGI TGA TIFF VTF"
# List of formats that we don't test since they are problematic
PROBLEMATIC="RAW VTF WBMP XPM"

TESTDIR="il_test_$$"
if test -f $TESTDIR
then
	echo "The directory '$TESTDIR', where we plan to dump test files, already exists (WTF?)."
	echo "This is quite strange and may have unwanted effects, bailing out..."
	exit 1
fi
echo
echo "Running saving and loading consistency test..."

FAILED_FORMATS=""
PASSED_FORMATS=""

# if using Wine makes sense, use it...
if test "xlinux-gnu" != "xlinux-gnu"
	then
	if [ '("xLINUX" = "xMINGW32" -o "xLINUX" = "xCYGWIN") -a $(wine --version > /dev/null 2>&1 )' ] 
	then
		WINE="wine"
		echo "Warning: Using wine to test executables (not 100% reliable)"
	fi
fi

mkdir $TESTDIR
cd $TESTDIR
for EXTENSION in $EXTENSIONS
do
	#echo expr match "' $CAN_SAVE '" '.*\s'$EXTENSION'\s.*'
	if test $(expr "' $CAN_SAVE '" : '.* '$EXTENSION' .*') -eq 0 -o $(expr "' $PROBLEMATIC '" : '.* '$EXTENSION' .*') -ne 0 
	then # This extension is not considered as supported...
		continue;
	fi
	test -n	"$VERBOSE" && echo $WINE ./testil -e $EXTENSION
	# EXEEXT comes in when one compiles on platforms that append extensions to executables (testil.exe)
	$WINE ../testil -e$VERBOSE $EXTENSION
	
	# We have to capture whether the test has failed or not
	if test ! $? -eq 0
	then # we have an error here...
		FAILED_FORMATS="$FAILED_FORMATS $EXTENSION"
		FAILED="$?"
	else #no error...
		PASSED_FORMATS="$PASSED_FORMATS $EXTENSION"
	fi
done

cd ..
rm -rf $TESTDIR

#let's tell something to the user as well:
if test "x$FAILED" = "x" 
then #everything went fine
	echo "All examined formats were OK:$PASSED_FORMATS"
else #something went wrong
	echo "Errors were encountered during the test :-("
	echo "Formats that were OK:$PASSED_FORMATS"
	echo "Failed formats:$FAILED_FORMATS"
	FAILED="1"
fi # end of something went wrong
echo "Problematic (untested) formats: $PROBLEMATIC"

# And we have to tell the result to the shell, too...
exit $FAILED
