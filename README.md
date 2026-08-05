AIX-MESSANGER

Hi GitHub. 
This project was created as part of my portfolio. 
I don't plan to develop it further; 
I'll keep it for the portfolio and as a template for someone.

About me:

I'm 15 years old, I'm from Russia, and I'm eager to become a developer (somehow, somewhere, I haven't decided yet), but not like Alexander Makhan (YandereDev).

How to install my product on your PC:

My product is designed ONLY for Linux (for Windows, you need to install WSL).
Clone my repository with the command "git clone https://github.com/godblessed-srth/aix-messanger-new.git", then navigate to the project folder and build it with the command "make".

WARNING:

There's a bug in the main.cpp file with a pointer to std::vector<User> users: after registering multiple users, entering the id command may cause the program to produce incomprehensible output or crash.
The solution is to store the user ID or replace vector with a list.
