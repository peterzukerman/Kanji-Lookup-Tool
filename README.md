Kanji Lookup Tool

![alt text](https://github.com/uiuc-sp18-cs126/final-project-peterzukerman/blob/master/mockupImage.jpg)

This is an application that helps learners of Japanese to simplify their character learning experience. It is designed to take in a list of kanji characters that the user already knows and returns a list of all the definitions of those words and example sentences using those words. This application uses a UI window that allows a user to the characters that they know. The application has two databases, one for characters, and one for sentences. The external libraries that this project uses are three-fold. It uses (https://xerces.apache.org/xerces-c/) for parsing the sentence database, which is in XML format. The application uses openFrameworks to assist with GUI work, and uses the ofxDatGui library. 


I need to look at how to import these two libraries into C++ in visual studio, and familiarize myself with the syntaxes of each parser. The most difficult part of the project will be the UI component because I have never worked with UI in C++. I may use another external library to simplify the ui component. Working with utf8 strings also proved to be very challening, particularly because both databases were encoded in a japanese text format called JIS. Thus, I had to convert them to utf8 and figure out how to parse user input to match it with the database.
