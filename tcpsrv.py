from socket import *

serverPort = 12001
serverSocket = socket(AF_INET,SOCK_STREAM)
serverSocket.bind(('',serverPort))

serverSocket.listen(1)
print ('The server is ready to receive')

while True:
	connectionSocket, addr = serverSocket.accept()
	print (addr)
	sentence = connectionSocket.recv(1024)
	print(sentence)
	capitalizedSentence = sentence.decode().upper()
	connectionSocket.send(capitalizedSentence.encode())
	connectionSocket.close()

