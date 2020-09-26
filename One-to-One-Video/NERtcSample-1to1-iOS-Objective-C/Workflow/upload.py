import requests
import os
import json
import sys
import qrcode

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
	file = open(FILE_PATH, 'rb')
	print('file is {}'.format(file))
	files = {'file': (os.path.basename(FILE_PATH), file, 'multipart/form-data', {'Expires': '0'})}
	response = session.post(url, files=files, headers={'Connection':'close'}).json()
	print(json.dumps(response, indent=4, sort_keys=False))
	file.close()
	return response["data"]
	

session = login('admin', 'admin123456')
app_url = upload(session, FILE_PATH)

print("Generate QRCode for url: {}".format(app_url))
img = qrcode.make(app_url)
img.save(QRCODE_OUTPUT)

