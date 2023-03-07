# This is a Makefile.  Its purpose is to create the program “small”.
#
# The rules, below, indicate what depends on what, and how to build
# things when they get out-of-date.  It is VERY important to know that
# what looks like eight leading spaces is really a leading tab
# character.  Leading spaces won’t work--it MUST be a tab character.
#
# For the following questions, do the command if there is one,
# and then answer the question.  If you need another line for you
# answer, continue it on the next line, indented.
#
# As an example, I’ve already answered (1), which has nothing to do
# with anything else in this lab.
#
# Question 1 is worth 0.09 points; questions 2–14 are worth 0.07
# points each.
#
#  1) Command:  date +%A
#     Question: Describe the output of that command.
#     Answer:   It’s today’s day of the week.
#
#  2) Command:  make
#     Question: Describe what happens.  Don’t just write the commands;
#     		describe what each command does.
#     Answer:   what this did was compile foo.cc and main.cc into foo.o and main.o and then linked them together
#		into an executable called "small"
# 
#  3) Command:  ./small
#     Question: What is the output?  Reproduce the output exactly.
#     Answer:   Hi from main at main.cc:15
#    		Hi from foo at foo.cc:14

#
#  4) Command:  make
#     Question: Why did nothing much happen?
#     Answer:   because there was nothing changed so it did not need to remake the small file.
#
#  5) Command:  rm small; make
#     Question: What got remade, and why?
#     Answer:   Because small was deleted, small was recreated in the directory.
#
#  6) Command:  rm foo.o; make 
#     Question: What got remade, and why?
#     Answer:   Same as question 5, because foo.o was deleted it was remade and then recompiled into small.
#
#  7) Command:  make clean 
#     Question: What did that do?
#     Answer:   Deleted the executable and all *.o files.
#
#  8) Command:  make 
#     Question: What got remade, and why?
#     Answer:   The same 3 files that were created in the original make were created with this one because they were deleted with
#		the previous command.
#
#  9) Question: Why does main.o depend on foo.h?
#		I know that it’s because the Makefile says so.
#		Why was that dependency put into the Makefile?
#     Answer:   main.cc includes the line #include "foo.h" and this makes main.o dependant on foo.h
#
# 10) Command:  Create a new function bar() in bar.cc & bar.h,
# 		similar to foo.cc.  Change main.cc to call the new
# 		bar() function, make sure to #include the proper .h
# 		files everywhere, and type “make”.  Don’t alter Makefile.
#     Question: Why did it fail?
#     Answer:   This failed because bar.h is not included in main.cc
#
# 11) Command:  Fix the Makefile; verify with “make” until it compiles.
#     Question: Describe your changes.  Don’t just show the changed
#     		lines--describe the purpose of each change.
#     Answer:   What I did here was add a bar.o file output that also compiles into small along with main.o and foo.o
#
# 12) Command:  Uncomment the CXXFLAGS= line, and type “make”.
#     Question: Why didn't anything happen?
#     Answer:   small was already compiled with the same files as the last time it compiled.
#
# 13) Command:  Force a rebuild with: make clean; make 
#     Question: What’s new about the commands executed?
#     Answer:   It does a ton of error/warning testing against all of the files that will be compiled within the make file.
#
# 14) Command: 	make clean; ls -l clean
#     Question: The target is “clean”, but no file “clean” got created.
#     		Why not?
#     Answer:   because when you run make clean, it is the same as running -rm -f small *.o, and this does nothing for a clean file.
#
# For extra fame & glory (but no extra points):
#
# 15) Command:  Consult the make manual at
# 		https://www.gnu.org/software/make/manual/make.html
#		and improve this Makefile by using $@ in the rule
#		that creates “small” itself.

# The CXX variable contains the name of the C++ compiler.  You can’t
# have plus signs in a Make variable, so X is a rotated plus sign.
CXX=g++

CXXFLAGS=-std=c++17 -Wall -Wextra -Wpedantic -Werror -Wfatal-errors -Winit-self -Wshadow -Wlogical-op -Wcomment -Wctor-dtor-privacy -Wold-style-cast -D_GLIBCXX_DEBUG -fno-diagnostics-show-option

small: main.o foo.o bar.o
	$(CXX) $(CXXFLAGS) main.o foo.o bar.o -o small

main.o: main.cc foo.h
	$(CXX) $(CXXFLAGS) -c main.cc

foo.o: foo.cc foo.h
	$(CXX) $(CXXFLAGS) -c foo.cc

bar.o: bar.cc bar.h
	$(CXX) $(CXXFLAGS) -c bar.cc

clean:
	-rm -f small *.o
