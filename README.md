# CS 126 Final Project - Peter Zukerman
• The project will be a openFrameworks application 

• Implement a windowed application 

• Use a significant library that we do not cover in class

This is an application that helps learners of Japanese to simplify their character learning experience. It is designed to take in a list of kanji characters that the user already knows and returns a list of all the definitions of those words and example sentences using those words. It also gives the user export options to sort the data returned in various formats, for example for memorization through flashcards. This application uses a UI window that allows a user to submit a file of the characters that they know, or just type them in. The application has three databases, one for characters, one for sentences, and one for all words (a dictionary). The external libraries that this project uses are three-fold. It uses (https://xerces.apache.org/xerces-c/) for parsing the sentence database, which is in XML format. It also uses Ben Strasser’s CSV parser (https://github.com/ben-strasser/fast-cpp-csv-parser) for reading the dictionary and kanji files. The application uses openFrameworks to assist with GUI work and exporting into a different file format, and the entire application runs in the window. 


I need to look at how to import these two libraries into C++ in visual studio, and familiarize myself with the syntaxes of each parser. The most difficult part of the project will be the UI component because I have never worked with UI in C++. I may use another external library to simplify the ui component. Also, the output will be difficult because I need to figure out a way to organize the information that the user wants and export it into various files. Finally, I want to add a drop down menu for allowing the user to configurate the program to work as he or she intends.
