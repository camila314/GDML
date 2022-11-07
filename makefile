export CPLUS_INCLUDE_PATH=/Users/jakrillis/projects/builds/macosx-sdks/MacOSX10.5.sdk/usr/include
main:
	g++ -isysroot /Users/jakrillis/projects/builds/macosx-sdks/MacOSX10.5.sdk/ -std=c++11 GDML/*.cpp -I GDML/ -I GDMl/Zydis -c -g
	ar rcs GDML.a *.o
	libtool -static -o libGDML.a GDML.a GDML/libZydis.a
clean:
	rm *.o *.a
release:
	mv libGDML.a /Users/jakrillis/projects/gdmods/customtrigger/Cacao/Static/libGDML.a