# Remote-Keylogger
A remote keylogger written on C for educational purposes.

A program I've written with C exclusively for windows. 
It is divided in 2 parts. The Client and the Server, with Client being the "victim".
Server listens for a connection from the victim. When the victim runs the compiled Client code, 
the console window hides itself and connects to the Server. The client program listens for keystrokes in the while(1) loop,
and captures it in the pChar* array. It appends the '\0' null string terminator and sends it via the created connection to the Server.
The server then prints it in real-time to the console window of the user.
