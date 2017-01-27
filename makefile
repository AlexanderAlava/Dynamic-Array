#########################################################################
##01/16/2017																            Alexander Alava##
##makefile																				 					  U35432961##
##																																	   ##
## This is the makefile for the file "lineTest" and all its dependants ##
#########################################################################


dynarr: testDynArray.o
		g++ -o dynarr testDynArray.o

testDynArray.o: testDynArray.cpp dynarr.h
	g++ -c testDynArray.cpp
