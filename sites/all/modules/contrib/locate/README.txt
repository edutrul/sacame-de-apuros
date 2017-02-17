Locate
======

Requirements:
* locate unix tool
* env should allow php exec

Considerations:
* The search files root path should not be served by Apache or other web
servers. The stream wrapper will stream the file from any file on the local
system as long as the web server user has access to read it.
