#!/usr/bin/env python2

import SocketServer
import csv, random

flag = open('flag.txt').read().strip()

questions = []
answers = []

with open('capitals.csv', 'rb') as csvfile:
	spamreader = csv.reader(csvfile, delimiter=',', quotechar='|')
	for row in spamreader:
		questions.append(row[1].replace('\xa0',''))
		answers.append(row[2])

with open('states.csv', 'rb') as csvfile:
	spamreader = csv.reader(csvfile, delimiter=',', quotechar='|')
	for row in spamreader:
		questions.append(row[0])
		answers.append(row[1])

SocketServer.TCPServer.allow_reuse_address = True

class ThreadedTCPRequestHandler(SocketServer.BaseRequestHandler):
	def handle(self):
		self.request.settimeout(15)
		self.request.sendall("Welcome to Tux Trivia Show!!!\n")

		for i in range(1000):
			num = random.randint(0,len(questions)-1)
			capital = questions[num]
			ans = answers[num]
			self.request.sendall("What is the capital of "+capital+"?\n")
			try:
				response = self.request.recv(2048).strip()
				if response.lower() == ans.lower():
					try:
						self.request.sendall("Correct! Next question coming...\n\n")
					except Exception:
						self.request.sendall("Error!\n")
						return
				else:
					self.request.sendall("INCORRECT!\n")
					self.request.sendall("You have lost Tux Trivia Show :'(\n")
					return
			except:
				self.request.sendall("\n\nTime out!")
				return

		self.request.sendall("Here is your flag: " + flag)

class ThreadedTCPServer(SocketServer.ThreadingMixIn, SocketServer.TCPServer):
	pass

if __name__ == '__main__':
	server = ThreadedTCPServer(('0.0.0.0', 3455), ThreadedTCPRequestHandler)
	server.allow_reuse_address = True
	server.serve_forever()
