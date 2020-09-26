import requests
import os
import json
import sys
import fcntl
import time 

BASE_URL = sys.argv[1]
FILE_PATH = sys.argv[2]
QRCODE_OUTPUT = sys.argv[3]

def login(username,password):
	print("Start login")
	session = requests.Session()
	url = BASE_URL + "/account/login/"
	payload = {"username": username, "password": password}
	headers = {'Content-Type': 'application/json'}
	response = session.post(url, headers=headers, data=json.dumps(payload)).json()
	print(json.dumps(response, indent=4, sort_keys=False))
	return session

def upload(session,file):
	print("Uploading file {}".format(file))
	url = BASE_URL + "/app/upload"
	response = None
	while True:    
		try:
		    with open(FILE_PATH, 'rb') as io: 
		        fcntl.flock(io, fcntl.LOCK_EX | fcntl.LOCK_NB)
		        files = {'file': (os.path.basename(FILE_PATH), io, 'multipart/form-data', {'Expires': '0'})}
		        response = session.post(url, files=files).json()
		        fcntl.flock(io, fcntl.LOCK_UN)
		        break 
		except:
		       #wait before retrying  
				time.sleep(0.05)
	# files = {'file': (os.path.basename(FILE_PATH), open(FILE_PATH, 'rb'), 'multipart/form-data', {'Expires': '0'})}
	# response = session.post(url, files=files).json()
	print(json.dumps(response, indent=4, sort_keys=False))
	return response["data"]
	

session = login('admin', 'admin123456')
qrcode_url = upload(session, FILE_PATH)

print("Downloading QRCode: {}".format(qrcode_url))
	
io = open(QRCODE_OUTPUT, 'wb')
io.write(requests.get(qrcode_url).content)
io.close()


