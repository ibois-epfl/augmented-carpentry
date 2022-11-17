# -----------------------------------------------
# File that provides "make uninstall" target
#  We use the file 'install_manifest.txt'
# -----------------------------------------------
if(NOT EXISTS "/home/ibois/augmented-carpentry/build_feb14/deps/TSlam/install_manifest.txt")
  message(FATAL_ERROR "Cannot find install manifest: \"/home/ibois/augmented-carpentry/build_feb14/deps/TSlam/install_manifest.txt\"")
endif(NOT EXISTS "/home/ibois/augmented-carpentry/build_feb14/deps/TSlam/install_manifest.txt")

file(READ "/home/ibois/augmented-carpentry/build_feb14/deps/TSlam/install_manifest.txt" files)
string(REGEX REPLACE "\n" ";" files "${files}")
foreach(file ${files})
  message(STATUS "Uninstalling \"$ENV{DESTDIR}${file}\"")
  execute_process(COMMAND rm $ENV{DESTDIR}${file})
endforeach(file)
