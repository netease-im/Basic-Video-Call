import sys

xml1 = "<?xml version=\"1.0\" encoding=\"utf-8\"?>" \
	   "\n" \
	  "<resources>" \
	   "\n" \
	  "\t<string name=\"app_key\" translatable=\"false\">"

xml2 = "</string>" \
	   "\n" \
	  "</resources>"

APP_KEY_FILE_PATH = sys.argv[1]
APP_KEY = sys.argv[2]

xml = xml1 + str(APP_KEY) + xml2

f = open(APP_KEY_FILE_PATH, mode="w", encoding='utf8')
f.write(xml)
f.close()
