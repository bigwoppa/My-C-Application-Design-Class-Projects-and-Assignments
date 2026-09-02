# Module 02: 5 Action Records Page

Before starting this assignment, I did some personal review of C++ syntax. So far, it feels a lot like Python with extra steps.

## Most Interesting Thing

One thing I found interesting was that C++ file manipulation does not work the same way a database would. To delete a record from the CSV file, I created a temporary CSV file, copied over every record except the one being deleted, then replaced the original CSV with the temporary file.