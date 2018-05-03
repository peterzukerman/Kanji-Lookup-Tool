APR 18:

Created initial project. Added openFrameworks gui. Created cpp program to convert CSV to dictionary for parsing. Uploaded databases to github. Starting Gui work.

APR 24:

CSV reader works. Loads example sentences with jpn and eng meaning, and japanese reading correctly. Reformated the example sentence database to be tab delimited instead of comma delimited.

APR 25:

XML reader works and is optimized for use outside of the program (through method calls for specific character.) CSV reader now parses into a HashMap sorted by character, with each character's values being a vector of 2d arrays containing the example sentences.

APR 26

Both readers work. Began work on GUI.

APR 29

Gui startup complete. Text input and button finished. Now to work on connecting dictionary and user input.

MAY 1

Gui finished. Works with hex kanji input only, due to serioues limits of openFrameworks and the forced GUI system we have to use. Reading, meaning and examples are printed out to the screen.

MAY 2

Project complete! Fully formatted, pleasant GUI. Now correctly prints out japanese character and examples with proper formatting!
