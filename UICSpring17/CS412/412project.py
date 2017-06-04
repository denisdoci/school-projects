import json
import pandas as pd
import json
import numpy as np
import shapefile
from shapely.geometry import MultiPolygon, Point, shape
import numpy as np
from sklearn import linear_model
from sklearn.model_selection import train_test_split
import matplotlib.pyplot as plt
from sklearn.metrics import f1_score


crimeurl = "https://data.cityofchicago.org/resource/6zsd-86xi.json"
crimescsv = "crimes.csv"
boundriesfile = "Boundaries - Neighborhoods.geojson"
unemploymentFile = "unemployment.csv"


# todo: create neighborhood array
#print(js)
def convertLocationRowToCoordinate(row):
	#print(row)
	row = row['Location']
	#print("location"+row)
	return row if not pd.isnull(row) else None

def createPointFromCoordinates(coordinates):
	#print("before" + coordinates)
	coordinates = coordinates.replace("(","")
	coordinates = coordinates.replace("'","")
	coordinates = coordinates.replace(")","")
	coordinates = tuple(map(float, coordinates.split(',')))
	#print(Point(coordinates[0], coordinates[1]))
	return Point(coordinates[1], coordinates[0])

def findNeighborhoodFromPoint(point, polygonAndNameList):
	for neighborhood in polygonAndNameList:
		# js = get multipolygod
		#print(neighborhood)
		#print(point)
		if(neighborhood[1].contains(point)):
			#print(neighborhood)
			return neighborhood[0]


def convertLocationRowToNeighborhood(row,neighborhoodNameAndShape):
	#print(neighborhoodNameAndShape)
	coordinates = convertLocationRowToCoordinate(row)
	#print(coordinates)
	point = createPointFromCoordinates(coordinates)
	#print(point)
	#print("before neighborhood call")
	neighborhood = findNeighborhoodFromPoint(point, neighborhoodNameAndShape)
	#print("after")
	#print(neighborhood)
	return neighborhood

def getNeighborhoodsAndPolygons(js):
	neighborhoodNameAndShape = []
	for feature in js['features']:
		polygon = shape(feature['geometry'])
		neighborhoodNameAndShape.append((feature['properties']['pri_neigh'], polygon))
	return neighborhoodNameAndShape

def accumNumberofCrimes(row, dfcrime):
	#print(row)
	accum = 0
	for index, crimerow in dfcrime.iterrows():
		if crimerow['neighborhood'] == row['Neighborhood']:
			accum += 1
		#print(crimerow)
	return accum

def getListOfDescriptions(dfcrime):
	fullDescriptions = list(dfcrime['Primary Type'])
	uniquesubset = set(fullDescriptions)
	#print(uniquesubset)
	return list(uniquesubset)

def getDescriptionCount(row, dfcrime, description):
	dfDescription = dfcrime.loc[dfcrime['Primary Type'] == description]
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

#dfcrime = pd.read_json(crimeurl)
dfunemplyoment = pd.read_csv(unemploymentFile)
dfcrime2 = pd.read_csv(crimescsv)
#print(dfcrime2)
#dfcrime = dfcrime.dropna(subset=['location'])
#print(dfcrime2.size)
dfcrime2 = dfcrime2.dropna(subset=['Location'])
dfcrime2 = dfcrime2.ix[:10000]
#print(dfcrime2.size)

with open(boundriesfile) as f:
	js = json.load(f)
neighborhoodNameAndShape = getNeighborhoodsAndPolygons(js)
#print(neighborhoodNameAndShape)
uniquedescriptions = getListOfDescriptions(dfcrime2)
#dfcrime['neighborhood'] = dfcrime[['location']].apply(lambda row: convertLocationRowToNeighborhood(row,neighborhoodNameAndShape), axis=1)
dfcrime2['neighborhood'] = dfcrime2[['Location']].apply(lambda row: convertLocationRowToNeighborhood(row,neighborhoodNameAndShape), axis=1)
dfunemplyoment['number of crimes'] = dfunemplyoment.apply(lambda row: accumNumberofCrimes(row,dfcrime2), axis=1,)
print("before drop")
dfcrime2 = dfcrime2.dropna(subset=['neighborhood'])
print("after drop")
#print(uniquedescriptions)
for description in uniquedescriptions:
	dfunemplyoment[str(description)] = dfunemplyoment.apply(lambda row: getDescriptionCount(row, dfcrime2, description), axis=1)
#for description in unique
#print(dfcrime2)

print(dfunemplyoment)
"""
x_cols = ['number of crimes', 'ASSAULT']
dfunemplyoment_x_train, dfunemplyoment_x_test, dfunemplyoment_y_train, dfunemplyoment_y_test = train_test_split(dfunemplyoment[x_cols], dfunemplyoment['unemployment'])
"""

msk = np.random.rand(len(dfunemplyoment)) < 0.8
train = dfunemplyoment[msk]
test = dfunemplyoment[~msk]


y = train[['Unemployment']].values
lengthy = len(y)
x = train['number of crimes'].values
lengthx = len(x)

#print(x)
#print(y)
y = y.reshape(lengthy, 1)
x = x.reshape(lengthx, 1)

regr = linear_model.LinearRegression(normalize=True)
regr.fit(x, y)	

ytest = test['Unemployment'].values
xtest = test['number of crimes'].values

lengthytest = len(ytest)
lengthxtest = len(xtest)

ytest = ytest.reshape(lengthytest, 1)
xtest = xtest.reshape(lengthxtest, 1)

f1 = f1_score(y, ytest, average=None)
print()

plt.scatter(xtest, ytest,  color='black')
plt.plot(xtest, regr.predict(xtest), color='blue', linewidth=3)
plt.xticks(())
plt.yticks(())
plt.ylabel('Unemployment')
plt.xlabel('Number of Crimes')
plt.title('Linear Regression')
plt.show()


# plt.scatter(x, y,  color='black')
# plt.plot(x, regr.predict(x), color='blue', linewidth=3)
# plt.xticks(())
# plt.yticks(())
# plt.ylabel('Unemployment')
# plt.xlabel('Number of Crimes')
# plt.title('Linear Regression')
# plt.show()

#TODO: machine learning stuff
#TODO: some graphs
