#include<webearl>
using namespace webe;
void addStudent(Request &request,Response &response)
{
//some file handling/database code to store student roll number and name arrived in request
}
void getAllStudents(Request &request,Response &response)
{
//open file and send records as HTML
}
void studentEditForm(Request &request,Response &response)
{
/*
extract roll number from request
file handling/database code to search roll number and send back html

<!DOCTYPE HTML>
<html lang='en'>
<head>
<meta charset='utf-8'>
<title>Web Projector</title>
</head>
<body>
Student [Edit Module]
<form method='get' action='updateStudent'>
Roll number : //the roll number of student searched
<input type='hidden' id='rollNumber' name='rollNumber' value='//roll number found'><br>
Name
<input type='text' id='name' name='name' value='//name against roll number'><br>
<button type='submit'>Update</button>
</form>
<a href='index.html'>Home</a>
</body>
</html>
*/
}
void updateStudent(Request &request,Response &response)
{
/*
extract data against roll number and name
file handling to search roll number
than update data
and send back html

<!DOCTYPE HTML>
<html lang='en'>
<head>
<meta charset='utf-8'>
<title>Web Projector</title>
</head>
<body>
Student [Update Module]
<h3>Student updated.</h3>
<form method='get' action='index.html'>
<button type='submit'>Ok</button>
</form>
</body>
</html>
*/
}
void deleteStudentConfirmation(Request &request,Response &response)
{
/*
file handling code to search roll number and send html

<!DOCTYPE HTML>
<html lang='en'>
<head>
<meta charset='utf-8'>
<title>Web Projector</title>
</head>
<body>
Student [Delete Module]
<form method='get' action='deleteStudent'>
Roll number : //roll number of student found
<input type='hidden' id='rollNumber' name='rollNumber'>
Name : //name of student found
<input type='hidden' id='name' name='name'>
<button type='submit'>Delete</button>
</form>
</body>
</html>
*/
}
void deleteStudent(Request &request,Response &response)
{
//delete and send back [ok] html
}
int main()
{
WebProjector server(5050);
server.onRequest("/addStudent",addStudent);
server.onRequest("/getStudents",getAllStudents);
server.onRequest("/editStudent",editStudentForm);
server.onRequest("/updateStudent",updateStudent);
server.onRequest("/deleteStudentConfirmation",deleteStudentConfirmation);
server.onRequest("/deleteStudent",deleteStudents);
server.start();
return 0;
}