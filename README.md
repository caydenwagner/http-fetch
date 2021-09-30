# Lab_HTTP2 
### httpget_large

### Objective:

For this lab, you will write a C program that will use TCP sockets to produce HTTP requests and display the HTTP responses.  You will also use Wireshark to view the HTTP traffic and debug your program.  The HTTP responses will require multiple reads and you will be required to parse the Content-Length header to determine the size of the response.

### Problem:

You must write a program, httpget_large, that will take at least two command line arguments, a web server address and a path to a web page.  Multiple web pages (at most 5) can be specified on the command line and this will cause your program to make multiple HTTP requests. 

```
Build an HTTP request using the command line arguments
Display the HTTP request (printf)
Send the request to the server
// Display (printf) the resulting HTTP response: use for debugging purposes 
// but not when you	actually run your tests.
Display the total bytes read via recv()
```
* Note:
	* If multiple files are specified on the command line, run the above steps for each file.

You must reuse one connection to the server for all requests (a persistent connection).  	Make sure you set *Connection: keep-alive*

Each file may be larger then 4096.  You will need to determine the size of the file from the HTTP response header and call recv() until you have received the correct number of bytes.  Read from recv() 4096 bytes at a time.  Each time you call recv(), print a message to the screen so you know how many times you need to call recv() to read one file.
		
No dynamic memory is required.
		
An example run in shown in this document with some data redacted.  

You will need to submit both your source code (via GitHub) and a written lab report (PDF, to Moodle) providing the data you generate and the answer to discussion questions.  The discussion questions may have answers in the notes, in the textbook, or require you to do research online. 

Wireshark:

```
Wireshark Settings Preferences | Protocols | TCP |  UNCHECK Allow subdissector to reassemble TCP streams 
```

Steps:

 * Open Wireshark, and start capturing http traffic.

 * Open Firefox (so we all get the same results) and load the page:

	 * http://64.59.225.81/chadd/cs360f21/LargeHttp.html

 * In Wireshark, find the HTTP message that GETs the page and the HTTP response that returns the page.  Take a screenshot of the listing window to show how many data packets are involved in the delivery of the web page.
```
    1. How many packets do you see coming from the server?

    2. What is the maximum and minimum size of the packets coming from the server?
       
    3. In your first captured HTTP response (200 OK), what is the Content-Length?  
       What value does this represent?

    4. What is the content of the Connection: field in your captured HTTP request?  
       What does this mean?
       
    5. What HTTP header information shows up in the last HTTP packet you receive 
       from the server?  Why is this the case?
```

* Use your httpget_large command to fetch the web page.  Be sure to use Wireshark to capture the HTTP request and HTTP response.  Take a screenshot of the listing window to show how many data packets are involved in the delivery of the web page.
```
    6. How many recv() calls were required to completely read the file?

    7. Are there more recv() calls or more packets sent from the server to the client?  
       Why is this the case?
```
* Restart the Wireshark capture.

* Use your program to load the following two web pages using a persistent connection:
	* http://64.59.225.81/chadd/cs360f21/LargeHttp.html
	* http://64.59.225.81/chadd/cs360f21/LargeHttp2.html
	
* Be sure to use Wireshark to capture the HTTP request and HTTP response.  Take a screenshot of the listing window to show how many data packets are involved in the delivery of the web page.

```
    8. Explain, using the listing window, how you are sure this is a persistent connection.  
       Be sure to indicate which pieces of data in the listing window you are relying on 
       to make this decision.
       
    9. Try the above with three files (fetch LabHttp.html from the previous Lab three times).
       Inspect the HTTP responses for each of these requests.  How does the Keep-Alive: field differ?

    10. In your the first HTTP response, what is the max value for Keep-Alive: ?
    
    10.1 Publish a Release on GitHub.  See Moodle video! 
         Tag: v1.0 
         Release Title: 'Multiple File Read'

    11. Edit your code to take the first file listed on the command line and request that file 
        max+1 times using the same persistent connection.  Call sleep(1) before sending each 
        request so you do not overload the server or have your IP banned. What happens to the 
        connection?  How many responses return correctly? How does the Keep-Alive: field differ 
        in all these requests? Use /chadd/cs360f21/LabHttp.html for this test.
        Commit this code to GitHub
        
    11.1  Publish a Release on GitHub.  
          Tag: v1.1 
          Release Title: 'One File Read Many Times'

```
       
### Example Run	

```
you@linux# httpget_large 64.59.225.81 /chadd/cs360f21/LargeHttp.html  /chadd/cs360f21/LargeHttp2.html

>|GETXXXXXXXXXXX
XXXXXXXXXXX
XXXXXXXXXXX
XXXX

|<

recv()
recv()
…
recv()

Total Bytes Read: XXXXX

>|GETXXXXXXXXXXX
XXXXXXXXXXX
XXXXXXXXXXX

|<

recv()
recv()
…
recv()

Total Bytes Read: XXXXX
