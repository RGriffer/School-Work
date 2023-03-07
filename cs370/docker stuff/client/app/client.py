import urllib.request

fp = urllib.request.urlopen("http://localhost:5000/")

encodedContent = fp.read()
decodedContent = encodedContent.decode("utf8")

print(decodedContent)

fp.close()