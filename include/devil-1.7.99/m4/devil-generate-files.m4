dnl
dnl Generate list of modules with formats that they contain
dnl Example of modules.lst:
dnl
dnl #This is a comment
dnl  #This is not a comment (there is space before '#')
dnl base: BMP RAW TGA
dnl #<modulename>: <space-separated list of formats>
dnl
AC_DEFUN([GENERATE_MODULES_LST],
	 [dnl How will be the file called?
	  MODULES_LST_FILENAME="modules.lst"
	  dnl Where are we going to save it in the build tree?
	  MODULES_LST_PATH="lib"
	  dnl Let's create that directory
	  AS_MKDIR_P([$MODULES_LST_PATH])
	  MODULES_LST="$MODULES_LST_PATH/$MODULES_LST_FILENAME"
	  MODULES_LST_TEMP="${MODULES_LST}.temp"
	  dnl Some comments to the beginning of the file
	  dnl We have to quote it because '#' is a nasty m4 character
	  AS_ECHO([["#This is a list of modules for DevIL. Lines BEGINNING WITH '#' are ignored"]]) > $MODULES_LST_TEMP
	  AS_ECHO([["#The list should be generated by the './configure' script."]]) >> $MODULES_LST_TEMP 
	  AS_ECHO([["#Example entry:"]]) >> $MODULES_LST_TEMP
	  AS_ECHO([["#   <module_name>: <supported formats>"]]) >> $MODULES_LST_TEMP
	  AS_ECHO([["#   base: BMP GIF TGA"]]) >> $MODULES_LST_TEMP
	  dnl Let's inform the user what are we up to
	  dnl [class_count=${#CLASS_NAMES[@]}]
	  class_count=$NUM_CLASSES
	  AC_MSG_NOTICE([Generating $MODULES_LST_TEMP, a list of modules. $class_count modules will be built. See m4/devil-generate-files.m4 for further comments ])
	  dnl for (( i=0; i < $class_count; i++ ))
	  i=0
	  while test $i -lt $class_count
	  dnl for i in $(seq 0 $class_count)
	  do
		dnl Output the $MODULES_LST_TEMP line by line
		eval "TEMP_MODULE_NAME=\"\${lib_prefix}\$CLASS_NAMES_$i\""
		eval "TEMP_MODULE_FORMATS=\"\$CLASS_FORMATS_$i\""
		AS_ECHO(["$TEMP_MODULE_NAME:$TEMP_MODULE_FORMATS"]) >> $MODULES_LST_TEMP
	  	dnl AC_DEFINE_UNQUOTED([[${CLASS_DEFINE[$i]}_FORMATS]],
	  	eval "TEMP_CLASS_DEFINE_FORMATS=\"\${CLASS_DEFINE_$i}_FORMATS\""
dnl	  	AC_DEFINE_UNQUOTED([$TEMP_CLASS_DEFINE_FORMATS],
		dnl		   [[${CLASS_FORMATS[$i]}]],
dnl				   [$TEMP_MODULE_FORMATS],
dnl				   [Formats we support])
		i=$(expr $i + 1)
	  done 
	  dnl Now check whether the temp and possibly old MODULES_LST files are different.
	  dnl There is no reason to overwrite the old one if they are the same...
	  AS_IF([ cmp -s $MODULES_LST $MODULES_LST_TEMP],
		[dnl They are the same... 
		 rm $MODULES_LST_TEMP ],
		[dnl The new one is better :-) 
		 mv $MODULES_LST_TEMP $MODULES_LST])
	  AC_SUBST([MODULES_LST_FILENAME]) ])

dnl
dnl We output formats sorted regarding to the class they belong to
dnl It is maybe not minimalistic, but it is at least documented...
dnl
AC_DEFUN([GENERATE_FORMATS_TEXI],
	 [OUTFILE_FILENAME="formats.texi"
	  OUTFILE_PATH="docs"
	  AS_MKDIR_P([$OUTFILE_PATH])
	  OUTFILE="$OUTFILE_PATH/$OUTFILE_FILENAME"
	  OUTFILE_TEMP="${OUTFILE}.temp"
	  AS_MKDIR_P([docs])
	  AC_MSG_NOTICE([Going to (re)generate $OUTFILE - the formats description part of documentation.])
	  dnl We have a feature to put strings in $SUPPORTED_FORMATS into the @code{} stuff. 
	  ALSO_HIGHLIGHT=" TARGA ICO WAD 2000"
	  echo > $OUTFILE_TEMP
	  dnl [class_count=${#CLASS_NAMES[@]}]
	  class_count=$NUM_CLASSES
	  dnl for (( i=0; i < $class_count; i++ ))
	  i=0
	  while test $i -lt $class_count
	  dnl for i in $(seq 0 $class_count)
	  do
		dnl remember we have to double the '[' and ']' brackets here. 
		dnl Also note that '@<:@' = '[' and '@:>@' = ']'
		dnl We have to use that because of unbalanced square brackets usage
		AS_ECHO([]) >> $OUTFILE_TEMP
		dnl The class will become a section in the manual
		dnl Protective quoting for '[' and ']'
		dnl [echo "@section Class ${CLASS_NAMES[$i]}" >> $OUTFILE_TEMP]
		eval "TEMP_CLASS_NAME=\"\$CLASS_NAMES_$i\"" 
		AS_ECHO(["@section Class $TEMP_CLASS_NAME"]) >> $OUTFILE_TEMP
		dnl A few words about it
		dnl [echo "${CLASS_DESCRIPTIONS[$i]}" >> $OUTFILE_TEMP]
		dnl TEMP_CLASS_DESCRIPTION=$(eval "AS_ECHO_N([\"\$CLASS_DESCRIPTIONS_$i\"])" )
		eval "TEMP_CLASS_DESCRIPTION=\"\$CLASS_DESCRIPTIONS_$i\"" 
		AS_ECHO(["$TEMP_CLASS_DESCRIPTION"]) >> $OUTFILE_TEMP
		dnl Now describing every class's format
		dnl [for FORMAT in ${CLASS_FORMATS[$i]}]
		eval "FORMATS=\"\$CLASS_FORMATS_$i\""
		for FORMAT in $FORMATS
		do
			ABILITIES=""
			dnl grep TEST_FORMAT is a defined macro, so we prevent its expansion by omitting the last letter
			[TEST_FORMAT_LINE=$($GREP TEST_FORMAT ${srcdir}/configure.ac | $GREP "\[$FORMAT\]")]
			DESCRIPTION=$(AS_ECHO_N(["$TEST_FORMAT_LINE"]) dnl
			dnl Extracting "The Third" parameter
			[| sed -e 's/[^,]*,[^,]*,[[:blank:]]*\@<:@\([^@:>@]*\).*/\1/')]
			dnl Get possible format strings by erasing non-formats strings
			MAYBE_FORMATS=$(AS_ECHO_N(["$DESCRIPTION"]) | [sed -e 's/\<[A-Z0-9]*[^A-Z0-9 ]\{1,\}[[:alnum:]_]*\>//g'] dnl
			dnl Cleanup stuff
			[| sed -e 's/[.,()]//g')]
			for suspect in $MAYBE_FORMATS
			do
				dnl Is the word in the supported format list? 
				dnl If so, substitute the word in the description
				AS_ECHO_N(["${MENTIONED_FORMATS}${ALSO_HIGHLIGHT}"]) | $GREP -q "\<$suspect\>" dnl
				&& DESCRIPTION=$(AS_ECHO_N(["$DESCRIPTION"]) | [sed -e "s/\<\($suspect\)\>\([^}]\)/@code{\1}\2/")]
			done
			EXTENSIONS=$($GREP SET_FORMAT ${srcdir}/src-IL/src/il_stack.c dnl
			dnl Extracting the last parameter (=extensions string) of Set_format functions 
			[| $GREP _$FORMAT | sed -e 's/.*"\([^"]*\)".*/ \1/']dnl
			dnl And finally add '*.' before each extension
			[| sed -e 's/ \([^ ]\+\)/ @code{*.\1}/g']dnl
			dnl And really finally separate them with commas :-)
			[| sed -e 's/}[[:blank:]]\+@/}, @/g')]
			DEPENDENCY=$(AS_ECHO_N(["$TEST_FORMAT_LINE"]) | $GREP SETTLE dnl Assuring that there is the SETTLE param...
			dnl Extracting "The Last" parameter if it has the SETTLE_ prefix and making the rest lowercase
			[| sed -e 's/.*SETTLE_\([^@:>@]*\).*/\L\1\E/')]
			dnl Can we load it?
			$GREP -q ilLoad_$FORMAT ${srcdir}/src-IL/src/* && ABILITIES="$ABILITIES LOAD"
			dnl Can we save it?
			$GREP -q ilSave_$FORMAT ${srcdir}/src-IL/src/* && ABILITIES="$ABILITIES SAVE"
			dnl Can we check whether a file is a valid format?
			$GREP -q ilIsValid_$FORMAT ${srcdir}/src-IL/src/* && ABILITIES="$ABILITIES ISVALID" 

			dnl Entry for the format index (called 'ft')
			echo "@ftindex $FORMAT" >> $OUTFILE_TEMP
			dnl The format description will be a subsection
			echo "@subsection Format $FORMAT" >> $OUTFILE_TEMP
			dnl A few words about the format
			echo "$DESCRIPTION" >> $OUTFILE_TEMP
			dnl Another short format characteristics
			echo "@itemize" >> $OUTFILE_TEMP
			dnl What extensions characterize it?
			echo -e "\t@item Extensions:$EXTENSIONS" >> $OUTFILE_TEMP
			dnl What can we do with it?
			echo -e "\t@item Supported operations: $ABILITIES" >> $OUTFILE_TEMP
			dnl What libs do we need to be able to use it?
			test "x$DEPENDENCY" != "x" && echo -e "\t@item Dependency: @code{$DEPENDENCY} library" >> $OUTFILE_TEMP
			dnl End of the short characteristics list
			echo "@end itemize" >> $OUTFILE_TEMP
			echo >> $OUTFILE_TEMP
		done
		i=$(expr $i + 1)
	  done
	  dnl Now check whether the temp and possibly old MODULES_LST files are different.
	  dnl There is no reason to overwrite the old one if they are the same...
	  AS_IF([ cmp -s $OUTFILE $OUTFILE_TEMP ],
		[dnl They are the same... 
		 rm $OUTFILE_TEMP ],
		[dnl The new one is better (:-) 
		 mv $OUTFILE_TEMP $OUTFILE]) ])

dnl Usage:
dnl 	GET_FIELD(<text>, <column>, <delimiter>)
dnl Example:
dnl 	GET_FIELD(["our big mac"], [2], [ ])
AC_DEFUN([GET_FIELD],
	 [$(AS_ECHO_N(["$1"]) | cut -d '$3' -f $2)])

AC_DEFUN([GENERATE_PTR_DEFINES_H],
	 [dnl What file are we actually generating?
	  PTR_DEFINES_H_FILENAME="ptr_defines.h"
	  PTR_DEFINES_H_PATH="include/IL"
	  AS_MKDIR_P([$PTR_DEFINES_H_PATH])
	  PTR_DEFINES_H="$PTR_DEFINES_H_PATH/$PTR_DEFINES_H_FILENAME"
	  PTR_DEFINES_H_TEMP="${PTR_DEFINES_H}.temp"
	  dnl Let's tell the user. This is not an easy task.
	  AC_MSG_NOTICE([[Generating function pointer #defines to the $PTR_DEFINES_H file. This will take some time...]])
	  dnl Let's make a nice header guard
	  PTR_DEFINES_H_CODE="AS_TR_CPP([$PTR_DEFINES_H_FILENAME])"
	  dnl Putting the first header guard in place...
	  dnl We have to quote it because '#' is a nasty m4 character
	  [echo "#ifndef $PTR_DEFINES_H_CODE" > $PTR_DEFINES_H_TEMP
	  echo "#define $PTR_DEFINES_H_CODE" >> $PTR_DEFINES_H_TEMP]
	  echo >> $PTR_DEFINES_H_TEMP
	  dnl We even have to include something in our header. Because of typedefs...
	  [echo '#include "IL/devil_internal_exports.h"' >> $PTR_DEFINES_H_TEMP
	  echo >> $PTR_DEFINES_H_TEMP]
	  dnl We have to take care of C++ compilers since we are outputting declarations..
	  [echo "#ifdef __cplusplus" >> $PTR_DEFINES_H_TEMP
	  echo 'extern "C" {' >> $PTR_DEFINES_H_TEMP
	  echo "#endif /* __cplusplus */" >> $PTR_DEFINES_H_TEMP
	  echo >> $PTR_DEFINES_H_TEMP]
	  dnl Now we will take a look what return type and what parameters do those functions have.
dnl	  OPERATIONS=( 	"ilLoad" 	"ilLoadF" 	"ilLoadL" dnl
dnl			"ilSave" 	"ilSaveF" 	"ilSaveL" dnl
dnl			"ilIsValid" 	"ilIsValidF" 	"ilIsValidL" )
	  OPERATIONS="ilLoad ilLoadF ilLoadL ilSave ilSaveF ilSaveL ilIsValid ilIsValidF ilIsValidL"
	  dnl [for (( op=0; $op < ${#OPERATIONS[@]}; op++ ))]
	  for op in $OPERATIONS
	  do
		dnl We do this by investigating declaration of typedefs of pointers to those functions
		dnl [OPERATION_PTR_TYPEDEF=$(sed -n "/typedef.*${OPERATIONS[$op]}_ptr/p" ${srcdir}/src-IL/include/il_internal.h | sed -e 's/.*typedef\s*\(.*\);/\1/')]
		[OPERATION_PTR_TYPEDEF=$(sed -n "/typedef.*${op}_ptr/p" ${srcdir}/src-IL/include/il_internal.h | sed -e 's/.*typedef[[:blank:]]*\(.*\);/\1/') ]
		dnl [RETURN_TYPES[$op]=$(echo $OPERATION_PTR_TYPEDEF | sed -e 's/^\(\w*\).*/\1/')]
		[RETURN_TYPES="$RETURN_TYPES$(echo $OPERATION_PTR_TYPEDEF | sed -e 's/^\([[:alnum:]_]*\).*/\1/') "]
		[PARAMETERS="${PARAMETERS}$(echo $OPERATION_PTR_TYPEDEF | sed -e 's/.*\(([^()]*)\)[[:blank:]]*$/\1/')^" ]
		dnl [PARAMETERS[$op]=$(echo $OPERATION_PTR_TYPEDEF | sed -e 's/.*\(([^()]*)\)\s*$/\1/')]
	  done
	  dnl Yes, we have to take care even of formats that we won't be compiling in...
	  for FORMAT in $MENTIONED_FORMATS
	  do			
			dnl Let's limit the number of files where we search for every format
			FORMAT_FILES=$($GREP -l "_${FORMAT}" dnl
				'--exclude=*il_io.c' '--exclude=*il_stack.c' '--exclude=*il_states.c' '--exclude=*il_internal.c' dnl
				${srcdir}/src-IL/src/*)
		echo "/* Now examining format $FORMAT */" >> $PTR_DEFINES_H_TEMP
		dnl [for (( op=0; $op < ${#OPERATIONS[@]}; op++ ))]
		dnl for op in $(seq 1 9)
		op=1
		while test $op -le 9
		do
			TEMP_OP="GET_FIELD([$OPERATIONS], [$op], [ ])"
			TEMP_RET="GET_FIELD([$RETURN_TYPES], [$op], [ ])"
			TEMP_PAR="GET_FIELD([$PARAMETERS], [$op], [^])"
			dnl We need to escape '[' and ']' with '@<:@' and '@:>@' again since we are
			dnl passing them to macros and we would have to quad quote them...
			dnl Why is the following macro triplequoted? I don't know, but it has to be...
dnl			PTR_DEFINE="AS_TR_CPP([[[${OPERATIONS[$op]}_${FORMAT}_PTR]]])"
			PTR_DEFINE="AS_TR_CPP([${TEMP_OP}_${FORMAT}_PTR])"
			dnl Do we compile the format in? Is that format function mentioned in the source code?
			dnl We really need the "\<${FORMAT}\>" stuff here since for example BMP is contained in WBMP...
			AS_IF([echo ${SUPPORTED_FORMATS} | $GREP -q "\<${FORMAT}\>" && $GREP -q "${TEMP_OP}_${FORMAT}" $FORMAT_FILES],
			      dnl OK, we will make a declaration and #definition of pointer to that function
dnl 			      [[echo "${RETURN_TYPES[$op]} ${OPERATIONS[$op]}_${FORMAT}${PARAMETERS[$op]};" >> $PTR_DEFINES_H_TEMP
 			      echo "${TEMP_RET} ${TEMP_OP}_${FORMAT}${TEMP_PAR};" >> $PTR_DEFINES_H_TEMP
dnl				echo "#define $PTR_DEFINE & ${OPERATIONS[$op]}_${FORMAT}" >> $PTR_DEFINES_H_TEMP
				echo "[#]define $PTR_DEFINE & ${TEMP_OP}_${FORMAT}" >> $PTR_DEFINES_H_TEMP
dnl				echo >> $PTR_DEFINES_H_TEMP]],
				echo >> $PTR_DEFINES_H_TEMP,
			      dnl OK, we will just say that the pointer to that function is NULL.
			      [[echo "#define $PTR_DEFINE NULL" >> $PTR_DEFINES_H_TEMP]])
			op=$(expr $op + 1)
		done
		echo "/* Finished examining $FORMAT */" >> $PTR_DEFINES_H_TEMP
		echo >> $PTR_DEFINES_H_TEMP
	  done
	  dnl End of the C++ compiler caretaking...
	  [echo "#ifdef __cplusplus" >> $PTR_DEFINES_H_TEMP
	  echo '} /* end extern "C" */' >> $PTR_DEFINES_H_TEMP
	  echo "#endif /* __cplusplus*/" >> $PTR_DEFINES_H_TEMP]
	  dnl End of the header guard...
	  [echo "#endif /* $PTR_DEFINES_H_CODE */" >> $PTR_DEFINES_H_TEMP]
	  echo >> $PTR_DEFINES_H_TEMP
	  dnl Now check whether the temp and possibly old PTR_DEFINES_H files are different.
	  dnl There is no reason to overwrite the old one if they are the same...
	  AS_IF([ cmp -s $PTR_DEFINES_H $PTR_DEFINES_H_TEMP ],
		[dnl They are the same... 
		 rm $PTR_DEFINES_H_TEMP ],
		[dnl The new one is better :-) 
		 mv $PTR_DEFINES_H_TEMP $PTR_DEFINES_H]) 
	  AC_SUBST([PTR_DEFINES_H_FILENAME]) ])
