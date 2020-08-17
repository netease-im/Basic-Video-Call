import re
import os
import sys

APP_KEY = os.environ['APP_KEY']
if APP_KEY is None:
	print "APP_KEY Not found"
	sys.exit(1)
APP_KEY_FILE = os.environ['APP_KEY_HEADER_PATH']
if APP_KEY_FILE is None:
	print "APP_KEY_FILE Not found"
	sys.exit(1)
io = open(APP_KEY_FILE, 'w+')
text = io.read()

ret = re.sub('AppKey\s@\"\S*\"', 'AppKey @\"' + APP_KEY + '\"', text)
io.write(ret)

io.close()

