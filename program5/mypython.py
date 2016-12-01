#!/usr/bin/python
#CS 344
#Assignment 5
#Chad Gibeaut 
#3/1/16
import random
print "\n\n\n\n\n\n\n\n\n\n\nStarting My program"
file1 = open("myfile1","w+",-1)
file2 = open("myfile2","w+",-1)	#open three files with different names (read and write access)
file3 = open("myfile3","w+",-1)
str1=""
str2=""		#create three blank strings
str3=""
for x in range(0,10):	#each loop add a char to the end of the string based on random int
	str1=str1+str(unichr(random.randint(97,122)))  
	str2=str2+str(unichr(random.randint(97,122)))  #convert random int to char (ASCII values)
	str3=str3+str(unichr(random.randint(97,122))) 
file1.write(str1)	#write string to file
file1.write("\n")	#write new line to file	
file2.write(str2)	#repeat for 2
file2.write("\n")
file3.write(str3)	#repeat for 3
file3.write("\n")

file1.seek(0,0)		
file2.seek(0,0)		#move file pointers back to start of file
file3.seek(0,0)
print "\nFile1: ",file1.read(10)
print "File2: ",file2.read(10)		#print the first 10 char of file (that is all there is)
print "File3: ",file3.read(10)

num1=random.randint(1,42)			#create random number from 1 to 42
num2=random.randint(1,42)			#and a second one
print "\nNumber 1: ", num1 			#print numbers
print "\nNumber 2: ", num2
print "Product of num1 and num2: ",num1*num2 #print product

file1.close()
file2.close() #close files 
file3.close()

