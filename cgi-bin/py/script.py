import os


print ("Content-type: text/html\r\n\r\n")
if os.environ['REQUEST_METHOD'] == 'POST':
    print("You sent the following data:<br>")
    print("Hello " + os.environ['name'] + "!<br>")
    print("Your email is: " + os.environ['email'] + "<br>")
elif os.environ['REQUEST_METHOD'] == 'DELETE':
    print("Your method was DELETE<br>")
else:
    print("Your method was GET<br>")
