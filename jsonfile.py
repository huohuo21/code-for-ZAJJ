#!/usr/bin/env python
import json
import argparse
import math

parser = argparse.ArgumentParser()
parser.add_argument('--input', '-i', help='input json file')
args = parser.parse_args()

data = {}
with open(args.input) as jsonfile:
	data = json.load(jsonfile)

up = 0.0
down = 0.0
for ele in data['params']:
	up += (ele['r'][1]-ele['r'][0])*(ele['r'][1]-ele['r'][0])
	down += (ele['r'][1]-ele['r'][2])*(ele['r'][1]-ele['r'][2])
print 'up:',math.sqrt(up), ',down:',math.sqrt(down)
