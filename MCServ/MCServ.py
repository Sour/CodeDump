#!/usr/bin/env python
import os
import time
import win32ui
import sys
import datetime
import shutil
import subprocess

serverStart = datetime.datetime.now()
backupInterval = 1
serverDir = 'C:\\Users\\Wil\\Downloads\\modpacks^Direwolf20_1_6_4^1_0_17^Direwolf20Server\\'
worldDir = 'C:\\Users\\Wil\\Downloads\\modpacks^Direwolf20_1_6_4^1_0_17^Direwolf20Server\\world'
backupDir = 'C:\\Users\\Wil\\Downloads\\modpacks^Direwolf20_1_6_4^1_0_17^Direwolf20Server\\backup\\world'

def runBatch():
	os.chdir(serverDir)
	p = Popen("ServerStart.bat", cwd=r"C:\Users\Wil\Downloads\modpacks^Direwolf20_1_6_4^1_0_17^Direwolf20Server")
	stdout, stderr = p.communicate()
	#os.startfile('ServerStart.bat')

def checkForServer():
	try:
		win32ui.FindWindow(None, 'MCServ 1.0')
	except win32ui.error:
		runBatch()
	else:
		print('Server was found')

def backupWorld():
	if(os.path.exists(backupDir)):
		shutil.rmtree(backupDir)
	shutil.copytree(worldDir, backupDir)
	print('Backed up world')

def main():
	checkForServer()

	global serverStart
	now = datetime.datetime.now()

	if((serverStart.hour + backupInterval) == now.hour and (serverStart.minute + 5 >= now.minute)):
		serverStart = datetime.datetime.now()
		print('Time to backup the server: %s was the last backup, it is now: %s' % (serverStart, now))
		backupWorld()
	else:
		print('sleeping 30 seconds')
		time.sleep(30)

	print('Checking for Server: %s was the last backup, it is now: %s' % (serverStart, now))
	main()

if __name__ == "__main__":
	main();
