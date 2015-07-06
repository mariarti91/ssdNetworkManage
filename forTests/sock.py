#!/usr/bin/python
#!-*- coding:utf-8 -*-

import socket

sock = socket.socket()

sock.bind(("", 9090))
sock.listen(1)

while True:
	conn, addr = sock.accept()
	print "get connection!"
	data = conn.recv(100)
	print "Data: " + data.decode("utf-8")
	conn.send("\x00\x03aga")
