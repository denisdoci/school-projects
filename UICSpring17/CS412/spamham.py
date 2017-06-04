"""
    Octave and julia doesn't work on my mac for some reason
    so I did the whole program in python. I used scikit learn
    for most all of the bayes and score calculations
"""
import pandas as pd
import numpy as np
from sklearn.model_selection import train_test_split
from sklearn.feature_extraction.text import TfidfTransformer
from sklearn.feature_extraction.text import CountVectorizer
from sklearn.naive_bayes import MultinomialNB
from sklearn import metrics
import matplotlib.pyplot as plt


with open('SMSSpamCollection', 'r') as f:
    dataFull = f.read()
    lines = dataFull.split("\n")
    lines = list(map(lambda line: line.split("\t"), lines))
    del lines[-1]

    targets = map(lambda line: line[0], lines)
    targets = map(lambda target: 1 if target == "spam" else 0, targets)
    data = map(lambda line: line[1], lines)
    df = pd.DataFrame(
    {'target': list(targets),
     'data': list(data)
     })
    df['data'] = df['data'].astype(str)
    train,test = train_test_split(df, test_size = 0.2)
    count_vect = CountVectorizer()
    X_train_counts = count_vect.fit_transform(test.data)
    tfidf_transformer = TfidfTransformer()
    X_train_tfidf = tfidf_transformer.fit_transform(X_train_counts)


    f1Score=[None]
    accuracyScore=[None]
    
    clf = MultinomialNB().fit(X_train_tfidf, test.target)
    docs_test = test.data
    predicted = clf.predict(X_train_tfidf)
    print(metrics.classification_report(test.target, predicted))
    print('Confusion Matrix ')
    print(metrics.confusion_matrix(test.target, predicted))

    
    i1=0.03125
    i2= 0.0625
    i3=0.125
    i4=0.25
    i5=.5
    i6=1
    
    x = [i1,i2,i3,i4,i5,i6]
    for i in x:
        clf = MultinomialNB(alpha=i).fit(X_train_tfidf, test.target)
        docs_test = test.data
        predicted = clf.predict(X_train_tfidf)
        fscore = metrics.f1_score(test.target, predicted)
        accuracy = metrics.accuracy_score(test.target, predicted)
        f1Score.append(fscore)
        accuracyScore.append(accuracy)

    i0=None
    x = [i0,i1,i2,i3,i4,i5,i6]

    plt.plot(x,f1Score)
    plt.ylabel('fscore')
    plt.xlabel('alpha values')
    plt.show()

    plt.plot(x,accuracyScore)
    plt.ylabel('accuracy score')
    plt.xlabel('alpha values')
    plt.show()
