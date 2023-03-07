from flask import Flask
import sys
#@app.route('/')
def test():	
	return str(int(sys.argv[1])**(.5))
