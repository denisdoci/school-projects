import json
import pandas as pd
import json
import numpy as np
import shapefile
from shapely.geometry import MultiPolygon, Point, shape
import numpy as np
from sklearn import linear_model
import matplotlib.pyplot as plt

crimeurl = "https://data.cityofchicago.org/resource/6zsd-86xi.json"
boundriesfile = "Boundaries - Neighborhoods.geojson"
unemploymentFile = "unemployment.csv"

with open(boundriesfile) as f:
	boundries = json.load(f)

		
	# todo: create neighborhood array
	#print(js)
	def convertLocationRowToCoordinate(row):
		#print(row)
		row = row['location']
		return row['coordinates'] if not pd.isnull(row) else None

	def createPointFromCoordinates(coordinates):
		#print(coordinates)
		return Point(coordinates[0], coordinates[1])

	def findNeighborhoodFromPoint(point, polygonAndNameList):
		for neighborhood in polygonAndNameList:
			# js = get multipolygod
			if(neighborhood[1].contains(point)):
				return neighborhood[0]


	def convertLocationRowToNeighborhood(row,neighborhoodNameAndShape):
		#print(neighborhoodNameAndShape)
		coordinates = convertLocationRowToCoordinate(row)
		point = createPointFromCoordinates(coordinates)
		#print("before neighborhood call")
		neighborhood = findNeighborhoodFromPoint(point, neighborhoodNameAndShape)
		#print("after")
		return neighborhood

	def getNeighborhoodsAndPolygons(js):
		neighborhoodNameAndShape = []
		for feature in js['features']:
			polygon = shape(feature['geometry'])
			neighborhoodNameAndShape.append((feature['properties']['pri_neigh'], polygon))
		return neighborhoodNameAndShape

	def return0():
		return 0
	def accumNumberofCrimes(row, dfcrime):
		#print(row)
		accum = 0
		for index, crimerow in dfcrime.iterrows():
			if crimerow['neighborhood'] == row['Neighborhood']:
				accum += 1
			#print(crimerow)
		return accum

	def getListOfDescriptions(dfcrime):
		fullDescriptions = list(dfcrime['primary_type'])
		uniquesubset = set(fullDescriptions)
		#print(uniquesubset)
		return list(uniquesubset)

	def getDescriptionCount(row, dfcrime, description):
		dfDescription = dfcrime.loc[dfcrime['primary_type'] == description]
		dfNeighborhoodAndDescription = dfDescription.loc[dfDescription['neighborhood'] == row['Neighborhood']]
		return len(dfNeighborhoodAndDescription.index)
		"""
		accum = 0
		for index, crimerow in dfcrime.iterrows():
			if crimerow['neighborhood'] == row['Neighborhood'] and crimerow['primary_type'] ==  description:
				accum += 1
			#print(crimerow)
		return accum
		"""

	dfcrime = pd.read_json(crimeurl)
	dfunemplyoment = pd.read_csv(unemploymentFile)
	dfcrime = dfcrime.dropna(subset=['location'])

	with open(boundriesfile) as f:
		js = json.load(f)
	neighborhoodNameAndShape = getNeighborhoodsAndPolygons(js)
	uniquedescriptions = getListOfDescriptions(dfcrime)
	dfcrime['neighborhood'] = dfcrime[['location']].apply(lambda row: convertLocationRowToNeighborhood(row,neighborhoodNameAndShape), axis=1)
	dfunemplyoment['number of crimes'] = dfunemplyoment.apply(lambda row: accumNumberofCrimes(row,dfcrime), axis=1)
	#print(uniquedescriptions)
	for description in uniquedescriptions:
		dfunemplyoment[str(description)] = dfunemplyoment.apply(lambda row: getDescriptionCount(row, dfcrime, description), axis=1)
	#for description in unique
	#print(dfcrime)

	print(dfunemplyoment)
	y = dfunemplyoment['Unemployment'].values
	x = dfunemplyoment[['number of crimes']].values
	length = len(x)

	#print(x)
	#print(y)
	x = x.reshape(length, 1)
	y = y.reshape(length, 1)

	regr = linear_model.LinearRegression()
	regr.fit(x, y)	

	plt.scatter(x, y,  color='black')
	plt.plot(x, regr.predict(x), color='blue', linewidth=3)
	plt.xticks(())
	plt.yticks(())
	plt.ylabel('Unemployment')
	plt.xlabel('Number of Crimes')
	plt.title('Linear Regression')
	plt.show()

	#TODO: machine learning stuff
	#TODO: some graphs
