import re
import os
import sys

# Read heaer file
APP_KEY_FILE = os.environ['APP_KEY_HEADER_PATH']
if APP_KEY_FILE is None:
	print "APP_KEY_FILE Not found"
	sys.exit(1)
io = open(APP_KEY_FILE, "r+")
text = io.read()

# Throw error if original app key is valid
appKeyStr = re.search('AppKey\s@\"\S*\"',text).group()
if re.match("AppKey\s@\"[a-f0-9]{32}\"", appKeyStr) is not None:
	print "A valid app key is submitted!"
	sys.exit(1)

APP_KEY = os.environ['APP_KEY']
if APP_KEY is None: 
	print "APP_KEY not found in secrets"
	sys.exit(1)

# Stub valid key and write back
ret = re.sub('AppKey\s@\"\S*\"', 'AppKey @\"' + APP_KEY + '\"', text)
io.seek(0)
io.write(ret)
io.truncate()

io.close()

