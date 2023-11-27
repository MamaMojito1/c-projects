#To link this library in code blocks
got to your project -> build option -> debug -> linker settings
click add now browse your <winsock.h> file it will be in your MinGW\lib folder
its name will be ""libwsock32.a"" file
add this file
now you are free to use

#To link this library in Visual studio
right click your solution -> properties -> linker -> input -> additional dependencies
write wsock32.lib and click ok
