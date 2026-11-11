#include<webearl>
#include<fstream>
#include<string>
#include<cstdio>
using namespace webe;
void addStudent(Request &request,Response &response)
{
string rollNumber=request.get("rollNumber");
string name=request.get("name");
if(rollNumber.empty() || name.empty())
{
response.write("<h3>Roll number and name are required.</h3>");
return;
}
ofstream fout("students.data",ios::app);
if(!fout)
{
response.write("<h3>Unable to open student data file.</h3>");
return;
}
fout<<rollNumber<<"|"<<name<<"\n";
fout.close();
response.write("<!DOCTYPE HTML>");
response.write("<html lang='en'>");
response.write("<head><title>[Web Projector]</title></head>");
response.write("<body>");
response.write("<h3>Student added successfully.</h3>");
response.write("<a href='index.html'>Home</a>");
response.write("</body>");
response.write("</html>");
}
void getAllStudents(Request &request,Response &response)
{
ifstream fin("students.data");
if(!fin)
{
response.write("<h3>No student records found.</h3>");
response.write("<a href='index.html'>Home</a>");
return;
}
string line;
response.write("<!DOCTYPE html>");
response.write("<html>");
response.write("<head><title>[Web Projector]</title></head>");
response.write("<body>");
response.write("<h2>All Students</h2>");
response.write("<table border='1' cellpadding='10'>");
response.write("<tr><th>Roll Number</th><th>Name</th></tr>");
while(getline(fin,line))
{
int pos=line.find('|');
if(pos==string::npos) continue;
string rollNumber=line.substr(0,pos);
string name=line.substr(pos+1);
response.write("<tr>");
response.write("<td>"+rollNumber+"</td>");
response.write("<td>"+name+"</td>");
response.write("</tr>");
}
response.write("</table>");
response.write("<br><a href='index.html'>Home</a>");
response.write("</body>");
response.write("</html>");
fin.close();
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
<title>[Web Projector]</title>
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
string rollNumber=request.get("rollNumber");
if(rollNumber.empty())
{
response.write("<h3>Roll number is required.</h3>");
response.write("<a href='index.html'>Home</a>");
return;
}
ifstream fin("students.data");
if(!fin)
{
response.write("<h3>Unable to open student records.</h3>");
response.write("<a href='index.html'>Home</a>");
return;
}
string line;
string name;
bool found=false;
while(getline(fin,line))
{
int pos=line.find('|');
if(pos==string::npos) continue;
string storedRollNumber=line.substr(0,pos);
if(storedRollNumber==rollNumber)
{
name=line.substr(pos+1);
found=true;
break;
}
}
fin.close();
if(!found)
{
response.write("<h3>Student not found.</h3>");
response.write("<a href='index.html'>Home</a>");
return;
}
response.write("<!DOCTYPE HTML>");
response.write("<html lang='en'>");
response.write("<head>");
response.write("<meta charset='utf-8'>");
response.write("<title>[Web Projector]</title>");
response.write("</head>");
response.write("<body>");
response.write("<h2>Student [Edit Module]</h2>");
response.write("<form method='get' action='updateStudent'>");
response.write("<b>Roll number: <\b>");
response.write(rollNumber);
response.write("<input type='hidden' id='rollNumber' name='rollNumber' value='");
response.write(rollNumber);
response.write("'><br>");
response.write("<b>Name: </b>");
response.write("<input type='text' id='name' name='name' value='");
response.write(name);
response.write("'><br>");
response.write("<button type='submit'>Update</button>");
response.write("</form>");
response.write("<br>");
response.write("<a href='index.html'>Home</a>");
response.write("</body>");
response.write("</html>");
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
<title>[Web Projector]</title>
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
string rollNumber=request.get("rollNumber");
string name=request.get("name");
if(rollNumber.empty() || name.empty())
{
response.write("<h3>Roll number and name are required.</h3>");
response.write("<a href='index.html'>Home</a>");
return;
}
ifstream fin("students.data");
if(!fin)
{
response.write("<h3>Unable to open student records.</h3>");
response.write("<a href='index.html'>Home</a>");
return;
}
ofstream fout("students.tmp");
if(!fout)
{
fin.close();
response.write("<h3>Unable to update student records.</h3>");
response.write("<a href='index.html'>Home</a>");
return;
}
string line;
bool found=false;
while(getline(fin,line))
{
int pos=line.find('|');
if(pos==string::npos)
{
fout<<line<<"\n";
continue;
}
string storedRollNumber=line.substr(0,pos);
if(storedRollNumber==rollNumber)
{
fout<<rollNumber<<"|"<<name<<"\n";
found=true;
}
else
{
fout<<line<<"\n";
}
}
fin.close();
fout.close();
if(!found)
{
remove("students.tmp");
response.write("<h3>Student not found.</h3>");
response.write("<a href='index.html'>Home</a>");
return;
}
remove("students.data");
rename("students.tmp","students.data");
response.write("<!DOCTYPE HTML>");
response.write("<html lang='en'>");
response.write("<head>");
response.write("<meta charset='utf-8'>");
response.write("<title>[Web Projector]</title>");
response.write("</head>");
response.write("<body>");
response.write("<h2>Student [Update Module]</h2>");
response.write("<h3>Student updated.</h3>");
response.write("<form method='get' action='index.html'>");
response.write("<button type='submit'>Ok</button>");
response.write("</form>");
response.write("</body>");
response.write("</html>");
response.close();
}
void deleteStudentConfirmation(Request &request,Response &response)
{
/*
file handling code to search roll number and send html

<!DOCTYPE HTML>
<html lang='en'>
<head>
<meta charset='utf-8'>
<title>[Web Projector]</title>
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
string rollNumber=request.get("rollNumber");
if(rollNumber.empty())
{
response.write("<h3>Roll number is required.</h3>");
response.write("<a href='index.html'>Home</a>");
return;
}
ifstream fin("students.data");
if(!fin)
{
response.write("<h3>Unable to open student records.</h3>");
response.write("<a href='index.html'>Home</a>");
return;
}
string line;
string name;
bool found=false;
while(getline(fin,line))
{
int pos=line.find('|');
if(pos==string::npos) continue;
string storedRollNumber=line.substr(0,pos);
if(storedRollNumber==rollNumber)
{
name=line.substr(pos+1);
found=true;
break;
}
}
fin.close();
if(!found)
{
response.write("<h3>Student not found.</h3>");
response.write("<a href='index.html'>Home</a>");
return;
}
response.write("<!DOCTYPE HTML>");
response.write("<html lang='en'>");
response.write("<head>");
response.write("<meta charset='utf-8'>");
response.write("<title>[Web Projector]</title>");
response.write("</head>");
response.write("<body>");
response.write("<h2>Student [Delete Module]</h2>");
response.write("<form method='get' action='deleteStudent'>");
response.write("Roll number: ");
response.write(rollNumber);
response.write("<input type='hidden' id='rollNumber' name='rollNumber' value='");
response.write(rollNumber);
response.write("'><br>");
response.write("Name: ");
response.write(name);
response.write("<input type='hidden' id='name' name='name' value='");
response.write(name);
response.write("'><br>");
response.write("<button type='submit'>Delete</button>");
response.write("</form>");
response.write("</body>");
response.write("</html>");
}
void deleteStudent(Request &request,Response &response)
{
//delete and send back [ok] html
string rollNumber=request.get("rollNumber");
if(rollNumber.empty())
{
response.write("<h3>Roll number is required.</h3>");
response.write("<a href='index.html'>Home</a>");
return;
}
ifstream fin("students.data");
if(!fin)
{
response.write("<h3>Unable to open student records.</h3>");
response.write("<a href='index.html'>Home</a>");
return;
}
ofstream fout("students.tmp");
if(!fout)
{
fin.close();
response.write("<h3>Unable to delete student record.</h3>");
response.write("<a href='index.html'>Home</a>");
return;
}
string line;
bool found=false;
while(getline(fin,line))
{
int pos=line.find('|');
if(pos==string::npos)
{
fout<<line<<"\n";
continue;
}
string storedRollNumber=line.substr(0,pos);
if(storedRollNumber==rollNumber)
{
found=true;
continue;
}
fout<<line<<"\n";
}
fin.close();
fout.close();
if(!found)
{
remove("students.tmp");
response.write("<h3>Student not found.</h3>");
response.write("<a href='index.html'>Home</a>");
return;
}
remove("students.data");
if(rename("students.tmp","students.data")!=0)
{
response.write("<h3>Unable to update student records.</h3>");
response.write("<a href='index.html'>Home</a>");
return;
}
response.write("<!DOCTYPE HTML>");
response.write("<html lang='en'>");
response.write("<head>");
response.write("<meta charset='utf-8'>");
response.write("<title>[Web Projector]</title>");
response.write("</head>");
response.write("<body>");
response.write("<h2>Student [Delete Module]</h2>");
response.write("<h3>Student deleted successfully.</h3>");
response.write("<form method='get' action='index.html'>");
response.write("<button type='submit'>Ok</button>");
response.write("</form>");
response.write("</body>");
response.write("</html>");
}
int main()
{
WebProjector server(5050);
server.onRequest("/addStudent",addStudent);
server.onRequest("/getStudents",getAllStudents);
server.onRequest("/editStudent",studentEditForm);
server.onRequest("/updateStudent",updateStudent);
server.onRequest("/deleteStudentConfirmation",deleteStudentConfirmation);
server.onRequest("/deleteStudent",deleteStudent);
server.start();
return 0;
}