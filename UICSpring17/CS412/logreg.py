"""
    Octave and julia doesn't work on my mac for some reason
    so I did the whole program in python. I used scikit learn
    for most all of the bayes and score calculations
"""
import pandas as pd
import numpy as np
import math
from sklearn.model_selection import train_test_split
from sklearn.linear_model import SGDClassifier
from sklearn.preprocessing import StandardScaler
from sklearn.feature_extraction.text import CountVectorizer

from sklearn.naive_bayes import MultinomialNB
from sklearn import metrics
import matplotlib.pyplot as plt


train=pd.read_csv('/Users/denisdoci/Desktop/spambasetrain.csv')
train_y=train.iloc[:,-1]
train_x=train.iloc[:,:len(train.columns)-1]

test=pd.read_csv('/Users/denisdoci/Desktop/spambasetest.csv')
test_y=test.iloc[:,-1]
test_x=test.iloc[:,:len(test.columns)-1]


learning_rates=[1, .01, 0.0001, 0.000001]
trainingAccuracies = []
testingAccuracies = []
kvalues = [-8,-6,-4,-2,0,2]
kTestingAccuracies = []
kTrainingAccuracies = []

for learning_rate in learning_rates:
	clf_LR = SGDClassifier(learning_rate='optimal', eta0=learning_rate, penalty = 'none')
	clf_LR.fit(train_x, train_y)
	score = clf_LR.score(train_x, train_y)
	trainingAccuracies.append(score)
	clf_LRT = SGDClassifier(learning_rate='optimal', eta0=learning_rate, penalty = 'none')
	clf_LRT.fit(test_x, test_y)
	score = clf_LRT.score(test_x, test_y)
	testingAccuracies.append(score)




for k in kvalues:
	clf_LR = SGDClassifier(learning_rate='optimal', penalty='l2', alpha=math.pow(2,k))
	clf_LR.fit(train_x, train_y)
	score = clf_LR.score(train_x, train_y)
	kTrainingAccuracies.append(score)
	clf_LRT = SGDClassifier(learning_rate='optimal', penalty = 'l2', alpha=math.pow(2,k))
	clf_LRT.fit(test_x, test_y)
	score = clf_LRT.score(test_x, test_y)
	kTestingAccuracies.append(score)

print(trainingAccuracies)
print(testingAccuracies)


plt.plot(learning_rates, trainingAccuracies)
plt.ylabel('training accuracies')
plt.xlabel('learning rates')
plt.show()

plt.plot(learning_rates, testingAccuracies)
plt.ylabel('testing accuracies')
plt.xlabel('learning rates')
plt.show()



plt.plot(kvalues, kTrainingAccuracies)
plt.ylabel('training accuracies')
plt.xlabel('k values')
plt.show()

plt.plot(kvalues, kTestingAccuracies)
plt.ylabel('testing accuracies')
plt.xlabel('k values')
plt.show()
