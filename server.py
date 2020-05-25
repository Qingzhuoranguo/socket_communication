from socket import *
import sys

serverPort = 12000
serverSocket = socket(AF_INET, SOCK_STREAM)	
serverSocket.bind(('192.168.0.22',serverPort))
serverSocket.listen(1)

print ("Server ready to receive")

i = 0
while True:
	msg = ""
	connectionSocket, addr = serverSocket.accept()

	msg = connectionSocket.recv (1024).decode()
	print (msg)
	# msg = list(msg)
	# if len(msg) != 3:
	# 	msg = "Invalid input!"
	# else:
	# 	try:
	# 		a = float(msg[0])
	# 		b = float(msg[2])
	# 	except ValueError:
	# 		msg = "Invalid input!"
	# 	else:
	# 		msg = "The sum of the numbers is:  " + str(a + b)
	# 		additional_msg = input()
	# 		msg = "\n" + msg +"\n"+"Aaron says: " + additional_msg
	msg = input()
	connectionSocket.send(msg.encode())

	connectionSocket.close()